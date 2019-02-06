#pragma once
#include "AgenteControladorAbs.h"
#include "Evaluador.h"
ref class AgenteControlador : public AgenteControladorAbs
{
public:
	AgenteControlador();
	~AgenteControlador();

	String^ obtenerNivelLogro();
	void evaluarActividad();

private:
	Evaluador^ evaluador;
};

