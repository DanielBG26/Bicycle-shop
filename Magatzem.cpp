#include "Magatzem.h"
#include "Empresa.h"
#include "Data.h"
#include "Proveidor.h"

#include <queue>
#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;

void Magatzem::enmagatzemarComanda(vector<Bicicleta*>& paquet, Data dataEntrada)
{

	vector<Bicicleta*> LlistaAux; // vector para ordenar auxiliar
	vector<Bicicleta*>::iterator actual; //iterador`para recorrer paquet bicis y crear el vector auxiliar
	int count = 0;
	Proveidor p;

	/////prueba magatzem/////
	vector<Bicicleta*>::iterator Fechas; //Creamos un iterador de fechas, que recorra el paquet de bicis y les añada una fecha

	//Recorremos cada uno de los modelos bicicletas y les ponemos fechas aleatorias (no del todo aleatorias que esten en este caso -10dias o +10 dias de la data proporcionada)
	for (Fechas = paquet.begin(); Fechas != paquet.end(); Fechas++)
	{
		if ((*Fechas)->getDataEntrada().getDia() == 0)
		{
			(*Fechas)->setDataEntrada(p.generaDataEnviament(dataEntrada,40));
		}
	}

	//Creamos un clon del vector bicicletas paquet, para utilizarlo para ordenarlas en el siguiente for
	for (actual = paquet.begin(); actual != paquet.end(); actual++)
	{
		LlistaAux.push_back((*actual)->clone());
	}
	//Ordenamos vector de las bicicletas por fechas
	for (int i = 0; i < paquet.size() - 1; i++)
	{
		//int s = i; //Como va buscando el mas pequeño todo el rato, estas variables es para que no mire los mas pequeños puestos anteriormente por ejemplo (3,4,5,1) lo pondria (1,4,5,3) y en la siguiente (4,5,3) seria (1,3,5,4)
		for (int s = i + 1; s < paquet.size(); s++)
		{
			if (!(paquet[i]->getDataEntrada() < paquet[s]->getDataEntrada()))
			{
				LlistaAux[i] = paquet[i]; /// Esto es para que que si encuentra una fecha anterior la guarde en auxiliar
				paquet[i] = paquet[s]; /// la fecha mayor la pone donde estaba la anterior
				paquet[s] = LlistaAux[i]; /// el auxiliar que tenia la fecha anterior la pone en la mayor

			}

		}
	}

	Empresa e;
	vector<Bicicleta*>::iterator actual2;

	actual2 = paquet.begin();

	vector<Bicicleta*> LlistaAux2;
	for (actual = paquet.begin(); actual != paquet.end(); actual++)
	{
		LlistaAux2.push_back((*actual)->clone());
	}

	for (int a = 0; a < paquet.size() - 1; a++)
	{
		int pos = -10;
		int F = 0;
		bool Change = false;
		for (int s = a + 1; s < paquet.size(); s++)
		{
			if (Change == false)
			{
				if ((paquet[a]->getModel() != paquet[s]->getModel()) && (F == 0))
				{
					pos = s;

					F++;
				}
				if ((paquet[a]->getModel() == paquet[s]->getModel()) && (F == 1))
				{
					LlistaAux2[a] = paquet[s];

					int c = s;
					for (c; c > pos; c--)
					{
						paquet[c] = paquet[c - 1];
					}
					paquet[pos] = LlistaAux2[a];
					Change = true;
				}
			}
		}

	}

	priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta> QueueBic;
	for (int i = 0; i < paquet.size(); i++)
	{
		if (i != (paquet.size() - 1))
		{
			if (paquet[i]->getModel() == paquet[i + 1]->getModel()) // Esta condicion es para cuando cambien de tipo de bicis en el vector paquet, inicializar otra vez el QueueBic
			{
				if (paquet[i]->getCodiRus() == "")
				{
					paquet[i]->setCodiRus(e.generaCodiRus(paquet[i]->getModel()));// Añadimos el codigo ruso
				}
				paquet[i]->setPreu(paquet[i]->getTipus());
				QueueBic.push(paquet[i]); // Llenamos la cola con los valores ya ordenados por fecha entrada de las bicicicletas
				m_stock[(paquet[i])->getModel()] = QueueBic; //Añadimos la bici a los contenedores m_stock por modelos
			}
			else
			{
				if (paquet[i]->getCodiRus() == "")
				{
					paquet[i]->setCodiRus(e.generaCodiRus(paquet[i]->getModel()));// Añadimos el codigo ruso
				}
				paquet[i]->setPreu(paquet[i]->getTipus());
				QueueBic.push(paquet[i]); // Llenamos la cola con los valores ya ordenados por fecha entrada de las bicicicletas
				m_stock[(paquet[i])->getModel()] = QueueBic; //Añadimos la bici a los contenedores m_stock por modelos

				QueueBic = priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>();
			}
		}
		/// Este es para hacer el ultimo
		else
		{
			if (paquet[i]->getCodiRus() == "")
			{
				paquet[i]->setCodiRus(e.generaCodiRus(paquet[i]->getModel()));// Añadimos el codigo ruso
			}
			paquet[i]->setPreu(paquet[i]->getTipus());
			QueueBic.push(paquet[i]); // Llenamos la cola con los valores ya ordenados por fecha entrada de las bicicicletas
			m_stock[(paquet[i])->getModel()] = QueueBic; //Añadimos la bici a los contenedores m_stock por modelos
		}
	}
	for (int i = 0; i < paquet.size(); i++)
	{
		Empresa::afegeixSeguiment(paquet[i]);
		Empresa::actualitzaEstat(paquet[i]->getCodiRus(), EstatBicicleta::EN_MAGATZEM, this);
	}

}

float Magatzem::procesQA(Comanda& c, vector<Bicicleta*>& paquet, Data dataActual)
{
	float costTotal = 0.0;
	//Calculamos el coste de las bicis

	int CostTotalCom = 0;

	for (int i = 0; i != c.getLlistaComanda().size(); i++)
	{
		CostTotalCom += c.getLlistaComanda()[i].m_quantitat;
	}
	c.setTotalBicicletas(CostTotalCom);


	for (int i = 0; i < paquet.size(); i++)
	{

		if ((dataActual <= paquet[i]->getDataEntrada()) && (c.getTotalBicicletes() == paquet.size())) /// cambiar
		{
			//cout << "normal " << endl;
			costTotal += paquet[i]->getPreu(); /// cambiar
		}
		else
		{
			//cout << "con descuento 10% " << endl;
			costTotal += paquet[i]->getPreu() * 1.1;
		}
	}

	return costTotal;
}

bool Magatzem::rebreComanda(Comanda& c, vector<Bicicleta*>& paquet, Data dataRecepcioPaquet)
{
	vector<Bicicleta*>::iterator Fechas; //Creamos un iterador de fechas, que recorra el paquet de bicis y les añada una fecha

	Proveidor p;
	int diesmaxim = 0;

	//Recorremos cada uno de los modelos bicicletas y les ponemos fechas aleatorias (no del todo aleatorias que esten en este caso -10dias o +10 dias de la data proporcionada)
	for (Fechas = paquet.begin(); Fechas != paquet.end(); Fechas++)
	{
		(*Fechas)->setDataEntrada(p.generaDataEnviament(dataRecepcioPaquet, diesmaxim));
	}
	
	//Llamamos a enmagatzemarComanda pasandole el paquet de bicis (que ahora ya si tiene datas) y la data dada
	enmagatzemarComanda(paquet, dataRecepcioPaquet);
	//Aqui mismo hemos sumado las bicicletas que pedian en comanda, haciendo un total de bicis del pedido (sumando todas sin importar el modelo) y añadiendolo a TotalBicicletas de la comanda.
	int suma2 = 0;
	for (int i = 0; i < c.getLlistaComanda().size(); i++)
	{
		suma2 += c.getLlistaComanda()[i].m_quantitat;
	}
	c.setTotalBicicletas(suma2);

	//mandamos el paquete de bicis y si la fecha es superior a la que toca, se le hace un descuento del 10%
	float cost = procesQA(c, paquet, dataRecepcioPaquet);

	//Miramos si el total de bicicletas es el correcte
	bool correcte = false;
	int suma = 0;


	if (paquet.size() == c.getTotalBicicletes())
	{
		correcte = true;
	}
	else
	{
		//cout << "INCORRECTO LO QUE SE HA PEDIDO Y LO QUE HA LLEGADO " << endl;
	}
	//Generamos una factura txt con el nombre comanda.txt
	generaFactura(correcte, cost, c);

	mostraCataleg();

	return correcte;
}

void Magatzem::generaFactura(bool paquetComplet, float costCorregit, Comanda& c)
{
	ofstream fs("factura.txt");
	fs << "Resum comanda." << endl;
	fs << "Dades Entitat responsable:" << endl;
	fs << "Nom: " << m_nom << endl;
	//fs << "Codi identificicatiu: " << m_codi << endl;
	fs << "Codi identificatiu: " << "Principal" << endl;
	fs << "Articles." << endl;
	if (paquetComplet == true)
	{
		for (int i = 0; i < c.getLlistaComanda().size(); i++)
		{
			if (c.getLlistaComanda()[i].tipus == TipusBicicleta::INFANTIL)
			{
				fs << string(c.getLlistaComanda()[i].m_model) << " * " << c.getLlistaComanda()[i].m_quantitat << endl << endl;
			}
			if (c.getLlistaComanda()[i].tipus == TipusBicicleta::MTB)
			{
				fs << string(c.getLlistaComanda()[i].m_model) << " * " << c.getLlistaComanda()[i].m_quantitat << endl << endl;
			}
			if (c.getLlistaComanda()[i].tipus == TipusBicicleta::CARRETERA)
			{
				fs << string(c.getLlistaComanda()[i].m_model) << " * " << c.getLlistaComanda()[i].m_quantitat << endl << endl;
			}

		}
	}
	else
	{
		fs << "El paquet no pasa els test de qualitat." << endl;
		fs << "Es redueix el cost del paquet en un 1.1" << endl;
	}

	fs << "Preu final: " << costCorregit << endl;
}

Bicicleta* Magatzem::agafaBicicletaAntiga(const string& model)
{
	map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator it;
	
	Bicicleta* b;
	
	for (it = m_stock.begin(); it != m_stock.end(); it++)
	{
		if (it->first == model)
		{
			return (it->second.top());
		}
	}
	
	return nullptr;
}

void Magatzem::mostraCataleg()
{

}