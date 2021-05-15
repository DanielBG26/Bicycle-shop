#include "Graf.h"
#include <iostream>

using namespace std;


Graf::Graf(vector<Botiga*> llistaVertexs, vector<Aresta> llistaArestes)
{
	
	m_arestes.resize(llistaVertexs.size());


	for (int i = 0; i < llistaVertexs.size(); i++)
	{
		m_arestes[i].resize(llistaVertexs.size());
	}
	for (int a = 0; a < llistaVertexs.size(); a++) //fila
	{
		for (int b = 0; b < llistaVertexs.size(); b++) // columna
		{
			m_arestes[a][b] = -1;
		}
	}
	for (int c = 0; c < llistaArestes.size(); c++) // columna
	{
		m_arestes[llistaArestes[c].inici][llistaArestes[c].desti] = llistaArestes[c].pes;
		m_arestes[llistaArestes[c].desti][llistaArestes[c].inici] = llistaArestes[c].pes;
	}
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int y = 0; y < llistaVertexs.size(); y++)
	{
		m_vertexs.push_back(new Node(llistaVertexs[y]));
	}

	for (int i = 0; i < m_vertexs.size(); i++)
	{
		vector<Botiga*> veines;

		for (int s = 0; s < m_vertexs.size(); s++)
		{
			if (s != i)
			{
				veines.push_back(m_vertexs[s]->botiga);
				m_vertexs[i]->botiga->setveinesOrdenades(veines);
			}
		}
	}
}

vector<Node*> Graf::getVertexs() const
{
	
	return m_vertexs;
}

vector<vector<int>> Graf::getArestes() const
{
	return m_arestes;
}

vector<Botiga*> Graf::getBotiguesOrdenades(Node* nodeInici)
{
		vector<Botiga*> VB;
		vector<int> Vb;
		vector<int> Vb2;
		int index = -1;
		int index2 = -1;
		int index3 = -1;
		int tam = 0;


		for (int i = 0; i < m_vertexs.size(); i++)
		{

			if (m_vertexs[i]->botiga->getNom() == nodeInici->botiga->getNom())
			{
				index = i;
				tam = m_vertexs[i]->botiga->getBotiguesProperes().size();
				VB.resize(tam);
				Vb.resize(tam + 1);
			}
		}
		for (int s = 0; s < VB.size(); s++)
		{
			VB[s] = new Botiga;
		}

		////////////////////////////////////////////////////////////////////////////////////
		index2 = index;
		index3 = index;
		Vb[index] = -1;


		//Esto nos indica los nodos adjacentes a la tienda pasada en getBotiguesOrdenades // Falta los que no son adjacentes a estos
		for (int a = 0; a < tam + 1; a++)
		{
			if ((m_arestes[index][a] != -1) && (Vb[a] != -1)) //podemos añadir numero si es diferente a -1 o 0
			{
				Vb[a] = m_arestes[index][a];
			}
		}
		
		//Este debe añadir hacia la izquierda
		int tamM = tam + 1;

		if ((index <= Vb.size()) || (Vb[Vb.size()] != 0))
		{
			while (Vb[0] == 0)
			{
				for (int b = 0; b < tamM; tamM--)
				{
					if ((m_arestes[index - 1][tamM - 1] != -1) && (Vb[tamM - 1] != -1)) //podemos añadir numero si es diferente a -1 o 0
					{
						Vb[tamM - 1] = m_arestes[index - 1][tamM - 1] + Vb[tamM];
						index--;
					}
				}
			}
		}
		
		//Esto esta añadiendo hacia la derecha
		if ((index2 == 0) || (Vb[0] != 0)) //si el indice es 0 es decir es la tienda 0 la que nos pasan, por como nos dan la matriz de uniones, tenemos que ir add el index para acabar de completar sus uniones.
		{
			while (Vb[Vb.size() - 1] == 0)
			{
				for (int c = 0; c < tam + 1; c++)
				{
					if (m_arestes[index2 + 1][c] != -1) //&& (Vb[c] != -1)) //podemos añadir numero si es diferente a -1 o 0
					{
						if (Vb[c] != -1)
						{
							Vb[c] = m_arestes[index2 + 1][c] + Vb[c - 1];
							index2++;
							if (index2+1 >= m_arestes.size())
							{
								return vector<Botiga*>();
							}
						}
					}
				}
			}
		}


		Vb[index3] = 0;
		

		for (int i = 0; i < Vb.size(); i++)
		{
			if (Vb[i] != 0)
			{
				Vb2.push_back(Vb[i]);
			}
		}


		vector<int> aux;
		vector<Node*> aux2;
		vector<Botiga*> aux3;
		aux.resize(1);
		aux2.resize(1);
		aux3.resize(1);
		int a = 0;
		for (int i = 0; i < tam; i++)
		{
			VB[i] = m_vertexs[index3]->botiga->getBotiguesProperes()[a];
			a++;
		}

		int count = 0;
		for (int llena = 0; llena < Vb.size(); llena++)
		{
			if (Vb[llena] == 0)
			{
				count++;
				if (count > 1)
				{
					
					return vector<Botiga*>();
				}
				
				
			}
		}

		for (int i = 0; i < tam; i++)
		{
			for (int m = i + 1; m < tam; m++)
			{
				if (Vb2[i] > Vb2[m])
				{
					aux[0] = Vb2[i];
					Vb2[i] = Vb2[m];
					Vb2[m] = aux[0];


					aux3[0] = VB[i];
					VB[i] = VB[m];
					VB[m] = aux3[0];

				}
			}
		}

		return VB;
	}
	
	


Graf& Graf::operator=(Graf g)
{
	
	Graf s;
	return s;
}
