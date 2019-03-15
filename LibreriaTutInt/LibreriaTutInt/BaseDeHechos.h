#pragma once

#include "Hecho.h"
#include <cliext/vector>

using namespace cliext;


ref class BaseDeHechos
{
public:
#pragma region Constructores y destructores
	BaseDeHechos();
	~BaseDeHechos();
#pragma endregion
#pragma region Metodos
	void agregarHechos(Hecho^ hecho);
	bool existeHecho(Hecho^ hecho);
	int estadoHecho(Hecho^ hecho);
	void borrarHechos();
#pragma endregion

private:
	vector<Hecho^>hechos;
};

