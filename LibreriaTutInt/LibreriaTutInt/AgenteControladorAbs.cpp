#include "AgenteControladorAbs.h"


AgenteControladorAbs::AgenteControladorAbs(Usuario ^ _usuario, String^ _nombreArchivo)
{
	usuario = _usuario;
	direccion = _nombreArchivo;
	archivo = gcnew LeerArchivo(direccion);
	archivo->set_nombreArchivo_bcUsuario("Pipe.txt");
	archivo->ingresarReglas_BC();
	conector = archivo->obtenerConector();
	percepciones = gcnew Percepciones();

}

AgenteControladorAbs::~AgenteControladorAbs()
{
	delete usuario;
	delete conector;
}


