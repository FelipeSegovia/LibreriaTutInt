#include "BaseDeHechos.h"



BaseDeHechos::BaseDeHechos()
{
	this->hechos = nullptr;
}

BaseDeHechos::~BaseDeHechos()
{
	delete this->hechos;
}

void BaseDeHechos::agregarHechos(Hecho ^ hecho)
{
	if (this->existeHecho(hecho) == FALSO && hecho->getEstado() == VERDADERO)
	{
		this->hechos.push_back(hecho);
	}
	else if (hecho->getEstado() != INDETERMINADO)
	{
		this->hechos.push_back(hecho);
	}
	else
	{
		System::Exception("Error: se queria ingerear un hecho indeterminado");
	}
}

bool BaseDeHechos::existeHecho(Hecho ^ hecho)
{
	//Recorro el vector comparando los argumentos y las relaciones
	for (int i = 0; i < this->hechos.size();i++)
	{
		if (hechos[i]->getArgumento().at(0)->ToString() == hecho->getArgumento().at(0)->ToString() && hechos[i]->getRelacion() == hecho->getRelacion())
		{
			return true;
		}
	}
	return false;

}

int BaseDeHechos::estadoHecho(Hecho ^ hecho)
{
	int valor = -1;
	//comparo cada hecho con el parametro de entrada
	for (int i = 0; i < this->hechos.size();i++)
	{
		if (this->hechos[i]->getArgumento().at(0)->ToString() == hecho->getArgumento().at(0)->ToString() && hecho->getRelacion() == this->hechos[i]->getRelacion())
		{
			valor = this->hechos[i]->getEstado();
		}
	}
	return valor;
}

void BaseDeHechos::borrarHechos()
{
	this->hechos.clear();
}
