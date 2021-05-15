#include "Botiga.h"
#include "Empresa.h"

bool Botiga::solicitaComanda(Comanda& c, Magatzem& m)
{
   
    map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>> maa;
    map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator it;
    //Creem un map auxiliar ja que directament no ens funciona (it = m.getStock().begin())
    maa = m.getStock();
    it = maa.begin();
    bool ComandaOK = true;
    bool StockOK = true;
    bool StockOKThis = true;
    int ContadorQuant = 0;


    for (lineaComanda l : c.getLlistaComanda())
    {
        it = maa.begin();
        //va recorrent el map amb el iterador, mirant si esta el model
        while (it->first != l.m_model)
        {
            it++;
            StockOKThis = true;
        } 
        ContadorQuant = l.m_quantitat;
        
        while ((StockOKThis != false) && (ContadorQuant != false))
        {
            //si el stock del model es 0
            if (magatzem->getStock()[l.m_model].size() == 0)
            {
              ContadorQuant = false;
              if (l.m_quantitat > 0)
              {
                  StockOKThis = false;
                  StockOK = false;
              }
            }
            else
            {
                //agafa la bicicileta mes antiga del magatzem (la que te una data més petita)
                Bicicleta* bicicleta = magatzem->agafaBicicletaAntiga(l.m_model);
               
                if (bicicleta != nullptr)
                {
                    m_stockBotiga[l.m_model].push(bicicleta);
                    it->second.pop();
                    m.setStock(maa);
                    Empresa::actualitzaEstat(bicicleta->getCodiRus(), EstatBicicleta::EN_BOTIGA, this);
                    ContadorQuant--;
                }
                
            }
        }
        if (StockOK == false)
        {
            ComandaOK = false;
        }
    }
    return ComandaOK;
}

bool Botiga::solicitaComanda(Comanda& c)
{
    //crida al solicitaComanda de la anterior entrega, pero mira primer que el magatzem no sigui null
    bool solicita = false;

    if (magatzem == nullptr)
    {
        return solicita;
    }
    return solicitaComanda(c, *magatzem);
}

void Botiga::mostraCataleg()
{
}

int Botiga::calculaStockTotal()
{
    map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator tam;
    tam = m_stockBotiga.begin();
    int tamany = 0;

    //Va calculant quantes bicicles te la botiga, independentment del model
    for (tam; tam != m_stockBotiga.end(); tam++)
    {
        tamany += tam->second.size();
    }

    return tamany;
}


bool Botiga::solicitaBicicletaAMagatzem(const string& model, Bicicleta*& bicicleta)
{
    map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator Existeix;
    map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>> maa;

    //Comprova si en el magatzem hi ha el model solicitat
    maa = magatzem->getStock();
    Existeix = maa.find(model);
    
    if (Existeix != maa.end())
    {
        if (Existeix->second.size() > 0)
        {
            bicicleta = Existeix->second.top();
            Existeix->second.pop();
            magatzem->setStock(maa);
            return true;
        }
        else
        {
            return false;
        }

    }
	return false;
}

bool Botiga::procesa_venda(const string& model, Bicicleta*& bicicleta)
{
    
    //comprova si hi ha stocks en la botiga, sino en botigues veines i sino en magatzem.
    bool procesa = false;

    procesa = comprobaBicicletaEnStock(model, bicicleta);
    if (procesa)
    {
        return procesa;
    }
    else
    {
        procesa = ComprobaStockEnVeines(model, bicicleta);
        if (procesa)
        {
            return procesa;
        }
        else
        {
            procesa = solicitaBicicletaAMagatzem(model, bicicleta); 
            if(procesa)
            {
                return procesa;
            }
            else
            {
                return procesa;
            }
        }
    }
}

bool Botiga::comprobaBicicletaEnStock(const string& model, Bicicleta*& bicicleta)
{
    //Comprova si en la botiga actual hi ha el model solicitat
    map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator Existeix;
    

    Existeix = m_stockBotiga.find(model);
    if (Existeix != m_stockBotiga.end())
    {
        if (Existeix->second.size() > 0)
        {
            bicicleta = Existeix->second.top();
            Existeix->second.pop();
            return true;
        }
        else
        {
            return false;
        }

    }
    return false;
}

bool Botiga::ComprobaStockEnVeines(const string& model, Bicicleta*& bicicleta)
{
    //Comprova si en les botigues veines de la botiga actual hi ha el model solicitat
    map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator Existeix;
    std::vector<Botiga*>::iterator it;
    if (m_veines.size() != 0)
    {
        for (int i = 0; i < m_veines.size(); i++)
        {
            
            Existeix = m_veines[i]->m_stockBotiga.find(model);
            if (Existeix != m_veines[i]->m_stockBotiga.end()) 
            {
                //cout << "Si que hay stock " << endl;
                bicicleta = m_veines[i]->m_stockBotiga[model].top();
                m_veines[i]->m_stockBotiga[model].pop();
                return true;
            }
            else
            {
                //cout << "No hay stock " << endl;
                
            }
        }
    }
    
    return false;
    
}