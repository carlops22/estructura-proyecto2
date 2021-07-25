#include "MapSV.h"

MapSV::MapSV(){
	tam=0;
	
}

MapSV::~MapSV(){
	
	
}
int MapSV::binBusqueda(string s, int i, int r){
	
	if(i<=r){
		int mid=(i+r)/2;
		if(s==(_array[mid].first))
			return mid;

		if(s<(_array[mid].first))
			return binBusqueda(s,i,mid-1);
		if(s>(_array[mid].first))
			return binBusqueda(s,mid+1,r);
	}
	return -1;
	
	
}
void MapSV::insert(pair<string,int> par){
	if(tam==0){
		tam++;
		_array.push_back(par);
	}
	else{
		for(int i=0;i<tam;i++){
			if(par.first<_array[i].first){
				tam++;
				_array.insert(_array.begin()+i,par);
				return;
			}
			if(par.first==_array[i].first)
				return;
		}
		_array.push_back(par);
		tam++;
	}
	
}

void MapSV::erase(string s){
	int r= at(s);
	if(r!=-1)
		_array.erase(_array.begin()+r);
}
int MapSV::at(string s){
	int indice=binBusqueda(s,0,tam-1);
	if(indice==-1){
		cout<<"No se encontro llave"<<endl;
		return -1;
	}
	return _array[indice].second;
	
}
int MapSV::size(){
	return tam;
}
bool MapSV::empty(){
	bool r=false;
	if(tam==0)
		r=true;
	return r;
	
}