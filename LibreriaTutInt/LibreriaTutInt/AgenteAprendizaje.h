#pragma once
#include "AgenteAprendizajeAbstract.h"
#include "Conector.h"
#include "Percepciones.h"

ref class AgenteAprendizaje : public AgenteAprendizajeAbstract
{

private:
	Conector ^ conector;
	Percepciones ^ percepciones;

public:
#pragma region Constructor y Destructor
	AgenteAprendizaje(Conector ^ conector, Percepciones ^ percepciones);
	~AgenteAprendizaje();
#pragma endregion
#pragma region Methods
	virtual void obtenerNivelActuacion() override;
	virtual int obtenerCritica() override;
	virtual Regla^ obtenerProblema() override;
	virtual void realimentarElementoAprendizaje() override;
	virtual void determinarElementoActuacion() override;
#pragma endregion

};