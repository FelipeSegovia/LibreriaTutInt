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

ref class AgenteControladorAbs abstract
{

public:
	virtual vector<String^> determinarActividad() = 0;
	virtual vector<String^> determinarActividadConHabilidad(String^ meta) = 0;
	virtual vector<String^> determinarActividadConDificultad(String^ meta) = 0;
	virtual vector<String^> determinarActividadDificultadHabilidad(String^ meta) = 0;
	virtual String^ obtenerNivelLogro() = 0;
	virtual void evaluarActividad(String^ _habilidad, String^ _dificultad, int _actividad, vector<String^> _respuestas) = 0;

};

#endif // !AGENTECONTROLADORABS_H
