#pragma once

#include "Regla.h"

using namespace System;
using namespace System::Collections;
using namespace cliext;

ref class BaseDeConocimiento : public IComparer {

public:
#pragma region Constructores y Destructores
	BaseDeConocimiento();
	~BaseDeConocimiento();
#pragma endregion
#pragma region Metodos
	void agregarRegla(Regla ^regla);
	void ordenarMenorAMayor();
	Regla^ obtenerRegla(int x);
	Regla^ obtenerRegla(Regla ^ regla);
	virtual int Compare(Object^ x, Object^ y) = IComparer::Compare;
#pragma endregion
#pragma region Gets && Sets
	int getNumeroReglas();
	int getReglasMarcadas();
	void setReglasMarcadas(int numReglas);
#pragma endregion

private:
	ArrayList ^ reglas;
	int reglasMarcadas;
	int numeroReglas;
};