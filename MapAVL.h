#ifndef MAPAVL_H
#define MAPAVL_H


#include "ADTMap.h"
#include<vector>
using namespace std;


class MapAVL: public ADTMap{

	private:
		vector<pair<string,int>> _array;
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