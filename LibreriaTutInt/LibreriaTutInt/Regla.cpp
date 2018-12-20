#include "Regla.h"


Regla::Regla()
{
	this->cabeza = nullptr;
	this->cuerpo = gcnew vector<Hecho^>();
	this->peso = 0;
}

Regla::Regla(Hecho ^ head, vector<Hecho^> boddy, int peso)
{
	this->cabeza = gcnew Hecho(head->getRelacion(), head->getArgumento());
	this->cuerpo = boddy;
	this->peso = peso;
}

Regla::Regla(Hecho ^ head, vector<Hecho^> boddy)
{
	this->cabeza = gcnew Hecho(head->getRelacion(), head->getArgumento());
	this->cuerpo = boddy;
}

Regla::Regla(const Regla ^& r)
{
	throw gcnew System::NotImplementedException();
}

Regla::~Regla()
{
}

Hecho ^ Regla::getCabeza()
{
	return this->cabeza;
}

vector<Hecho^> Regla::getCuerpo()
{
	return this->cuerpo;
}

bool Regla::getMarcada()
{
	return this->marcada;
}

int Regla::getPeso()
{
	return this->peso;
}

int Regla::getNumeroCondiciones()
{
	if (this->cabeza != nullptr)
		return cuerpo.size();
	else
		return 0;
}

int Regla::getHechosConfirmados()
{
	return hechosConfirmados;
}

double Regla::getPorcentajeHechosConfirmados()
{
	return (hechosConfirmados * 100.0) / getNumeroCondiciones();
}

void Regla::setCabeza(Hecho ^ head)
{
	this->cabeza = head;
}

void Regla::setCuerpo(vector<Hecho^> boddy)
{
	this->cuerpo = boddy;
}

void Regla::setMarcada(bool marca)
{
	this->marcada = marca;
}

void Regla::setPeso(int _peso)
{
	this->peso = _peso;
}

void Regla::setHechosConfirmados(int confirmados)
{
	this->hechosConfirmados = confirmados;
}

bool Regla::operator==(Regla ^ r2)
{
	Object ^obj = this;
	Object ^obj2 = r2;
	if (obj == nullptr && obj2 == nullptr)
	{
		return true;
	}
	else if ((obj == nullptr && obj2 != nullptr) || (obj != nullptr && obj2 == nullptr))
	{
		return false;
	}
	else if ((this->getCabeza() == r2->getCabeza()) && (this->getNumeroCondiciones() == r2->getNumeroCondiciones())) {
		bool iguales = true;
		for (int x = 0; x < this->getNumeroCondiciones(); x++) {
			//Tienen el mismo numero de condiciones por lo que el limite de x vale para los dos
			if (this->getCuerpo().at(x) != r2->getCuerpo().at(x)) {
				iguales = false;
			}
		}
		return iguales;
	}
	return false;
}

bool Regla::operator!=(Regla ^ r2)
{
	Object ^obj = this;
	Object ^obj2 = r2;
	if (obj == nullptr && obj2 == nullptr)
	{
		return false;
	}
	else if ((obj == nullptr && obj2 != nullptr) || (obj != nullptr && obj2 == nullptr))
	{
		return true;
	}
	else if ((this->getCabeza() == r2->getCabeza()) && (this->getNumeroCondiciones() == r2->getNumeroCondiciones())) {
		bool iguales = true;
		for (int x = 0; x < this->getNumeroCondiciones(); x++) {
			//Tienen el mismo numero de condiciones por lo que el limite de x vale para los dos
			if (this->getCuerpo().at(x) != r2->getCuerpo().at(x)) {
				iguales = true;
			}
		}
		return iguales;
	}
	return true;
}

bool Regla::Equals(Regla ^ r1)
{
	if (this == r1)
		return true;
	return false;
}

Regla% Regla::operator=(const Regla% r)
{
	return *this;
}
