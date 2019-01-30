#pragma once
#include <cliext/vector>

using namespace cliext;
using System::String;

ref class Percepciones
{
public:
#pragma region Constructor y Destructor
	Percepciones();
	~Percepciones();
#pragma endregion
#pragma region Gets & Sets
	vector<String^> getRespuestas();
	int getNumeroActividad();
	String^ getNivel_de_logro();
	String^ getHabilidad();
	String^ getDificultad();
	String^ getNivel_de_actuacion();
	double getTotal_actuacion();
	void setRespuestas(vector<String^> respuestas);
	void setNumeroActividad(int numero_actividad);
	void setNivel_de_logro(String^ _NivelDeLogro);
	void setHabilidad(String^ _habilidad);
	void setDificultad(String^ _dificultad);
	void setNivel_de_actuacion(String^ _niv_de_actuacion);
	void setTotal_actuacion(double _total_actuacion);
#pragma endregion
private: 
	vector<String^> respuestas;
	int numero_actividad;
	String^ nivel_de_Logro;
	String^ habilidad;
	String^ dificultad;
	String^ nivel_de_actuacion;
	double total_actuacion;
};

