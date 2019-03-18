#pragma once
#include "AgenteAprendizajeAbstract.h"
#include "Conector.h"
#include "Percepciones.h"
#include "Regla.h"
#include "ConjuntoFactores.h"

using namespace System;

ref class AgenteAprendizaje : public AgenteAprendizajeAbstract
{

private:
	Conector ^ conector;
	Percepciones ^ percepciones;
	ConjuntoFactores ^ factores;
	String ^ totalActuacionAnterior;
	Regla ^ reglaNivelActuacion;
	double porcentajeActuacion;
	double minimoActuacion;
	double maximoActuacion;

public:
#pragma region Constructor y Destructor
	AgenteAprendizaje(Conector ^ conector, Percepciones ^ percepciones);
	AgenteAprendizaje(Conector ^ conector, Percepciones ^ percepciones, ConjuntoFactores ^ _factores);
	~AgenteAprendizaje();
#pragma endregion
#pragma region Methods
	virtual void obtenerNivelActuacion() override;
	virtual void obtenerNivelActuacionDificultad() override;
	virtual void obtenerNivelActuacionConFactores() override;
	virtual int obtenerCritica() override;
	virtual Regla^ obtenerProblema() override;
	virtual void realimentarElementoAprendizaje() override;
	virtual void determinarElementoActuacion() override;
	virtual void determinarProgresoMedio() override;
	Regla^ getActuacionObtenida();
	double getMinimoActuacion();
	double getMaximoActuacion();
	void setMinimoActuacion(double _minimoActuacion);
	void setMaximoActuacion(double _maximoActuacion);
	void setPorcentajeActuacion(double _porcentajeActuacion);
#pragma endregion
};