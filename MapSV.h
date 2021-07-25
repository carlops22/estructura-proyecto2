#ifndef MAPSV_H
#define MAPSV_H

#include <iostream>
#include "ADTMap.h"
#include<vector>
using namespace std;


class MapSV: public ADTMap{

	private:
		vector<pair<string,int> > _array;
		int binBusqueda(string, int, int);
		int tam;
	public:
	
		MapSV();
		~MapSV();
		void insert(pair<string,int>);
		void erase(string);
		int at(string);
		int size();
		bool empty();	




};



#endif