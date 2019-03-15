#include "LeerArchivo.h"



LeerArchivo::LeerArchivo()
{
}

LeerArchivo::LeerArchivo(String ^ dir_bc_original)
{
	this->dir_bc_original = dir_bc_original;
	conector = gcnew Conector();
}

LeerArchivo::~LeerArchivo()
{
	delete conector;
}

void LeerArchivo::ingresarReglasBC_usuario()
{
	StreamReader^ dir_bc_original = File::OpenText(this->dir_bc_original);

	String^ direccion_bc_usuario = obtenerDireccion_bc_Usuario();
	if (direccion_bc_usuario != nullptr)
	{
		StreamWriter^ insertarDatos_bc_usuario = gcnew StreamWriter(direccion_bc_usuario);
		String^ linea_leida;
		while ((linea_leida = dir_bc_original->ReadLine()) != nullptr)
		{
			insertarDatos_bc_usuario->WriteLine(linea_leida);
		}
		insertarDatos_bc_usuario->Close();
	}
	dir_bc_original->Close();
}

void LeerArchivo::ingresarReglas_BC()
{

	ingresarReglasBC_usuario();

	String^ direccion = obtenerDireccion_bc_Usuario();
	StreamReader^ archivo_bc = File::OpenText(direccion);
	String^ linea_leida;

	while ((linea_leida = archivo_bc->ReadLine()) != nullptr)
	{
		array<String^>^ separarCabeza_Cuerpo = linea_leida->Split(':');

		String^ cabeza = separarCabeza_Cuerpo[0];
		String^ cuerpo = separarCabeza_Cuerpo[1];

		String^ antecedenteCabeza = cabeza->Split('(', ')')[0];
		String^ consecuenteCabeza = cabeza->Split('(', ')')[1];

		Hecho^ hechoCabeza = gcnew Hecho(antecedenteCabeza, gcnew Argumento(consecuenteCabeza));

		array<String^>^ separar_cuerpo = cuerpo->Split(',');


		String^ antecedenteCuerpo;
		String^ consecuenteCuerpo;
		vector<Hecho^> vectHechosCuerpo;
		int pesoRegla;
		for each(String^ parteCuerpo in separar_cuerpo)
		{
			antecedenteCuerpo = parteCuerpo->Split('(', ')')[0];
			consecuenteCuerpo = parteCuerpo->Split('(', ')')[1];

			if (antecedenteCuerpo == "peso")
			{
				pesoRegla = int::Parse(consecuenteCuerpo);
			}
			else
			{
				Hecho^ hechoCuerpo = gcnew Hecho(antecedenteCuerpo, gcnew Argumento(consecuenteCuerpo));

				vectHechosCuerpo.push_back(hechoCuerpo);
			}

		}
		this->conector->agregarRegla(gcnew Regla(hechoCabeza, vectHechosCuerpo, pesoRegla));
	}
	archivo_bc->Close();
}

void LeerArchivo::set_nombreArchivo_bcUsuario(String ^ nombreArchivo_bcUsuario)
{
	this->nombre_bc_usuario = nombreArchivo_bcUsuario;
}

void LeerArchivo::set_direccion_bcOriginal(String ^ dir_bc)
{
	this->dir_bc_original = dir_bc;
}

Conector ^ LeerArchivo::obtenerConector()
{
	return this->conector;
}

String ^ LeerArchivo::obtenerNombreBC_usuario()
{
	String^ nombre;

	int contador_caracteres = 0;
	for each(char c in this->nombre_bc_usuario)
	{
		if (c == '.')
		{
			nombre = this->nombre_bc_usuario->Substring(0, contador_caracteres);
		}
		contador_caracteres++;
	}
	return nombre;
}

String ^ LeerArchivo::obtenerDireccion_bc_Usuario()
{
	this->direccion_bc_usuario = obtenerNombreBC_usuario() + "/" + this->nombre_bc_usuario;

	if (!System::IO::File::Exists(direccion_bc_usuario))
	{
		Directory::CreateDirectory(obtenerNombreBC_usuario()); //Se crea la carpeta
		FileStream^ crear_archivo = gcnew FileStream(direccion_bc_usuario, FileMode::Create);

		crear_archivo->Close();
	}

	return this->direccion_bc_usuario;
}
