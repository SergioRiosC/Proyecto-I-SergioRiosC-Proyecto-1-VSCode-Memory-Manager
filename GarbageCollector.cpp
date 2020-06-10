#include "GarbageCollector.hpp"
#include <iostream>
#include <thread>
#include "pthread.h"
#include <chrono>
//#include "Lista.hpp"

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
        garbageColector->lista->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        return garbageColector->referenceCnt++;
    }
    return -1;
}

int Collector::addPtr(double *memEspc){
    if(garbageColector->referenceCnt != 3){
        garbageColector->listaD->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        return garbageColector->referenceCnt++;
    }
    return -1;
}

void Collector::dereference(int id){
    if (id != -1)
    {
        
        garbageColector->lista->dereference(id);
        garbageColector->listaD->dereference(id);
        //garbageColector->garbage();
    }
            
}

void Collector::reference(int id){
    if (id != -1)
    {
        garbageColector->lista->reference(id);
    } 
}

void Collector::garbage(){
    Nodo<int> *aux = garbageColector->lista->getHead();
    while(aux != NULL){
        if(aux->getReferencias() == -1)
            garbageColector->lista->eliminarNodo(aux);
        aux = aux->getSig();
    }
    
    Nodo<double> *aux2 = garbageColector->listaD->getHead();
    while(aux2 != NULL){
        if(aux2->getReferencias() == -1)
            garbageColector->listaD->eliminarNodo(aux2);
        aux2 = aux2->getSig();
    }
    
    /*
    for(int i=0;i<garbageColector->referenceCnt;i++){
        
        if (garbageColector->lista->getReferencias(i) == -1)
        {
            garbageColector->lista->eliminarNodo(i);
        }
        
    }*/
}

void Collector::llamador(){
    while (collector_activado)
    {        
        cout<<"Se está llamando al GarbageCollector \n";
        garbageColector->garbage();
        std::this_thread::sleep_for(std::chrono::seconds(1));        
    }
    
}