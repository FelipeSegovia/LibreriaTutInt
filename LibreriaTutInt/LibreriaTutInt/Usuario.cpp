#include "Usuario.h"

Usuario::Usuario()
{
	this->habilidad = nullptr;
	this->dificultad = nullptr;
	this->numero_actividad = 0;
	this->problema = nullptr;
	this->nivel_actuacion = nullptr;
	this->usuario_anterior = nullptr;
	this->habilidades = gcnew vector<String^>();
}

Usuario::Usuario(String ^ _habilidad, String ^ _dificultad, int _numActividad)
{
	this->habilidad = _habilidad;
	this->dificultad = _dificultad;
	this->numero_actividad = _numActividad;
	this->problema = nullptr;
	this->nivel_actuacion = nullptr;
	this->usuario_anterior = nullptr;
	this->habilidades = gcnew vector<String^>();
}

Usuario::Usuario(String ^ _habilidad, int _numActividad)
{
	this->habilidad = _habilidad;
	this->dificultad = nullptr;
	this->numero_actividad = _numActividad;
	this->problema = nullptr;
	this->nivel_actuacion = nullptr;
	this->usuario_anterior = nullptr;
	this->habilidades = gcnew vector<String^>();
}

Usuario::Usuario(String ^ _habilidad, String ^ _dificultad, int _numActividad, String ^ _problema, String ^ _nivelActuacion)
{
	this->habilidad = _habilidad;
	this->dificultad = _dificultad;
	this->numero_actividad = _numActividad;
	this->problema = _problema;
	this->nivel_actuacion = _nivelActuacion;
	this->usuario_anterior = nullptr;
	this->habilidades = gcnew vector<String^>();
}

Usuario::Usuario(String ^ _habilidad, int _numActividad, String ^ _problema, String ^ _nivelActuacion)
{
	this->habilidad = _habilidad;
	this->dificultad = nullptr;
	this->numero_actividad = _numActividad;
	this->problema = _problema;
	this->nivel_actuacion = _nivelActuacion;
	this->usuario_anterior = nullptr;
	this->habilidades = gcnew vector<String^>();
}

Usuario::Usuario(String ^ _habilidad, String ^ _dificultad, int _numActividad, Usuario ^ _usuarioAnterior)
{
	this->habilidad = _habilidad;
	this->dificultad = _dificultad;
	this->numero_actividad = _numActividad;
	this->problema = nullptr;
	this->nivel_actuacion = nullptr;
	this->usuario_anterior = _usuarioAnterior;
	this->habilidades = gcnew vector<String^>();
}

Usuario::Usuario(String ^ _habilidad, int numActividad, Usuario ^ _usuarioAnterior)
{
	this->habilidad = _habilidad;
	this->dificultad = nullptr;
	this->numero_actividad = numActividad;
	this->problema = nullptr;
	this->nivel_actuacion = nullptr;
	this->usuario_anterior = _usuarioAnterior;
	this->habilidades = gcnew vector<String^>();
}

Usuario::Usuario(String ^ _habilidad, String ^ _dificultad, int _numActividad, String ^ _problema, String ^ _nivelActuacion, Usuario ^ _usuarioAnterior)
{
	this->habilidad = _habilidad;
	this->dificultad = _dificultad;
	this->numero_actividad = _numActividad;
	this->problema = _problema;
	this->nivel_actuacion = _nivelActuacion;
	this->usuario_anterior = _usuarioAnterior;
	this->habilidades = gcnew vector<String^>();
}

Usuario::Usuario(String ^ _habilidad, int _numActividad, String ^ _problema, String ^ _nivelActuacion, Usuario ^ _usuarioAnterior)
{
	this->habilidad = _habilidad;
	this->dificultad = nullptr;
	this->numero_actividad = _numActividad;
	this->problema = _problema;
	this->nivel_actuacion = _nivelActuacion;
	this->usuario_anterior = _usuarioAnterior;
	this->habilidades = gcnew vector<String^>();
}

Usuario::~Usuario()
{
	delete this->usuario_anterior;
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

bool Usuario::getPaso_actividad()
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

Usuario ^ Usuario::getUsuario_anterior()
{
	return this->usuario_anterior;
}

void Usuario::setHabilidad(String ^ _habilidad)
{
	this->habilidad = _habilidad;
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

void Usuario::setPaso_actividad(bool _aprobacion)
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

void Usuario::setUsuario_anterior(Usuario ^ _usuarioAnterior)
{
	this->usuario_anterior = _usuarioAnterior;
}