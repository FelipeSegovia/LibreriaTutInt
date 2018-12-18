#pragma once

#include "Argumento.h"
#include <cliext/vector>

using namespace System;
using namespace cliext;


const int VERDADERO = 0;
const int FALSO = 1;
const int INDETERMINADO = 2;

ref class Hecho
{
public:
#pragma region Constructores y Destructor
	Hecho();
	Hecho(String^ predicado, vector<Argumento^> args, int estado);
	Hecho(String^ predicado, vector<Argumento^> args);
	Hecho(String^ predicado, Argumento^ args, int estado);
	Hecho(String^ predicado, Argumento^ args);
	~Hecho();
#pragma endregion
#pragma region Gets && Sets
	String^ getRelacion();
	void setRelacion(String^ relacion);
	vector<Argumento^> getArgumento();
	void setArgumento(Argumento^ arg);
	int getNumeroArgumentos();
	int getEstado();
	void setEstado(int estado);
	String^ getEstadoTexto();
	bool getPermanente();
	void setPermanente(bool permanente);
#pragma endregion
#pragma region Metodos
	bool operator==(Hecho^ h2);
	bool operator!=(Hecho^ h2);
	bool Equals(Hecho^ h2);
	Hecho% operator=(const Hecho% h);
#pragma endregion

private:

	String^ predicado;
	vector<Argumento^> argumentos;
	int estado;
	bool permamente = false;


};

