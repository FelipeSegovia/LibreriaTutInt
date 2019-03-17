#pragma once
#include "Factor.h"

using namespace System::Collections;

ref class ConjuntoFactores
{
public:
	ConjuntoFactores();
	~ConjuntoFactores();
	void agregarFactor(Factor ^ factor);
	void borrarFactor(String ^ nombreFactor);
	Factor ^ obtenerFactor(String ^ nombreFactor);
	Factor ^ obtenerFactor(int posicionFactor);
	ArrayList ^ getFactores();
	void setFactores(ArrayList ^ _factores);

private:
	ArrayList ^ factores;
};
