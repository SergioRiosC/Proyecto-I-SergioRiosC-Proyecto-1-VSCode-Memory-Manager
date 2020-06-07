#include "GarbageCollector.hpp"
#include <iostream>
#include <thread>
#include "pthread.h"
#include <chrono>

using namespace std;

bool collector_activado = false;
Collector* Collector::garbageColector = NULL;

Collector::Collector(){
    referenceCnt = 0;
    garbageColector = NULL;
}

Collector::~Collector(){
    cout<<"Se dejó de llamar al GarbageCollector";
    collector_activado = false;
}

Collector *Collector::myCollector(){
    if(garbageColector == NULL){
        garbageColector = new Collector();
        cout<<"Se inicializo el Garbage\n";
        collector_activado = true;
    }
    return garbageColector;
}

int Collector::addPtr(int *memEspc){
    if(garbageColector->referenceCnt != 3){
        garbageColector->memSps[referenceCnt] = memEspc;
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        garbageColector->referencias[referenceCnt]++;
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<garbageColector->referencias[referenceCnt]<<"\n";
        return garbageColector->referenceCnt++;
    }
    return -1;
}

void Collector::dereference(int id){
    if (id != -1)
    {
        if(garbageColector->referencias[id] == 1){
            garbageColector->referencias[id] -= 2;
        }
        else
            garbageColector->referencias[id]--;
        cout<<"Referencias a la id " <<id <<": " <<garbageColector->referencias[id]<<"\n";
        //garbageColector->garbage();
    }
            
}

void Collector::reference(int id){
    if (id != -1)
    {
        garbageColector->referencias[id]++;
        cout<<"Referencias a la id " <<id <<": " <<garbageColector->referencias[id]<<"\n";
    } 
}

void Collector::garbage(){
    for(int i=0;i<garbageColector->referenceCnt;i++){
        if (garbageColector->referencias[i] == -1)
        {
            cout<<"se intenta borrar "<<i<<"\n";
            int *ptr;
            ptr = garbageColector->memSps[i]; 
            delete[] ptr;
            garbageColector->referencias[i] = 0;
        }
        
    }
}

void Collector::llamador(){
    while (collector_activado)
    {        
        //cout<<"Se está llamando al GarbageCollector \n";
        garbageColector->garbage();
        //std::this_thread::sleep_for(std::chrono::seconds(1));        
    }
    
}