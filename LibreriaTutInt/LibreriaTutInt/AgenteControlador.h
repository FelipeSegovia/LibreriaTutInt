#pragma once
#include "AgenteControladorAbs.h"
#include "Evaluador.h"
ref class AgenteControlador : public AgenteControladorAbs
{
public:
	AgenteControlador(Usuario^ _usuario, String^ _nombreArchivo) : AgenteControladorAbs(_usuario, _nombreArchivo) {};
	~AgenteControlador();

	virtual vector<String^> determinarActividadConHabilidad(String^ meta) override;
	virtual vector<String^> determinarActividadConDificultad(String^ meta) override;
	virtual vector<String^> determinarActividadDificultadHabilidad(String^ meta) override;
	virtual String^ obtenerNivelLogro() override;
	virtual void evaluarActividad(String^ _habilidad, String^ _dificultad, int _actividad, vector<String^> _respuestas) override;

private:
	Evaluador^ evaluador;
};

