#include "Conector.h"

Conector::Conector()
{
	this->reglas = gcnew BaseDeConocimiento();
	this->hechos = gcnew BaseDeHechos();
}

Conector::~Conector()
{
	delete reglas;
	delete hechos;
	delete conector;
	delete motorInferencia;
}

Conector ^ Conector::obtenerConector()
{
	if (Conector::conector == nullptr)
	{
		Conector^ conector = gcnew Conector();
		return conector;
	}
	return this->conector;
}

void Conector::agregarRegla(Regla ^ regla)
{
	this->reglas->agregarRegla(regla);
}

void Conector::agregarHecho(Hecho ^ hecho)
{
	this->hechos->agregarHechos(hecho);
}

void Conector::borrarHechos()
{
	this->hechos->borrarHechos();
}

bool Conector::getLeyendoRegla()
{
	return this->leyendoRegla;
}

void Conector::inicioRegla()
{
	this->leyendoRegla = true;
}

void Conector::finRegla()
{
	this->leyendoRegla = false;
}

String ^ Conector::ejecutarMotorInferencia(String ^objetivo, int encadenamiento)
{
	motorInferencia = gcnew MotorDeInferencia(this->hechos, this->reglas);
	Hecho ^ resultado = nullptr;
	String ^ argumento;
	resultado = motorInferencia->ejecutar(objetivo, encadenamiento);
	if (motorInferencia->getTerminoInferencia()) {
		argumento = resultado->getArgumento()->getNombreArgumento();
		borrarHechos();
	}
	delete motorInferencia;

	return argumento;
}

MotorDeInferencia ^ Conector::obtenerMotorDeInferencia()
{
	return this->motorInferencia;
}

Regla ^ Conector::transformarString_A_Regla(String ^ regla)
{
	array<String^>^ separarCabeza_Cuerpo = regla->Split(':');

	String^ cabeza = separarCabeza_Cuerpo[0];
	String^ cuerpo = separarCabeza_Cuerpo[1];

	String^ antecedenteCabeza = cabeza->Split('(', ')')[0];
	String^ consecuenteCabeza = cabeza->Split('(', ')')[1];

	Hecho^ hechoCabeza = gcnew Hecho(antecedenteCabeza, gcnew Argumento(consecuenteCabeza));
	hechoCabeza->setPermanente(true);

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
			hechoCuerpo->setPermanente(true);

			vectHechosCuerpo.push_back(hechoCuerpo);
		}

	}
	return gcnew Regla(hechoCabeza, vectHechosCuerpo, pesoRegla);
}

BaseDeConocimiento ^ Conector::obtenerBaseDeConocimiento()
{
	this->reglas->ordenarMenorAMayor();
	return reglas;
}

BaseDeHechos ^ Conector::obtenerBaseDeHechos()
{
	return this->hechos;
}

void Conector::cerrarArchivo()
{
	this->reglas = gcnew BaseDeConocimiento();
	this->hechos = gcnew BaseDeHechos();
}

String ^ Conector::pasarRegla_A_String(Regla ^ regla)
{

	String^ cabezaRegla = regla->getCabeza()->getRelacion() + "(" + regla->getCabeza()->getArgumento()->getNombreArgumento() + "):-";
	String^ cuerpoRegla;

	for (int i = 0; i < regla->getCuerpo().size(); i++)
	{
		cuerpoRegla = cuerpoRegla + regla->getCuerpo()[i]->getRelacion() + "(" + regla->getCuerpo()[i]->getArgumento()->getNombreArgumento() + "),";
	}
	String^ reglaString = cabezaRegla + cuerpoRegla + "peso(" + regla->getPeso().ToString() + ")";

	return reglaString;
}
