#include "BaseDeConocimiento.h"

BaseDeConocimiento::BaseDeConocimiento() {
	this->reglas = gcnew ArrayList();
	this->reglasMarcadas = 0;
}

BaseDeConocimiento::~BaseDeConocimiento() {
	delete this->reglas;
}

void BaseDeConocimiento::agregarRegla(Regla ^regla) {
	if (regla != nullptr) {
		this->reglas->Add(regla);
	}
	else {
		System::Windows::Forms::MessageBox::Show("Regla vacia.");
	}
}

void BaseDeConocimiento::ordenarMenorAMayor() {
	IComparer^ comparer = gcnew BaseDeConocimiento;
	reglas->Sort(comparer);
}

Regla^ BaseDeConocimiento::obtenerRegla(int x) {
	Object ^ object = reglas[x];
	Regla ^ regla = (Regla^)object;
	return regla;
}

int BaseDeConocimiento::getNumeroReglas() {
	return this->reglas->Count;
}

int BaseDeConocimiento::getReglasMarcadas() {
	return this->reglasMarcadas;
}

void BaseDeConocimiento::setReglasMarcadas(int numReglas) {
	this->reglasMarcadas = numReglas;
}

int BaseDeConocimiento::Compare(Object^ x, Object^ y) {
	Regla ^re1 = (Regla^)x;
	Regla ^re2 = (Regla^)y;
	size_t largo1 = 0;
	size_t largo2 = 0;
	if (re1 != nullptr)
	largo1 = re1->getCuerpo().size();
	if (re2 != nullptr)
	largo2 = re2->getCuerpo().size();
	if (largo1 > largo2)
	return 1;
	if (largo1 < largo2)
		return -1;
	else
	return 0;
}