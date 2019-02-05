#include "Percepciones.h"

Percepciones::Percepciones()
{
	this->contadorAlto = 0;
	this->contadorMedio = 0;
	this->contadorBajo = 0;
}

Percepciones::~Percepciones()
{}

vector<String^> Percepciones::getRespuestas()
{
	return this->respuestas;
}

int Percepciones::getNumeroActividad()
{
	return this->numeroActividad;
}

int Percepciones::getContadorAlto()
{
	return this->contadorAlto;
}

int Percepciones::getContadorMedio()
{
	return this->contadorMedio;
}

int Percepciones::getContadorBajo()
{
	return this->contadorBajo;
}

String ^ Percepciones::getNivelDeLogro()
{
	return this->nivelDeLogro;
}

String ^ Percepciones::getHabilidad()
{
	return this->habilidad;
}

String ^ Percepciones::getDificultad()
{
	return this->dificultad;
}

String ^ Percepciones::getNivelDeActuacion()
{
	return this->nivelDeActuacion;
}

String^ Percepciones::getTotalActuacion()
{
	return this->totalActuacion;
}

String ^ Percepciones::getProgresoActual()
{
	return this->progresoActual;
}

Regla^ Percepciones::getProblemaGenerado()
{
	return this->problemaGenerado;
}

void Percepciones::setRespuestas(vector<String^> respuestas)
{
	this->respuestas = respuestas;
}

void Percepciones::setNumeroActividad(int numero_actividad)
{
	this->numeroActividad = numero_actividad;
}

void Percepciones::setContadorAlto(int contadorAlto)
{
	this->contadorAlto = contadorAlto;
}

void Percepciones::setContadorMedio(int contadorMedio)
{
	this->contadorMedio = contadorMedio;
}

void Percepciones::setContadorBajo(int contadorBajo)
{
	this->contadorBajo = contadorBajo;
}

void Percepciones::setNivelDeLogro(String ^ _NivelDeLogro)
{
	this->nivelDeLogro = _NivelDeLogro;
}

void Percepciones::setHabilidad(String ^ _habilidad)
{
	this->habilidad = _habilidad;
}

void Percepciones::setDificultad(String ^ _dificultad)
{
	this->dificultad = _dificultad;

}

void Percepciones::setNivelDeActuacion(String ^ _niv_de_actuacion)
{
	this->nivelDeActuacion = _niv_de_actuacion;
}

void Percepciones::setTotalActuacion(String^ _total_actuacion)
{
	this->totalActuacion = _total_actuacion;
}

void Percepciones::setProgresoActual(String^ progresoActual)
{
	this->progresoActual = progresoActual;
}

void Percepciones::setProblemaGenerado(Regla ^ problema)
{
	this->problemaGenerado = problema;
}
