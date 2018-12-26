#pragma once

using namespace System;

ref class Argumento
{
public:
#pragma region Constructores y Destructores
	Argumento();
	Argumento(String^ nombre);
	~Argumento();
#pragma endregion
#pragma region Get y Sets
	String^ getNombreArgumento();
	void setNombreArg(String^ nombre);
#pragma endregion
#pragma region Metodos
	bool operator==(Argumento^ arg);
	bool operator!=(Argumento^ arg);
	bool Equals(Argumento^ arg);
#pragma endregion
private:
	String^ argumento;
};

