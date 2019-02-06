#include "AgenteControlador.h"



AgenteControlador::AgenteControlador()
{
}

AgenteControlador::~AgenteControlador()
{
}

String^ AgenteControlador::obtenerNivelLogro()
{
	evaluador->getNivel_de_logro();
}

void AgenteControlador::evaluarActividad()
{
	evaluador = gcnew Evaluador("Pauta.txt");
	//evaluador->revisar_actividad(usuario->getHabilidad(),);
}
