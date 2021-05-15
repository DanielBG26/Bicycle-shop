#pragma once

#include "Bicicleta.h"
#include <string>

class BicicletaInfantil : public Bicicleta
{
public:
	BicicletaInfantil() {}
	BicicletaInfantil(const string& model, string descripcio, const int& temporada, const Talla& talla, const Quadre& quadre, const Roda& roda, const Fre& fre, TipusBicicleta tipus, const bool& plegable)
	:Bicicleta(model, descripcio, temporada, talla, Quadre::ALUMINI, Roda::RODA_14, Fre::RIM, TipusBicicleta::INFANTIL), m_plegable(plegable) {}
	BicicletaInfantil(const BicicletaInfantil&) {}
	~BicicletaInfantil() {};

	bool getPlegable() const { return m_plegable; }
	void setPlegable(const bool& plegable) { m_plegable = plegable; }
	void setQuadre(const Quadre& quadre) { if (quadre == Quadre::ALUMINI) { m_quadre = quadre; } else { m_quadre = Quadre::ALUMINI; } }
	void setFre(const Fre& fre) override { if (fre == Fre::RIM) { m_fre = fre; } else { m_fre = Fre::RIM; } }
	void setRoda(const Roda& roda) override { if (roda == Roda::RODA_14 || roda == Roda::RODA_20) { m_roda = roda; } else { m_roda = Roda::RODA_14; } }
	void setTipus(TipusBicicleta tipus) override { m_tipus = tipus; }

protected:
	ostream& format(ostream& os) const override { return os; }
private:
	bool m_plegable;

};


