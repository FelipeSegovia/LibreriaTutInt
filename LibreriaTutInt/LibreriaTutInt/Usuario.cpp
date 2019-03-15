#include "Usuario.h"

Usuario::Usuario()
{
	this->habilidad = nullptr;
	this->dificultad = nullptr;
	this->numero_actividad = 0;
	this->problema = nullptr;
	this->nivel_actuacion = nullptr;
	this->habilidades = gcnew vector<String^>();
	this->dificultades = gcnew vector<String^>();
	this->actividad_hecha = false;
}

Usuario::Usuario(String ^ _habilidad, String ^ _dificultad, int _numActividad)
{
	this->habilidad = _habilidad;
	this->dificultad = _dificultad;
	this->numero_actividad = _numActividad;
	this->problema = nullptr;
	this->nivel_actuacion = nullptr;
	this->habilidades = gcnew vector<String^>();
	this->actividad_hecha = false;
}

Usuario::Usuario(String ^ _habilidad, int _numActividad)
{
	this->habilidad = _habilidad;
	this->dificultad = nullptr;
	this->numero_actividad = _numActividad;
	this->problema = nullptr;
	this->nivel_actuacion = nullptr;
	this->habilidades = gcnew vector<String^>();
	this->actividad_hecha = false;
}

Usuario::Usuario(String ^ _habilidad, String ^ _dificultad, int _numActividad, String ^ _problema, String ^ _nivelActuacion)
{
	this->habilidad = _habilidad;
	this->dificultad = _dificultad;
	this->numero_actividad = _numActividad;
	this->problema = _problema;
	this->nivel_actuacion = _nivelActuacion;
	this->habilidades = gcnew vector<String^>();
	this->actividad_hecha = false;
}

Usuario::Usuario(String ^ _habilidad, int _numActividad, String ^ _problema, String ^ _nivelActuacion)
{
	this->habilidad = _habilidad;
	this->dificultad = nullptr;
	this->numero_actividad = _numActividad;
	this->problema = _problema;
	this->nivel_actuacion = _nivelActuacion;
	this->habilidades = gcnew vector<String^>();
	this->actividad_hecha = false;
}

Usuario::Usuario(String ^ _habilidad, String ^ _dificultad, int _numActividad, Usuario ^ _usuarioAnterior)
{
	this->habilidad = _habilidad;
	this->dificultad = _dificultad;
	this->numero_actividad = _numActividad;
	this->problema = nullptr;
	this->nivel_actuacion = nullptr;
	this->habilidades = gcnew vector<String^>();
	this->actividad_hecha = false;
}

Usuario::Usuario(String ^ _habilidad, int numActividad, Usuario ^ _usuarioAnterior)
{
	this->habilidad = _habilidad;
	this->dificultad = nullptr;
	this->numero_actividad = numActividad;
	this->problema = nullptr;
	this->nivel_actuacion = nullptr;
	this->habilidades = gcnew vector<String^>();
	this->actividad_hecha = false;
}

Usuario::~Usuario()
{
}

String ^ Usuario::getHabilidad()
{
	return this->habilidad;
}

String ^ Usuario::getDificultad()
{
	return this->dificultad;
}

int Usuario::getNum_actividad()
{
	return this->numero_actividad;
}

String ^ Usuario::getProblema()
{
	return this->problema;
}

String ^ Usuario::getNivel_actuacion()
{
	return this->nivel_actuacion;
}

int Usuario::getTotal_actividades()
{
	return this->total_actividades;
}

bool Usuario::getHizo_actividad()
{
	return this->actividad_hecha;
}

vector<String^> Usuario::getHabilidades()
{
	return this->habilidades;
}

vector<String^> Usuario::getDificultades()
{
	return dificultades;
}

vector<String^> Usuario::getHistorialNivelActuacion()
{
	return this->historialNivActuacion;
}

void Usuario::setHabilidad(String ^ _habilidad)
{
	this->habilidad = _habilidad;
}

Regla ^ Usuario::getReglaNivActuacion()
{
	return this->regla_nivActuacion;
}

void Usuario::setReglaNivActuacion(Regla ^ regla)
{
	this->regla_nivActuacion = regla;
	setNivel_actuacion(this->regla_nivActuacion->getCabeza()->getArgumento()->getNombreArgumento());
}

void Usuario::setDificultad(String ^ _dificultad)
{
	this->dificultad = _dificultad;
}

void Usuario::setNumero_actividad(int _numActividad)
{
	this->numero_actividad = _numActividad;
}

void Usuario::setProblema(String^ _problema)
{
	this->problema = _problema;
}

void Usuario::setNivel_actuacion(String ^ _nivActuacion)
{
	this->nivel_actuacion = _nivActuacion;
	this->historialNivActuacion.push_back(_nivActuacion);
}

void Usuario::setHabilidades(vector<String^> _habilidades)
{
	this->habilidades = _habilidades;
}

void Usuario::setDificultades(vector<String^> _dificultades)
{
	dificultades = _dificultades;
}

void Usuario::setHabilidades(String ^ habilidad)
{
	this->habilidades.push_back(habilidad);
}

void Usuario::setHizo_actividad(bool _aprobacion)
{
	this->actividad_hecha = _aprobacion;
}

void Usuario::setTotalActividades(int _totalAct)
{
	this->total_actividades = _totalAct;
}

void Usuario::setHistorialNivelActuacion(vector<String^> _historial)
{
	this->historialNivActuacion = _historial;
}

