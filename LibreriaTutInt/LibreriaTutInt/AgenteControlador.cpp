#include "AgenteControlador.h"

AgenteControlador::AgenteControlador(Usuario ^ _usuario, String ^ _nombreArchivo, String^ nombre_usuario)
{
	usuario = _usuario;
	direccion = _nombreArchivo;
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

		BaseDeHechos^ baseHechos = conector->obtenerBaseDeHechos();
		BaseDeConocimiento^ baseConocimiento = conector->obtenerBaseDeConocimiento();

		/*
		La regla deberia ser por ejemplo:
			generarProblema(Avanza): nivelActuacion(...), peso(...)
										o
			generarProblema("Habilidad"_"numActividad"): habilidad(...),actividad(...)
		*/

		baseHechos->agregarHechos(gcnew Hecho(reglaNivActuacion->getCabeza()->getRelacion(), gcnew Argumento(reglaNivActuacion->getCabeza()->getArgumento()->getNombreArgumento()), VERDADERO));
		baseHechos->agregarHechos(gcnew Hecho("peso", gcnew Argumento("50"), VERDADERO));

		motorInferencia = gcnew MotorDeInferencia(baseHechos, baseConocimiento);

		Hecho^ resultado = motorInferencia->ejecutar(meta, ENCADENAMIENTO_ADELANTE);

		if (motorInferencia->getTerminoInferencia())
		{
			//No existe un problema
			if (usuario->getProblema() == nullptr)
			{
				String^ habilidad;
				String^ actividad_asignada;
				if (resultado->getArgumento()->getNombreArgumento() == "Avanza")
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
				else if (resultado->getArgumento()->getNombreArgumento() == "Mantiene")
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
				else if (resultado->getArgumento()->getNombreArgumento() == "Retrocede")
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

							delete baseHechos;
							delete baseConocimiento;
							delete motorInferencia;

							return actividad;
						}
					}
				}
				else if (reglaProblema->getCabeza()->getArgumento()->getNombreArgumento() == "Siguiente_Habilidad")
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

							delete baseHechos;
							delete baseConocimiento;
							delete motorInferencia;

							return actividad;
						}
					}
				}
				else
				{
					array<String^>^ separar_componentes = resultado->getArgumento()->getNombreArgumento()->Split('_');

					String^ hab = separar_componentes[0];
					String^ act = separar_componentes[1];

					actividad.push_back(hab);
					actividad.push_back(act);

					percepciones->setHabilidad(hab);
					percepciones->setNumeroActividad(Convert::ToInt32(act));

					conector->borrarHechos();

					delete motorInferencia;
					delete baseConocimiento;
					delete baseHechos;

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

		BaseDeHechos^ baseHechos = conector->obtenerBaseDeHechos();
		BaseDeConocimiento^ baseConocimiento = conector->obtenerBaseDeConocimiento();

		/*
		La regla deberia ser por ejemplo:
			generarProblema(Siguiente_Dificultad): dificultad(...),actividad(..)
										o
			generarProblema("Dificultad"_"numActividad"): dificultad(...),actividad(...)
		*/

		baseHechos->agregarHechos(gcnew Hecho(reglaNivActuacion->getCabeza()->getRelacion(), gcnew Argumento(reglaNivActuacion->getCabeza()->getArgumento()->getNombreArgumento()), VERDADERO));
		baseHechos->agregarHechos(gcnew Hecho("actividad", gcnew Argumento(usuario->getNum_actividad().ToString()), VERDADERO));

		motorInferencia = gcnew MotorDeInferencia(baseHechos, baseConocimiento);

		Hecho^ resultado = motorInferencia->ejecutar(meta, ENCADENAMIENTO_ADELANTE);

		if (motorInferencia->getTerminoInferencia())
		{
			//No existe un problema
			if (usuario->getProblema() == nullptr)
			{
				String^ dificultad;
				String^ actividad_asignada;
				if (resultado->getArgumento()->getNombreArgumento() == "Avanza")
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
				else if (resultado->getArgumento()->getNombreArgumento() == "Mantiene")
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
				else if (resultado->getArgumento()->getNombreArgumento() == "Retrocede")
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

							delete baseHechos;
							delete baseConocimiento;
							delete motorInferencia;

							return actividad;
						}
					}
				}
				else if (reglaProblema->getCabeza()->getArgumento()->getNombreArgumento() == "Siguiente_Dificultad")
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

							delete baseHechos;
							delete baseConocimiento;
							delete motorInferencia;

							return actividad;
						}
					}
				}
				else
				{
					array<String^>^ separar_componentes = resultado->getArgumento()->getNombreArgumento()->Split('_');

					String^ hab = separar_componentes[0];
					String^ act = separar_componentes[1];

					actividad.push_back(hab);
					actividad.push_back(act);

					percepciones->setHabilidad(hab);
					percepciones->setNumeroActividad(Convert::ToInt32(act));

					conector->borrarHechos();

					delete motorInferencia;
					delete baseConocimiento;
					delete baseHechos;

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
		String^ tmpRegla = usuario->getNivel_actuacion();
		Regla^ reglaNivActuacion = conector->transformarString_A_Regla(tmpRegla);

		BaseDeHechos^ base_de_hechos = conector->obtenerBaseDeHechos();
		BaseDeConocimiento^ base_de_conocimiento = conector->obtenerBaseDeConocimiento();

		base_de_hechos->agregarHechos(gcnew Hecho(reglaNivActuacion->getCabeza()->getRelacion(), gcnew Argumento(reglaNivActuacion->getCabeza()->getArgumento()->getNombreArgumento()), VERDADERO));
		base_de_hechos->agregarHechos(gcnew Hecho("dificultad", gcnew Argumento(usuario->getDificultad()), VERDADERO));
		base_de_hechos->agregarHechos(gcnew Hecho("peso", gcnew Argumento("50"), VERDADERO));

		motorInferencia = gcnew MotorDeInferencia(base_de_hechos, base_de_conocimiento);
		Hecho^ resultado = motorInferencia->ejecutar(meta, ENCADENAMIENTO_ADELANTE);

		if (motorInferencia->getTerminoInferencia())
		{
			if (usuario->getProblema() == nullptr) //solo nivel de actuacion por lo que no existe critica
			{
				String^ habilidad;

				if (resultado->getArgumento()->getNombreArgumento() == "Siguiente_Habilidad")
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
								usuario->getDificultad() != resultado->getArgumento()->getNombreArgumento()) //Llego a la ultima actividad o cambio dif
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
							delete base_de_conocimiento;
							delete base_de_hechos;

							return actividad;
						}
						else
						{
							actividad.push_back(habilidad);

							percepciones->setHabilidad(habilidad);

							conector->borrarHechos();

							delete motorInferencia;
							delete base_de_conocimiento;
							delete base_de_hechos;

							return actividad;
						}
					}
				}
				else
				{
					//Busco la actividad sgte
					int actividad_sgte;
					if (usuario->getNum_actividad() == usuario->getTotal_actividades() ||
						usuario->getDificultad() != resultado->getArgumento()->getNombreArgumento()) //Llego a la ultima actividad o cambio dif
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

					actividad.push_back(usuario->getHabilidad());
					actividad.push_back(resultado->getArgumento()->getNombreArgumento());
					actividad.push_back(actividad_sgte.ToString());

					percepciones->setHabilidad(usuario->getHabilidad());
					percepciones->setDificultad(resultado->getArgumento()->getNombreArgumento());
					percepciones->setNumeroActividad(actividad_sgte);

					conector->borrarHechos();

					delete motorInferencia;
					delete base_de_conocimiento;
					delete base_de_hechos;

					return actividad;
				}

			}
			else //Existe problema
			{
				String^ tmpRegla = usuario->getProblema();
				Regla^ reglaProblema = conector->transformarString_A_Regla(tmpRegla);

				if (reglaProblema->getCabeza()->getArgumento()->getNombreArgumento() == "Siguiente_Habilidad_Racha")
				{
					if (usuario->getHistorialNivelActuacion().size() == 0)
					{
						actividad.push_back(usuario->getHabilidad());
						actividad.push_back(usuario->getDificultad());
						actividad.push_back(Convert::ToString(usuario->getTotal_actividades() - 1)); //ultima actividad de la dificultad

						percepciones->setHabilidad(usuario->getHabilidad());
						percepciones->setDificultad(usuario->getDificultad());
						percepciones->setNumeroActividad(usuario->getTotal_actividades() - 1);

						return actividad;
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

							actividad.push_back(habilidad);
							actividad.push_back(usuario->getDificultad());
							actividad.push_back("1");

							percepciones->setHabilidad(habilidad);
							percepciones->setDificultad(usuario->getDificultad());
							percepciones->setNumeroActividad(1);

							conector->borrarHechos();

							delete base_de_conocimiento;
							delete base_de_hechos;
							delete motorInferencia;

							return actividad;
						}
					}
				}
				else if (reglaProblema->getCabeza()->getArgumento()->getNombreArgumento() == "Siguiente_Habilidad")
				{
					if (usuario->getHistorialNivelActuacion().size() == 0)
					{
						//lo avanzo a la dificultad siguiente y conservo la habilidad
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

						actividad.push_back(usuario->getHabilidad());
						actividad.push_back(dificultad);
						actividad.push_back("1");

						percepciones->setHabilidad(usuario->getHabilidad());
						percepciones->setDificultad(dificultad);
						percepciones->setNumeroActividad(1);

						return actividad;

					}
					else
					{
						//Avanzo dificultad y habilidad
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

						actividad.push_back(habilidad);
						actividad.push_back(dificultad);
						actividad.push_back("1");

						percepciones->setHabilidad(habilidad);
						percepciones->setDificultad(dificultad);
						percepciones->setNumeroActividad(1);
					}
					conector->borrarHechos();
					delete motorInferencia;
					return actividad;
				}
			}
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
	evaluador = gcnew Evaluador("Pauta.txt");
	evaluador->revisar_actividad(_habilidad, _dificultad, _actividad, _respuestas);
}
