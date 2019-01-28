#include "Percepciones.h"

Percepciones::Percepciones()
{
}

Percepciones::~Percepciones()
{}

vector<String^> Percepciones::getRespuestas()
{
	return this->respuestas;
}

int Percepciones::getNumeroActividad()
{
	return this->numero_actividad;
}

String ^ Percepciones::getNivel_de_logro()
{
	return this->nivel_de_Logro;
}

String ^ Percepciones::getHabilidad()
{
	return this->habilidad;
}

String ^ Percepciones::getDificultad()
{
	return this->dificultad;
}

String ^ Percepciones::getNivel_de_actuacion()
{
	return this->nivel_de_actuacion;
}

double Percepciones::getTotal_actuacion()
{
	return this->total_actuacion;
}

void Percepciones::setRespuestas(vector<String^> respuestas)
{
	this->respuestas = respuestas;
}

void Percepciones::setNumeroActividad(int numero_actividad)
{
	this->numero_actividad = numero_actividad;
}

void Percepciones::setNivel_de_logro(String ^ _NivelDeLogro)
{
	this->nivel_de_Logro = _NivelDeLogro;
}

void Percepciones::setHabilidad(String ^ _habilidad)
{
	this->habilidad = _habilidad;
}

void Percepciones::setDificultad(String ^ _dificultad)
{
	this->dificultad = _dificultad;

}

void Percepciones::setNivel_de_actuacion(String ^ _niv_de_actuacion)
{
	this->nivel_de_actuacion = _niv_de_actuacion;
}

void Percepciones::setTotal_actuacion(double _total_actuacion)
{
	this->total_actuacion = _total_actuacion;
}
