#pragma once

#include "BaseDeConocimiento.h"
#include "BaseDeHechos.h"
#include "Regla.h"
#include "Hecho.h"

using namespace System;
using namespace System::Collections;

// REVISAR ESTO
const int ENCADENAMIENTO_ATRAS = 0;
const int ENCADENAMIENTO_ADELANTE = 1;

ref class MotorDeInferencia {

public:
#pragma region Constructores y Destructores
	MotorDeInferencia(BaseDeHechos ^ baseHechos, BaseDeConocimiento ^ baseConocimiento);
	~MotorDeInferencia();
#pragma endregion
#pragma region Metodos
	Hecho ^ encadenamientoHaciaAdelante(String ^ hecho);
	Hecho ^ encadenamientoHaciaAtras(Hecho ^ hechoMeta);
	Hecho ^ ejecutar(String ^ objetivo, int encadenamiento);
	void desmarcarReglas();
#pragma endregion
#pragma region Gets && Sets
	Regla ^ getReglaInferida();
	bool getTerminoInferencia();
	void setDetenerInferencia(bool value);
#pragma endregion

private:
	BaseDeHechos ^ baseHechos;
	BaseDeConocimiento ^ baseConocimiento;
	Regla ^ reglaInferida;
	bool terminoInferencia;
	bool detenerInferencia;
	int nivel;
};