#include "AgenteControlador.h"

AgenteControlador::~AgenteControlador()
{
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
			generarProblema(Siguiente_Habilidad): habilidad(...),actividad(..)
										o
			generarProblema("Habilidad"_"numActividad"): habilidad(...),actividad(...)
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
				String^ habilidad;

				if (resultado->getArgumento()->getNombreArgumento() == "SgteHabilidad")
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
					}
					//Designo la actividad
					if (habilidad == "Termino")
					{
						actividad.push_back(habilidad);
						percepciones->setHabilidad(habilidad);

						delete motorInferencia;
						delete baseConocimiento;
						delete baseHechos;

						return actividad;
					}
					else
					{
						//La regla de define de la siguiente manera
						// estado("Habilidad"_"numActividad"): habilidad(...),actividad(...)

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

				if (resultado->getArgumento()->getNombreArgumento() == "SgteDificultad")
				{
					if (usuario->getHistorialNivelActuacion().size() == 0)
					{
						dificultad = usuario->getHabilidad();
					}
					else
					{
						if (usuario->getDificultad() == usuario->getDificultades()[usuario->getDificultades().size() - 1])
						{
							dificultad = "Termino";
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
					}
					//Designo la actividad
					if (dificultad == "Termino")
					{
						actividad.push_back(dificultad);
						percepciones->setDificultad(dificultad);

						delete motorInferencia;
						delete baseConocimiento;
						delete baseHechos;

						return actividad;
					}
					else
					{
						//La regla de define de la siguiente manera
						// estado("Dificultad"_"numActividad"): dificultad(...),actividad(...)

						array<String^>^ separar_componentes = resultado->getArgumento()->getNombreArgumento()->Split('_');

						String^ dif = separar_componentes[0];
						String^ act = separar_componentes[1];

						actividad.push_back(dif);
						actividad.push_back(act);

						percepciones->setDificultad(dif);
						percepciones->setNumeroActividad(Convert::ToInt32(act));

						conector->borrarHechos();

						delete motorInferencia;
						delete baseConocimiento;
						delete baseHechos;

						return actividad;
					}
				}
				else
				{
					array<String^>^ separar_componentes = resultado->getArgumento()->getNombreArgumento()->Split('_');

					String^ dif = separar_componentes[0];
					String^ act = separar_componentes[1];

					actividad.push_back(dif);
					actividad.push_back(act);

					percepciones->setDificultad(dif);
					percepciones->setNumeroActividad(Convert::ToInt32(act));

					conector->borrarHechos();

					delete motorInferencia;
					delete baseConocimiento;
					delete baseHechos;

					return actividad;
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
		base_de_hechos->agregarHechos(gcnew Hecho("actividad", gcnew Argumento(Convert::ToString(usuario->getNum_actividad())), VERDADERO));

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
						if (habilidad != "Termino")
						{
							array<String^>^ separar_componentes = resultado->getArgumento()->getNombreArgumento()->Split('_');

							String^ dif = separar_componentes[0];
							String^ act = separar_componentes[1];

							actividad.push_back(habilidad);
							actividad.push_back(dif);
							actividad.push_back(act);

							percepciones->setHabilidad(habilidad);
							percepciones->setDificultad(dif);
							percepciones->setNumeroActividad(Convert::ToInt32(act));

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
					//Aqui deberia aparecer la dificultad y la actividad, aludiendo que esta en la misma habilidad
					array<String^>^ separar_componentes = resultado->getArgumento()->getNombreArgumento()->Split('_');

					String^ dif = separar_componentes[0];
					String^ act = separar_componentes[1];

					actividad.push_back(usuario->getHabilidad());
					actividad.push_back(dif);
					actividad.push_back(act);

					percepciones->setHabilidad(usuario->getHabilidad());
					percepciones->setDificultad(dif);
					percepciones->setNumeroActividad(Convert::ToInt32(act));

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
