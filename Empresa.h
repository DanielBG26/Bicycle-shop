#pragma once
#include <string>

#include "Botiga.h"
#include "Comanda.h"
#include "Magatzem.h"
#include "Proveidor.h"
#include "Graf.h"
#include <iostream>
/**
 *
* La clase empresa aglutina la inforamcion para gestionar la comunicacion del almacen con el proveedor, asi como las tiendas.
* La empresa se define por un conjunto de tiendas, un almacen y un proveedor.
* La empresa realizar� pedidos al provedor y recibira una notificacion indicando si el pedido ha llegado correctamente a almacen.
* 
**/
using namespace std;

enum class EstatBicicleta {
	EN_MAGATZEM,
	EN_BOTIGA,
	VENUDA,
	RETORNADA
};

struct DadesSeguiment {
	Bicicleta* m_bicicleta;
	vector<pair<EstatBicicleta, Entitat*>> m_historic;
	DadesSeguiment() 
	{
		m_bicicleta = nullptr;
		m_historic = vector<pair<EstatBicicleta, Entitat*>>();
	}
};


class Empresa 
{
public:
	Empresa() {}
	Empresa(string name, int numBotigues, Magatzem* magatzemPrincipal, Proveidor& p)
	: m_name(name), m_numBotigues(numBotigues), m_magatzem(magatzemPrincipal), m_proveidor(p){if (numBotigues < 0) { m_numBotigues = 0; }}

	Empresa(string name, vector<Botiga*> botigues, vector<Aresta> conexionsBotigues, Magatzem* magatzemPrincipal, Proveidor& p);
	//:m_name(name), m_botigues(botigues), m_conexions(conexionsBotigues),m_magatzem(magatzemPrincipal), m_proveidor(p){}

	string getName() const { return m_name; }
	Magatzem* getMagatzem() {return m_magatzem;}

	
	vector<Botiga*>& getBotigues()
	{
		for (int a = 0; a < m_botigues.size(); a++)
		{
			if (m_botigues[a] == NULL)
			{
				m_botigues[a] = new Botiga;
			}
		}
		return m_botigues;
	}

	void setProveidor(Proveidor& proveidor) { m_proveidor = proveidor; }
	Proveidor& getProveidor() { return m_proveidor; }
	static int getSeguentCodiRus();
	bool realitzaComanda(Comanda& c, Proveidor& p);
	string static generaCodiRus(const string& model);

	bool realitzaComanda(Comanda& c);
	static bool afegeixSeguiment(Bicicleta* bicicleta);
		
	
	static bool actualitzaEstat(const string& codiRus, EstatBicicleta nouEstat, Entitat* novaEntitat);
	static bool comprobaEstatCodi(string codiRus, EstatBicicleta objectiu);
	
	
	static map<string, DadesSeguiment> getTaula() { return m_taulaSeguiment; }
	static void setTaula(map<string, DadesSeguiment> taulaSeguiment) { m_taulaSeguiment = taulaSeguiment; }
	
private:
	string m_name;
	Magatzem* m_magatzem;
	int m_numBotigues;
	vector<Botiga*> m_botigues;
	vector<Aresta> m_conexions;
	Proveidor m_proveidor;
	
	
	static map<string, DadesSeguiment>  m_taulaSeguiment;
	
};