#pragma once
#include "AgenteAprendizajeAbstract.h"
#include "Conector.h"
#include "Percepciones.h"
#include "Regla.h"

ref class AgenteAprendizaje : public AgenteAprendizajeAbstract
{

private:
	Conector ^ conector;
	Percepciones ^ percepciones;
	String ^ totalActuacionAnterior;
	Regla ^ reglaNivelActuacion;
	double porcentajeActuacion;

public:
#pragma region Constructor y Destructor
	AgenteAprendizaje(Conector ^ conector, Percepciones ^ percepciones);
	~AgenteAprendizaje();
#pragma endregion
#pragma region Methods
	virtual void obtenerNivelActuacion() override;
	virtual void obtenerNivelActuacionDificultad() override;
	virtual int obtenerCritica() override;
	virtual Regla^ obtenerProblema() override;
	virtual void realimentarElementoAprendizaje() override;
	virtual void determinarElementoActuacion() override;
	virtual void determinarProgresoMedio() override;
	Regla^ getActuacionObtenida();
#pragma endregion
};