#include "Evaluador.h"

Evaluador::Evaluador(String ^ _direccion_pauta, int limit_inf, int limit_med, int limit_sup)
{
	this->direccion_pauta = _direccion_pauta;
	this->limite_inf = limit_inf;
	this->limite_med = limit_med;
	this->limite_sup = limit_sup;
}

Evaluador::~Evaluador()
{
}

void Evaluador::revisar_actividad(String ^ habilidad, String ^ dificultad, int actividad, vector<String^> respuestas_percepciones)
{
	leerPauta();

	if (habilidad == nullptr) //Lo hago con dificultad
	{
		revisar_act_soloDificultad(dificultad, actividad, respuestas_percepciones);
	}
	else if (dificultad == nullptr) //lo hago con habilidad
	{
		revisar_act_soloHabilidad(habilidad, actividad, respuestas_percepciones);
	}
	else //lo hago con habilidad y dificultad
	{
		revisar_act_conHab_y_Dif(habilidad, dificultad, actividad, respuestas_percepciones);
	}

	obtenerNiveldeLogro();
}



String ^ Evaluador::getNivel_de_logro()
{
	return this->nivel_de_logro;
}

double Evaluador::getPorcentaje_logro()
{
	return this->porcentaje_logro;
}

int Evaluador::getRespuestas_buenas()
{
	return this->contBuenas;
}

int Evaluador::getRespuestas_malas()
{
	return this->contMalas;
}


void Evaluador::leerPauta()
{
	StreamReader^ filePauta = File::OpenText(this->direccion_pauta);
	int contador_lineasX = 0;
	int contador_lineasY = 0;
	String^ linea;
	while ((linea = filePauta->ReadLine()) != nullptr)
	{
		contador_lineasY++;
		if (contador_lineasX < linea->Length)
		{
			contador_lineasX = linea->Length;
		}
	}
	filePauta->Close();
	//inicializo los arreglos

	this->componentes_pauta = gcnew array<array<String^>^>(contador_lineasY);
	this->respuestas_pauta = gcnew array<array<String^>^>(contador_lineasY);

	String^ linea_leida;
	array<String^>^ separar_componentes;
	array<String^>^ separar_respuestas;

	filePauta = File::OpenText(this->direccion_pauta);
	int contador = 0;
	while ((linea_leida = filePauta->ReadLine()) != nullptr)
	{
		separar_componentes = linea_leida->Split(',');
		this->componentes_pauta[contador] = gcnew array<String^>(contador_lineasX);
		for (int i = 0; separar_componentes->Length - 1 > i; i++)
		{

			this->componentes_pauta[contador][i] = separar_componentes[i]->ToString();
		}

		separar_respuestas = linea_leida->Split('(', ' ', ')');
		this->respuestas_pauta[contador] = gcnew array<String^>(contador_lineasX);
		for (int i = 1; separar_respuestas->Length - 1 > i; i++)
		{

			this->respuestas_pauta[contador][i - 1] = separar_respuestas[i]->ToString();
		}
		contador++;
	}
	filePauta->Close();
}

void Evaluador::obtenerNiveldeLogro()
{
	this->porcentaje_logro = ((contBuenas * 100) / (contBuenas + contMalas));
	if ((porcentaje_logro >= 0) && (porcentaje_logro <= this->limite_inf))
	{
		this->nivel_de_logro = "No_Logrado";
	}
	else if ((porcentaje_logro > this->limite_inf) && (porcentaje_logro <= this->limite_med))
	{
		this->nivel_de_logro = "Medianamente_Logrado";
	}
	else if ((porcentaje_logro > this->limite_med) && (porcentaje_logro <= this->limite_sup))
	{
		this->nivel_de_logro = "Logrado";
	}
}

void Evaluador::revisar_act_soloHabilidad(String^ _habilidad, int actividad, vector<String^> _respuestas_percepciones)
{
	int contador = 0;
	//comparo los resultados con los valores de la pauta
	while (contador < this->componentes_pauta->Length)
	{
		//Comparo las componentes
		if (_habilidad == this->componentes_pauta[contador][0]->ToString() &&
			actividad == Int32::Parse(this->componentes_pauta[contador][1]->ToString()))
		{
			//Comparo los resultados de la actividad
			for (int i = 0; i < this->respuestas_pauta[contador]->Length; i++)
			{
				if (this->respuestas_pauta[contador][i] != nullptr)
				{
					if (respuestas_pauta[contador][i] == _respuestas_percepciones[i]->ToString())
					{
						this->contBuenas++;
					}
					else
					{
						this->contMalas++;
					}
				}

			}
		}
		contador++;
	}
}

void Evaluador::revisar_act_soloDificultad(String ^ _dificultad, int actividad, vector<String^> _respuestas_percepciones)
{
	int contador = 0;
	//comparo los resultados con los valores de la pauta
	while (contador < this->componentes_pauta->Length)
	{
		//Comparo las componentes
		if (_dificultad == this->componentes_pauta[contador][0]->ToString() &&
			actividad == Int32::Parse(this->componentes_pauta[contador][1]->ToString()))
		{
			//Comparo los resultados de la actividad
			for (int i = 0; i < this->respuestas_pauta[contador]->Length; i++)
			{
				if (this->respuestas_pauta[contador][i] != nullptr)
				{
					if (respuestas_pauta[contador][i] == _respuestas_percepciones[i]->ToString())
					{
						this->contBuenas++;
					}
					else
					{
						this->contMalas++;
					}
				}

			}
		}
		contador++;
	}
}

void Evaluador::revisar_act_conHab_y_Dif(String^ _habilidad, String^ _dificultad, int actividad, vector<String^> respuestas_percepciones)
{
	int contador = 0;
	//comparo los resultados con los valores de la pauta
	while (contador < this->componentes_pauta->Length)
	{
		//Comparo las componentes
		if (_habilidad == this->componentes_pauta[contador][0]->ToString() &&
			_dificultad == this->componentes_pauta[contador][1]->ToString() &&
			actividad == Int32::Parse(this->componentes_pauta[contador][2]->ToString()))
		{
			//Comparo los resultados de la actividad
			for (int i = 0; i < this->respuestas_pauta[contador]->Length; i++)
			{
				if (this->respuestas_pauta[contador][i] != nullptr)
				{
					if (respuestas_pauta[contador][i] == respuestas_percepciones[i]->ToString())
					{
						this->contBuenas++;
					}
					else
					{
						this->contMalas++;
					}
				}

			}
		}
		contador++;
	}
}
