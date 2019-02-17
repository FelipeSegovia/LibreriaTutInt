#pragma once
#ifndef EVALUADOR
#define EVALUADOR

#include <cliext/vector>

using System::String;
using System::Int32;
using namespace cliext;
using namespace System::IO;

ref class Evaluador
{
public:
	Evaluador(String^ _direccion_pauta);
	~Evaluador();
	void revisar_actividad(String^ habilidad, String^ dificultad, int actividad, vector<String^> respuestas_percepciones);
	String^ getNivel_de_logro();
	double getPorcentaje_logro();
private:
	void leerPauta();
	void obtenerNiveldeLogro();
	void revisar_act_soloHabilidad(String^ _habilidad, int actividad, vector<String^> _respuestas_percepciones);
	void revisar_act_soloDificultad(String^ _dificultad, int actividad, vector<String^> _respuestas_percepciones);
	void revisar_act_conHab_y_Dif(String^ _habilidad, String^ _dificultad, int actividad, vector<String^> respuestas_percepciones);
private:

	array<array<String^>^>^ componentes_pauta;
	array<array<String^>^>^ respuestas_pauta;
	String^ nivel_de_logro;
	String^ direccion_pauta;
	double porcentaje_logro;
	int contBuenas;
	int contMalas;
};

#endif // !EVALUADOR