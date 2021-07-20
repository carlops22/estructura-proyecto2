#ifndef ADTMAP_H
#define ADTMAP_H
#include<string>
#include<utility>

using namespace std;

class ADTMap{
	public:
		virtual void insert(pair<string,int>) = 0;
		virtual void erase(string)= 0;
		virtual int at(string)= 0;
		virtual int size() = 0;
		virtual bool empty()=0;
};


#endif