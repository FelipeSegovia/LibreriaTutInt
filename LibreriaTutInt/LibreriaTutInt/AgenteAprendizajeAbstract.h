#pragma once
#include "Regla.h"

using namespace System;

ref class AgenteAprendizajeAbstract abstract
{

public:
	virtual void obtenerNivelActuacion() = 0;
	virtual void obtenerNivelActuacionDificultad() = 0;
	virtual void obtenerNivelActuacionConFactores() = 0;
	virtual int obtenerCritica() = 0;
	virtual Regla^ obtenerProblema() = 0;
	virtual void realimentarElementoAprendizaje() = 0;
	virtual void determinarElementoActuacion() = 0;
	virtual void determinarProgresoMedio() = 0;
};