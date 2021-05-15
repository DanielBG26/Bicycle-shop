#pragma once

#include <string>

#include "Data.h"


/**
* Enumeraciones necesarias para la creacion de bicicletas.
* Los valores son necesarios para poder realizar un control de errores eficiente.
* Si algun constructor recibe un parametro "ileagal" debeis establecer como valor por defecto
* el valor permitido mas peque�o del enum.
* 
**/

enum class TipusBicicleta
{
	INFANTIL = 100,
	MTB = 200,
	CARRETERA = 250
};

enum class Fre
{
	DISC = 0,
	RIM = 1,
};

enum class Quadre
{
	ALUMINI = 0,
	CARBONO = 1,
};

enum class Roda
{
	RODA_26 = 0,
	RODA_27 = 1,
	RODA_29 = 2,
	RODA_14 = 3,
	RODA_20 = 4,
	RODA_700 = 5,
};


enum class Talla
{
	XS = 0,
	S = 1,
	M = 2,
	L = 3,
	XL = 4,
};


/**
* Bicicleta es una clase que contiene toda la informacion relevante para definir una bicicleta generica.
* 
**/
class Bicicleta
{
public:
	virtual ~Bicicleta() {};
	string getModel() const { return m_model; }
	string getDescripcio() const { return m_descripcioModel;}
	string getCodiRus() const { return m_codiRus; }
	int getTemporada() const { return m_temporada; }
	Talla getTalla() const { return m_talla; }
	Quadre getQuadre() const { return m_quadre; }
	Roda getRoda() const { return m_roda; }
	Fre getFre() const { return m_fre; }
	TipusBicicleta getTipus() const { return m_tipus; }
	Data getDataEntrada() const { return m_dataEntradaMagatzem;}
	virtual void setModel(const string& model) final { m_model = model; }
	virtual void setDescripcio(const string& descripcio) final { m_descripcioModel = descripcio; }
	virtual void setCodiRus(const string& codirus) final { m_codiRus = codirus; }
	virtual void setTemporada(const int& temporada) final { m_temporada = temporada; }
	virtual void setTalla(const Talla& talla) final { m_talla = talla; }
	virtual void setRoda(const Roda& roda) { m_roda = roda; }
	virtual void setFre(const Fre& fre) { m_fre = fre; }
	virtual void setQuadre(const Quadre& quadre) { m_quadre = quadre; }
	virtual void setTipus(TipusBicicleta tipus) { m_tipus = tipus; }
	virtual void setPreu(TipusBicicleta cost) { m_preu = float(cost);}
	virtual float getPreu() const { return m_preu; }

	void setDataEntrada(Data d) { m_dataEntradaMagatzem = d; }

	Bicicleta* clone() { return new Bicicleta(*this); }
	bool operator<(const Bicicleta& b1) const 
	{
		if (m_dataEntradaMagatzem < b1.getDataEntrada())
		{
			return true;
		}
		return false;
	};
	
protected:
	Bicicleta();
	Bicicleta(const string& model, const string& descripcio, const int& temporada, Talla talla,Quadre quadre, Roda roda, Fre fre, TipusBicicleta tipus);
	Bicicleta(Bicicleta& b);
	virtual ostream& format(ostream& os) const { return os; }
	friend ostream& operator <<(ostream& os, const Bicicleta& b)
	{
		return os;
	}

	string m_model;
	string m_descripcioModel;
	string m_codiRus;
	int m_temporada;
	Talla m_talla;
	Quadre m_quadre;
	Roda m_roda;
	Fre m_fre;
	TipusBicicleta m_tipus;
	Data m_dataEntradaMagatzem;
	float m_preu;
	

};

struct CmpBicicleta {
	bool operator()(Bicicleta* a, Bicicleta* b) const
	{
		return b->getDataEntrada() < a->getDataEntrada();
	}

};