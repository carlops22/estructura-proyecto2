#ifndef MAPAVL_H
#define MAPAVL_H


#include "ADTMap.h"
#include<vector>
using namespace std;


class MapAVL: public ADTMap{

	private:
		struct nodo{
			nodo *padre;
			nodo *izq, *der;
			int altura;
			int balance;
			nodo(pair<string,int> &pair, nodo &p, nodo &i, nodo &d);
			void update_balance();
		}
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
