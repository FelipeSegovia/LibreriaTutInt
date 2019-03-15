#include "BaseDeHechos.h"

BaseDeHechos::BaseDeHechos()
{
	this->hechos = gcnew vector<Hecho^>();
}

BaseDeHechos::~BaseDeHechos()
{
	delete this->hechos;
}

void BaseDeHechos::agregarHechos(Hecho ^ hecho)
{

	if (hecho != nullptr)
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
			//System::Windows::Forms::MessageBox::Show("Error: se queria ingerear un hecho indeterminado");
		}
	}
	else
	{
		System::Windows::Forms::MessageBox::Show("Error: se queria ingerear un hecho null");
	}
}

bool BaseDeHechos::existeHecho(Hecho ^ hecho)
{
	for (int i = 0; i < this->hechos.size(); i++)
	{
		if (hechos[i]->getArgumento()->getNombreArgumento() == hecho->getArgumento()->getNombreArgumento() && hechos[i]->getRelacion() == hecho->getRelacion())
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
	for (int i = 0; i < this->hechos.size(); i++)
	{
		if (this->hechos[i]->getArgumento()->getNombreArgumento() == hecho->getArgumento()->getNombreArgumento() && hecho->getRelacion() == this->hechos[i]->getRelacion())
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
