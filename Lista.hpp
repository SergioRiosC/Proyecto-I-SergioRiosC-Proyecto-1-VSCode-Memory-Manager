
#include<iostream>
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/ostreamwrapper.h"
#include <fstream>
#include <unistd.h>
#include <sstream>

using namespace std;
using namespace rapidjson;


template <typename N>
/**
 * @brief Classe que contiene las listas enlazadas segun los tipos de datos
 * @author Mat
 * */
class Nodo{
    //friend class Lista<N>;
private:
    N *memEspc;
    int id;
    int referencias = 0;
    Nodo *sig;
    Nodo *ant;
public:
    /**
     * @brief Constructor de los nodos
     * @param newDato Espacio de memoria del dato 
     * @param id Identificador del dato
     * @author Mat
*/
    Nodo(N *newDato, int id){
        this->memEspc = newDato; 
        this->id = id;
        this->referencias++;
        this->sig = NULL;
        this->ant = NULL;
        cout<<"Desde Nodo(): dato = "<<*newDato<<" memEspc = "<<newDato<<"\n";
    };
/**
 * @brief Funcion para sumar las referencias del dato
 * @author Mat
 * */
    void agregar_referencia(){
        this->referencias++;
    }
/**
 * @brief Funcion para resta las referencias del dato
 * @author Mat
 * */
    void quitar_referencia(){
        this->referencias--;
    }

/**
 * @brief Funcion para obtener las referencias del dato
 * @author Mat
 * @return referencias del dato
 * */
    int getReferencias(){
        return referencias;
    }
/**
 * @brief Funcion para establecer las referencias del dato
 * @author Mat
 * */
    void setReferenecias(int newRef){
        this->referencias = newRef;
    }
/**
 * @brief Funcion para establecer el nodo siguiente 
 * @author Mat
 * @param setter Nodo al agregar el siguiente
 * */
    void setSig(Nodo<N> *setter){
        this->sig = setter;
    }
/**
 * @brief Funcion para obtener el nodo siguiente
 * @author Mat
 * @return nodo siguiente
 * */
    Nodo<N> *getSig(){
        return this->sig;
    }
/**
 * @brief Funcion para  asignar el siguiente nodo a otro nodo
 * @author Mat
 * @param setter nodo a asignar siguiente
 * */
    void setAnt(Nodo<N> *setter){
        this->ant = setter;
    }
/**
 * @brief Funcion para obtener el nodo anterior
 * @author Mat
 * @return Nodo anterior
 * */
    Nodo<N> *getAnt(){
        return this->ant;
    }
/**
 * @brief Funcion para obtener el id del dato
 * @author Mat
 * @return id del dato
 * */
    int getId(){
        return this->id;
    }
/**
 * @brief Funcion para asignar el id al dato
 * @author Mat
 * @param id id a asignar
 * */
    void setId(int id){
        this->id = id;
    }
   
   /**
 * @brief Funcion para obtener el espacio en memoria del dato
 * @author Mat
 * @return espacio en menoria del dato
 * */
    N *getMemEspc(){
        return this->memEspc;
    }

};




template <typename L>
/**
 * @brief Clase que contiene la lista enlazada de los datos
 * @author Mat
 * */
class Lista{
private:
    Nodo<L> *head;
    Nodo<L> *tail;
    
public:
/**
 * @brief constructor de la lista
 * @author Mat
 * */
    Lista(){
        head = NULL;
        tail = NULL;
    };
/**
 * @brief Funcion para obtener la cabeza de la lista
 * @author Mat
 * @return cabeza de la lista
 * */
    Nodo<L> *getHead(){
        return this->head;
    }
/**
 * @brief Funcion para saber si la lista esta vacia
 * @author Mat
 * @return true si esta vacia. False si no lo esta
 * */
    bool vacia(){
        if(this->head == NULL && this->tail == NULL){
            return true;
        }else
        {
            return false;
        }
        
    }
    
    /**
 * @brief Funcion para encontrar un nodo especifico
 * @author Mat
 * @param id id del nodo
 * @return nodo buscado
 * */
    Nodo<L> *buscarNodo(int id){
        if(this->head == NULL){
            return NULL;
        }else
        {
            Nodo<L> *aux = this->head;
            bool encontrado = false;
            while(aux != NULL && !encontrado){
                if(aux->getId() == id){
                    cout<<"se encontro el nodo "<<id<<"\n";
                    encontrado = true;            
                }else
                {
                    aux = aux->getSig();
                }
                
                
            }
            return aux;
        }
        
        
    }

/**
 * @brief Funcion para agregar referencias a un dato 
 * @author Mat
 * @param id id del nodo al que se le agregan las referencias
 * @return true si ecuentra el nodo. False si no lo encuentra
 * */
    bool reference(int id){
        Nodo<L> *aux = buscarNodo(id);
        if(aux!=NULL){

            aux->agregar_referencia();
            cout << "Referencias a la id " << id <<": " << aux->getReferencias() <<"\n";
            
            return true;
        }else{
            cout<<"Desde reference: No se encontro el nodo"<<id<<"\n";
            return false;
        }
    }

/**
 * @brief Funcion para quitar referencias a un dato 
 * @author Mat
 * @param id id del nodo que contiene el dato a dereferenciar
 * @return true si encuentra el nodo. False si no lo encuentra
 *
 * */
    bool dereference(int id){
        cout<<"Desde dereference: llamando buscador\n";
        Nodo<L> *aux = buscarNodo(id);
        if(aux != NULL){
            int auxReferencias = aux->getReferencias();
            if( auxReferencias == 1)
                aux->setReferenecias(auxReferencias - 2);
            else
                aux->setReferenecias(auxReferencias - 1);

            cout << "Referencias a la id " << id <<": " << aux->getReferencias() <<"\n";
            
            stringstream ssId;
            stringstream ssR;
            ssId<<id;
            ssR <<aux->getReferencias();
            
           //modificarJson(ssId.str().c_str(),ssR.str().c_str());
            return true;
        
        }else
            cout<<"Desde dereference: No se encontro el nodo"<<id<<"\n";

            return false;
        
    }

/**
 * @brief Funcion para agregar datos al archivo JSON 
 * @author Mat
 * @param id id del dato a agregar
 * @param referencias cantidad de referencias del dato
 * */
    void modificarRefJson(string id, string referencias){
        ifstream url("JSONFiles/prueba.json");
        IStreamWrapper isw(url);
        Document doc;
        doc.ParseStream(isw);
        Value o(kObjectType);
        //o = doc.FindMember(id.c_str()); 
        o = doc[id.c_str()];
        //cout<<o.GetString()<<"\n";
        Value::MemberIterator ref = o.FindMember("Referncias");
        ref->value.SetString(referencias.c_str(),doc.GetAllocator());
        ofstream ofs2("JSONFiles/prueba.json");
        OStreamWrapper osw(ofs2);
        Writer<OStreamWrapper> writer2(osw);
        doc.Accept(writer2);
    }

/**
 * @brief Funcion para agregar un nodo a la lista
 * @author Mat
 * @param newDato dato a agregar
 * @param id id del dato a agregar
 * */
    void agregarNodo(L *newDato, int id){
        if(vacia()){
           Nodo<L> * newPtr = new Nodo<L>(newDato, id); //creates new node
		   head = newPtr; //start and end pointer are same becuase there is only one object in list
		   tail = newPtr;
        }else //if node(s) exist in list insert additional object before the first
        {
            Nodo<L> * newPtr = new Nodo<L>(newDato, id);
            tail->setSig(newPtr); //the next pointer of the new node points to the node that was previously first
            newPtr->setAnt(tail);
            tail = newPtr; //the pointer for the new node is now the starting node
        }
    }

 
/**
 * @brief Funcion para eliminar contenido del archivo JSON
 * @author Mat
 * @param id id del dato a eliminar
 * */
    void delJson(string id){
        ifstream url("JSONFiles/prueba.json");
        IStreamWrapper isw(url);
        Document doc;
        doc.ParseStream(isw);
        if(doc.HasMember(id.c_str())){
            doc.EraseMember(id.c_str());
        }
        ofstream ofs2("JSONFiles/prueba.json");
        OStreamWrapper osw(ofs2);
        Writer<OStreamWrapper> writer2(osw);
        doc.Accept(writer2);
    }

/**
 * @brief Funcion para eliminar algun nodo de la  lista
 * @author Mat
 * @param nodo Nodo a eliminar
 * */
    void eliminarNodo(Nodo<L> *nodo){
        cout<<"se intenta borrar ID= "<<nodo->getId()<<"MemEspc= "<<nodo->getMemEspc()<<"\n";
        
        if(nodo->getAnt() != NULL && nodo->getSig() != NULL){
            nodo->getAnt()->setSig(nodo->getSig());
            nodo->getSig()->setAnt(nodo->getAnt());
        }
        else if(nodo->getAnt() != NULL)
            nodo->getAnt()->setSig(nodo->getSig());
        else if(nodo->getSig() != NULL)
            nodo->getSig()->setAnt(nodo->getAnt());
        else{
            this->head = NULL;
            this->tail = NULL;
        }

        stringstream ssId;
        ssId << nodo->getId();
        //delJson(ssId.str().c_str());

        //aux->ant->sig = aux->sig;
        //aux->sig->ant = aux->ant;
        delete nodo->getMemEspc();
        delete nodo;

    }

};