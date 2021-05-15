#pragma once

#include "Bicicleta.h"

enum class ModalitatC {
	AERO,
	GRANFONDO,
	GRAVEL,
	RENDIMIENTO,
};


class BicicletaCarretera : public Bicicleta
{
public:
	BicicletaCarretera() {}
	BicicletaCarretera(const string& model, string descripcio, const int& temporada, const Talla& talla, const Quadre& quadre, const Roda& roda, const Fre& fre, TipusBicicleta tipus, ModalitatC modalitat, bool electrica)
	: Bicicleta(model, descripcio, temporada, talla, quadre, Roda::RODA_700, fre, TipusBicicleta::CARRETERA), m_modalitatC(modalitat), m_electricaC(electrica) {}
	BicicletaCarretera(const BicicletaCarretera&) {}
	~BicicletaCarretera() {};
	void setModalitat(const ModalitatC& modalitat) { m_modalitatC = modalitat; }
	ModalitatC getModalitat() const { return m_modalitatC; }

	void setElectricaC(const bool& electrica) { m_electricaC = electrica; }
	bool getElectrica() const { return m_electricaC; }
	void setRoda(const Roda& roda) override { if (roda == Roda::RODA_700) { m_roda = roda; } else { m_roda = Roda::RODA_700; } };
	void setTipus(TipusBicicleta tipus) override { if (tipus == TipusBicicleta::CARRETERA) { m_tipus = tipus; } };


protected:
	ostream& format(ostream& os) const override { return os; }
private:
	ModalitatC m_modalitatC;
	bool m_electricaC;

};

