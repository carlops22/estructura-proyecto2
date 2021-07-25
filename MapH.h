#ifndef MAPH_H
#define MAPH_H

#include <iostream>
#include <string>
#include <vector>
#include "ADTMap.h"

using namespace std;

class MapH :public ADTMap {
    private:
    int tamV,tam2,numhash,posicion,colisiones_at,colisiones_insert;
    vector<pair<string,int>> *listita;
    int hashingpolinomial(string llavesita);
    int segundahashing(string llavesita);
    void agrandar();

    public:
        MapH(int n);
        ~MapH();
        void insert(pair<string,int> lista);
        void erase(string llave);
        int at(string llave);
        int size();
        bool empty();
        int getcolisionesat();
        int getcolisionesinsert();

};
#endif