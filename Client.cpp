#include "Client.h"
#include "Empresa.h"


//bool comprarBicicleta(string model, Botiga &b) -> realiza una compra. Si consigue hacer la
//compra con éxito, actualiza el estado y la guarda.Return: true / false según el resultado de
//compra

bool Client::comprarBicicleta(string model, Botiga& b)
{
	map<string, priority_queue<Bicicleta*, vector<Bicicleta*>, CmpBicicleta>>::iterator it;
	Bicicleta *bici;

	if(b.procesa_venda(model, bici))
	{
		if (b.comprobaBicicletaEnStock(model, bici)) //comproba stock botiga
		{
			//cout << "Hay bicicleta en la botiga, asi que la apuntamos " << endl;
			m_bicicletes.push_back(bici);
			Empresa::afegeixSeguiment(bici);
			Empresa::actualitzaEstat(bici->getCodiRus(), EstatBicicleta::VENUDA, &b);
		}
		else
		{
			if (b.ComprobaStockEnVeines(model, bici))
			{
				//cout << "No hay en la tienda pero hay en otras tiendas, asi que la apuntamos " << endl;
				m_bicicletes.push_back(bici);
				Empresa::afegeixSeguiment(bici);
				Empresa::actualitzaEstat(bici->getCodiRus(), EstatBicicleta::VENUDA, &b);
			}
			else
			{
				if (b.solicitaBicicletaAMagatzem(model, bici))
				{
					//cout << "No hay en las tiendas, pero hay en el almacen, lo apuntamos " << endl;
					m_bicicletes.push_back(bici);
					Empresa::afegeixSeguiment(bici);
					Empresa::actualitzaEstat(bici->getCodiRus(), EstatBicicleta::VENUDA, &b);
				}
				else
				{
					//cout << "Existe pero no hay stock en ningun sitio " << endl;
				}	
			}
		}
		return true;
	}
	return false;
}
