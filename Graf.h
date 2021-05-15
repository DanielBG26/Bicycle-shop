#pragma once
#include <limits.h>
#include "Botiga.h"
#include <algorithm>


struct Node
{
	bool visitat;
	Botiga* botiga;
	int distanciaMinima;
	Node(Botiga* b) :visitat(false), botiga(b), distanciaMinima(INT_MAX) {}
};

struct Aresta
{
	int inici, desti, pes;
};
class Graf
{
private:
	const int ARESTA_NULA = -1;

	
	int getPes(Node* inici, Node* desti) { m_inici = inici; }
	int getIndex(Node* vertex) { m_vertex = vertex; }

public:
	Graf() {};
	Graf(vector<Botiga*> llistaVertexs, vector<Aresta> llistaArestes);
	vector<Node*> getVertexs() const;
	void setArestes(const vector<vector<int>>& v) { m_arestes = v; }
	vector<vector<int>> getArestes() const;
	vector<Botiga*> getBotiguesOrdenades(Node* nodeInici);
	

	vector<vector<int>> m_arestes;
	vector<Node*> m_vertexs;
	Graf& operator=(Graf g);
	Node* m_inici;
	Node* m_desti;
	Node* m_vertex;
};
