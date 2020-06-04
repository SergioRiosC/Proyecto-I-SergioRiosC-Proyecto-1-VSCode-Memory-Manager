
#include <iostream>
#include <random>
#include "GarbageCollector.hpp"

using namespace std;

template <typename T>
class VSPTR{
private:
    T *dato;
    int id;
    VSPTR(){
        dato = new T();
        id = -1;
        Collector::myCollector(); 
    };
    
    


public:
    static VSPTR<T> New(){
        return VSPTR<T>();
    };
    
    ~VSPTR(){
        cout<<"ID="<<this->id<<"\n";
        if(this->id != -1){
            Collector* collector =Collector::myCollector();            
            collector->dereference(this->id);
        }
    };

    VSPTR<T> operator *(){
        return *this;
    };

    void  operator =(T dato){

        if(this->id == -1){
            *this->dato = dato;
            this->id = Collector::myCollector()->addPtr(&*this->dato);
            cout<<"ID operador ="<<this->id<<"\n";
            
            Collector::myCollector()->reference(this->id);
        }else
        {
            *this->dato = dato;
        }
        
    };


    T operator&(){
        return *(dato);
    };

    

};

