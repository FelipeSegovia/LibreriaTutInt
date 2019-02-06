#pragma once
#ifndef USUARIO_H
#define USUARIO_H

#include <cliext/vector>

using System::String;
using cliext::vector;

ref class Usuario
{
public:
	Usuario(String^ _habilidad, String^ _dificultad, int _numActividad);
	Usuario(String^ _habilidad, int _numActividad);
	Usuario(String^ _habilidad, String^ _dificultad, int _numActividad, String^ _problema, String^ _nivelActuacion);
	Usuario(String^ _habilidad, int _numActividad, String^ _problema, String^ _nivelActuacion);
	Usuario(String^ _habilidad, String^ _dificultad, int _numActividad, Usuario^ _usuarioAnterior);
	Usuario(String^ _habilidad, int numActividad, Usuario^ _usuarioAnterior);
	Usuario(String^ _habilidad, String^ _dificultad, int _numActividad, String^ _problema, String^ _nivelActuacion, Usuario^ _usuarioAnterior);
	Usuario(String^ _habilidad, int _numActividad, String^ _problema, String^ _nivelActuacion, Usuario^ _usuarioAnterior);
	Usuario();
	~Usuario();
	String^ getHabilidad();
	String^ getDificultad();
	int getNum_actividad();
	String^ getProblema();
	String^ getNivel_actuacion();
	int getTotal_actividades();
	bool getPaso_actividad();
	vector<String^> getHabilidades();
	vector<String^> getDificultades();
	vector<String^> getHistorialNivelActuacion();
	Usuario^ getUsuario_anterior();
	void setHabilidad(String^ _habilidad);
	void setDificultad(String^ _dificultad);
	void setNumero_actividad(int _numActividad);
	void setProblema(String^ _problema);
	void setNivel_actuacion(String^ _nivActuacion);
	void setHabilidades(vector<String^> _habilidades);
	void setDificultades(vector<String^> _dificultades);
	void setHabilidades(String^ habilidad);
	void setPaso_actividad(bool _aprobacion);
	void setTotalActividades(int _totalAct);
	void setHistorialNivelActuacion(vector<String^> _historial);
	void setUsuario_anterior(Usuario^ _usuarioAnterior);
private:
	String^ habilidad;
	String^ dificultad;
	int numero_actividad;
	int total_actividades;
	bool actividad_hecha;
	String^ problema;
	String^ nivel_actuacion;
	vector<String^> habilidades;
	vector<String^> dificultades;
	vector<String^> historialNivActuacion;
	Usuario^ usuario_anterior;

};


#endif // !USUARIO_H
