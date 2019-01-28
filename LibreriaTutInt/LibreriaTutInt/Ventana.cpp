#include "Ventana.h"
#include "Conector.h"
#include "BaseDeConocimiento.h"
#include "MotorDeInferencia.h"
#include "Hecho.h"
#include "LeerArchivo.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;
[STAThread]
void Main()
{

	LeerArchivo^ archivo = gcnew LeerArchivo("C:/Users/felip/source/repos/Libreria/LibreriaTutInt/LibreriaTutInt/Base_de_conocimiento/Base_de_conocimiento.txt"); //Ruta de la base de conocimiento original
	archivo->set_nombreArchivo_bcUsuario("bcPipe.txt"); //Nombre del archivo que va a ser creado para el usuario
	archivo->ingresarReglas_BC();

	Conector^ conector = archivo->obtenerConector();

	BaseDeConocimiento^ baseConocimiento = conector->obtenerBaseDeConocimiento();

	BaseDeHechos^ baseHechos = conector->obtenerBaseDeHechos();

	baseHechos->agregarHechos(gcnew Hecho("h", gcnew Argumento("7"), VERDADERO));
	baseHechos->agregarHechos(gcnew Hecho("h", gcnew Argumento("8"), VERDADERO));

	MotorDeInferencia^ motorInferencia = gcnew MotorDeInferencia(baseHechos, baseConocimiento);

	Hecho^ resultado = nullptr;

	resultado = motorInferencia->ejecutar("2", ENCADENAMIENTO_ADELANTE);
	String^ h = "";
	if (motorInferencia->getTerminoInferencia())
	{
		h = resultado->getArgumento()->getNombreArgumento();
		baseHechos->borrarHechos();
	}

	MessageBox::Show(h);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	LibreriaTutInt::Ventana form;
	Application::Run(%form);
}