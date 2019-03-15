#pragma once
#include "Regla.h"
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
	int getContadorAlto();
	int getContadorMedio();
	int getContadorBajo();
	String^ getNivelDeLogro();
	String^ getHabilidad();
	String^ getDificultad();
	String^ getNivelDeActuacion();
	String^ getTotalActuacion();
	String^ getProgresoActual();
	Regla^ getProblemaGenerado();
	void setRespuestas(vector<String^> respuestas);
	void setNumeroActividad(int numero_actividad);
	void setContadorAlto(int contadorAlto);
	void setContadorMedio(int contadorMedio);
	void setContadorBajo(int contadorBajo);
	void setNivelDeLogro(String^ _NivelDeLogro);
	void setHabilidad(String^ _habilidad);
	void setDificultad(String^ _dificultad);
	void setNivelDeActuacion(String^ _niv_de_actuacion);				// Obtenido en la actividad
	void setTotalActuacion(String^ _total_actuacion);				// Segun el progreso en las actividades
	void setProgresoActual(String^ progresoActual);
	void setProblemaGenerado(Regla^ problema);
#pragma endregion
private:
	vector<String^> respuestas;
	int numeroActividad;
	int contadorAlto;
	int contadorMedio;
	int contadorBajo;
	String^ nivelDeLogro;
	String^ habilidad;
	String^ dificultad;
	String^ nivelDeActuacion;
	String^ totalActuacion;
	String^ progresoActual;
	Regla^ problemaGenerado;											// Problema determinado por el agente aprendizaje
};

