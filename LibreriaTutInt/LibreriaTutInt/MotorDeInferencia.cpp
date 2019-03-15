#include "MotorDeInferencia.h"

MotorDeInferencia::MotorDeInferencia(BaseDeHechos ^ baseHechos, BaseDeConocimiento ^ baseConocimiento)
{
	this->baseConocimiento = baseConocimiento;
	this->baseHechos = baseHechos;
	this->detenerInferencia = false;
	this->terminoInferencia = false;
	this->nivel = 0;
}

MotorDeInferencia::~MotorDeInferencia()
{
	delete this->baseConocimiento;
	delete this->baseHechos;
}

Hecho ^ MotorDeInferencia::encadenamientoHaciaAdelante(String ^ hecho)
{
	ArrayList ^ conjuntoConflicto = gcnew ArrayList();
	Regla ^ reglaActual = nullptr;
	bool cambio = true;
	desmarcarReglas();

	while (baseConocimiento->getReglasMarcadas() < baseConocimiento->getNumeroReglas() && cambio)
	{
		for (int x = 0; x < baseConocimiento->getNumeroReglas(); x++)
		{
			reglaActual = baseConocimiento->obtenerRegla(x);
			if (!reglaActual->getMarcada())
			{
				bool reglaComprobable = true;
				for (int y = 0; y < reglaActual->getNumeroCondiciones(); y++)
				{
					Hecho ^ condicion = reglaActual->getCuerpo()[y];
					if (baseHechos->existeHecho(condicion))
					{
						int estadoRegla = baseHechos->estadoHecho(condicion);
						if (estadoRegla == FALSO)
						{
							if (!reglaActual->getMarcada())
							{
								reglaActual->setMarcada(true);
								int valor = baseConocimiento->getReglasMarcadas();
								baseConocimiento->setReglasMarcadas(valor++);
							}
							reglaComprobable = false;
						}
						else if (estadoRegla == INDETERMINADO)
						{
							reglaComprobable = false;
						}
					}
					else
					{
						reglaComprobable = false;
					}
				}
				if (reglaComprobable)
				{
					conjuntoConflicto->Add(reglaActual);
				}
			}
		}
		Regla ^reglaMasCondiciones = nullptr;
		int numeroCondiciones = 0;
		reglaActual = nullptr;
		for (int z = 0; z != conjuntoConflicto->Count; z++)
		{
			reglaActual = (Regla^)conjuntoConflicto[z];
			if (reglaActual->getNumeroCondiciones() > numeroCondiciones)
			{
				reglaMasCondiciones = reglaActual;
				numeroCondiciones = reglaActual->getNumeroCondiciones();
			}
		}
		conjuntoConflicto->Clear();

		if (reglaMasCondiciones != nullptr)
		{
			reglaMasCondiciones->getCabeza()->setEstado(VERDADERO);
			baseHechos->agregarHechos(reglaMasCondiciones->getCabeza());
			reglaMasCondiciones->setMarcada(true);
			int valor = baseConocimiento->getReglasMarcadas();
			baseConocimiento->setReglasMarcadas(valor++);
			if (reglaMasCondiciones->getCabeza()->getRelacion() == hecho)
			{
				reglaInferida = reglaMasCondiciones;
				return reglaMasCondiciones->getCabeza();
			}
		}
	}
	return nullptr;
}

Hecho ^ MotorDeInferencia::encadenamientoHaciaAtras(Hecho ^ hechoMeta)
{
	if (baseHechos->existeHecho(hechoMeta))
	{
		hechoMeta->setEstado(baseHechos->estadoHecho(hechoMeta));
		return hechoMeta;
	}

	BaseDeConocimiento ^ conjuntoConflicto = gcnew BaseDeConocimiento();
	for (int x = 0; x < baseConocimiento->getNumeroReglas(); x++)
	{
		Regla ^reglaActual = baseConocimiento->obtenerRegla(x);
		if (reglaActual->getCabeza() == hechoMeta)
		{
			conjuntoConflicto->agregarRegla(reglaActual);
		}
	}

	if (conjuntoConflicto->getNumeroReglas() > 0)
	{
		Regla ^reglaActual = nullptr;
		Hecho ^resultado = nullptr;
		int contadorFalso = 0;
		for (int x = 0; x < conjuntoConflicto->getNumeroReglas(); x++)
		{
			reglaActual = conjuntoConflicto->obtenerRegla(x);
			bool verdadero = true;
			bool indeterminado = false;
			bool reglaFalsa = false;
			int tam = reglaActual->getCuerpo().size();
			for (int y = 0; y < tam && !reglaFalsa; y++)
			{
				if (baseHechos->existeHecho(reglaActual->getCuerpo()[y]))
				{
					if (baseHechos->estadoHecho(reglaActual->getCuerpo()[y]) == FALSO)
					{
						reglaFalsa = true;
						verdadero = false;
						hechoMeta->setEstado(FALSO);
						baseHechos->agregarHechos(hechoMeta);
					}
				}
			}
			tam = reglaActual->getCuerpo().size();
			for (int y = 0; y < tam && !reglaFalsa; y++)
			{
				nivel++;
				resultado = encadenamientoHaciaAtras(reglaActual->getCuerpo()[y]);
				nivel--;
				if (resultado->getEstado() == FALSO)
				{
					verdadero = false;
					y = reglaActual->getCuerpo().size();
					hechoMeta->setEstado(FALSO);
					baseHechos->agregarHechos(hechoMeta);
				}
				else if (resultado->getEstado() == INDETERMINADO)
				{
					indeterminado = true;
					y = reglaActual->getCuerpo().size();
				}
			}
			if (verdadero && !indeterminado)
			{
				hechoMeta->setEstado(VERDADERO);
				baseHechos->agregarHechos(hechoMeta);
				return hechoMeta;
			}
			else if (!verdadero && !indeterminado)
			{
				hechoMeta->setEstado(FALSO);
				baseHechos->agregarHechos(hechoMeta);
				contadorFalso++;
			}
		}
		if (contadorFalso == conjuntoConflicto->getNumeroReglas())
		{
			hechoMeta->setEstado(FALSO);
			baseHechos->agregarHechos(hechoMeta);
			return hechoMeta;
		}
	}
	baseHechos->agregarHechos(hechoMeta);
	return hechoMeta;
}

Hecho ^ MotorDeInferencia::ejecutar(String ^ objetivo, int encadenamiento)
{
	if (encadenamiento == ENCADENAMIENTO_ATRAS)
	{
		Regla ^ regla = gcnew Regla();
		ArrayList ^ reglasRestantes = gcnew ArrayList();
		terminoInferencia = false;

		for (int i = 0; i < baseConocimiento->getNumeroReglas(); i++)
		{
			if (baseConocimiento->obtenerRegla(i)->getCabeza()->getRelacion()->ToString() == objetivo)
			{
				reglasRestantes->Add(baseConocimiento->obtenerRegla(i));
			}
		}

		while (reglasRestantes->Count > 0)
		{
			for (int i = 0; i < reglasRestantes->Count; i++)
			{
				regla = (Regla^)reglasRestantes[i];
				regla->setHechosConfirmados(0);
				for (int j = 0; j < regla->getNumeroCondiciones(); j++)
				{
					if (baseHechos->existeHecho(regla->getCuerpo()[j]))
					{
						int valor = regla->getHechosConfirmados();
						valor++;
						regla->setHechosConfirmados(valor);
					}
				}
			}
			Regla ^reglaMaximo = nullptr;
			double valorMaximo = -1;
			for (int it = 0; it < reglasRestantes->Count; it++)
			{
				regla = (Regla^)reglasRestantes[it];
				if (valorMaximo < regla->getPorcentajeHechosConfirmados())
				{
					reglaMaximo = regla;
					valorMaximo = regla->getPorcentajeHechosConfirmados();
				}
			}
			desmarcarReglas();
			nivel = 0;
			Hecho ^hechoResultado = encadenamientoHaciaAtras(reglaMaximo->getCabeza());
			if (hechoResultado->getEstado() == VERDADERO)
			{
				terminoInferencia = true;
				reglaInferida = reglaMaximo;
				return hechoResultado;
			}
			if (reglaMaximo != nullptr)
			{
				reglasRestantes->Remove(reglaMaximo);
			}
		}
		terminoInferencia = true;
		Hecho ^indeterminado = gcnew Hecho(objetivo, gcnew Argumento("X"), INDETERMINADO);
		return indeterminado;
	}
	else
	{
		Hecho ^hechoResultado = encadenamientoHaciaAdelante(objetivo);
		if (hechoResultado != nullptr && hechoResultado->getEstado() == VERDADERO)
		{
			terminoInferencia = true;
			return hechoResultado;
		}
	}
	terminoInferencia = true;
	Hecho ^ indeteriminado = gcnew Hecho(objetivo, gcnew Argumento("X"), INDETERMINADO);
	return indeteriminado;										// No se encontro
}

void MotorDeInferencia::desmarcarReglas()
{
	Regla ^reglaActual = nullptr;
	for (int x = 0; x < baseConocimiento->getNumeroReglas(); x++)
	{
		reglaActual = baseConocimiento->obtenerRegla(x);
		if (reglaActual->getMarcada())
		{
			reglaActual->setMarcada(false);
		}
	}
}

Regla ^ MotorDeInferencia::getReglaInferida()
{
	return this->reglaInferida;
}

bool MotorDeInferencia::getTerminoInferencia()
{
	return this->terminoInferencia;
}

void MotorDeInferencia::setDetenerInferencia(bool value)
{
	this->detenerInferencia = value;
}


