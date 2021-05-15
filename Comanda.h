#pragma once
#include <vector>

#include "Bicicleta.h"
#include "Data.h"

/**
* Entrada que agrupa los datos de cada pedido. Contiene el tipo, la cantidad y el modelo.
**/
struct lineaComanda{
	TipusBicicleta tipus;
	int m_quantitat;
	string m_model;
};

/**
* Clase que almacena el pedido y los datos relacionados con �l.
* Una comanda debe de ser capaz de saber el totl de bicicletas pedidas, la fecha de entrega y el coste asociado a la misma.
**/
class Comanda
{
public:

	Comanda(const Data& entregaPrevista, vector<lineaComanda>& comanda)
	{
		m_entregaPrevista = entregaPrevista;

		for (int i = 0; i < comanda.size(); i++)
		{
			if ((comanda[i].m_quantitat >= 0) && (comanda[i].m_model != ""))
			{
				m_llista_comanda.push_back(comanda[i]);
			}
		}
	}
	int getTotalBicicletes() const { return m_totalBicicletes; }
	void setTotalBicicletas(const int& bicicletes) { m_totalBicicletes = bicicletes; }
	Data getDataEntregaPrevista() const { return m_entregaPrevista; }
	float getCostTotal() 
	{
		float count = 0.0;
		for (int i = 0; i < m_llista_comanda.size(); i++)
		{
			if (m_llista_comanda[i].tipus == TipusBicicleta::INFANTIL)
			{
				count += float(m_llista_comanda[i].m_quantitat) * 100.0;
			}
			if (m_llista_comanda[i].tipus == TipusBicicleta::MTB)
			{
				count += float(m_llista_comanda[i].m_quantitat) * 200.0;
			}
			if (m_llista_comanda[i].tipus == TipusBicicleta::CARRETERA)
			{
				count += float(m_llista_comanda[i].m_quantitat) * 250.0;
			}

		}
		m_costTotal = count;
		return m_costTotal;
	}
	vector<lineaComanda> getLlistaComanda() const
	{
		return m_llista_comanda;
	}


private:
	vector<lineaComanda> m_llista_comanda;

	int m_totalBicicletes;
	Data m_entregaPrevista;
	float m_costTotal;
};
