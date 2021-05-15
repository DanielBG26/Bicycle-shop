#pragma once

#include "Bicicleta.h"
#include <string>


enum class Categoria {
	RIGIDA = 0,
	DOBLE = 1,
};

enum class Modalitat {
	DESCENS = 0,
	ENDURO = 1,
	RALLY = 2,
	TRAIL = 3,
};


class BicicletaMTB : public Bicicleta
{
public:
	BicicletaMTB() {}
	BicicletaMTB(const string& model, string descripcio, const int& temporada, const Talla& talla, const Quadre& quadre, const Roda& roda, const Fre& fre, TipusBicicleta tipus, Categoria categoria, Modalitat modalitat, bool electrica)
	: Bicicleta(model, descripcio, temporada, talla, quadre, Roda::RODA_26, Fre::DISC, TipusBicicleta::MTB), m_categoria(categoria), m_modalitat(modalitat), m_electrica(electrica) {}
	BicicletaMTB(const BicicletaMTB&) {}
	~BicicletaMTB() {} 

	void setCategoria(const Categoria& categoria) { m_categoria = categoria; }
	Categoria getCategoria() const { return m_categoria; }
	void setModalitat(const Modalitat& modalitat) { m_modalitat = modalitat; }
	Modalitat getModalitat() const { return m_modalitat; }
	void setElectrica(const bool& electrica) { m_electrica = electrica; }
	bool getElectrica() const { return m_electrica; }
	void setRoda(const Roda& roda) override { if (roda == Roda::RODA_26 || roda == Roda::RODA_27 || roda == Roda::RODA_29) { m_roda = roda; } else { m_roda = Roda::RODA_26; } }
	void setFre(const Fre& fre) override { if (fre == Fre::DISC) { m_fre = fre; } else { m_fre = Fre::DISC; } }
	void setTipus(TipusBicicleta tipus) override { if (tipus == TipusBicicleta::MTB) { m_tipus = tipus; } else { m_tipus = TipusBicicleta::MTB; } }

	Quadre getQuadre() const { return m_quadre; }
	Roda getRoda() const { return m_roda; }
	Fre getFre() const { return m_fre; }
protected:
	ostream& format(ostream& os) const override { return os; }
private:
	Categoria m_categoria;
	Modalitat m_modalitat;
	bool m_electrica;

};