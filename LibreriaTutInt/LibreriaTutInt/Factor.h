#pragma once
#include <cliext/vector>

using namespace cliext;
using System::String;

ref class Factor
{
public:
#pragma region Constructor y Destructor
	Factor(String^ _nombre, vector<String^> _rangos, double _peso);
	~Factor();
#pragma endregion
#pragma region Gets & Sets
	String^ getNombre();
	vector<String^> getRangos();
	double getPeso();
	String^ getNivelObtenido();
	void setNombre(String^ _nombre);
	void setRangos(vector<String^> _rangos);
	void setPeso(double _peso);
	void setNivelObtenido(String^ _nivelObtenido);
#pragma endregion

private:
	String^ nombre;
	vector<String^> rangos;
	double peso;
	String^ nivelObtenido;
};
