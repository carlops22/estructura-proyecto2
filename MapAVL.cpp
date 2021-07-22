#include "MapAVL.h"
#include <algorithm>
MapAVL::MapAVL(){
	raiz=nullptr;
}

MapAVL::~MapAVL(){
	
}
void MapAVL::init_nodo(ptrnodo nodio,pair<string,int> &pair){
			nodio->par=pair;
			nodio->padre=nullptr;
			nodio->izq=nullptr;
			nodio->der=nullptr;
			nodio->balance=0;
		}
		
//funcion de busqueda binaria de arbol, busca una llave desde cierto nodo hacia abajo
ptrnodo MapAVL::bin_searchtree(ptrnodo nodio, string key){
		if (nodio == nullptr || key == nodio->par.first) {
			return nodio;
		}

		if (key < nodio->par.first) {
			return bin_searchtree(nodio->izq, key);
		} 
		return bin_searchtree(nodio->der, key);
}

//recorre el arbol hasta encontrar el nodo con la llave más pequeña
ptrnodo MapAVL::min_node(ptrnodo nodio){
	while(nodio->izq!=nullptr)
		nodio=nodio->izq;
	return nodio;
}
//funcion para eliminar nodo
ptrnodo MapAVL::delete_nodo(ptrnodo nodio, string key){
	// busca la llave, traversando el arbol
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
		}
		
		//caso 2: nodo tiene un solo hijo
		else if(nodio->izq== nullptr){
			nodo *temp=nodio;
			nodio=nodio->der;
			delete temp;
		}
		
		else if(nodio->der== nullptr){
			nodo *temp=nodio;
			nodio=nodio->izq;
			delete temp;
		}
		
		//caso 3: tiene ambos hijos (izquierda,derecha)
		else{
			nodo *temp=min_node(nodio->der);
			nodio->par=temp->par;
			nodio->der= delete_nodo(nodio->der,temp->par.first);
		}
	}
	
	//ahora se updatea el balance de los nodos, piko idea :) 
	
	
	return nodio;
}

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
	if(nodio->balance>0){
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
	else if(nodio->balance<0){
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
void MapAVL::insert(pair<string,int> pair){
	
}

void MapAVL::erase(string key){
	
}

int MapAVL::at(string key){
	
}

int MapAVL::size(){
	
}

bool MapAVL::empty(){
	
}	