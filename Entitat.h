#pragma once
#include <string>

using namespace std;

class Entitat
{
public:
	
	string getNom() const { return m_nom;}
	string getCodi() const { return m_codiIdentificatiu;}
	void setNom(string nom) { m_nom = nom; }
	void setCodi(string codi) { m_codiIdentificatiu = codi; }
protected:
	Entitat() {};
	Entitat(string nom, string codiIdentificatiu) { m_nom = nom; m_codiIdentificatiu = codiIdentificatiu; }
	string m_nom;
	string m_codiIdentificatiu;

};