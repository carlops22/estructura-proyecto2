#include "MapH.h"
#include<vector>
using namespace std;

//inicializa contador de tamaño y colisiones
MapH::MapH(){
	sizen=0;
	cols_ins=0;
	cols_at=0;
	rehash_pos=1;
}

MapH::~MapH(){
}

	//dos funciones de acumulacion polinomial para el hashing
	int MapH::hash_1(string k){ //acumulacion polinomial para cada caracter
		long long int sum=0;

		for(int i=0;i <k.length(); i++)
			sum += (long long int)k.at(i)*(long long int)pow(10,i);
		return sum%hash_size;
	}
	int MapH::hash_2(string k){ //acumulacion polinomial para cada 2 caracteres
		long long int sum=0;

		for(int i=0;i <k.length(); i+=2)
			sum += (long long int)k.at(i)*(long long int)pow(11,i);
		return sum%hash_size;
	}
/*
unsigned long MapH::func_hash(string k){
	int k1=hash_1(k);
	int k2=hash_2(k);
	if()
	for (int i = 0; i < hash_size; i++){
        int index = (k1 + i * k2)%hash_size;
        if (hash_table.at(index).first=="AVAILABLE" || (hash_table[index].first.size()==0 && hash_table[index].second==0) || hash_table[index].first==k){ //si la posicion esta desocupada
            return index;
		}
		cols_ins++; //aumenta colision
		cols_at++;
    }
	cout<<"error"<<endl;
    return -1;
}
*/
//funcion de rehashing
void MapH::rehashing(){
	rehash_pos++;		
	hash_size=prime_table[rehash_pos];
	//utiliza una nueva tabla del tamaño del siguiente numero primo de la tabla
	vector<pair<string,int>> hash_temp=hash_table;
	hash_table.clear();
	hash_table.resize(hash_size);
	
	for(int i=0; i<prime_table[rehash_pos-1];i++){ //recorre  la antigua tabla de hash 
	//si se encuentra un elemento se procede a sacar la posicion con la priera funcion de hashing
		if(!(hash_temp[i].first=="AVAILABLE" || (hash_temp[i].first.size()==0 && hash_temp[i].second==0))){
			int hashPos=hash_1(hash_temp[i].first);
			if(hash_table[hashPos].first.size()==0 && hash_table[hashPos].second==0){
				hash_table[hashPos]=hash_temp[i];				
			}

			//si ocurre una colision se utiliza la segunda tabla de hash para recalcular la posicion
			else{
				int hashPos2=hash_2(hash_temp[i].first);
				for(int j=1;j<prime_table[rehash_pos-1];j++){
					int newhashPos=(hashPos+j*hashPos2)%hash_size;
					if(hash_table[newhashPos].first.size()==0 && hash_table[newhashPos].second==0){
						hash_table[newhashPos]=hash_temp[i];
						break;
					}
				}
				
			}
		}			
	}
	
	
}

void MapH::insert(pair<string,int> par){
	//si se llena se hace rehashing
	if(sizen==prime_table[rehash_pos-1]){
		rehashing();

	}
	int hashPos=hash_1(par.first); //valor de posicion a guardar sin colision
	if(!(hash_table.at(hashPos).first=="AVAILABLE" || (hash_table[hashPos].first.size()==0 && hash_table[hashPos].second==0))){ //si hay colision
		int hashPos2=hash_2(par.first); //segundo hashing para caso con colision
		for(int i=1;i<=hash_size;i++){
			int newhashPos=(hashPos+i*hashPos2)%hash_size;
			//caso 1: se encuentra llave repetida
			if(par.first.compare(hash_table[newhashPos].first)==0){
				hash_table[newhashPos].second=par.second;
				cols_ins++;
				return;
			}
			//caso 2: se encuentra una posicion vacia
			if(hash_table.at(newhashPos).first=="AVAILABLE" || (hash_table[newhashPos].first.size()==0 && hash_table[newhashPos].second==0)){
				hash_table[newhashPos].first=par.first;
				hash_table[newhashPos].second=par.second;
				sizen++;
				return;
			}
			cols_ins++;
		}
	}
	//caso perfecto: encuentra la posicion vacia desde el primer hashing
	else{
		hash_table[hashPos].first=par.first;
		hash_table[hashPos].second=par.second;
		sizen++;
		return;
	}
}
//funcion para eliminar llave
void MapH::erase(string k){
	int hashPos=hash_1(k);
	int hashPos2=hash_2(k);
	int i=0;
	//compara la posicion generada por el double hashing y se va aumentando el contador de colisiones 
	while(k.compare(hash_table[(hashPos+i*hashPos2)%hash_size].first)!=0){
		if(hash_table[(hashPos+i*hashPos2)%hash_size].first.size() ==0 && hash_table[(hashPos+i*hashPos2)%hash_size].second ==0)
			return;
		i++;
	}
	//marca la posicion eliminada como disponible y se disminuye el contador de tamaño
	hash_table[(hashPos+i*hashPos2)%hash_size].first="AVAILABLE";
	sizen--;
}
int MapH::at(string k){
	int hashPos=hash_1(k);
	int hashPos2=hash_2(k);
	int i=0;
	//se compara en la posicion del DH, si se encuentra con una posicion vacia termina la busqueda
	// y se asume que no existe tal clave
	while(k.compare(hash_table[(hashPos+i*hashPos2)%hash_size].first)!=0){
		if(hash_table[(hashPos+i*hashPos2)%hash_size].first.size() ==0 && hash_table[(hashPos+i*hashPos2)%hash_size].second ==0)
			return INT_MAX;
		i++;
		cols_at++;
	}
	return hash_table[(hashPos+i*hashPos2)%hash_size].second;
}
int MapH::size(){
	return sizen;
}

bool MapH::empty(){
	if(!sizen)
		return true;
	return false;
}	


int MapH::getCols_ins(){
	return cols_ins;
}

int MapH::getCols_at(){
	return cols_at;
}
