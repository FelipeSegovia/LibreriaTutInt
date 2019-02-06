#include "AgenteControladorAbs.h"


AgenteControladorAbs::AgenteControladorAbs(Usuario ^ _usuario,String^ _nombreArchivo)
{
	usuario = _usuario;
	direccion = _nombreArchivo;
	archivo = gcnew LeerArchivo(direccion);
	archivo->set_nombreArchivo_bcUsuario("Pipe.txt");
	archivo->ingresarReglas_BC();
	conector = archivo->obtenerConector(); 
	percepciones = gcnew Percepciones();
	
}

AgenteControladorAbs::~AgenteControladorAbs()
{
	delete usuario;
	delete conector;
}

vector<String^> AgenteControladorAbs::determinarActividadConHabilidad(String ^ meta)
{
	vector<String^> actividad;

	//Usuario nuevo
	if ((usuario->getNum_actividad() == 0))
	{
		actividad.push_back(usuario->getHabilidades()[0]);
		actividad.push_back("1");

		percepciones->setHabilidad(usuario->getHabilidades()[0]);
		percepciones->setNumeroActividad(1);

		return actividad;
	}
	else
	{
		String^ tmpRegla = usuario->getNivel_actuacion();
		Regla^ reglaNivActuacion = conector->transformarString_A_Regla(tmpRegla);

		BaseDeHechos^ baseHechos = conector->obtenerBaseDeHechos();
		BaseDeConocimiento^ baseConocimiento = conector->obtenerBaseDeConocimiento();

		baseHechos->agregarHechos(gcnew Hecho(reglaNivActuacion->getCabeza()->getRelacion(), gcnew Argumento(reglaNivActuacion->getCabeza()->getArgumento()->getNombreArgumento()),VERDADERO));
		baseHechos->agregarHechos(gcnew Hecho("actividad",gcnew Argumento(usuario->getNum_actividad().ToString()),VERDADERO));


		motorInferencia = gcnew MotorDeInferencia(baseHechos, baseConocimiento);
		
		Hecho^ resultado = motorInferencia->ejecutar(meta, ENCADENAMIENTO_ADELANTE);

		if (motorInferencia->getTerminoInferencia())
		{
			if (usuario->getProblema() == nullptr)
			{
				String^ habilidad;
				if (resultado->getArgumento()->getNombreArgumento() == "Siguiente_Habilidad")
				{
					for (int i = 0; i < usuario->getHabilidades().size();i++)
					{
						if (usuario->getHabilidad() != usuario->getHabilidades()[usuario->getHabilidades().size()-1])
						{
							if (usuario->getHabilidad() == usuario->getHabilidades()[i])
							{
								habilidad = usuario->getHabilidades()[i + 1];
								break;
							}
						}
						else
						{
							habilidad = "Termino";
						}
						
					}

					if (habilidad != "Termino")
					{
						bool encontrada = false;
						for (int i = 0; i < usuario->getTotal_actividades(); i++)
						{
							if (usuario->getNum_actividad() == i)
							{
								actividad.push_back(habilidad);
								actividad.push_back(Convert::ToString(i+1));

								percepciones->setHabilidad(habilidad);
								percepciones->setNumeroActividad(i+1);

								encontrada = true;
							}
						}
						if (!encontrada)
						{
							actividad.push_back(habilidad);
							actividad.push_back("1");

							percepciones->setHabilidad(habilidad);
							percepciones->setNumeroActividad(1);
						}
					}
				}
			}
			else
			{

				String^ tmpRegla = usuario->getProblema();
				Regla^ reglaProblema = conector->transformarString_A_Regla(tmpRegla);

				if (reglaProblema->getCabeza()->getArgumento()->getNombreArgumento() == "Siguiente_Habilidad_Racha")
				{
					if (usuario->getHistorialNivelActuacion().size() == 0)
					{
						if (usuario->getNum_actividad() < usuario->getTotal_actividades())
						{
							actividad.push_back(usuario->getHabilidad());
							actividad.push_back(Convert::ToString(usuario->getNum_actividad() + 1));

							percepciones->setHabilidad(usuario->getHabilidad());
							percepciones->setNumeroActividad(usuario->getNum_actividad() + 1);
						}
					}
					else
					{
						//Busco la habilidad sgte 
						if (usuario->getHabilidad() == usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
						{
							if (usuario->getNum_actividad() == usuario->getTotal_actividades())
							{
								actividad.push_back("FIN");
							}
							else
							{
								actividad.push_back(usuario->getHabilidad());
								actividad.push_back(Convert::ToString(usuario->getNum_actividad() + 1));
								
								percepciones->setHabilidad(usuario->getHabilidad());
								percepciones->setNumeroActividad(usuario->getNum_actividad() + 1);

							}
						}
						else
						{
							for (int x = 0; x < usuario->getHabilidades().size(); x++)
							{
								if (usuario->getHabilidad() == usuario->getHabilidades()[x])
								{
									actividad.push_back(usuario->getHabilidades()[x + 1]);
									actividad.push_back(Convert::ToString(usuario->getNum_actividad() + 1));

									percepciones->setHabilidad(usuario->getHabilidades()[x + 1]);
									percepciones->setNumeroActividad(usuario->getNum_actividad() + 1);
								}
							}
						}
					}
				}
			}
		}
	}
	return actividad;
}

vector<String^> AgenteControladorAbs::determinarActividadConDificultad(String ^ meta)
{
	vector<String^> actividad;

	//Usuario nuevo
	if (usuario->getNum_actividad() == 0)
	{
		actividad.push_back(usuario->getDificultades()[0]);
		actividad.push_back("1");

		percepciones->setHabilidad(usuario->getDificultades()[0]);
		percepciones->setNumeroActividad(1);
	}
	else
	{
		String^ tmpRegla = usuario->getNivel_actuacion();
		Regla^ reglaNivActuacion = conector->transformarString_A_Regla(tmpRegla);

		BaseDeHechos^ baseHechos = conector->obtenerBaseDeHechos();
		BaseDeConocimiento^ baseConocimiento = conector->obtenerBaseDeConocimiento();

		baseHechos->agregarHechos(gcnew Hecho(reglaNivActuacion->getCabeza()->getRelacion(), gcnew Argumento(reglaNivActuacion->getCabeza()->getArgumento()->getNombreArgumento()),VERDADERO));
		baseHechos->agregarHechos(gcnew Hecho("actividad",gcnew Argumento(usuario->getNum_actividad().ToString()),VERDADERO));


		motorInferencia = gcnew MotorDeInferencia(baseHechos, baseConocimiento);
		
		Hecho^ resultado = motorInferencia->ejecutar(meta, ENCADENAMIENTO_ADELANTE);

		if (motorInferencia->getTerminoInferencia())
		{
			if (usuario->getProblema() == nullptr)
			{
				String^ dificultad;
				if (resultado->getArgumento()->getNombreArgumento() == "Siguiente_Dificultad")
				{
					for (int i = 0; i < usuario->getHabilidades().size(); i++)
					{
						if (usuario->getDificultad() != usuario->getDificultades()[usuario->getHabilidades().size() - 1])
						{
							if (usuario->getDificultad() == usuario->getDificultades()[i])
							{
								habilidad = usuario->getDificultades()[i + 1];
								break;
							}
						}
						else
						{
							dificultad = "Termino";
						}

					}

					if (dificultad != "Termino")
					{
						bool encontrada = false;
						for (int i = 0; i < usuario->getTotal_actividades(); i++)
						{
							if (usuario->getNum_actividad() == i)
							{
								actividad.push_back(dificultad);
								actividad.push_back(Convert::ToString(i + 1));

								percepciones->setHabilidad(dificultad);
								percepciones->setNumeroActividad(i + 1);

								encontrada = true;
							}
						}
						if (!encontrada)
						{
							actividad.push_back(dificultad);
							actividad.push_back("1");

							percepciones->setHabilidad(dificultad);
							percepciones->setNumeroActividad(1);
						}
					}
				}
			}
			else
			{

				String^ tmpRegla = usuario->getProblema();
				Regla^ reglaProblema = conector->transformarString_A_Regla(tmpRegla);

				if (reglaProblema->getCabeza()->getArgumento()->getNombreArgumento() == "Siguiente_Dificultad_Racha")
				{
					if (usuario->getHistorialNivelActuacion().size() == 0)
					{
						if (usuario->getNum_actividad() < usuario->getTotal_actividades())
						{
							actividad.push_back(usuario->getDificultad());
							actividad.push_back(Convert::ToString(usuario->getNum_actividad() + 1));

							percepciones->setHabilidad(usuario->getDificultad());
							percepciones->setNumeroActividad(usuario->getNum_actividad() + 1);
						}
					}
					else
					{
						//Busco la dificultad sgte 
						if (usuario->getDificultad() == usuario->getDificultades()[usuario->getDificultades().size() - 1])
						{
							if (usuario->getNum_actividad() == usuario->getTotal_actividades())
							{
								actividad.push_back("FIN");
							}
							else
							{
								actividad.push_back(usuario->getDificultad());
								actividad.push_back(Convert::ToString(usuario->getNum_actividad() + 1));

								percepciones->setHabilidad(usuario->getDificultad());
								percepciones->setNumeroActividad(usuario->getNum_actividad() + 1);

							}
						}
						else
						{
							for (int x = 0; x < usuario->getDificultades().size(); x++)
							{
								if (usuario->getDificultad() == usuario->getDificultades()[x])
								{
									actividad.push_back(usuario->getDificultades()[x + 1]);
									actividad.push_back(Convert::ToString(usuario->getNum_actividad() + 1));

									percepciones->setHabilidad(usuario->getDificultades()[x + 1]);
									percepciones->setNumeroActividad(usuario->getNum_actividad() + 1);
								}
							}
						}
					}
				}
			}
		}
	}


	return actividad;
}

vector<String^> AgenteControladorAbs::determinarActividadDificultadHabilidad(String ^ meta)
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
	else //Si ya ha avanzado
	{
		String^ tmpRegla = usuario->getNivel_actuacion();
		Regla^ reglaNivActuacion = conector->transformarString_A_Regla(tmpRegla);

		BaseDeHechos^ base_de_hechos = conector->obtenerBaseDeHechos();
		BaseDeConocimiento^ base_de_conocimiento = conector->obtenerBaseDeConocimiento();

		base_de_hechos->agregarHechos(gcnew Hecho(reglaNivActuacion->getCabeza()->getRelacion(),gcnew Argumento(reglaNivActuacion->getCabeza()->getArgumento()->getNombreArgumento()),VERDADERO));
		base_de_hechos->agregarHechos(gcnew Hecho("dificultad",gcnew Argumento(usuario->getDificultad()),VERDADERO));
		base_de_hechos->agregarHechos(gcnew Hecho("actividad",gcnew Argumento(Convert::ToString(usuario->getNum_actividad())),VERDADERO));

		motorInferencia = gcnew MotorDeInferencia(base_de_hechos, base_de_conocimiento);
		Hecho^ resultado = motorInferencia->ejecutar(meta,ENCADENAMIENTO_ADELANTE);

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
						//Busco la habilidad siguiente
						for (int i = 0; i < usuario->getHabilidades().size(); i++)
						{
							if (usuario->getDificultad() != usuario->getDificultades()[usuario->getHabilidades().size() - 1])
							{
								if (usuario->getDificultad() == usuario->getDificultades()[i])
								{
									habilidad = usuario->getDificultades()[i + 1];
									break;
								}
							}
							else
							{
								dificultad = "Termino";
							}

						}
					}
					if (dificultad != "Termino")
					{
						bool encontrada = false;
						for (int i = 0; i < usuario->getTotal_actividades(); i++)
						{
							if (usuario->getNum_actividad() == i)
							{
								actividad.push_back(dificultad);
								actividad.push_back(Convert::ToString(i + 1));

								percepciones->setHabilidad(dificultad);
								percepciones->setNumeroActividad(i + 1);

								encontrada = true;
							}
						}
						if (!encontrada)
						{
							actividad.push_back(dificultad);
							actividad.push_back("1");

							percepciones->setHabilidad(dificultad);
							percepciones->setNumeroActividad(1);
						}
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
				else
				{
					char regla[9999];

					String^ result = resultado->getArgumento()->getNombreArgumento();
					IntPtr cad = Marshal::StringToHGlobalAnsi(result);

					std::string* str = static_cast<std::string*>(cad.ToPointer());
					strcpy_s(regla, str->c_str());
						
					char *palabra, *nextToken;
					palabra = strtok_s(regla,"_",&nextToken); //Divide la cabeza del cuerpo
					actividad.push_back(Convert::ToString(palabra));
					actividad.push_back(Convert::ToString(nextToken));

					percepciones->setHabilidad(Convert::ToString(palabra)); 
					percepciones->setDificultad(Convert::ToString(nextToken));

					//Busco la actividad sgte

					if (usuario->getNum_actividad() == usuario->getTotal_actividades())
					{
						actividad.push_back("1");
						percepciones->setNumeroActividad(1);
					}
					else
					{
						actividad.push_back(Convert::ToString(usuario->getNum_actividad()+1));
						percepciones->setNumeroActividad(usuario->getNum_actividad() + 1);
					}
					conector->borrarHechos();
					delete motorInferencia;
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
						actividad.push_back("1");
						
						percepciones->setHabilidad(usuario->getHabilidad());
						percepciones->setDificultad(usuario->getDificultad());
						percepciones->setNumeroActividad(1);
					}
					else
					{
						String^ habilidad;
						//Avanzo a la siguiente habilidad
						if (usuario->getHabilidad() != usuario->getHabilidades()[usuario->getHabilidades().size()-1])
						{
							for (int i = 0; i < usuario->getHabilidades().size() -1; i++)
							{
								if (usuario->getHabilidad() == usuario->getHabilidades()[i])
								{
									habilidad = usuario->getHabilidades()[i + 1];
								}
							}
							actividad.push_back(habilidad);
							actividad.push_back(usuario->getDificultades()[0]);
							actividad.push_back("1");

							percepciones->setHabilidad(habilidad);
							percepciones->setDificultad(usuario->getDificultades()[0]);
							percepciones->setNumeroActividad(1);
						}
						else
						{
							habilidad = "FIN";

							actividad.push_back(habilidad);
							actividad.push_back(usuario->getDificultades()[0]);
							actividad.push_back("1");

							percepciones->setHabilidad(habilidad);
							percepciones->setDificultad(usuario->getDificultades()[0]);
							percepciones->setNumeroActividad(1);
						}
					}
					conector->borrarHechos();
					delete motorInferencia;
					return actividad;
				}
				else if(reglaProblema->getCabeza()->getArgumento()->getNombreArgumento() == "Siguiente_Habilidad")
				{
					if (usuario->getHistorialNivelActuacion().size() == 0)
					{
						actividad.push_back(usuario->getHabilidad());
						actividad.push_back(usuario->getDificultades()[1]);
						actividad.push_back("1");

						percepciones->setHabilidad(usuario->getHabilidad());
						percepciones->setDificultad(usuario->getDificultades()[1]);
						percepciones->setNumeroActividad(1);
					}
					else
					{
						String^ habilidad;
						//Avanzo a la siguiente habilidad
						if (usuario->getHabilidad() != usuario->getHabilidades()[usuario->getHabilidades().size() - 1])
						{
							for (int i = 0; i < usuario->getHabilidades().size() - 1; i++)
							{
								if (usuario->getHabilidad() == usuario->getHabilidades()[i])
								{
									habilidad = usuario->getHabilidades()[i + 1];
								}
							}
							actividad.push_back(habilidad);
							actividad.push_back(usuario->getDificultades()[1]);
							actividad.push_back("1");

							percepciones->setHabilidad(habilidad);
							percepciones->setDificultad(usuario->getDificultades()[1]);
							percepciones->setNumeroActividad(1);
						}
						else
						{
							habilidad = "FIN";

							actividad.push_back(habilidad);
							actividad.push_back(usuario->getDificultades()[1]);
							actividad.push_back("1");

							percepciones->setHabilidad(habilidad);
							percepciones->setDificultad(usuario->getDificultades()[1]);
							percepciones->setNumeroActividad(1);
						}
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


