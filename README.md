# Bicycle-shop

Bicicleta
-La clase Bicicleta es padre de BicicletaMTB, BicicletaCarretera, BicicletaInfantil.


Empresa
-RealitzaComanda: La empresa hace una solicitud al proveedor. (Llamada a procesaComanda)
-AfegeixSeguiment: Añade a la m_taulaSeguiment la bicicleta, si se ha insertado se devuelve 
True.
-ActualitzaEstat: Se inicializan en el almacén, y cada vez que cambie ya sea a tienda, vendida o 
devuelta, pues se le añadirá el nuevo estado donde se encuentra, pero manteniendo el 
anterior.
-ComprobaEstatCodi: ya proporcionado, comprueba que el estado es correcto.


Proveidor
-ProcesaComanda: Creamos todas las bicis del pedido solicitado, le añadimos valores a las 
variables de estas y hacemos la llamada a rebreComanda de almacén.
-GeneraDataEnviament: Desde almacén llamamos a este método para que le asigne fechas 
aleatorias (no del todo sino con la fecha que nos dan, variamos con un random aleatorio los 
días que pueden salir)


Magatzem (Entidad padre)
-RebreComanda: Añadimos las fechas aleatorias a las bicicletas, y llamamos a 
enmagatzemarComanda, luego procesQA y generaFactura.
-EnmagatzemarComanda: Ordenamos las bicicletas por fechas, luego ordenamos por modelo, 
luego le añadimos el código ruso, las metemos en el map m_stock, las añadimos a la 
m_taulaSeguiment y les ponemos en estado En_Magatzem.
-ProcesQA: Calculamos el coste de las bicicletas pedidas.
-GeneraFactura: Generamos la factura en un txt, en caso que no se cumpla algún requisito el 
coste se reducira un 10%.
-AgafaBicicletaAntiga: Coge la bicicleta más antigua del modelo que le pasen.


Botiga (Entidad padre)
-SolicitaComanda: Comprobamos que el almacén contenga bicicletas, y en caso de contener 
vamos a SolicitaComanda(Comanda& c, magatzem& m), y miramos si el modelo que se solicita 
si esta en el almacén y en caso que este en el almacén si hay stock suficiente, en el caso de que
no tenga le vende las que tenga y actualiza su estado a botiga.
-CalculaStockTotal: Calculamos el total de bicicletas que tiene la botiga.
-SolicitaBicicletaAMagatzem: Consulta si hay bicicletas del modelo que se ha pedido, si hay 
stock pues devuelve un true, de lo contrario devolvería un false.
-ProcesaVenda: primero comprueba si hay bicicletas en Stock en la tienda (llama a 
ComprobaBicicletaEnStock), en caso de no tener bicicletas en Stock comprueba las tiendas Memoria LP Proyecto parte 2
vecinas (llama a ComprobaStockEnVeines), y en caso de no tener tampoco consulta si el 
almacén tiene (SolicitaBicicletaAMagatzem).
-ComprobaBicicletaEnStock: Comprueba si hay bicicletas en la tienda del modelo solicitado, 
devolviendo un true o false dependiendo si hay stock o no.
-ComprobaStockVeines: Comprueba si hay bicicletas en las tiendas vecinas, y devuelve true o 
false si en alguna de las tiendas hay stock del modelo solicitado.


Client (Entidad padre)
-ComprarBicicleta: Si la bicicleta se compra correctamente guardamos la bicicleta en el vector 
de cliente, la eliminamos de la tienda o del almacén, y en la m_taulaSeguiment actualizamos la 
bicicleta a “Venuda”.


Comanda
-Esta clase sirve para hacer los pedidos, ya sea de “empresa-magatzem”, “magatzem-botiga” o 
“botiga-client”.


Graf
-Graf::Graf(vector llistaVertexs, vector llistaArestes): Guardamos los vértices y creamos la 
matriz de adyacencia a partir de la lista de aristas.

![2](https://user-images.githubusercontent.com/83342143/118343242-0ad54380-b528-11eb-9a40-5c3cd5926844.PNG)


