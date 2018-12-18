#pragma once

#include <cliext/vector>
#include "Hecho.h"

using namespace System;
using namespace cliext;

ref class Regla
{
public:
#pragma region Constructores y Destructor
	Regla();
	Regla(Hecho ^head, vector<Hecho^> boddy, int peso);
	Regla(Hecho^ head, vector<Hecho^> boddy);
	Regla(const Regla^ &r);
	~Regla();
#pragma endregion
#pragma region Gets y Sets
	Hecho^ getCabeza();
	vector<Hecho^> getCuerpo();
	bool getMarcada();
	int getPeso();
	int getNumeroCondiciones();
	int getHechosConfirmados();
	double getPorcentajeHechosConfirmados();
	void setCabeza(Hecho ^head);
	void setCuerpo(vector<Hecho^> boddy);
	void setMarcada(bool marca);
	void setPeso(int _peso);
	void setHechosConfirmados(int confirmados);
#pragma endregion
#pragma region Override
	bool operator == (Regla ^r2);
	bool operator != (Regla ^r2);
	bool Equals(Regla ^r1);
	Regla% operator=(const Regla% r);
#pragma endregion


private:
#pragma region Atributos
	Hecho^ cabeza;
	vector<Hecho^> cuerpo;
	bool marcada = false;
	int hechosConfirmados = 0;
	int peso;
#pragma endregion

};

