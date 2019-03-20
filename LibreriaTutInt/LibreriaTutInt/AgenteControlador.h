#pragma once
#include "AgenteControladorAbs.h"
#include "Evaluador.h"
#include "AgenteAprendizaje.h"
#include "ConjuntoFactores.h"

ref class AgenteControlador : public AgenteControladorAbs
{
public:
	AgenteControlador(Usuario^ _usuario, String^ _nombreArchivo, String^ nombre_usuario, int limit_inf, int limit_sup);
	~AgenteControlador();
	virtual vector<String^> determinarActividad() override;
	virtual vector<String^> determinarActividadConHabilidad(String^ meta) override;
	virtual vector<String^> determinarActividadConDificultad(String^ meta) override;
	virtual vector<String^> determinarActividadDificultadHabilidad(String^ meta) override;
	virtual String^ obtenerNivelLogro() override;
	virtual void evaluarActividad(String^ _habilidad, String^ _dificultad, int _actividad, vector<String^> _respuestas) override;
	void determinarNivelDeActuacion();
	Usuario^ getUsuario();
	String^ getProblema();
	Percepciones^ getPercepciones();
	ConjuntoFactores ^ getFactores();
	void setFactores(ConjuntoFactores ^ _factores);
	void setAprendizaje(AgenteAprendizaje ^ _aprendizaje);
	AgenteAprendizaje ^ getAprendizaje();

private:
	Conector^ conector;
	Evaluador^ evaluador;
	Percepciones^ percepciones;
	MotorDeInferencia^ motorInferencia;
	ConjuntoFactores ^ factores;
	AgenteAprendizaje ^ aprendizaje;
	String^ habilidad;
	String^ dificultad;
	String^ direccion;
	String^ actuacion;
	String^ problema;
	int actividad;
	Usuario^ usuario;
	LeerArchivo^ archivo;
	int limite_inf;
	int limite_sup;
};

