#pragma once
#include "BaseDeConocimiento.h"
#include "BaseDeHechos.h"
#include "Hecho.h"
#include "Regla.h"

ref class Conector
{
public:
	Conector();
	~Conector();
	Conector^ obtenerConector();
	void agregarRegla(Regla^ regla);
	void agregarHecho(Hecho^ hecho);
	void borrarHechos();
	bool getLeyendoRegla();
	void inicioRegla();
	void finRegla();
	String ^ ejecutarMotorInferencia(String ^objetivo, int encadenamiento);
	Regla^ transformarString_A_Regla(String^ regla);
	BaseDeConocimiento^ obtenerBaseDeConocimiento();
	BaseDeHechos^ obtenerBaseDeHechos();
	void cerrarArchivo();
	String^ pasarRegla_A_String(Regla^ regla);
private:
	Conector^ conector;
	BaseDeConocimiento^ reglas;
	BaseDeHechos^ hechos;
	bool leyendoRegla = false;
};

