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
	void revisar_actividad(String^ habilidad,String^ dificultad,int actividad, vector<String^> respuestas_percepciones);
	String^ getNivel_de_logro();
	double getPorcentaje_logro();
private:
	void leerPauta();
	void obtenerNiveldeLogro();
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