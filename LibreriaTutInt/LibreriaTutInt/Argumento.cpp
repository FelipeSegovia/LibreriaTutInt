#include "Argumento.h"

Argumento::Argumento()
{
	this->argumento = nullptr;
}

Argumento::Argumento(String ^ nombre)
{
	this->argumento = nombre;
}

Argumento::~Argumento()
{
	delete argumento;
}

String ^ Argumento::getNombreArgumento()
{
	return this->argumento;
}

void Argumento::setNombreArg(String ^ nombre)
{
	this->argumento = nombre;
}

bool Argumento::operator==(Argumento ^ arg)
{
	Object^ obj = this;
	Object^ obj2 = arg;


	if (obj == nullptr && obj2 == nullptr)
	{
		return true;
	}
	else if ((obj != nullptr && obj2 == nullptr) || (obj == nullptr && obj2 != nullptr))
	{
		return false;
	}
	else if (this->getNombreArgumento() == arg->getNombreArgumento())
	{
		return true;
	}

	return false;

}

bool Argumento::operator!=(Argumento ^ arg)
{
	Object^ obj = this;
	Object^ obj2 = arg;


	if (obj == nullptr && obj2 == nullptr)
	{
		return false;
	}
	else if ((obj != nullptr && obj2 == nullptr) || (obj == nullptr && obj2 != nullptr))
	{
		return true;
	}
	else if (this->getNombreArgumento() == arg->getNombreArgumento())
	{
		return false;
	}

	return true;
}

bool Argumento::Equals(Argumento ^ arg)
{
	if (this == arg)
	{
		return true;
	}
	return false;
}
