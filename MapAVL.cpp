#include "MapAVL.h"
#include <algorithm>
MapAVL::MapAVL(){
	raiz=nullptr; //inicializa la raiz
	numNodos=0;  //inicializa contador de nodos
}

MapAVL::~MapAVL(){
	postOrder_delete_nodo(raiz); //se hace un delete recorriendo en post order desde la raiz
}
//funcion para inicializar un nodo, con sus punteros nulos
void MapAVL::init_nodo(ptrnodo nodio,pair<string,int> pair){
			nodio->par=pair;
			nodio->padre=nullptr;
			nodio->izq=nullptr;
			nodio->der=nullptr;
			nodio->balance=0;
}


//funcion de busqueda binaria de arbol, busca una llave desde cierto nodo hacia abajo
ptrnodo MapAVL::bin_searchtree(ptrnodo nodio, string key){
	//caso 1: el nodo no existe o encontro llave
		if (nodio == nullptr || key == nodio->par.first) {
			return nodio;
		}
	//caso 2: la llave es menor al del nodio, se recorre por la rama izquierda
		if (key < nodio->par.first) {
			return bin_searchtree(nodio->izq, key);
		} 
	//caso 3: la llave es mayor al del nodio, se recorre por la rama derecha
		return bin_searchtree(nodio->der, key);
}

//recorre el arbol hasta encontrar el nodo con la llave más pequeña
ptrnodo MapAVL::min_node(ptrnodo nodio){
	while(nodio->izq!=nullptr)
		nodio=nodio->izq;
	return nodio;
}
//funcion para eliminar nodo
ptrnodo MapAVL::delete_nodo(ptrnodo nodio){
	nodio->izq=nullptr;
	nodio->der=nullptr;
	return nodio;
}

//funcion principal para eliminar un nodo
ptrnodo MapAVL::delete_nodo(ptrnodo nodio, string key){
	// busca la llave, atravesando el arbol
	if(nodio==nullptr)
		return nodio;
	else if(key<nodio->par.first)
		nodio->izq=delete_nodo(nodio->izq,key);
	else if(key>nodio->par.first)
		nodio->der=delete_nodo(nodio->der,key);
	//encontro la llave, basta borrarlo
	else{ 
		//caso 1: nodo es hoja
		if(nodio->izq==nullptr && nodio->der==nullptr){
			delete nodio;
			nodio=nullptr;
			return nodio;
		}
		
		//caso 2: nodo tiene un solo hijo
		else if(nodio->izq== nullptr){
			ptrnodo temp=nodio;
			nodio=nodio->der;
			delete temp;
			return nodio;
		}
		
		else if(nodio->der== nullptr){
			ptrnodo temp=nodio;
			nodio=nodio->izq;
			delete temp;
			return nodio;
		}
		
		//caso 3: tiene ambos hijos (izquierda,derecha)
		else{
			ptrnodo temp=min_node(nodio->der);
			nodio->par=temp->par;
			nodio->der= delete_nodo(nodio->der,temp->par.first);
		}
	}
	
	if (nodio == nullptr)
    	return nodio;
    // si se desbalancea hay que realizar 4 tipos de rotaciones
 
    // izquierda izquierda
    if (nodio->balance > 1 &&
        nodio->izq->balance >= 0)
        derRotar(nodio);
 
    // izquierda derecha
    if (nodio->balance > 1 &&
        nodio->izq->balance < 0)
    {
        izqRotar(nodio->izq);
        derRotar(nodio);
    }
 
    // derecha derecha
    if (nodio->balance < -1 &&
        nodio->der->balance <= 0)
        izqRotar(nodio);
 
    // derecha izquierda
    if (nodio->balance < -1 &&
        nodio->der->balance > 0)
    {
        derRotar(nodio->der);
        izqRotar(nodio);
    }
	
	return nodio;
}
//funcion para rotar a la derecha un nodo
void MapAVL::derRotar(ptrnodo nodio){
	
	ptrnodo nodo= nodio->izq;
	nodio->izq=nodo->der;
	
	//caso 1: si el arbol no esta cargado a la izquierda(zigzag) 
	// se asigna el nuevo padre del hijo derecho de nodo  como nodio (ya que cambio de lugar)
	if(nodo->der!=nullptr)
		nodo->der->padre=nodio;
	
	nodo->padre=nodio->padre;
	
	//caso 2: si el nodio a rotar es la raiz se asigna nodo como nueva raiz
	if(nodio->padre==nullptr)
		this->raiz=nodo;
	//caso 3: si el nodio es el hijo derecho de su padre 
	// se le asigna nodo como su nuevo hijo derecho (al padre)
	else if(nodio==nodio->padre->der)
		nodio->padre->der=nodo;
	//viceversa (hijo izquierdo)
	else
		nodio->padre->izq=nodo;
	
	nodo->der=nodio;
	nodio->padre=nodo;
	
	nodio->balance=nodio->balance+1-min(0,nodo->balance);
	nodo->balance=nodo->balance+1+max(0,nodio->balance);
}
//funcion para rotar a la izquierda de un determinado nodo
void MapAVL::izqRotar(ptrnodo nodio){
	ptrnodo nodo=nodio->der;
	nodio->der=nodo->izq;
	
	//caso 1: si el arbol no esta cargado a la derecha(esta como zigzag)
	// se asigna el nuevo padre como del hijo izquierdo de nodo como nodio(cambio de lugar)
	if(nodo->izq!=nullptr)
		nodo->izq->padre=nodio;
	
	nodo->padre=nodio->padre;
	
	//caso 2: si el nodio a rotar es la raiz se asigna nodo como nueva raiz
	if(nodio->padre==nullptr)
		this->raiz=nodo;
	
	//caso 3: si el nodio es el hijo izquierdo de su padre
	// se le asigna nodo como su nuevo hijo izquierdo
	else if(nodio==nodio->padre->izq)
		nodio->padre->izq=nodo;
	else
		nodio->padre->der=nodo;
	
	nodo->izq=nodio;
	nodio->padre=nodo;
	
	nodio->balance=nodio->balance-1-max(0,nodo->balance);
	nodo->balance=nodo->balance-1+min(0,nodio->balance);
	
	
}
//funcion para mantener actualizada el balance
void MapAVL::update_balance(ptrnodo nodio){
	
	//caso 1: el nodo esta desbalanceado, se prosigue a equilibrar el arbol
	if(nodio->balance<-1 || nodio->balance>1){
		rebalance(nodio);
		return;
	}
	 // Si el nodo no es la raiz procede a actualizar los valores de balance de mas arriba
	if(nodio->padre !=nullptr){
		// caso 1: si es el nodo de la izquierda, se  resta 1 al balance del padre
		if(nodio==nodio->padre->izq){
			nodio->padre->balance-=1;	
		}
		//caso 2: si es el nodo de la derecha del padre, suma 1 al balance del padre 
		if(nodio==nodio->padre->der){
			nodio->padre->balance+=1;
		}
		//caso 3: se continua recursivamente con el padre del nodo mientras sea no-cero
		if(nodio->padre->balance!=0){
			update_balance(nodio->padre);
		}
	}
	
}
void MapAVL::rebalance(ptrnodo nodio){
	//balance del nodo 1 o mayor
	if(nodio->balance>1){
		//caso 1: rotacion por zigzag hacia la derecha, se rota el nodo hijo a la derecha y luego el nodo a la izq
		if(nodio->der->balance<0){
			derRotar(nodio->der);
			izqRotar(nodio);
		}
		//caso 2: rotacion por arbol cargado a la derecha, se rota el nodo a la izquierda y queda balanceado
		else
			izqRotar(nodio);
	}
	//balance es -1 o menor
	else if(nodio->balance<-1){
		//caso 3: rotacion por zigzag hacia la izquierda, se rota el nodo hijo a la izquierda y luego el nodo a la der
		if(nodio->izq->balance>0){
			izqRotar(nodio->izq);
			derRotar(nodio);
			
		}
		//caso 4: rotacion por arbol cargado a la izquierda, se rota el nodo a la derecha 
		else
			derRotar(nodio);
	}
	
		
	
}
//funcion para eliminar nodos en postorder
void MapAVL::postOrder_delete_nodo(ptrnodo nodio){
	if(nodio == nullptr) return;
	postOrder_delete_nodo(nodio->izq);
	postOrder_delete_nodo(nodio->der);
	delete_nodo(nodio);

}

void MapAVL::insert(pair<string,int> pair){
	
	ptrnodo nodio= new nodo;
	init_nodo(nodio,pair);

	ptrnodo x=this->raiz; //puntero auxiliar para recorrer arbol
	ptrnodo y=nullptr;
	//recorre hasta encontrar una posicion vacia
	while(x!=nullptr){
		y=x;
		//caso 1: si es la llave es menor recorre hacia la izquierda
		if(nodio->par.first<x->par.first)
			x=x->izq;
		//caso 2: recorre a la derecha
		else
			x=x->der;
	}
	//y es el padre de x
	nodio->padre=y;
	//si y sigue siendo nullptr es pq nodio es le primer elemento del arbol
	if(y==nullptr)
		raiz=nodio;
	//si la llave es menor a  la de y se posiciona a su izquierda
	else if(nodio->par.first<y->par.first)
		y->izq=nodio;

	//de lo contrario a la derecha
	else 
		y->der=nodio;

	
	update_balance(nodio);
	numNodos++; //aumenta contador
}
//ejecuta delete_nodo que se encarga de eliminar el nodo a buscar con la llave
void MapAVL::erase(string key){
	ptrnodo temp=raiz;
	temp=delete_nodo(raiz,key);
	numNodos--;
	
}
//realiza la busqueda en arbol binario
int MapAVL::at(string key){
	ptrnodo nodo=bin_searchtree(raiz,key);
	if(!nodo) return -1;
	return nodo->par.second;
}
//retorna el tamaño del map
int MapAVL::size(){
	return numNodos;
}
//retorna si esta vacio o no el map
bool MapAVL::empty(){
	bool r=false;
	if(!numNodos)
		r=true;
	return r;
}	