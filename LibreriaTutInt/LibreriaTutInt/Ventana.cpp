#include "Ventana.h"
#include "LeerArchivo.h"
#include "Conector.h"
#include "Percepciones.h"
#include "AgenteAprendizaje.h"

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Threading;

[STAThread]
void Main()
{
	LeerArchivo ^ archivo = gcnew LeerArchivo("Base_de_conocimiento/baseConocimiento-opcionUno.txt");
	archivo->set_nombreArchivo_bcUsuario("baseConocimiento_Cony.txt");
	archivo->ingresarReglas_BC();

	Conector ^ conector = archivo->obtenerConector();
	Percepciones ^ percepciones = gcnew Percepciones();

	/********************* PRIMERA ACTIVIDAD **********************************/
	MessageBox::Show("PRIMERA ACTIVIDAD");
	percepciones->setNivelDeLogro("Logrado");
	percepciones->setDificultad("Basica");

	AgenteAprendizaje ^ agenteAprende = gcnew AgenteAprendizaje(conector, percepciones);

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
	percepciones->setNivelDeLogro("No_Logrado");
	percepciones->setDificultad("Basica");

	agenteAprende->setPorcentajeActuacion(0);
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

	agenteAprende->setPorcentajeActuacion(0);
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