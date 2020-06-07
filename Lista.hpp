#include "VSPtr.hpp"

template <typename N>
class Nodo{
    private:
        VSPTR<N> *dato;
        int referencias = 0;
        Nodo *sig;
        Nodo *ant;
    public:
        Nodo(VSPTR<N> &newDato){
           dato = newDato; 
        };
        void agregar_referencia(){
            this->referencias++;
        }
        void quitar_referencia(){
            this->referencias--;
        }
};




template <typename L>
class Lista
{
private:
    Nodo<L> *head;
    
public:
    Lista(){
        this->head = NULL;
    }
    Nodo crearNodo(L &newDato){
        Nodo<L> *newNodo = new Nodo<L>();
    }
};



