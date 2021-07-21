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
			int balance;
};

class MapAVL: public ADTMap{

	private:
		nodo *raiz;	
		void init_nodo(nodo &nodio,pair<string,int> &pair);
		void preOrder(nodo &nodio);
		void inOrder(nodo &nodio);
		void postOrder(nodo &nodio);
		void bin_searchtree(nodo &nodio, string key);
		void delete_nodo(nodo &nodio, string key);
		void update_balance(nodo &nodio);
		
	public:
		MapAVL();
		~MapAVL();
		void insert(pair<string,int>);
		void erase(string);
		int at(string);
		int size();
		bool empty();	
};



#endif