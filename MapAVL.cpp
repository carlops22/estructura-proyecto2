#include "MapAVL.h"
#include <algorithm>
MapAVL::MapAVL(){
	root=nullptr;
}

MapAVL::~MapAVL(){
	
}
void MapAVL::init_nodo(nodo &nodio,pair<string,int> &pair){
			nodio->par=pair;
			nodio->padre=nullptr;
			nodio->izq=nullptr;
			nodio->der=nullptr;
			nodio->balance=0;
		}

nodo& MapAVL::bin_searchtree(nodo &nodio, string key){
		if (nodio == nullptr || key == nodio->par.first) {
			return nodio;
		}

		if (key < nodio->par.first) {
			return searchTreeHelper(nodio->izq, key);
		} 
		return searchTreeHelper(nodio->der, key);
}

nodo& MapAVL::delete_nodo(nodo &nodio, string key){
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
			nodo *temp=minimum(nodio->der);
			nodio->par=temp->par;
			nodio->der= delete_nodo(nodio->der,temp->par.first);
		}
	}
	
	//ahora se updatea el balance de los nodos, piko idea :) 
	
	
	return nodio;
}

void MapAVL::update_balance(nodo &nodio){
	
	//caso 1: el nodo esta desbalanceado, se prosigue a balancear
	if(nodio->balance<-1 || nodio->balance>1){
		rebalance(nodio);
		return;
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