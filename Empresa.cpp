#include "Empresa.h"
#include "Magatzem.h"
#include <string>


int valor = 0;

map<string, DadesSeguiment> Empresa::m_taulaSeguiment;

Empresa::Empresa(string name, vector<Botiga*> botigues, vector<Aresta> conexionsBotigues, Magatzem* magatzemPrincipal, Proveidor& p)
{
	m_name = name;
	m_magatzem = new Magatzem;
	m_magatzem = magatzemPrincipal;
	m_proveidor = p;
	m_conexions = conexionsBotigues;
	
	for (int a = 0; a < botigues.size(); a++)
	{
		m_botigues.push_back(botigues[a]);
		m_botigues[a]->setMatgatzem(m_magatzem);
	}
	
	for (int b = 0; b < botigues.size(); b++)
	{
		vector<Botiga*> bot;
		for (int c = 0; c < botigues.size(); c++)
		{
			if (b != c)
			{
				bot.push_back(m_botigues[c]);		
			}
		}
		m_botigues[b]->setveinesOrdenades(bot);
	}


	m_numBotigues = m_botigues.size();
}

int Empresa::getSeguentCodiRus()
{
	return valor;
}

bool Empresa::realitzaComanda(Comanda& c, Proveidor& p)
{
	bool realitzada = p.procesaComanda(c, *m_magatzem);
	return realitzada;
}

string Empresa::generaCodiRus(const string& model)
{
	string a;
	string b;

	a = to_string(getSeguentCodiRus()); //pasamos el entero que toque a string para poder sumarle al modelo
	b = model;//+"_"; // pasamos por si acaso modelo que ya era un string a b, aunque este paso no es necesario

	valor++; //una vez ya hemos puesto el numero al model aumentamos en 1 para el siguiente que venga

	return b + a;
}

bool Empresa::realitzaComanda(Comanda& c)
{
	bool realitzada = m_proveidor.procesaComanda(c, *m_magatzem);
	return false;
}

bool Empresa::afegeixSeguiment(Bicicleta* bicicleta)
{
	map<string, DadesSeguiment>::iterator it;
	DadesSeguiment Ds;
	
	map<string, DadesSeguiment> m_taulaSeguimentAux;

	Ds.m_bicicleta = bicicleta;
	

	if (bicicleta == nullptr)
	{
		return false;
	}
	
	if (bicicleta->getCodiRus() == "") 
	{
		m_taulaSeguiment[bicicleta->getCodiRus()] = Ds;
		m_taulaSeguimentAux = m_taulaSeguiment;
		return false;
	}
	else
	{
		it = m_taulaSeguiment.find(bicicleta->getCodiRus());
		if (it == m_taulaSeguiment.end())
		{
			//cout << "No esta en el map " << endl;
			m_taulaSeguiment[bicicleta->getCodiRus()] = Ds;
			m_taulaSeguimentAux = m_taulaSeguiment;
			return true;
		}
		else
		{
			//cout << "Ya esta en el map no hace falta ponerlo " << endl;
			return false;
		}		
	}

	
	
	return false;
}

bool Empresa::actualitzaEstat(const string& codiRus, EstatBicicleta nouEstat, Entitat* novaEntitat)
{
	bool actualitza = true;

	map<string, DadesSeguiment> m_taulaSeguimentAux;
	map<string, DadesSeguiment>::iterator it;
	Magatzem* m_magatzems;

	
	it = m_taulaSeguiment.find(codiRus);
	if (it == m_taulaSeguiment.end()) 
	{ 
		actualitza = false; 
	}
	else if (novaEntitat == nullptr) 
	{ 
		actualitza = false; 
	}
	else
	{
		m_taulaSeguiment[codiRus].m_historic.push_back(make_pair(nouEstat, novaEntitat));
		actualitza = true;
	}

	m_taulaSeguimentAux = m_taulaSeguiment;
	
	return actualitza;
}

bool Empresa::comprobaEstatCodi(string codiRus, EstatBicicleta objectiu)
{
	map<string, DadesSeguiment>::iterator it2;
	map<string, DadesSeguiment> m_taulaSeguimentAux;
	m_taulaSeguimentAux = m_taulaSeguiment;
	
	if (m_taulaSeguiment.size() > 1)
	{
		it2 = m_taulaSeguiment.find(codiRus);
		if (it2 == m_taulaSeguiment.end()) { return false; }
	}
	if (m_taulaSeguiment.count(codiRus) > 0)
	{
		bool flag = false;
		vector<pair<EstatBicicleta, Entitat*>> historial = m_taulaSeguiment[codiRus].m_historic;
		vector<pair<EstatBicicleta, Entitat*>>::iterator it = historial.begin();
		while (!flag && it != historial.end())
		{
			flag = (*it).first == objectiu;
			++it;
		}
		return flag;

	}
	return true;

}