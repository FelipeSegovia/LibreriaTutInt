#include "AgenteControlador.h"

AgenteControlador::AgenteControlador(Usuario ^ _usuario, String ^ _nombreArchivo, String^ nombre_usuario, int limit_inf, int limit_sup)
{
	usuario = _usuario;
	direccion = _nombreArchivo;
	this->limite_inf = limit_inf;
	this->limite_sup = limit_sup;
	archivo = gcnew LeerArchivo(direccion);
	archivo->set_nombreArchivo_bcUsuario(nombre_usuario + ".txt");
	archivo->ingresarReglas_BC();
	conector = archivo->obtenerConector();
	percepciones = gcnew Percepciones();
}

AgenteControlador::~AgenteControlador()
{
}

vector<String^> AgenteControlador::determinarActividad()
{
	return vector<String^>();
}

vector<String^> AgenteControlador::determinarActividadConHabilidad(String ^ meta)
{
	vector<String^> actividad;

	//Si el usuario es nuevo
	if (usuario->getNum_actividad() == 0)
	{
		actividad.push_back(usuario->getHabilidades()[0]);
		actividad.push_back("1");

		percepciones->setHabilidad(usuario->getHabilidades()[0]);
		percepciones->setNumeroActividad(1);

		usuario->setNumero_actividad(1);

		return actividad;
	}
	else
	{
		String^ tmpRegla = usuario->getNivel_actuacion();
		Regla^ reglaNivActuacion = conector->transformarString_A_Regla(tmpRegla);

		/*
		La regla deberia ser por ejemplo:
			generarProblema(Avanza): nivelActuacion(...), peso(...)
										o
			generarProblema("Habilidad"_"numActividad"): habilidad(...),actividad(...)
		*/

		conector->agregarHecho(gcnew Hecho(reglaNivActuacion->getCabeza()->getRelacion(), gcnew Argumento(reglaNivActuacion->getCabeza()->getArgumento()->getNombreArgumento()), VERDADERO));
		conector->agregarHecho(gcnew Hecho("peso", gcnew Argumento("50"), VERDADERO));

		String^ resultado = conector->ejecutarMotorInferencia(meta, 1);

		if (motorInferencia->getTerminoInferencia())
		{
			//No existe un problema
			if (usuario->getProblema() == nullptr)
			{
				String^ habilidad;
				String^ actividad_asignada;
				if (resultado == "Avanza")
				{
					//Si esta en la ultima actividad y ultima habilidad
					//Si esta en la ultima actividad pero no en la ultima habilidad
					//Si esta en una actividad cualquiera
					if (usuario->getNum_actividad() == usuario->getTotal_actividades() && usuario->getHabilidad() == usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
					{
						actividad_asignada = "FIN";

						actividad.push_back(actividad_asignada);

						percepciones->setHabilidad(usuario->getHabilidad());
						percepciones->setNumeroActividad(usuario->getNum_actividad());

						return actividad;
					}
					else
					{
						if (usuario->getNum_actividad() == usuario->getTotal_actividades())
						{
							//Busco la habilidad sgte
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (usuario->getHabilidad() == usuario->getHabilidades()[i])
								{
									habilidad = usuario->getHabilidades()[i + 1];
								}
							}

							actividad_asignada = "1";

							actividad.push_back(habilidad);
							actividad.push_back(actividad_asignada);

							percepciones->setHabilidad(habilidad);
							percepciones->setNumeroActividad(Convert::ToInt32(actividad_asignada));

							return actividad;

						}
						else
						{
							actividad_asignada = Convert::ToString(usuario->getNum_actividad() + 1);


							actividad.push_back(usuario->getHabilidad());
							actividad.push_back(actividad_asignada);

							percepciones->setHabilidad(usuario->getHabilidad());
							percepciones->setNumeroActividad(Convert::ToInt32(actividad_asignada));

							return actividad;
						}
					}
				}
				else if (resultado == "Mantiene")
				{
					if (usuario->getTotal_actividades() == 1 || usuario->getNum_actividad() == 1)
					{
						actividad_asignada = "1";
					}
					else
					{
						if (usuario->getNum_actividad() == usuario->getTotal_actividades())
						{
							actividad_asignada = Convert::ToString(usuario->getNum_actividad() - 1);
						}
						else
						{
							actividad_asignada = Convert::ToString(usuario->getNum_actividad() + 1);
						}
					}
					actividad.push_back(usuario->getHabilidad());
					actividad.push_back(actividad_asignada);

					percepciones->setHabilidad(usuario->getHabilidad());
					percepciones->setNumeroActividad(Convert::ToInt32(actividad_asignada));

					return actividad;

				}
				else if (resultado == "Retrocede")
				{
					//Si esta en la primera habilidad 
					if (usuario->getHabilidad() == usuario->getHabilidades()[0])
					{
						if (usuario->getNum_actividad() == 1)
						{
							actividad_asignada = "1";
						}
						else
						{
							actividad_asignada = Convert::ToString(usuario->getNum_actividad() - 1);
						}

						actividad.push_back(usuario->getHabilidades()[0]);
						actividad.push_back(actividad_asignada);

						percepciones->setHabilidad(usuario->getHabilidades()[0]);
						percepciones->setNumeroActividad(Convert::ToInt32(actividad_asignada));

						return actividad;

					}
					else
					{
						//Retrocede una habilidad y se le asigna la ultima actividad de esa habilidad
						if (usuario->getNum_actividad() == 1)
						{
							//Busco la habilidad anterior
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (usuario->getHabilidad() == usuario->getHabilidades()[i])
								{
									habilidad = usuario->getHabilidades()[i - 1];
								}
							}
							//asigno la ultima actividad
							actividad_asignada = Convert::ToString(usuario->getTotal_actividades());
						}

						actividad.push_back(habilidad);
						actividad.push_back(actividad_asignada);

						percepciones->setHabilidad(habilidad);
						percepciones->setNumeroActividad(Convert::ToInt32(actividad_asignada));

						return actividad;
					}
				}
			}
			else //Si existe problema
			{
				String^ tmpRegla = usuario->getProblema();
				Regla^ reglaProblema = conector->transformarString_A_Regla(tmpRegla);

				if (reglaProblema->getCabeza()->getArgumento()->getNombreArgumento() == "Siguiente_Habilidad_Racha")
				{
					if (usuario->getHistorialNivelActuacion().size() == 0)
					{
						actividad.push_back(usuario->getHabilidad());
						actividad.push_back(Convert::ToString(usuario->getNum_actividad() + 1));

						percepciones->setHabilidad(usuario->getHabilidad());
						percepciones->setNumeroActividad(usuario->getNum_actividad() + 1);

						return actividad;
					}
					else
					{
						//Lo avanzo a la actividad 2 de la siguiente habilidad
						if (usuario->getHistorialNivelActuacion().size() == 0)
						{
							habilidad = usuario->getHabilidad();
						}
						else
						{
							String^ habilidad = nullptr;
							if (usuario->getHabilidad() == usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
							{
								habilidad = "FIN";
							}
							else
							{
								//Determino la habilidad siguiente
								int contador_habilidad = 0;
								while (contador_habilidad < usuario->getHabilidades().size() - 2)
								{

									if (usuario->getHabilidad() == usuario->getHabilidades()[contador_habilidad])
									{
										if (usuario->getHabilidades()[contador_habilidad + 1] != nullptr)
										{
											habilidad = usuario->getHabilidades()[contador_habilidad + 1];
										}
									}

									contador_habilidad++;
								}
							}

							actividad.push_back(habilidad);
							actividad.push_back("2");

							percepciones->setHabilidad(habilidad);
							percepciones->setNumeroActividad(2);

							conector->borrarHechos();

							delete motorInferencia;

							return actividad;
						}
					}
				}
				else if (resultado == "Siguiente_Habilidad")
				{
					if (usuario->getHistorialNivelActuacion().size() == 0)
					{
						actividad.push_back(usuario->getHabilidad());
						actividad.push_back(Convert::ToString(usuario->getNum_actividad() + 1));

						percepciones->setHabilidad(usuario->getHabilidad());
						percepciones->setNumeroActividad(usuario->getNum_actividad() + 1);

						return actividad;
					}
					else
					{
						//Lo avanzo a la actividad 2 de la siguiente habilidad
						if (usuario->getHistorialNivelActuacion().size() == 0)
						{
							habilidad = usuario->getHabilidad();
						}
						else
						{
							String^ habilidad = nullptr;
							if (usuario->getHabilidad() == usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
							{
								habilidad = "FIN";
							}
							else
							{
								//Determino la habilidad siguiente
								int contador_habilidad = 0;
								while (contador_habilidad < usuario->getHabilidades().size() - 2)
								{

									if (usuario->getHabilidad() == usuario->getHabilidades()[contador_habilidad])
									{
										if (usuario->getHabilidades()[contador_habilidad + 1] != nullptr)
										{
											habilidad = usuario->getHabilidades()[contador_habilidad + 1];
										}
									}

									contador_habilidad++;
								}
							}

							actividad.push_back(habilidad);
							actividad.push_back("2");

							percepciones->setHabilidad(habilidad);
							percepciones->setNumeroActividad(2);

							conector->borrarHechos();

							delete motorInferencia;

							return actividad;
						}
					}
				}
				else
				{
					array<String^>^ separar_componentes = resultado->Split('_');

					String^ hab = separar_componentes[0];
					String^ act = separar_componentes[1];

					actividad.push_back(hab);
					actividad.push_back(act);

					percepciones->setHabilidad(hab);
					percepciones->setNumeroActividad(Convert::ToInt32(act));

					conector->borrarHechos();

					delete motorInferencia;

					return actividad;
				}
			}
		}
	}

	return actividad;
}

vector<String^> AgenteControlador::determinarActividadConDificultad(String ^ meta)
{
	vector<String^> actividad;

	//Si el usuario es nuevo
	if (usuario->getNum_actividad() == 0)
	{
		actividad.push_back(usuario->getDificultades()[0]);
		actividad.push_back("1");

		percepciones->setHabilidad(usuario->getDificultades()[0]);
		percepciones->setNumeroActividad(1);

		usuario->setNumero_actividad(1);

		return actividad;
	}
	else
	{
		String^ tmpRegla = usuario->getNivel_actuacion();
		Regla^ reglaNivActuacion = conector->transformarString_A_Regla(tmpRegla);

		/*
		La regla deberia ser por ejemplo:
			generarProblema(Siguiente_Dificultad): dificultad(...),actividad(..)
										o
			generarProblema("Dificultad"_"numActividad"): dificultad(...),actividad(...)
		*/

		conector->agregarHecho(gcnew Hecho(reglaNivActuacion->getCabeza()->getRelacion(), gcnew Argumento(reglaNivActuacion->getCabeza()->getArgumento()->getNombreArgumento()), VERDADERO));
		conector->agregarHecho(gcnew Hecho("actividad", gcnew Argumento(usuario->getNum_actividad().ToString()), VERDADERO));


		String^ resultado = conector->ejecutarMotorInferencia(meta, 0);

		if (motorInferencia->getTerminoInferencia())
		{
			//No existe un problema
			if (usuario->getProblema() == nullptr)
			{
				String^ dificultad;
				String^ actividad_asignada;
				if (resultado == "Avanza")
				{
					//Si esta en la ultima actividad y ultima dificultad
					//Si esta en la ultima actividad pero no en la ultima dificultad
					//Si esta en una actividad cualquiera
					if (usuario->getNum_actividad() == usuario->getTotal_actividades() && usuario->getDificultad() == usuario->getDificultades()[usuario->getDificultades().size() - 1])
					{
						actividad_asignada = "FIN";

						actividad.push_back(actividad_asignada);

						percepciones->setDificultad(usuario->getDificultad());
						percepciones->setNumeroActividad(usuario->getNum_actividad());

						return actividad;
					}
					else
					{
						if (usuario->getNum_actividad() == usuario->getTotal_actividades())
						{
							//Busco la dificultad sgte
							for (int i = 0; i < usuario->getDificultades().size(); i++)
							{
								if (usuario->getDificultad() == usuario->getDificultades()[i])
								{
									dificultad = usuario->getDificultades()[i + 1];
								}
							}

							actividad_asignada = "1";

							actividad.push_back(dificultad);
							actividad.push_back(actividad_asignada);

							percepciones->setDificultad(dificultad);
							percepciones->setNumeroActividad(Convert::ToInt32(actividad_asignada));

							return actividad;

						}
						else
						{
							actividad_asignada = Convert::ToString(usuario->getNum_actividad() + 1);


							actividad.push_back(usuario->getDificultad());
							actividad.push_back(actividad_asignada);

							percepciones->setDificultad(usuario->getDificultad());
							percepciones->setNumeroActividad(Convert::ToInt32(actividad_asignada));

							return actividad;
						}
					}
				}
				else if (resultado == "Mantiene")
				{
					if (usuario->getTotal_actividades() == 1 || usuario->getNum_actividad() == 1)
					{
						actividad_asignada = "1";
					}
					else
					{
						if (usuario->getNum_actividad() == usuario->getTotal_actividades())
						{
							actividad_asignada = Convert::ToString(usuario->getNum_actividad() - 1);
						}
						else
						{
							actividad_asignada = Convert::ToString(usuario->getNum_actividad() + 1);
						}
					}
					actividad.push_back(usuario->getDificultad());
					actividad.push_back(actividad_asignada);

					percepciones->setDificultad(usuario->getDificultad());
					percepciones->setNumeroActividad(Convert::ToInt32(actividad_asignada));

					return actividad;

				}
				else if (resultado == "Retrocede")
				{
					//Si esta en la primera dificultad 
					if (usuario->getDificultad() == usuario->getDificultades()[0])
					{
						if (usuario->getNum_actividad() == 1)
						{
							actividad_asignada = "1";
						}
						else
						{
							actividad_asignada = Convert::ToString(usuario->getNum_actividad() - 1);
						}

						actividad.push_back(usuario->getDificultades()[0]);
						actividad.push_back(actividad_asignada);

						percepciones->setDificultad(usuario->getDificultades()[0]);
						percepciones->setNumeroActividad(Convert::ToInt32(actividad_asignada));

						return actividad;

					}
					else
					{
						//Retrocede una dificultad y se le asigna la ultima actividad de esa dificultad
						if (usuario->getNum_actividad() == 1)
						{
							//Busco la dificultad anterior
							for (int i = 0; i < usuario->getDificultades().size(); i++)
							{
								if (usuario->getDificultad() == usuario->getDificultades()[i])
								{
									dificultad = usuario->getDificultades()[i - 1];
								}
							}
							//asigno la ultima actividad
							actividad_asignada = Convert::ToString(usuario->getTotal_actividades());
						}

						actividad.push_back(dificultad);
						actividad.push_back(actividad_asignada);

						percepciones->setDificultad(dificultad);
						percepciones->setNumeroActividad(Convert::ToInt32(actividad_asignada));

						return actividad;
					}
				}
			}
			else //Si existe problema
			{
				String^ tmpRegla = usuario->getProblema();
				Regla^ reglaProblema = conector->transformarString_A_Regla(tmpRegla);

				if (reglaProblema->getCabeza()->getArgumento()->getNombreArgumento() == "Siguiente_Dificultad_Racha")
				{
					if (usuario->getHistorialNivelActuacion().size() == 0)
					{
						actividad.push_back(usuario->getDificultad());
						actividad.push_back(Convert::ToString(usuario->getNum_actividad() + 1));

						percepciones->setDificultad(usuario->getDificultad());
						percepciones->setNumeroActividad(usuario->getNum_actividad() + 1);

						return actividad;
					}
					else
					{
						//Lo avanzo a la actividad 2 de la siguiente dificultad
						if (usuario->getHistorialNivelActuacion().size() == 0)
						{
							dificultad = usuario->getDificultad();
						}
						else
						{
							String^ dificultad = nullptr;
							if (usuario->getDificultad() == usuario->getDificultades()[usuario->getDificultades().size() - 1])
							{
								dificultad = "FIN";
							}
							else
							{
								//Determino la dificultad siguiente
								int contador_dificultad = 0;
								while (contador_dificultad < usuario->getDificultades().size() - 2)
								{

									if (usuario->getDificultad() == usuario->getDificultades()[contador_dificultad])
									{
										if (usuario->getDificultades()[contador_dificultad + 1] != nullptr)
										{
											dificultad = usuario->getDificultades()[contador_dificultad + 1];
										}
									}

									contador_dificultad++;
								}
							}

							actividad.push_back(dificultad);
							actividad.push_back("2");

							percepciones->setDificultad(dificultad);
							percepciones->setNumeroActividad(2);

							conector->borrarHechos();

							delete motorInferencia;

							return actividad;
						}
					}
				}
				else if (resultado == "Siguiente_Dificultad")
				{
					if (usuario->getHistorialNivelActuacion().size() == 0)
					{
						actividad.push_back(usuario->getDificultad());
						actividad.push_back(Convert::ToString(usuario->getNum_actividad() + 1));

						percepciones->setDificultad(usuario->getDificultad());
						percepciones->setNumeroActividad(usuario->getNum_actividad() + 1);

						return actividad;
					}
					else
					{
						//Lo avanzo a la actividad 2 de la siguiente dificultad
						if (usuario->getHistorialNivelActuacion().size() == 0)
						{
							dificultad = usuario->getHabilidad();
						}
						else
						{
							String^ dificultad = nullptr;
							if (usuario->getDificultad() == usuario->getDificultades()[usuario->getDificultades().size() - 1])
							{
								dificultad = "FIN";
							}
							else
							{
								//Determino la dificultad siguiente
								int contador_dificultad = 0;
								while (contador_dificultad < usuario->getDificultades().size() - 2)
								{

									if (usuario->getDificultad() == usuario->getDificultades()[contador_dificultad])
									{
										if (usuario->getDificultades()[contador_dificultad + 1] != nullptr)
										{
											dificultad = usuario->getHabilidades()[contador_dificultad + 1];
										}
									}

									contador_dificultad++;
								}
							}

							actividad.push_back(dificultad);
							actividad.push_back("2");

							percepciones->setDificultad(dificultad);
							percepciones->setNumeroActividad(2);

							conector->borrarHechos();

							delete motorInferencia;

							return actividad;
						}
					}
				}
				else
				{
					array<String^>^ separar_componentes = resultado->Split('_');

					String^ hab = separar_componentes[0];
					String^ act = separar_componentes[1];

					actividad.push_back(hab);
					actividad.push_back(act);

					percepciones->setHabilidad(hab);
					percepciones->setNumeroActividad(Convert::ToInt32(act));

					conector->borrarHechos();

					delete motorInferencia;

					return actividad;
				}
			}
		}
	}

	return actividad;
}

vector<String^> AgenteControlador::determinarActividadDificultadHabilidad(String ^ meta)
{
	vector<String^> actividad;

	//Si el usuario es nuevo
	if (usuario->getNum_actividad() == 0)
	{
		String^ hab = this->usuario->getHabilidades()[0];
		actividad.push_back(usuario->getHabilidades()[0]);
		actividad.push_back(usuario->getDificultades()[0]);
		actividad.push_back("1");

		percepciones->setHabilidad(usuario->getHabilidades()[0]);
		percepciones->setDificultad(usuario->getDificultades()[0]);
		percepciones->setNumeroActividad(1);
	}
	else
	{
		Regla^ reglaNivActuacion = usuario->getReglaNivActuacion();

		conector->agregarHecho(gcnew Hecho(reglaNivActuacion->getCabeza()->getRelacion(), gcnew Argumento(reglaNivActuacion->getCabeza()->getArgumento()->getNombreArgumento()), VERDADERO));
		conector->agregarHecho(gcnew Hecho("dificultad", gcnew Argumento(usuario->getDificultad()), VERDADERO));

		String^ resultado = conector->ejecutarMotorInferencia(meta, 1);

		if (percepciones->getProblemaGenerado() == nullptr) //solo nivel de actuacion por lo que no existe critica
		{
			String^ habilidad;

			if (resultado == "Siguiente_Habilidad")
			{
				if (usuario->getHistorialNivelActuacion().size() == 0)
				{
					habilidad = usuario->getHabilidad();
				}
				else
				{
					if (usuario->getHabilidad() == usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
					{
						habilidad = "Termino";
					}
					else
					{
						//Determino la habilidad siguiente
						int contador_habilidad = 0;
						while (contador_habilidad < usuario->getHabilidades().size())
						{

							if (usuario->getHabilidad() == usuario->getHabilidades()[contador_habilidad])
							{
								if (usuario->getHabilidades()[contador_habilidad + 1] != nullptr)
								{
									habilidad = usuario->getHabilidades()[contador_habilidad + 1];
									break;
								}
							}

							contador_habilidad++;
						}
					}
					if (habilidad != "Termino")
					{
						int actividad_sgte;
						if (usuario->getNum_actividad() == usuario->getTotal_actividades() ||
							usuario->getDificultad() != resultado) //Llego a la ultima actividad o cambio dif
						{
							actividad_sgte = 1;
						}
						else
						{
							for (int i = 1; i < usuario->getTotal_actividades(); i++)
							{
								if (usuario->getNum_actividad() == i)
								{
									actividad_sgte = i + 1;
									break;
								}
							}
						}

						actividad.push_back(habilidad);
						actividad.push_back(usuario->getDificultades()[0]);
						actividad.push_back(actividad_sgte.ToString());

						percepciones->setHabilidad(habilidad);
						percepciones->setDificultad(usuario->getDificultades()[0]);
						percepciones->setNumeroActividad(actividad_sgte);

						conector->borrarHechos();

						delete motorInferencia;

						return actividad;
					}
					else
					{
						actividad.push_back(habilidad);

						percepciones->setHabilidad(habilidad);

						conector->borrarHechos();

						delete motorInferencia;

						return actividad;
					}
				}
			}
			else if (usuario->getNivel_actuacion() == "Alto") //Avanza dificultad pero sigue en la misma habilidad
			{
				String^ dificultad_sgte = usuario->getDificultad();
				String^ habilidad_sgte = usuario->getHabilidad();
				int actividad_sgte = usuario->getNum_actividad();

				if ((usuario->getNum_actividad() == usuario->getTotal_actividades()) && (usuario->getHizo_actividad() == true))
				{
					//avanzo una dificultad
					for (int i = 0; i < usuario->getDificultades().size(); i++)
					{
						if (usuario->getDificultad() == usuario->getDificultades()[i])
						{
							dificultad_sgte = usuario->getDificultades()[i + 1];
							break;
						}
					}

					actividad_sgte = 1;

				}
				else
				{
					if (usuario->getHizo_actividad() == true)
					{
						actividad_sgte++;
					}
				}

				usuario->setDificultad(dificultad_sgte);
				usuario->setNumero_actividad(actividad_sgte);
				usuario->setHizo_actividad(false);

				percepciones->setHabilidad(usuario->getHabilidad());
				percepciones->setDificultad(dificultad_sgte);
				percepciones->setNumeroActividad(actividad_sgte);

				actividad.push_back(usuario->getHabilidad());
				actividad.push_back(dificultad_sgte);
				actividad.push_back(actividad_sgte.ToString());

				conector->borrarHechos();

				delete motorInferencia;

				return actividad;
			}
			else if (usuario->getNivel_actuacion() == "Medio") //si mantiene su nivel de actuacion, repite la actividad o avanza a la siguiente actividad
			{

				int actividad_sgte = usuario->getNum_actividad();
				if ((usuario->getNum_actividad() != usuario->getTotal_actividades()) && (usuario->getHizo_actividad() == true))
				{
					actividad_sgte += 1;
				}

				usuario->setNumero_actividad(actividad_sgte);
				usuario->setHizo_actividad(false);

				percepciones->setHabilidad(usuario->getHabilidad());
				percepciones->setDificultad(usuario->getDificultad());
				percepciones->setNumeroActividad(actividad_sgte);

				actividad.push_back(usuario->getHabilidad());
				actividad.push_back(usuario->getDificultad());
				actividad.push_back(actividad_sgte.ToString());

				conector->borrarHechos();

				delete motorInferencia;

				return actividad;
			}
			else if (usuario->getNivel_actuacion() == "Bajo")
			{
				int actividad_sgte = usuario->getNum_actividad();
				String^ dificultad_sgte = usuario->getDificultad();
				String^ habilidad_stge = usuario->getHabilidad();

				if ((usuario->getNum_actividad() == 1) && (usuario->getHizo_actividad() == true))
				{
					if (usuario->getDificultad() == usuario->getDificultades()[0]) {
						if (usuario->getHabilidad() != usuario->getHabilidades()[0])
						{
							dificultad_sgte = usuario->getDificultades()[usuario->getDificultades().size()];
							actividad_sgte = usuario->getTotal_actividades();
						}
					}
					else
					{
						//Baja una dificultad
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (usuario->getDificultad() == usuario->getDificultades()[i])
							{
								dificultad_sgte = usuario->getDificultades()[i - 1];
								break;
							}
						}
						//se pone en la ultima actividad de esa dificultad
						actividad_sgte = usuario->getTotal_actividades();
					}
				}
				else //retrocede una actividad
				{
					actividad_sgte = usuario->getNum_actividad() - 1;
				}

				usuario->setNumero_actividad(actividad_sgte);
				usuario->setHabilidad(habilidad_stge);
				usuario->setDificultad(dificultad_sgte);
				usuario->setHizo_actividad(false);

				percepciones->setHabilidad(habilidad_stge);
				percepciones->setDificultad(dificultad_sgte);
				percepciones->setNumeroActividad(actividad_sgte);

				actividad.push_back(habilidad_stge);
				actividad.push_back(dificultad_sgte);
				actividad.push_back(actividad_sgte.ToString());

				conector->borrarHechos();

				delete motorInferencia;

				return actividad;
			}
		}
		else //Existe problema
		{
			String^ tmpRegla = usuario->getProblema();

			String^ actividad_asignada = usuario->getNum_actividad().ToString();
			String^ dificultad_asignada = usuario->getDificultad();
			String^ habilidad_asignada = usuario->getHabilidad();

			if (tmpRegla == "Avanza_Uno")
			{

				//si esta en la ultima actividad
				if (Convert::ToInt32(actividad_asignada) == usuario->getNum_actividad())
				{
					//si esta en la ultima dificultad
					if (dificultad_asignada == usuario->getDificultades()[usuario->getDificultades().size() - 1])
					{
						//si esta en la ultima habilidad
						if (habilidad_asignada == usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
						{
							habilidad_asignada = "FIN";
						}
						else
						{
							//busco la habilidad sgte
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (habilidad_asignada == usuario->getHabilidades()[i])
								{
									habilidad_asignada = usuario->getHabilidades()[i + 1];
									break;
								}
							}
							dificultad_asignada = usuario->getDificultades()[0];
							actividad_asignada = "1";
						}
					}
					else
					{
						//busco la dificultad sgte
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (dificultad_asignada == usuario->getDificultades()[i])
							{
								dificultad_asignada = usuario->getDificultades()[i + 1];
								break;
							}
						}
						actividad_asignada = "1";
					}
				}
				else
				{
					actividad_asignada = (Convert::ToInt32(actividad_asignada) + 1).ToString();
				}
			}
			else if (tmpRegla == "Avanza_Dos")
			{
				if ((Convert::ToInt32(actividad_asignada) + 2) <= usuario->getTotal_actividades())
				{
					actividad_asignada = (Convert::ToInt32(actividad_asignada) + 2).ToString();
				}
				else if ((usuario->getTotal_actividades() - (Convert::ToInt32(actividad_asignada) + 2)) == -1)
				{
					//si esta en la ultima dificultad
					if (dificultad_asignada == usuario->getDificultades()[usuario->getDificultades().size() - 1])
					{
						//si esta en la ultima habilidad
						if (habilidad_asignada == usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
						{
							habilidad_asignada = "FIN";
						}
						else
						{
							//busco la habilidad sgte
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (habilidad_asignada == usuario->getHabilidades()[i])
								{
									habilidad_asignada = usuario->getHabilidades()[i + 1];
									break;
								}
							}
							dificultad_asignada = usuario->getDificultades()[0];
							actividad_asignada = "1";
						}
					}
					else
					{
						//busco la dificultad sgte
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (dificultad_asignada == usuario->getDificultades()[i])
							{
								dificultad_asignada = usuario->getDificultades()[i + 1];
								break;
							}
						}
						actividad_asignada = "1";
					}
				}
				else if (((usuario->getTotal_actividades() - (Convert::ToInt32(actividad_asignada) + 2)) == -2))
				{
					//si esta en la ultima dificultad
					if (dificultad_asignada == usuario->getDificultades()[usuario->getDificultades().size() - 1])
					{
						//si esta en la ultima habilidad
						if (habilidad_asignada == usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
						{
							habilidad_asignada = "FIN";
						}
						else
						{
							//busco la habilidad sgte
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (habilidad_asignada == usuario->getHabilidades()[i])
								{
									habilidad_asignada = usuario->getHabilidades()[i + 1];
									break;
								}
							}
							dificultad_asignada = usuario->getDificultades()[0];
							actividad_asignada = "2";
						}
					}
					else
					{
						//busco la dificultad sgte
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (dificultad_asignada == usuario->getDificultades()[i])
							{
								dificultad_asignada = usuario->getDificultades()[i + 1];
								break;
							}
						}
						actividad_asignada = "2";
					}
				}
			}
			else if (tmpRegla == "Avanza_Tres")
			{
				if ((Convert::ToInt32(actividad_asignada) + 3) <= usuario->getTotal_actividades())
				{
					actividad_asignada = (Convert::ToInt32(actividad_asignada) + 3).ToString();
				}
				else if ((usuario->getTotal_actividades() - (Convert::ToInt32(actividad_asignada) + 3)) == -1)
				{
					//si esta en la ultima dificultad
					if (dificultad_asignada == usuario->getDificultades()[usuario->getDificultades().size() - 1])
					{
						//si esta en la ultima habilidad
						if (habilidad_asignada == usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
						{
							habilidad_asignada = "FIN";
						}
						else
						{
							//busco la habilidad sgte
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (habilidad_asignada == usuario->getHabilidades()[i])
								{
									habilidad_asignada = usuario->getHabilidades()[i + 1];
									break;
								}
							}
							dificultad_asignada = usuario->getDificultades()[0];
							actividad_asignada = "1";
						}
					}
					else
					{
						//busco la dificultad sgte
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (dificultad_asignada == usuario->getDificultades()[i])
							{
								dificultad_asignada = usuario->getDificultades()[i + 1];
								break;
							}
						}
						actividad_asignada = "1";
					}
				}
				else if ((usuario->getTotal_actividades() - (Convert::ToInt32(actividad_asignada) + 3)) == -2)
				{
					//si esta en la ultima dificultad
					if (dificultad_asignada == usuario->getDificultades()[usuario->getDificultades().size() - 1])
					{
						//si esta en la ultima habilidad
						if (habilidad_asignada == usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
						{
							habilidad_asignada = "FIN";
						}
						else
						{
							//busco la habilidad sgte
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (habilidad_asignada == usuario->getHabilidades()[i])
								{
									habilidad_asignada = usuario->getHabilidades()[i + 1];
									break;
								}
							}
							dificultad_asignada = usuario->getDificultades()[0];
							actividad_asignada = "2";
						}
					}
					else
					{
						//busco la dificultad sgte
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (dificultad_asignada == usuario->getDificultades()[i])
							{
								dificultad_asignada = usuario->getDificultades()[i + 1];
								break;
							}
						}
						actividad_asignada = "2";
					}
				}
				else if ((usuario->getTotal_actividades() - (Convert::ToInt32(actividad_asignada) + 3)) == -3)
				{
					//si esta en la ultima dificultad
					if (dificultad_asignada == usuario->getDificultades()[usuario->getDificultades().size() - 1])
					{
						//si esta en la ultima habilidad
						if (habilidad_asignada == usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
						{
							habilidad_asignada = "FIN";
						}
						else
						{
							//busco la habilidad sgte
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (habilidad_asignada == usuario->getHabilidades()[i])
								{
									habilidad_asignada = usuario->getHabilidades()[i + 1];
									break;
								}
							}
							dificultad_asignada = usuario->getDificultades()[0];
							actividad_asignada = "3";
						}
					}
					else
					{
						//busco la dificultad sgte
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (dificultad_asignada == usuario->getDificultades()[i])
							{
								dificultad_asignada = usuario->getDificultades()[i + 1];
								break;
							}
						}
						actividad_asignada = "3";
					}
				}
			}
			else if (tmpRegla == "Retrocede_Uno")
			{
				if (actividad_asignada == "1")
				{
					//se encuentra en la primera dificultad
					if (dificultad_asignada == usuario->getDificultades()[0])
					{
						//si se encuentra en la primera habilidad
						if (habilidad_asignada != usuario->getHabilidades()[0])
						{
							//disminuye la habilidad
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (habilidad_asignada == usuario->getHabilidades()[i])
								{
									habilidad_asignada = usuario->getHabilidades()[i - 1];
									break;
								}
							}
							dificultad_asignada = usuario->getDificultades()[usuario->getHabilidades().size() - 1];
							actividad_asignada = usuario->getTotal_actividades().ToString();
						}
					}
					else
					{
						//disminuye una dificultad
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (dificultad_asignada == usuario->getDificultades()[i])
							{
								dificultad_asignada = usuario->getDificultades()[i - 1];
								break;
							}
						}
						actividad_asignada = usuario->getTotal_actividades().ToString();
					}
				}
				else
				{
					actividad_asignada = (Convert::ToInt32(actividad_asignada) - 1).ToString();
				}
			}
			else if (tmpRegla == "Retrocede_Dos")
			{
				if ((Convert::ToInt32(actividad_asignada) - 2) > 0)
				{
					actividad_asignada = (Convert::ToInt32(actividad_asignada) - 2).ToString();
				}
				else if ((Convert::ToInt32(actividad_asignada) - 2) == 0)
				{
					//si esta en la primera dificultad
					if (dificultad_asignada == usuario->getDificultades()[0])
					{
						//si esta en la primera habilidad
						if (habilidad_asignada != usuario->getHabilidades()[0])
						{
							//retrocedo una habilidad
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (habilidad_asignada == usuario->getHabilidades()[i])
								{
									habilidad_asignada = usuario->getHabilidades()[i - 1];
									break;
								}
							}
							dificultad_asignada = usuario->getDificultades()[usuario->getDificultades().size() - 1];
							actividad_asignada = usuario->getTotal_actividades().ToString();
						}
					}
					else
					{
						//busco la dificultad sgte
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (dificultad_asignada == usuario->getDificultades()[i])
							{
								dificultad_asignada = usuario->getDificultades()[i - 1];
								break;
							}
						}
						actividad_asignada = usuario->getTotal_actividades().ToString();
					}
				}
				else if ((Convert::ToInt32(actividad_asignada) - 2) < 0)
				{
					//si esta en la primera dificultad
					if (dificultad_asignada == usuario->getDificultades()[0])
					{
						//si esta en la primera habilidad
						if (habilidad_asignada != usuario->getHabilidades()[0])
						{
							//retrocedo una habilidad
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (habilidad_asignada == usuario->getHabilidades()[i])
								{
									habilidad_asignada = usuario->getHabilidades()[i - 1];
									break;
								}
							}
							dificultad_asignada = usuario->getDificultades()[usuario->getDificultades().size() - 1];
							actividad_asignada = (usuario->getTotal_actividades() - 1).ToString();
						}
					}
					else
					{
						//busco la dificultad sgte
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (dificultad_asignada == usuario->getDificultades()[i])
							{
								dificultad_asignada = usuario->getDificultades()[i - 1];
								break;
							}
						}
						actividad_asignada = (usuario->getTotal_actividades() - 1).ToString();
					}
				}
			}
			if (tmpRegla == "Retrocede_Tres")
			{
				if ((Convert::ToInt32(actividad_asignada) - 3) > 0)
				{
					actividad_asignada = (Convert::ToInt32(actividad_asignada) - 3).ToString();
				}
				else if ((Convert::ToInt32(actividad_asignada) - 3) == 0)
				{
					//si esta en la primera dificultad
					if (dificultad_asignada == usuario->getDificultades()[0])
					{
						//si esta en la primera habilidad
						if (habilidad_asignada != usuario->getHabilidades()[0])
						{
							//retrocedo una habilidad
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (habilidad_asignada == usuario->getHabilidades()[i])
								{
									habilidad_asignada = usuario->getHabilidades()[i - 1];
									break;
								}
							}
							dificultad_asignada = usuario->getDificultades()[usuario->getDificultades().size() - 1];
							actividad_asignada = usuario->getTotal_actividades().ToString();
						}
					}
					else
					{
						//busco la dificultad sgte
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (dificultad_asignada == usuario->getDificultades()[i])
							{
								dificultad_asignada = usuario->getDificultades()[i - 1];
								break;
							}
						}
						actividad_asignada = usuario->getTotal_actividades().ToString();
					}
				}
				else if ((Convert::ToInt32(actividad_asignada) - 3) < 0)
				{
					//si esta en la primera dificultad
					if (dificultad_asignada == usuario->getDificultades()[0])
					{
						//si esta en la primera habilidad
						if (habilidad_asignada != usuario->getHabilidades()[0])
						{
							//retrocedo una habilidad
							for (int i = 0; i < usuario->getHabilidades().size(); i++)
							{
								if (habilidad_asignada == usuario->getHabilidades()[i])
								{
									habilidad_asignada = usuario->getHabilidades()[i - 1];
									break;
								}
							}
							dificultad_asignada = usuario->getDificultades()[usuario->getDificultades().size() - 1];
							actividad_asignada = (usuario->getTotal_actividades() - 3).ToString();
						}
					}
					else
					{
						//busco la dificultad sgte
						for (int i = 0; i < usuario->getDificultades().size(); i++)
						{
							if (dificultad_asignada == usuario->getDificultades()[i])
							{
								dificultad_asignada = usuario->getDificultades()[i - 1];
								break;
							}
						}
						actividad_asignada = (usuario->getTotal_actividades() - 3).ToString();
					}
				}
			}

			usuario->setNumero_actividad(Convert::ToInt32(actividad_asignada));
			usuario->setHabilidad(habilidad_asignada);
			usuario->setDificultad(dificultad_asignada);
			usuario->setHizo_actividad(false);

			percepciones->setHabilidad(habilidad_asignada);
			percepciones->setDificultad(dificultad_asignada);
			percepciones->setNumeroActividad(Convert::ToInt32(actividad_asignada));

			actividad.push_back(habilidad_asignada);
			actividad.push_back(dificultad_asignada);
			actividad.push_back(actividad_asignada);

			conector->borrarHechos();

			delete motorInferencia;

		}
	}

	return actividad;
}

String^ AgenteControlador::obtenerNivelLogro()
{
	return evaluador->getNivel_de_logro();
}

void AgenteControlador::evaluarActividad(String^ _habilidad, String^ _dificultad, int _actividad, vector<String^> _respuestas)
{
	evaluador = gcnew Evaluador("Pauta.txt", limite_inf, limite_sup);
	evaluador->revisar_actividad(_habilidad, _dificultad, _actividad, _respuestas);
	percepciones->setNivelDeLogro(evaluador->getNivel_de_logro());
}

void AgenteControlador::determinarNivelDeActuacion()
{
	if (this->factores != nullptr)
	{
		aprendizaje = gcnew AgenteAprendizaje(this->conector, this->percepciones, this->factores);
	}
	else
	{
		aprendizaje = gcnew AgenteAprendizaje(this->conector, this->percepciones);
	}
	aprendizaje->determinarElementoActuacion();
	if (percepciones->getProblemaGenerado() == nullptr)
	{
		actuacion = percepciones->getNivelDeActuacion();
		usuario->setReglaNivActuacion(aprendizaje->getActuacionObtenida());
	}
	else
	{
		actuacion = percepciones->getNivelDeActuacion();
		problema = percepciones->getProblemaGenerado()->getCabeza()->getArgumento()->getNombreArgumento();
		usuario->setProblema(problema);
	}
}

Usuario ^ AgenteControlador::getUsuario()
{
	return this->usuario;
}

String ^ AgenteControlador::getProblema()
{
	return this->problema;
}

Percepciones^ AgenteControlador::getPercepciones()
{
	return this->percepciones;
}

ConjuntoFactores ^ AgenteControlador::getFactores()
{
	return this->factores;
}

void AgenteControlador::setFactores(ConjuntoFactores ^ _factores)
{
	this->factores = _factores;
}

void AgenteControlador::setAprendizaje(AgenteAprendizaje ^ _aprendizaje)
{
	this->aprendizaje = _aprendizaje;
}

AgenteAprendizaje ^ AgenteControlador::getAprendizaje()
{
	return this->aprendizaje;
}