#include "AgenteAprendizaje.h"

AgenteAprendizaje::AgenteAprendizaje(Conector ^ conector, Percepciones ^ percepciones)
{
	this->conector = conector;
	this->percepciones = percepciones;
}

AgenteAprendizaje::~AgenteAprendizaje()
{
	delete conector;
	delete percepciones;
}

void AgenteAprendizaje::obtenerNivelActuacion()
{
	String ^ nivelLogro = percepciones->getNivel_de_logro();

	double valorLogro;
	if (nivelLogro == "Logrado")
	{
		valorLogro = 99.9;
	}
	else if (nivelLogro == "Medianamente_Logrado")
	{
		valorLogro = 66.6;
	}
	else {
		valorLogro = 33.3;
	}


}

int AgenteAprendizaje::obtenerCritica()
{
	return 0;
}

Regla^ AgenteAprendizaje::obtenerProblema()
{
	return nullptr;
}

void AgenteAprendizaje::realimentarElementoAprendizaje()
{

}

void AgenteAprendizaje::determinarElementoActuacion()
{

}