#include "Ventana.h"
#include "LeerArchivo.h"
#include "Conector.h"
#include "Percepciones.h"
#include "AgenteAprendizaje.h"
#include "Factor.h"
#include "ConjuntoFactores.h"
#include <cliext/vector>

using namespace cliext;
using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Threading;

[STAThread]
void Main()
{
	LeerArchivo ^ archivo = gcnew LeerArchivo("Base_de_conocimiento/baseConocimiento-opcionDos.txt");
	archivo->set_nombreArchivo_bcUsuario("baseConocimiento_Cony.txt");
	archivo->ingresarReglas_BC();

	Conector ^ conector = archivo->obtenerConector();
	Percepciones ^ percepciones = gcnew Percepciones();

	/********************* PRIMERA ACTIVIDAD **********************************/
	MessageBox::Show("PRIMERA ACTIVIDAD");
	percepciones->setNivelDeLogro("Logrado");
	percepciones->setDificultad("Basica");

	// Se inicializan los factores 
	ConjuntoFactores ^ factores = gcnew ConjuntoFactores();

	vector<String^> factorUno;
	factorUno.push_back("Logrado");
	factorUno.push_back("Medianamente_Logrado");
	factorUno.push_back("No_Logrado");

	vector<String^> factorDos;
	factorDos.push_back("Bueno");
	factorDos.push_back("Regular");
	factorDos.push_back("Malo");

	factores->agregarFactor(gcnew Factor("NivelDeLogro", factorUno, 0.55));
	factores->agregarFactor(gcnew Factor("Motivacion", factorDos, 0.15));
	factores->agregarFactor(gcnew Factor("Eficacia", factorDos, 0.15));
	factores->agregarFactor(gcnew Factor("Autonomia", factorDos, 0.15));

	factores->obtenerFactor("NivelDeLogro")->setNivelObtenido("Logrado");
	factores->obtenerFactor("Motivacion")->setNivelObtenido("Malo");
	factores->obtenerFactor("Eficacia")->setNivelObtenido("Malo");
	factores->obtenerFactor("Autonomia")->setNivelObtenido("Malo");

	MessageBox::Show("Factor 1: " + factores->obtenerFactor(0)->getNombre() + " - " + factores->obtenerFactor(0)->getNivelObtenido() +
		"\nFactor 2: " + factores->obtenerFactor(1)->getNombre() + " - " + factores->obtenerFactor(1)->getNivelObtenido() +
		"\nFactor 3: " + factores->obtenerFactor(2)->getNombre() + " - " + factores->obtenerFactor(2)->getNivelObtenido() +
		"\nFactor 4: " + factores->obtenerFactor(3)->getNombre() + " - " + factores->obtenerFactor(3)->getNivelObtenido());

	AgenteAprendizaje ^ agenteAprende = gcnew AgenteAprendizaje(conector, percepciones, factores);
	agenteAprende->setMinimoActuacion(50);
	agenteAprende->setMaximoActuacion(80);
	agenteAprende->determinarElementoActuacion();

	MessageBox::Show("Nivel Actuacion: " + percepciones->getNivelDeActuacion() +
		"\nTotal Actuacion: " + percepciones->getTotalActuacion() +
		"\nProgreso: " + percepciones->getProgresoActual() +
		"\nContador Alto: " + percepciones->getContadorAlto() +
		"\nContador Medio: " + percepciones->getContadorMedio() +
		"\nContador Bajo: " + percepciones->getContadorBajo());
	if (percepciones->getProblemaGenerado() != nullptr)
	{
		MessageBox::Show("Problema Generado: " + percepciones->getProblemaGenerado()->getCabeza()->getArgumento()->getNombreArgumento());
	}
	else
	{
		MessageBox::Show("Problema Generado: null");
	}

	/********************* SEGUNDA ACTIVIDAD **********************************/
	MessageBox::Show("SEGUNDA ACTIVIDAD");
	percepciones->setNivelDeLogro("Logrado");
	percepciones->setDificultad("Basica");

	factores->obtenerFactor("NivelDeLogro")->setNivelObtenido("Logrado");
	factores->obtenerFactor("Motivacion")->setNivelObtenido("Malo");
	factores->obtenerFactor("Eficacia")->setNivelObtenido("Malo");
	factores->obtenerFactor("Autonomia")->setNivelObtenido("Malo");

	delete agenteAprende;
	agenteAprende = gcnew AgenteAprendizaje(conector, percepciones, factores);
	agenteAprende->setMinimoActuacion(50);
	agenteAprende->setMaximoActuacion(80);

	agenteAprende->determinarElementoActuacion();

	MessageBox::Show("Nivel Actuacion: " + percepciones->getNivelDeActuacion() +
		"\nTotal Actuacion: " + percepciones->getTotalActuacion() +
		"\nProgreso: " + percepciones->getProgresoActual() +
		"\nContador Alto: " + percepciones->getContadorAlto() +
		"\nContador Medio: " + percepciones->getContadorMedio() +
		"\nContador Bajo: " + percepciones->getContadorBajo());
	if (percepciones->getProblemaGenerado() != nullptr)
	{
		MessageBox::Show("Problema Generado: " + percepciones->getProblemaGenerado()->getCabeza()->getArgumento()->getNombreArgumento());
	}
	else
	{
		MessageBox::Show("Problema Generado: null");
	}


	/********************* TERCERA ACTIVIDAD **********************************/
	MessageBox::Show("TERCERA ACTIVIDAD");
	percepciones->setNivelDeLogro("No_Logrado");
	percepciones->setDificultad("Basica");

	factores->obtenerFactor("NivelDeLogro")->setNivelObtenido("Logrado");
	factores->obtenerFactor("Motivacion")->setNivelObtenido("Malo");
	factores->obtenerFactor("Eficacia")->setNivelObtenido("Malo");
	factores->obtenerFactor("Autonomia")->setNivelObtenido("Malo");

	delete agenteAprende;
	agenteAprende = gcnew AgenteAprendizaje(conector, percepciones, factores);
	agenteAprende->setMinimoActuacion(50);
	agenteAprende->setMaximoActuacion(80);
	agenteAprende->determinarElementoActuacion();

	MessageBox::Show("Nivel Actuacion: " + percepciones->getNivelDeActuacion() +
		"\nTotal Actuacion: " + percepciones->getTotalActuacion() +
		"\nProgreso: " + percepciones->getProgresoActual() +
		"\nContador Alto: " + percepciones->getContadorAlto() +
		"\nContador Medio: " + percepciones->getContadorMedio() +
		"\nContador Bajo: " + percepciones->getContadorBajo());
	if (percepciones->getProblemaGenerado() != nullptr)
	{
		MessageBox::Show("Problema Generado: " + percepciones->getProblemaGenerado()->getCabeza()->getArgumento()->getNombreArgumento());
	}
	else
	{
		MessageBox::Show("Problema Generado: null");
	}


	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	LibreriaTutInt::Ventana form;
	Application::Run(%form);
}