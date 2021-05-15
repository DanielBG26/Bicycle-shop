
#include "Bicicleta.h"

Bicicleta::Bicicleta() {
    m_model = "";
    m_descripcioModel = "";
    m_temporada = 0;
}

Bicicleta::Bicicleta(const string& model, const string& descripcio, const int& temporada, Talla talla, Quadre quadre, Roda roda, Fre fre, TipusBicicleta tipus)
{
    m_model = model;
    m_descripcioModel = descripcio;
    m_temporada = temporada;
    m_talla = talla;
    m_quadre = quadre;
    m_roda = roda;
    m_fre = fre;
    m_tipus = tipus;
}


Bicicleta::Bicicleta(Bicicleta& b) {
    m_model = b.m_model;
    m_descripcioModel = b.m_descripcioModel;
    m_temporada = b.m_temporada;
    m_talla = b.m_talla;
    m_quadre = b.m_quadre;
    m_roda = b.m_roda;
    m_fre = b.m_fre;
    m_tipus = b.m_tipus;
}
