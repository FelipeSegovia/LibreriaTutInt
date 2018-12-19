#include "Hecho.h"


Hecho::Hecho()
{
	this->predicado = nullptr;
	this->argumentos = gcnew vector<Argumento^>();
	this->estado = NULL;
	this->permamente = NULL;
}

Hecho::Hecho(String ^ predicado, vector<Argumento^> args, int estado)
{
	this->predicado = predicado;
	this->argumentos = args;
	this->estado = estado;
}

Hecho::Hecho(String ^ predicado, vector<Argumento^> args)
{
	this->predicado = predicado;
	this->argumentos = args;
	this->estado = INDETERMINADO;
}

Hecho::Hecho(String ^ predicado, Argumento ^ args, int estado)
{
	this->predicado = predicado;
	this->argumentos.push_back(args);
	this->estado = estado;
}

Hecho::Hecho(String ^ predicado, Argumento^ args)
{
	this->predicado = predicado;
	this->argumentos.push_back(args);
	this->estado = INDETERMINADO;
}

Hecho::~Hecho()
{
	delete this->predicado;
	delete this->argumentos;
	
}

String ^ Hecho::getRelacion()
{
	return this->predicado;
}

void Hecho::setRelacion(String ^ relacion)
{
	this->predicado = relacion;
}

vector<Argumento^> Hecho::getArgumento()
{
	return this->argumentos;
}

void Hecho::setArgumento(Argumento ^ arg)
{
	this->argumentos.push_back(arg);
}

int Hecho::getNumeroArgumentos()
{
	if (this->argumentos.size() != 0)
	{
		return this->argumentos.size();
	}
	return 0;
}

int Hecho::getEstado()
{
	return this->estado;
}

void Hecho::setEstado(int estado)
{
	this->estado = estado;
}

String ^ Hecho::getEstadoTexto()
{
	if (this->estado == VERDADERO)
		return "Verdadero";
	else if (this->estado == FALSO)
		return "Falso";
	else
		return "Indeterminado";
}

bool Hecho::getPermanente()
{
	return this->permamente;
}

void Hecho::setPermanente(bool permanente)
{
	this->permamente = permanente;
}

bool Hecho::operator==(Hecho ^ h2)
{
	Object ^ obj = this;
	Object ^ obj2 = h2;

	if (obj == nullptr && obj2 == nullptr)
	{
		return true;
	}
	else if ((obj == nullptr && obj2 != nullptr) || (obj != nullptr && obj2 == nullptr))
	{
		return false;
	}
	else if (this->getRelacion() == h2->getRelacion() && this->getNumeroArgumentos() == h2->getNumeroArgumentos())
	{
		bool iguales = true;
		for (int x = 0; x < this->getNumeroArgumentos(); x++) {
			//Tienen el mismo numero de argumento por lo que el limite de x vale para los dos
			if (this->argumentos[x] != h2->getArgumento()[x]) {
				iguales = false;
			}
		}
		return iguales;
	}

	return false;
}

bool Hecho::operator!=(Hecho ^ h2)
{
	Object ^ obj = this;
	Object ^ obj2 = h2;

	if (obj == nullptr && obj2 == nullptr)
	{
		return false;
	}
	else if ((obj == nullptr && obj2 != nullptr) || (obj != nullptr && obj2 == nullptr))
	{
		return true;
	}
	else if (this->getRelacion() == h2->getRelacion() && this->getNumeroArgumentos() == h2->getNumeroArgumentos())
	{
		bool iguales = true;
		for (int x = 0; x < this->getNumeroArgumentos(); x++) {
			//Tienen el mismo numero de argumento por lo que el limite de x vale para los dos
			if (this->argumentos[x] != h2->getArgumento()[x]) {
				iguales = true;
			}
		}
		return iguales;
	}

	return true;
}

bool Hecho::Equals(Hecho ^ h2)
{
	if (this == h2)
		return true;
	return false;
}

Hecho% Hecho::operator=(const Hecho% h)
{
	return *this;
}