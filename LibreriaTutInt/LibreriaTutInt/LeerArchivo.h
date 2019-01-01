#pragma once

#include "Argumento.h"
#include "Hecho.h"
#include "BaseDeConocimiento.h"
#include "Regla.h"

using System::String;
using namespace System::IO;

ref class LeerArchivo
{
public:
	LeerArchivo();
	LeerArchivo(String^ dir_bc_original);
	~LeerArchivo();
	void ingresarReglasBC_usuario();
	void ingresarReglas_BC();
	void set_nombreArchivo_bcUsuario(String^ nombreArchivo_bcUsuario);
	void set_direccion_bcOriginal(String^ dir_bc);
private:
	String^ obtenerNombreBC_usuario();
	String^ obtenerDireccion_bc_Usuario();
private:
	String^ dir_bc_original;
	String^ nombre_bc_usuario;
	String^ direccion_bc_usuario;
	BaseDeConocimiento^ baseDeConocimiento;
};

