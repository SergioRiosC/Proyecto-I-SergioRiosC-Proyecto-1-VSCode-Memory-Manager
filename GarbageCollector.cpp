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
        garbageColector->lista->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        return garbageColector->referenceCnt++;
}

int Collector::addPtr(double *memEspc){
        garbageColector->listaD->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        return garbageColector->referenceCnt++;
}

int Collector::addPtr(float *memEspc){
        garbageColector->listaF->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        return garbageColector->referenceCnt++;
}

int Collector::addPtr(long *memEspc){
        garbageColector->listaL->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        return garbageColector->referenceCnt++;
}

int Collector::addPtr(char *memEspc){
        garbageColector->listaC->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        return garbageColector->referenceCnt++;
}

void Collector::dereference(int id){
    if (id != -1)
    {
        
        if(garbageColector->lista->dereference(id))
            return;
        else if(garbageColector->listaD->dereference(id))
            return;
        else if(garbageColector->listaF->dereference(id))
            return;
        else if(garbageColector->listaL->dereference(id))
            return;
        else if(garbageColector->listaC->dereference(id))
            return;
        //garbageColector->garbage();
    }
            
}

void Collector::reference(int id){
    if (id != -1)
    {
        garbageColector->lista->reference(id);
        garbageColector->listaD->reference(id);
        /*garbageColector->listaF->reference(id);
        garbageColector->listaL->reference(id);
        garbageColector->listaC->reference(id);*/
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
    
    Nodo<float> *aux3 = garbageColector->listaF->getHead();
    while(aux3 != NULL){
        if(aux3->getReferencias() == -1)
            garbageColector->listaF->eliminarNodo(aux3);
        aux3 = aux3->getSig();
    }
    
    Nodo<long> *aux4 = garbageColector->listaL->getHead();
    while(aux4 != NULL){
        if(aux4->getReferencias() == -1)
            garbageColector->listaL->eliminarNodo(aux4);
        aux4 = aux4->getSig();
    }
    
    Nodo<char> *aux5 = garbageColector->listaC->getHead();
    while(aux5 != NULL){
        if(aux5->getReferencias() == -1)
            garbageColector->listaC->eliminarNodo(aux5);
        aux5 = aux5->getSig();
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