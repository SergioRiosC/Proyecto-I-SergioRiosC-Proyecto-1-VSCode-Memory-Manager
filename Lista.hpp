#include<iostream>

using namespace std;


/*class AbsNodo{
    private:
        int id;
        int referencias;
};*/


template <typename N>
class Nodo{
    //friend class Lista<N>;
private:
    N *memEspc;
    int id;
    int referencias = 0;
    Nodo *sig;
    Nodo *ant;
public:

    Nodo(N *newDato, int id){
        this->memEspc = newDato; 
        this->id = id;
        this->referencias++;
        this->sig = NULL;
        cout<<"Desde Nodo(): dato = "<<*newDato<<" memEspc = "<<newDato<<"\n";
    };

    void agregar_referencia(){
        this->referencias++;
    }

    void quitar_referencia(){
        this->referencias--;
    }

    int getReferencias(){
        return referencias;
    }

    void setReferenecias(int newRef){
        this->referencias = newRef;
    }

    void setSig(Nodo<N> *setter){
        this->sig = setter;
    }

    Nodo<N> *getSig(){
        return this->sig;
    }

    void setAnt(Nodo<N> *setter){
        this->ant = setter;
    }

    Nodo<N> *getAnt(){
        return this->ant;
    }

    int getId(){
        return this->id;
    }

    void setId(int id){
        this->id = id;
    }
    N *getMemEspc(){
        return this->memEspc;
    }

};




template <typename L>
class Lista{
private:
    Nodo<L> *head;
    Nodo<L> *tail;
    
public:
    Lista(){
        head = NULL;
        tail = NULL;
    };
    /*static Lista<L> New(){
        return *Lista<L>();
    };*/

    Nodo<L> *getHead(){
        return this->head;
    }

    bool vacia(){
        if(this->head == NULL && this->tail == NULL){
            return true;
        }else
        {
            return false;
        }
        
    }
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

    void reference(int id){
        Nodo<L> *aux = buscarNodo(id);
        if(aux!=NULL){

            aux->agregar_referencia();
            cout << "Referencias a la id " << id <<": " << aux->getReferencias() <<"\n";
        
        }else
            cout<<"Desde reference: No se encontro el nodo"<<id<<"\n";
        
    }

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
            
            return true;
        
        }else
            cout<<"Desde dereference: No se encontro el nodo"<<id<<"\n";

            return false;
        
    }

    int getReferencias(int id){
        Nodo<L> *aux = buscarNodo(id);
        if(aux != NULL){
            return aux->getReferencias();
        }else
        {
            cout<<"No se encontro el nodo"<<id;
            return 0;
        }
    }

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

    /*void eliminarNodo(int id){
        cout<<"se intenta borrar "<<id<<"\n";
        Nodo<L> *aux = buscarNodo(id);
        if(aux->getAnt() != NULL)
            aux->getAnt()->setSig(aux->getSig());
        if(aux->getSig() != NULL)
            aux->getSig()->setAnt(aux->getAnt());
        //aux->ant->sig = aux->sig;
        //aux->sig->ant = aux->ant;
        delete aux;

    }*/
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
        //aux->ant->sig = aux->sig;
        //aux->sig->ant = aux->ant;
        delete nodo->getMemEspc();
        delete nodo;

    }

};


