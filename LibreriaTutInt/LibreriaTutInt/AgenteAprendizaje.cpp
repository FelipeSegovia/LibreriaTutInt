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
	String ^ nivelLogro = percepciones->getNivelDeLogro();

	conector->agregarHecho(gcnew Hecho("nivelLogro", gcnew Argumento(nivelLogro), VERDADERO));
	String ^ argumentoLogro = conector->ejecutarMotorInferencia("valorLogro", 1);

	double valorLogro = System::Convert::ToDouble(argumentoLogro->ToString());

	// Si hubieran otros factores, sería la suma de cada valor * un peso otorgado
	porcentajeActuacion = valorLogro;

	// Obtener nivel de actuacion
	if (porcentajeActuacion < 50) {
		conector->agregarHecho(gcnew Hecho("rangoActuacion", gcnew Argumento("0-49"), VERDADERO));
	}
	else if (porcentajeActuacion >= 50 && porcentajeActuacion < 80) {
		conector->agregarHecho(gcnew Hecho("rangoActuacion", gcnew Argumento("50-79"), VERDADERO));
	}
	else if (porcentajeActuacion >= 80) {
		conector->agregarHecho(gcnew Hecho("rangoActuacion", gcnew Argumento("80-100"), VERDADERO));

	}

	String ^ nivelActuacion = conector->ejecutarMotorInferencia("nivelActuacion", 1);
	percepciones->setNivelDeActuacion(nivelActuacion);
}

void AgenteAprendizaje::obtenerNivelActuacionDificultad()
{
	// Obtener valor logro obtenido
	String ^ nivelLogro = percepciones->getNivelDeLogro();

	conector->agregarHecho(gcnew Hecho("nivelLogro", gcnew Argumento(nivelLogro), VERDADERO));
	String ^ argumentoLogro = conector->ejecutarMotorInferencia("valorLogro", 1);

	double valorLogro = System::Convert::ToDouble(argumentoLogro);


	// Obtener valor dificultad
	conector->agregarHecho(gcnew Hecho("dificultad", gcnew Argumento(percepciones->getDificultad()), VERDADERO));
	conector->agregarHecho(gcnew Hecho("nivelLogro", gcnew Argumento(nivelLogro), VERDADERO));
	String ^ argumentoDificultad = conector->ejecutarMotorInferencia("valorDificultad", 1);

	double valorDificultad = System::Convert::ToDouble(argumentoDificultad);

	porcentajeActuacion = (valorLogro * 0.8) + (valorDificultad * 0.2);

	// Obtener nivel de actuacion
	if (porcentajeActuacion < 50) {
		conector->agregarHecho(gcnew Hecho("rangoActuacion", gcnew Argumento("0-49"), VERDADERO));
	}
	else if (porcentajeActuacion >= 50 && porcentajeActuacion < 80) {
		conector->agregarHecho(gcnew Hecho("rangoActuacion", gcnew Argumento("50-79"), VERDADERO));
	}
	else if (porcentajeActuacion >= 80) {
		conector->agregarHecho(gcnew Hecho("rangoActuacion", gcnew Argumento("80-100"), VERDADERO));
	}

	String ^ nivelActuacion = conector->ejecutarMotorInferencia("nivelActuacion", 1);
	reglaNivelActuacion = conector->obtenerMotorDeInferencia()->getReglaInferida();
	percepciones->setNivelDeActuacion(nivelActuacion);
}

int AgenteAprendizaje::obtenerCritica()
{
	if (percepciones->getTotalActuacion() == nullptr)			// No se ha hecho ninguna actividad
	{
		percepciones->setTotalActuacion(percepciones->getNivelDeActuacion());
		return 0;
	}
	else
	{
		// Establecer si hay progreso, con la actividad actual y la ultima realizada
		conector->agregarHecho(gcnew Hecho("nivelActual", gcnew Argumento(percepciones->getNivelDeActuacion()), VERDADERO));
		conector->agregarHecho(gcnew Hecho("nivelAnterior", gcnew Argumento(percepciones->getTotalActuacion()), VERDADERO));
		String ^ argumentoProgreso = conector->ejecutarMotorInferencia("progreso", 0);

		totalActuacionAnterior = percepciones->getTotalActuacion();

		percepciones->setProgresoActual(argumentoProgreso);

		// Segun progreso se mantiene un contador, esto ayuda luego a determinar un problema si se debe
		if (argumentoProgreso == "Mantiene")
		{
			percepciones->setTotalActuacion(percepciones->getNivelDeActuacion());
			if (percepciones->getTotalActuacion() == "Alto")
			{
				percepciones->setContadorAlto(percepciones->getContadorAlto() + 1);
				percepciones->setContadorMedio(0);
				percepciones->setContadorBajo(0);
			}
			else if (percepciones->getTotalActuacion() == "Medio")
			{
				percepciones->setContadorAlto(0);
				percepciones->setContadorMedio(percepciones->getContadorMedio() + 1);
				percepciones->setContadorBajo(0);
			}
			else
			{
				percepciones->setContadorAlto(0);
				percepciones->setContadorMedio(0);
				percepciones->setContadorBajo(percepciones->getContadorBajo() + 1);
			}
		}
		else if (argumentoProgreso == "True")
		{
			percepciones->setTotalActuacion("Alto");
			percepciones->setContadorAlto(0);
			percepciones->setContadorMedio(0);
			percepciones->setContadorBajo(0);
		}
		else if (argumentoProgreso == "False")
		{
			percepciones->setTotalActuacion("Bajo");
			percepciones->setContadorAlto(0);
			percepciones->setContadorMedio(0);
			percepciones->setContadorBajo(0);
		}

		// Segun resultado progreso, establecer si hay critica
		conector->agregarHecho(gcnew Hecho("progreso", gcnew Argumento(argumentoProgreso), VERDADERO));
		String ^ argumentoCritica = conector->ejecutarMotorInferencia("generarCritica", 0);

		if (argumentoCritica == "True")			// True = hubo progreso o retroceso
		{
			return 1;
		}
		else										// Se mantiene
		{
			return 2;
		}
	}
	return 0;
}

Regla^ AgenteAprendizaje::obtenerProblema()
{
	conector->agregarHecho(gcnew Hecho("totalActuacion", gcnew Argumento(percepciones->getTotalActuacion()), VERDADERO));
	conector->agregarHecho(gcnew Hecho("contadorAlto", gcnew Argumento(percepciones->getContadorAlto().ToString()), VERDADERO));
	conector->agregarHecho(gcnew Hecho("contadorMedio", gcnew Argumento(percepciones->getContadorMedio().ToString()), VERDADERO));
	conector->agregarHecho(gcnew Hecho("contadorBajo", gcnew Argumento(percepciones->getContadorBajo().ToString()), VERDADERO));
	String ^ argumentoProblema = conector->ejecutarMotorInferencia("generarProblema", 0);
	Regla ^ problema = conector->obtenerMotorDeInferencia()->getReglaInferida();

	return problema;
}

void AgenteAprendizaje::realimentarElementoAprendizaje()
{
	// Cuanto aprendizaje (valor) hubo segun progreso o retroceso
	conector->agregarHecho(gcnew Hecho("progreso", gcnew Argumento(percepciones->getProgresoActual()), VERDADERO));
	conector->agregarHecho(gcnew Hecho("nivelActual", gcnew Argumento(percepciones->getNivelDeActuacion()), VERDADERO));
	conector->agregarHecho(gcnew Hecho("nivelAnterior", gcnew Argumento(totalActuacionAnterior), VERDADERO));
	String ^ argumentoAprendizaje = conector->ejecutarMotorInferencia("aprendizaje", 0);

	// Cambiar peso que tiene la regla que se disparo para el problema
	int valorAprendizaje = System::Convert::ToInt32(argumentoAprendizaje);
	int pesoActual = conector->obtenerBaseDeConocimiento()->obtenerRegla(percepciones->getProblemaGenerado())->getPeso();
	int total = pesoActual + valorAprendizaje;
	conector->obtenerBaseDeConocimiento()->obtenerRegla(percepciones->getProblemaGenerado())->setPeso(total);

	// Cambiar peso a las reglas que conllevan el problema generado
	int pesoNivelActuacion = conector->obtenerBaseDeConocimiento()->obtenerRegla(reglaNivelActuacion)->getPeso();
	int totalNivelActuacion = pesoNivelActuacion + valorAprendizaje;
	conector->obtenerBaseDeConocimiento()->obtenerRegla(reglaNivelActuacion)->setPeso(totalNivelActuacion);
}

void AgenteAprendizaje::determinarElementoActuacion()
{
	if (percepciones->getDificultad() != nullptr)
	{
		obtenerNivelActuacionDificultad();
	}
	else {
		obtenerNivelActuacion();
	}

	int critica = obtenerCritica();

	if (critica == 0)					// No hay critica, por ser primera actividad realizada
	{
		percepciones->setProblemaGenerado(nullptr);
	}
	else if (critica == 1)				// Hay critica
	{
		realimentarElementoAprendizaje();
		percepciones->setProblemaGenerado(nullptr);
	}
	else if (critica == 2)				// No hay critica
	{
		determinarProgresoMedio();
		Regla ^ problema = obtenerProblema();
		percepciones->setProblemaGenerado(problema);
	}
}

void AgenteAprendizaje::determinarProgresoMedio()
{
	if (percepciones->getContadorAlto() == 3)
	{
		percepciones->setContadorAlto(2);
	}
	else if (percepciones->getContadorBajo() == 3)
	{
		percepciones->setContadorBajo(2);
	}
	else if (percepciones->getContadorMedio() >= 2)
	{
		percepciones->setContadorMedio(2);
		if (porcentajeActuacion < 64)
		{
			percepciones->setTotalActuacion("Medio_Bajo");
		}
		else
		{
			percepciones->setTotalActuacion("Medio_Alto");
		}
	}
}

Regla ^ AgenteAprendizaje::getActuacionObtenida()
{
	return reglaNivelActuacion;
}

/*

- En determinarElementoActuacion, se decide si debe usar obtenerNivelActuacion o obtenerNivelActuacionDificultad, por lo que el desarrollador
no debe hacer nada.
- Para el obtenerCritica se necesita saber si ya se realizó actividades antes, para eso se toma en cuenta el total actuacion, este lo debe dar
antes el desarrollador, si se inicio sesion nuevamente, se utiliza percepciones->setTotal_actuacion() (es un String)
- Tomar en cuenta que cuando se inicie nuevamente, debe inicializar la cantidad que hay de cada contador de progreso (alto, medio, bajo) si
es el caso que ya ha realizado alguna actividad

*/