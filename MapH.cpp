#include "MapH.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

MapH :: MapH(int n){
    tamV=n/2;//tamanio vector
    tam2=0;//tamanio de inserciones y erase
    posicion=0;
    numhash=0;
    colisiones_at=0;
    colisiones_insert=0;
    listita = new vector<pair<string,int>>(tamV, make_pair(string(),0));
   
}

MapH :: ~MapH(){
    delete[] listita;
}

void MapH ::insert(pair<string, int> lista){
    //para ver el factor de carga 
    double tamanito=tam2/tamV;
    //si el factor de carga es mayor al 0.5 se agranda el vector
    if(tamanito >= 0.5){
        agrandar();
    }
    //se saca la posible posicion con el hashing
    posicion= hashingpolinomial(lista.first)%tamV;
   
    if(listita->at(posicion).first == string()){//inserta cuando ya encontro un lugar
        listita->at(posicion).first= lista.first;
        listita->at(posicion).second= lista.second;
        ++tam2;
    }else{//caso para cuando no encontro un lugar
        int p_inicial,cont=0;
        ++colisiones_insert;//aumenta por que hubo una colision
        //se saca una nueva posicion
        posicion= (hashingpolinomial(lista.first)%tamV + segundahashing(lista.first));
        p_inicial=posicion;
        bool inserto= true;
        while(inserto){
            //se inicia con la busqueda de un nuevo lugar para insertar
            if(listita->at(posicion).first == string()){//cuando encuentra lugar se inserta y se sale del ciclo
                listita->at(posicion).first= lista.first;
                listita->at(posicion).second= lista.second;
                ++tam2;
                inserto=false;break;
            }else{//si no busca otra posicion para poder insertar
                posicion= posicion + segundahashing(lista.first);
            }
            if(posicion>tamV){
                //si la posicion da mayor que el tamaño para dar la vuelta saca las diferencia entre la 
                //posicion y el tamaño del vector y empieza a buscar posiciones donde insertar desde esa diferencia
                int diferencia= posicion-tamV;
                posicion=diferencia;
                ++cont;
            }
            if(posicion==p_inicial && cont!=0){//si ya dio vueltas y no encontro lugar para insertar 
            //sale del ciclo
                inserto=false;break;
            }
            ++colisiones_insert;//aumenta por que hubo colisiones
        }
    }   
}

void MapH ::agrandar(){
    // se agranda el tamano al doble para tener un vector nuevo con el doble del tamano que 
    // vector original
    tamV=tamV*2;
    //se crea el vector pair con un tamano y se iniciliza todo el vector con string defaul y entero -1
    vector<pair<string,int>> *agrandando = new vector<pair<string,int>>(tamV,make_pair(string(),0));
    for(int i=0 ; i< tamV; ++i){
        //para el caso en que si haya colision pase a insertar al siguiente como solo es volver a poner 
        //el string junto con su numero solo hay que ver el caso de colison y si se tiene que insertar
        //al principio del vector pair
        if(listita->at(i).first != string()){
            //si el lugar es disstinto del string defaul es por que tiene insertado algo 
            //por lo tanto entra a la condicion, donde volveremos a sacar la posicion 
            //y lo insertaremos en la posicion "nueva"  
            posicion= hashingpolinomial(listita->at(i).first)%tamV;
            if(listita->at(posicion).first == string()){//cuando encuentra lugar se inserta y se sale del ciclo
                agrandando->at(posicion).first=listita->at(posicion).first;
                agrandando->at(posicion).second=listita->at(posicion).second;  
            }else{
                int p_inicial,cont=0;
                posicion= (hashingpolinomial(listita->at(posicion).first)%tamV + segundahashing(listita->at(posicion).first));
                p_inicial=posicion;
                bool inserto= true;
                while(inserto){
                    if(listita->at(posicion).first == string()){
                        agrandando->at(posicion).first=listita->at(posicion).first;
                        agrandando->at(posicion).second=listita->at(posicion).second;  
                        inserto=false;break;
                    }else{//si no busca otra posicion para poder insertar
                        posicion= posicion + segundahashing(listita->at(posicion).first);
                    }
                    if(posicion>tamV){
                        //si la posicion da mayor que el tamaño para dar la vuelta saca las diferencia entre la 
                //posicion y el tamaño del vector y empieza a buscar posiciones donde insertar desde esa diferencia
                        int diferencia= posicion-tamV;
                        posicion=diferencia;
                        ++cont;
                    }
                    //si ya dio vueltas y no encontro lugar para insertar se sale del ciclo
                    if(posicion==p_inicial && cont!=0){
                        inserto=false;break;
                    }
                }
            }
        }
    }
    // cuando todo este insertado en el vector nuevo borramos el anterior vector 
    //y le a ese vector le pasamos su nueva forma igualandolo al vector nuevo
    delete[] listita;
    listita = agrandando;
}


void MapH ::erase(string llave){
    //se saca la posible posicion con el hashing
    posicion= hashingpolinomial(llave)%tamV;
   
    if(listita->at(posicion).first == string()){//cuando encuentra la llave se borra y se sale del ciclo
        listita->at(posicion).first= "#";
        listita->at(posicion).second= -1;
        --tam2;
    }else{//caso para cuando no encontro la llave a borrar
        int p_inicial,cont=0;
        //se saca una nueva posicion
        posicion= (hashingpolinomial(llave)%tamV + segundahashing(llave));
        p_inicial=posicion;
        bool inserto= true;
        while(inserto){
            //se inicia con la busqueda de la llave para borrarla
            if(listita->at(posicion).first == llave){//cuando encuentra la llave se borra y se sale del ciclo
                listita->at(posicion).first= "#";
                listita->at(posicion).second= -1;
                --tam2;
                inserto=false;break;
            }else{//si no busca otra posicion para poder encontrar la llave
                posicion= posicion + segundahashing(llave);
            }
            if(posicion>tamV){
                //si la posicion da mayor que el tamaño para dar la vuelta saca las diferencia entre la 
                //posicion y el tamaño del vector y empieza a buscar posiciones donde insertar desde esa diferencia
                int diferencia= posicion-tamV;
                posicion=diferencia;
                ++cont;
            }
            if(posicion==p_inicial && cont!=0){//si ya dio vueltas y no encontro lugar para insertar 
            //sale del ciclo
                inserto=false;break;
            }
        }
    }
    
}

int MapH ::at(string llave){
//se saca la posible posicion con el hashing
    posicion= hashingpolinomial(llave)%tamV;
   
    if(listita->at(posicion).first == llave){//retornael numero cuando encuentra la misma llave
        return listita->at(posicion).second;
    }else{
        int p_inicial,cont=0;
        ++colisiones_at;//aumenta cuando encuentra colisiones
        //saca la nueva posicion puesto que hubo colision y tiene que buscar la llave
        posicion= (hashingpolinomial(llave)%tamV + segundahashing(llave));
        p_inicial=posicion;
        bool inserto= true;
        while(inserto){
            //si encuentra la llave retorna el numero 
            if(listita->at(posicion).first == llave){
                return listita->at(posicion).second;
                inserto=false;break;
            }else{
                //saca la nueva posicion a traves de un segundo hashing puesto que hubo colision
                posicion= posicion + segundahashing(llave);
            }
            if(posicion>tamV){
                //si la posicion da mayor que el tamaño para dar la vuelta saca las diferencia entre la 
                //posicion y el tamaño del vector y empieza a buscar posiciones donde insertar desde esa diferencia
                int diferencia= posicion-tamV;
                posicion=diferencia;
                ++cont;
            }
            if(posicion==p_inicial && cont!=0){
                inserto=false;break;//para cuaando ya no encontro la llave que estaba buscando
            }
            ++colisiones_at;//se aumenta por que encuentra colisiones
        }
    }   
    return -1;     
}

int MapH ::size(){//retorna el numero de inserciones que se han hecho
   return tam2;
}

bool MapH ::empty(){//si se a insertado al menos una vez retorna true por el contrario si no se a insertado
//se retorna false
   if(tam2 != 0){
       return true;
   }else{
       return false;
   }
}

int MapH ::hashingpolinomial(string llavesita){//aqui se trata de hacer un buen hash usando hash polinomial
   int  suma=0, poli=11;
   for(int i=0; i< llavesita.length();++i){
       suma= suma + (int)llavesita[i]*pow(poli,i);
   }
   return suma; 
}
int MapH :: segundahashing(string llavesita){
    int poli=7;
    int segundohahing= poli - (hashingpolinomial(llavesita)%poli);
    return segundohahing;
}
int MapH::getcolisionesat(){
    return colisiones_at;
}

int MapH::getcolisionesinsert(){
    return colisiones_insert;
}