#ifndef MAPH_H
#define MAPH_H

#include "ADTMap.h"
#include<vector>
#include <bits/stdc++.h>
using namespace std;

class MapH: public ADTMap{
	private:
		int prime_table[26]={53,97,193,389,769,1543,3079,6151,12289,24593,49157,98317,196613,393241,786433,1572869,3145739,6291469,12582917,25165843,50331653,100663319,201326611,402653189,805306457,1610612741};	
		int hash_size=prime_table[1];
		int rehash_pos;		
		vector<pair<string,int>> hash_table=vector<pair<string,int>>(hash_size); //inicializa el vector con tamaño primo más cercano a la mitad (N/2) 
		//int func_hash(string);
		int hash_1(string);
		int hash_2(string);
		int sizen;	
		int cols_ins;
		int cols_at;
		void rehashing();	
	public:
		MapH();
		~MapH();
		void insert(pair<string,int>);
		void erase(string);
		int at(string);
		int size();
		bool empty();
		int getCols_ins();
		int getCols_at();
};

#endif