#include "MapSV.h"

MapSV::MapSV(){
	tam=0;
	
}

MapSV::~MapSV(){
	
	
}
//busqueda binaria recursiva del mapa
int MapSV::binBusqueda(string s, int i, int r){
	//si el intervalo low es menor o igual al high
	if(i<=r){
		//se calcula el valor medio y se compara con la llave a buscar
		int mid=(i+r)/2;
		if(s==(_array[mid].first))
			return mid;
		//si resulta ser menor o mayor se busca en el intervalo superior o inferior
		if(s<(_array[mid].first))
			return binBusqueda(s,i,mid-1);
		if(s>(_array[mid].first))
			return binBusqueda(s,mid+1,r);
	}
	return -1;
	
	
}

//inserta un par
void MapSV::insert(pair<string,int> par){
	//si esta vacio lo ingresa inmediatamente
	if(tam==0){
		tam++;
		_array.push_back(par);
	}
	// de lo contrario se itera por todo vector hasta encontrar un elemento mayor y se inserta en su lugar
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
		//en peor caso se ingresa al final del vector 
		_array.push_back(par);
		tam++;
	}
	
}
// para eliminar un elemento simplemente se realiza una busqueda binaria y un erase del vector
void MapSV::erase(string s){
	int r= at(s);
	if(r!=-1)
		_array.erase(_array.begin()+r);
}
//ejecuta la busqueda binaria recursiva, retorna el numero del par
int MapSV::at(string s){
	int indice=binBusqueda(s,0,tam-1);
	if(indice==-1){
		return -1;
	}
	return _array[indice].second;
	
}
//retorna la cantidad de elementos en el mapa
int MapSV::size(){
	return tam;
}
//prueba si esta vacio el mapa
bool MapSV::empty(){
	bool r=false;
	if(tam==0)
		r=true;
	return r;
	
}