
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
    };
    
    


public:
    static VSPTR<T> New(){
        return VSPTR<T>();
    };
    
    ~VSPTR(){
        cout<<"ID="<<this->id<<"\n";
        if(this->id != -1){
            delete[] dato;
            cout<<"se elimino\n";
        }
    };

    VSPTR<T> operator *(){
        return *this;
    };

    void  operator =(T dato){

        if(this->id == -1){
            *this->dato = dato;
            this->id = ;
            cout<<"ID operador ="<<this->id<<"\n";
        }
    };


    T operator&(){
        return *(dato);
    };

    

};

