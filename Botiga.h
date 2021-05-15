#pragma once
#include "Magatzem.h"
#include "Entitat.h"


/**
* Clase para gestionar las acciones y el estoc de cada una de las tiendas que pertenecen a la empresa.
* Las tiendas pueden solicitar a un almacen un pedido.
* Cuando solicitien un pedido "recojeran" de almacen aquellos objetos que puedan, con tal de cubrir su pedido.
* Moveran los objetos del almacen a su propio estoc interno, que estar� ordenado igual que el del almacen.
* Ademas, la tienda necesita saber su estoc total.
**/

class Botiga : public Entitat
{
public:
	Botiga() { m_nom = ""; m_codiIdentificatiu = ""; }
	Botiga(string nom, string codi) : Entitat(nom, codi) {}; // { m_nom = nom; m_codiIdentificatiu = codi; }

	~Botiga() = default;
	bool solicitaComanda(Comanda& c, Magatzem& m);
	bool solicitaComanda(Comanda& c);
	void mostraCataleg();
	int calculaStockTotal();
	map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>> getStockBotiga() const { return m_stockBotiga; }
	
	vector<Botiga*> getBotiguesProperes() { return m_veines; };
	Magatzem* getMagatzem() { return magatzem; }
	void setMatgatzem(Magatzem* m) { magatzem = m; }
	void setveinesOrdenades(vector<Botiga*> veines) 
	{ 
		m_veines = veines; 
	}

	bool solicitaBicicletaAMagatzem(const string& model, Bicicleta*& bicicleta);
	bool procesa_venda(const string& model, Bicicleta*& bicicleta);
	bool comprobaBicicletaEnStock(const string& model, Bicicleta*& bicicleta);
	bool ComprobaStockEnVeines(const string& model, Bicicleta*& bicicleta);
private:
	Magatzem* magatzem;
	vector<Botiga*> m_veines;
	map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>> m_stockBotiga;
};

