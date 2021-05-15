#include "Proveidor.h"

#include <string>
#include "Proveidor.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
#include "time.h"
#include "BicicletaInfantil.h"
#include "BicicletaMTB.h"
#include "BicicletaCarretera.h"
#include "Empresa.h"
using namespace std;

Data Proveidor::generaDataEnviament(Data dataprevista, int diesmaxim = -10 + rand() % 21)
{
	diesmaxim = -10 + rand() % 21;
	//Si los dias que nos pasan son positivos sumamos los dias utilizando el operator de data
	if (diesmaxim >= 0)
	{
		dataprevista = dataprevista + diesmaxim; //sobrecarga operador
	}
	//Si los dias que nos pasan son negativos restamos utilizando un operator data- que hemos implementado nosotros.
	else
	{
		diesmaxim *= -1;
		dataprevista = dataprevista - diesmaxim;
	}

	return dataprevista;
}

bool Proveidor::procesaComanda(Comanda c, Magatzem& m)
{

	bool procesadaComanda = false;// es el booleano que recibira de almacen de si es correcta la comanda

	vector<Bicicleta*> bici; //Vector de punteros para guardar las bicicletas con sus caracteristicas

	BicicletaInfantil Inf; //Objeto BiciInfantil para utilizarlo en el vector de punteros
	BicicletaMTB mtb; //Objeto BiciIMTB para utilizarlo en el vector de punteros
	BicicletaCarretera Carr; //Objeto BiciCarr para utilizarlo en el vector de punteros

	Empresa e;

	srand(time(0)); //Para que funcione el random correctamente y haga diferentes randoms en la misma compilacion
	int count = 0;
	for (int i = 0; i < c.getLlistaComanda().size(); i++)
	{
		for (int a = 0; a < c.getLlistaComanda()[i].m_quantitat; a++)
		{
			Inf = BicicletaInfantil(); //Objeto BiciInfantil para utilizarlo en el vector de punteros
			mtb = BicicletaMTB(); //Objeto BiciIMTB para utilizarlo en el vector de punteros
			Carr = BicicletaCarretera(); //Objeto BiciCarr para utilizarlo en el vector de punteros

			if (c.getLlistaComanda()[i].tipus == TipusBicicleta::INFANTIL)
			{
				Inf.setPlegable(randomBool()); //Añadimos ya de paso un valor plegable random, ya que como no es de heredada de bici luego es un poco mas dificil añadirle este atributo
				bici.push_back(new BicicletaInfantil(Inf));

				bici[count]->setTipus(TipusBicicleta::INFANTIL);

				bici[count]->setModel("INF_" + c.getLlistaComanda()[i].m_model); //A modelo ya aprovechamos para añadirle el prefijo INF_
				bici[count]->setPreu(TipusBicicleta::INFANTIL);
				bici[count]->setTalla(randomTalla()); //Random de talla
				bici[count]->setQuadre(Quadre::ALUMINI); //Este no es random porque siempre sera de Aluminio
				bici[count]->setFre(Fre::RIM); //Este no es random porque siempre sera de RIM


				//bici[count]->setCodiRus(e.generaCodiRus(bici[count]->getModel()));
				//bici[count]->setQuantitat(c.getLlistaComanda()[i].m_quantitat); //Este atributo lo hemos añadido nosotros para saber cuantas bicis de ese tipo nos estan pidiendo.

				//En este caso Roda pueden ser ciertos valores y otros que no, por lo tanto vemos que le asigna random y si es uno de los validos se lo añadimos sino vuelve a hacer el random.
				do
				{
					bici[count]->setRoda(randomRoda());
				} while ((bici[count]->getRoda() != Roda::RODA_14) && (bici[count]->getRoda() != Roda::RODA_20));

			}
			if (c.getLlistaComanda()[i].tipus == TipusBicicleta::CARRETERA)
			{
				Carr.setModalitat(randomModalitatC()); //Añadimos ya de paso un valor ModalidadC random, ya que como no es de heredada de bici luego es un poco mas dificil añadirle este atributo
				Carr.setElectricaC(randomBool()); //Añadimos ya de paso un valor Electrica random, ya que como no es de heredada de bici luego es un poco mas dificil añadirle este atributo
				bici.push_back(new BicicletaCarretera(Carr));

				bici[count]->setTipus(TipusBicicleta::CARRETERA);

				bici[count]->setModel("CTR_" + c.getLlistaComanda()[i].m_model);
				bici[count]->setTipus(TipusBicicleta::CARRETERA);
				bici[count]->setPreu(TipusBicicleta::CARRETERA);
				bici[count]->setTalla(randomTalla());
				bici[count]->setQuadre(randomQuadre());
				bici[count]->setRoda(Roda::RODA_700);
				bici[count]->setFre(randomFre());

				//bici[count]->setCodiRus(e.generaCodiRus(bici[count]->getModel()));
				//bici[count]->setQuantitat(c.getLlistaComanda()[i].m_quantitat);


			}
			if (c.getLlistaComanda()[i].tipus == TipusBicicleta::MTB)
			{
				mtb.setCategoria(randomCategoria()); //Añadimos ya de paso un valor categoria random, ya que como no es de heredada de bici luego es un poco mas dificil añadirle este atributo
				mtb.setModalitat(randomModalitat());//Añadimos ya de paso un valor modalidad random, ya que como no es de heredada de bici luego es un poco mas dificil añadirle este atributo
				mtb.setElectrica(randomBool()); //Añadimos ya de paso un valor electrica random, ya que como no es de heredada de bici luego es un poco mas dificil añadirle este atributo
				bici.push_back(new BicicletaMTB(mtb));

				bici[count]->setTipus(TipusBicicleta::MTB);

				bici[count]->setModel("MTB_" + c.getLlistaComanda()[i].m_model);
				bici[count]->setTipus(TipusBicicleta::MTB);
				bici[count]->setPreu(TipusBicicleta::MTB);
				bici[count]->setTalla(randomTalla());
				bici[count]->setQuadre(randomQuadre());
				bici[count]->setFre(Fre::DISC);

				//bici[count]->setCodiRus(e.generaCodiRus(bici[count]->getModel()));
				//bici[count]->setQuantitat(c.getLlistaComanda()[i].m_quantitat);

				do
				{
					bici[count]->setRoda(randomRoda());
				} while (((bici[count]->getRoda() != Roda::RODA_26) && (bici[count]->getRoda() != Roda::RODA_27)) && (bici[count]->getRoda() != Roda::RODA_29));

				//bici[count]->setQuantitat(c.getLlistaComanda()[i].m_quantitat); //Este atributo lo hemos añadido nosotros para saber cuantas bicis de ese tipo nos estan pidiendo.
			}

			count++;
		}
	}
	
	procesadaComanda = m.rebreComanda(c, bici, c.getDataEntregaPrevista());
	
	return procesadaComanda;
}
