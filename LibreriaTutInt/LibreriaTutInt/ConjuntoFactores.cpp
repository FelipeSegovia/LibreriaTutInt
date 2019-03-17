#include"ConjuntoFactores.h"

ConjuntoFactores::ConjuntoFactores() 
{
	this->factores = gcnew ArrayList();
}

ConjuntoFactores::~ConjuntoFactores()
{

}

void ConjuntoFactores::agregarFactor(Factor ^ factor)
{
	this->factores->Add(factor);
}

void ConjuntoFactores::borrarFactor(String ^ nombreFactor)
{
	for (int i = 0; i < factores->Count; i++)
	{
		Factor ^ tmpFactor = (Factor ^)factores[i];
		if (tmpFactor->getNombre() == nombreFactor)
		{
			this->factores->Remove(tmpFactor);
		}
	}
}

Factor ^ ConjuntoFactores::obtenerFactor(String ^ nombreFactor)
{
	for (int i = 0; i < factores->Count; i++)
	{
		Factor ^ tmpFactor = (Factor ^)factores[i];
		if (tmpFactor->getNombre() == nombreFactor)
		{
			return tmpFactor;
		}
	}
	return nullptr;
}

Factor ^ ConjuntoFactores::obtenerFactor(int posicionFactor)
{
	return (Factor ^)this->factores[posicionFactor];
}

ArrayList ^ ConjuntoFactores::getFactores()
{
	return this->factores;
}

void ConjuntoFactores::setFactores(ArrayList ^ _factores)
{
	this->factores = _factores;
}