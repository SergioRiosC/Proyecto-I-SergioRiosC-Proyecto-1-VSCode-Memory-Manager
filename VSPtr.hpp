
#include <iostream>
#include <random>
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
        if(this->id != -1){
            delete[] dato;
            cout<<"se elimino";
        }
    };

    VSPTR<T> operator *(){
        return *this;
    };

    void  operator =(T dato){
        *this->dato = dato;
    };


    T operator&(){
        return *(dato);
    };

    

};

