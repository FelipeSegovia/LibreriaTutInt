#pragma once
#ifndef AGENTECONTROLADORABS_H
#define AGENTECONTROLADORABS_H

#include "Conector.h"
#include "Evaluador.h"
#include "Percepciones.h"
#include "Hecho.h"
#include "Regla.h"
#include "Argumento.h"
#include "Usuario.h"
#include "MotorDeInferencia.h"
#include "LeerArchivo.h"
#include <string>

using cliext::vector;
using namespace System;
using namespace System::Runtime::InteropServices;

ref class AgenteControladorAbs
{
public:
	AgenteControladorAbs(Usuario^ _usuario,String^ _nombreArchivo);
	~AgenteControladorAbs();

public:
	virtual vector<String^> determinarActividad() = 0;
	virtual vector<String^> determinarActividadConHabilidad(String^ meta);
	virtual vector<String^> determinarActividadConDificultad(String^ meta);
	virtual vector<String^> determinarActividadDificultadHabilidad(String^ meta);


protected: 
	Conector^ conector;
	Evaluador^ evaluador;
	Percepciones^ percepciones;
	MotorDeInferencia^ motorInferencia;
	String^ habilidad;
	String^ dificultad;
	String^ direccion;
	int actividad;
	Usuario^ usuario;
	LeerArchivo^ archivo;
};

#endif // !AGENTECONTROLADORABS_H
