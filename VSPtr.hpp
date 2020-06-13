
#include <iostream>
#include <random>
#include "GarbageCollector.cpp"

using namespace std;

template <typename T>
/**
 *@author Mathiw
 *@brief clase que instancia los VSPtr 
 */
class VSPTR{
private:
    T *dato;
    int id;  
    
public:

/**
 * @author Mathiw
 * @brief Constructor de la clase VSPTR
 * 
 * */
    VSPTR(){
        dato = new T();
        cout<<"nuevo espacio de memoria "<<dato<<"\n";
        id = -1;
        Collector::myCollector(); 
    };

/**
 * @author Mathiw
 * @brief Funcion que se encarga de sobrecargar la funcion New()
 * 
 * */
    static VSPTR<T> New(){
        return VSPTR<T>();
    };
    
/**
 * @author Mathiw
 * @brief Destructor de VSPTR
 * 
 * */
    ~VSPTR(){
        if(this->id != -1){
            Collector* collector =Collector::myCollector();            
            collector->dereference(this->id);
        }
    };

/**
 * @author Mathiw
 * @brief Funcion que se encarga de sobrecargar el operador *
 * @return dato dereferenciado
 * */

    VSPTR<T> operator *(){
        return *this;
    };



/**
 * @author Mathiw
 * @brief Funcion que se encarga de sobrecargar  el operador =
 * @param dato Dato a ser evaluado por el operador =
 * 
 * */
    void  operator =(T dato){

        if(this->id == -1){
            *this->dato = dato;
            this->id = Collector::myCollector()->addPtr(this->dato);
            //cout<<"ID operador ="<<this->id<<"\n";
            
            //Collector::myCollector()->reference(this->id);
        }else
        {
            *this->dato = dato;
        }
        
    };


/**
 * @author Mathiw
 * @brief Funcion que se encarga de
 * @return dato referenciado
 * */
    T operator&(){
        return *(dato);
    };

    

};