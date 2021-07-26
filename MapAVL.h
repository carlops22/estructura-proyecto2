#ifndef MAPAVL_H
#define MAPAVL_H
#include "ADTMap.h"
#include<vector>
#include <bits/stdc++.h>
using namespace std;

struct nodo{
			nodo *padre;
			nodo *izq, *der;
			pair<string,int> par;
			int balance; //factor de balance, si esta balanceado es 0
			int altura;
};
typedef nodo *ptrnodo;
class MapAVL: public ADTMap{

	private:
		nodo *raiz;	
		int numNodos;
		void init_nodo(ptrnodo nodio,pair<string,int> pair);
		void postOrder_delete_nodo(ptrnodo nodio);
		ptrnodo bin_searchtree(ptrnodo nodio, string key);
		ptrnodo delete_nodo(ptrnodo nodio);
		ptrnodo delete_nodo(ptrnodo nodio, string key);
		void update_balance(ptrnodo nodio);
		void rebalance(ptrnodo nodio);
		
	public:
		MapAVL();
		~MapAVL();
		void insert(pair<string,int>);
		void erase(string);
		int at(string);
		int size();
		bool empty();
		ptrnodo max_node(ptrnodo nodio);
		ptrnodo min_node(ptrnodo nodio);
		void izqRotar(ptrnodo nodio);
		void derRotar(ptrnodo nodio);		
};



#endif