#include "GarbageCollector.hpp"
#include <iostream>

using namespace std;

Collector* Collector::garbageColector = NULL;



Collector::Collector(){
    referenceCnt = 0;
    garbageColector = NULL;
};

Collector *Collector::myCollector(){
    if(garbageColector == NULL){
        garbageColector = new Collector();
        cout<<"Se inicializo el Garbage\n";
    }
    return garbageColector;
};

int Collector::addPtr(int *memEspc){
    if(garbageColector->referenceCnt != 3){
        cout<<"Se agrego "<<referenceCnt<<"\n";
        garbageColector->referencias[referenceCnt][0] = *memEspc;
        garbageColector->referencias[referenceCnt][1]++;
        return garbageColector->referenceCnt++;
    }
    return -1;
};

void Collector::dereference(int id){
    if (id != -1)
    {
        if(garbageColector->referencias[id][1] == 1)
            garbageColector->referencias[id][1] -= 2;
        else
            garbageColector->referencias[id][1]--;
        garbageColector->garbage();
    }
            
};

void Collector::reference(int id){
    if (id != -1)
    {
        garbageColector->referencias[id][1]++;
    } 
};

void Collector::garbage(){
    for(int i=0;i<garbageColector->referenceCnt;i++){
        if (garbageColector->referencias[i][1] == -1)
        {
            cout<<"se intenta borrar "<<i<<"\n";
            int *ptr;
            ptr = &garbageColector->referencias[i][0]; 
            delete[] ptr;
        }
        
    }
};