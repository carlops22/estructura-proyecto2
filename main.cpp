
#include <iostream>
#include <time.h>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>

#include "MapSV.h"
#include "MapH.h"
#include "MapAVL.h"
using namespace std;
//funcion para crear un string alfabetico random
string printRandomString(int n)
{
    char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
 
    string res = "";
    for (int i = 0; i < n; i++)
        res = res + alphabet[rand() % 26];
     
    return res;
}

int main(){
    srand(time(NULL));
    double tsvins,thins,tavlins,tsvat,tsvatfake,thatfake,tavlatfake,that,tavlat,tsverase,therase,tavlerase;
    cout<<"n;SVins;Hins;AVLins;SVat;Hat;AVLat;SVatfake;Hatfake;AVLatfake"<<endl;
    MapAVL avlmapa;
    for(int n=5000; n<=50000; n+=5000){
        MapSV *svmap=new MapSV();
        MapH *hmap=new MapH();
        MapAVL *avlmap=new MapAVL();
        vector<pair<string,int> > data;
        vector<pair<string,int> > datafake;
        for(int i=0;i<n;i++){
            data.push_back(make_pair(printRandomString(15),rand()%100+1));
        } 

        for(int i=0;i<n;i++){
            datafake.push_back(make_pair(printRandomString(7),rand()%100+1));
        } 
    
    
        int size_data=data.size();
        
        clock_t start,stop;
        
        //tiempos de insert
        //insert SVMap
      
        start=clock();
        for(int i=0;i<size_data;i++)
            svmap->insert(data[i]);
        stop=clock();
        tsvins=(double)(stop-start)/CLOCKS_PER_SEC/size_data;
     
        //insert HMap
       
        start=clock();
        for(int i=0;i<size_data;i++)
            hmap->insert(data[i]);
        stop=clock();
        thins=(double)(stop-start)/CLOCKS_PER_SEC/size_data;
     
        //insert AVLMap
        start=clock();
        for(int i=0;i<size_data;i++)
            avlmap->insert(data[i]);
        stop=clock();
        
        tavlins=(double)(stop-start)/CLOCKS_PER_SEC/size_data;

        // operaciones AT con datos existentes:

        //at SV
        start=clock();
        for(int i=0;i<size_data;i++)
            svmap->at(data[i].first);
        stop=clock();
        tsvat=(double)(stop-start)/CLOCKS_PER_SEC/size_data;
        
        //at H
        start=clock();
        for(int i=0;i<size_data;i++)
            hmap->at(data[i].first);
        stop=clock();
        that=(double)(stop-start)/CLOCKS_PER_SEC/size_data;
      
        //at AVL
        start=clock();
        for(int i=0;i<size_data;i++)
            avlmap->at(data[i].first);
        stop=clock();
        tavlat=(double)(stop-start)/CLOCKS_PER_SEC/size_data;

        // at con datos inexistentes:
        //at SV
        start=clock();
        for(int i=0;i<size_data;i++)
            svmap->at(datafake[i].first);
        stop=clock();
        tsvatfake=(double)(stop-start)/CLOCKS_PER_SEC/size_data;
        
        //at H
        start=clock();
        for(int i=0;i<size_data;i++)
            hmap->at(datafake[i].first);
        stop=clock();
        thatfake=(double)(stop-start)/CLOCKS_PER_SEC/size_data;
      
        //at AVL
        start=clock();
        for(int i=0;i<size_data;i++)
            avlmap->at(datafake[i].first);
        stop=clock();
        tavlatfake=(double)(stop-start)/CLOCKS_PER_SEC/size_data;



   /**
        //erase SV
        start=clock();
        for(int i=0;i<size_data;i++)
            svmap->erase(data[i].first);
        stop=clock();
        tsverase=(double)(stop-start)/CLOCKS_PER_SEC/size_data;
      
        //erase H
        start=clock();
        for(int i=0;i<size_data;i++)
            hmap->erase(data[i].first);
        stop=clock();
        therase=(double)(stop-start)/CLOCKS_PER_SEC/size_data;
  
        //erase AVL
       
        start=clock();
        for(int i=0;i<size_data;i++)
            avlmap->erase(data[i].first);
        stop=clock();
        tavlerase=(double)(stop-start)/CLOCKS_PER_SEC/size_data;
     
 **/
        //mostrar resultados en pantalla

        cout<<n<<";"<<tsvins<<";"<<thins<<";"<<tavlins<<";"<<tsvat<<";"<<that<<";"<<tavlat<<";";
        cout<<tsvatfake<<";"<<thatfake<<";"<<tavlatfake<<";"<<endl;

        //llamar a sus destructores
        delete(svmap);
        delete(hmap);
        delete(avlmap);
    }

    return 0;
}