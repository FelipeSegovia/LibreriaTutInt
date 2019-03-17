#include"Factor.h"

Factor::Factor(String^ _nombre, vector<String^> _rangos, double _peso)
{
	this->nombre = _nombre;
	this->rangos = _rangos;
	this->peso = _peso;
}

Factor::~Factor()
{

}

String^ Factor::getNombre()
{
	return this->nombre;
}

vector<String^> Factor::getRangos()
{
	return this->rangos;
}

double Factor::getPeso()
{
	return this->peso;
}

String^ Factor::getNivelObtenido()
{
	return this->nivelObtenido;
}

void Factor::setNombre(String^ _nombre)
{
	this->nombre = _nombre;
}

void Factor::setRangos(vector<String^> _rangos)
{
	this->rangos = _rangos;
}

void Factor::setPeso(double _peso)
{
	this->peso = _peso;
}

void Factor::setNivelObtenido(String^ _nivelObtenido)
{
	this->nivelObtenido = _nivelObtenido;
}