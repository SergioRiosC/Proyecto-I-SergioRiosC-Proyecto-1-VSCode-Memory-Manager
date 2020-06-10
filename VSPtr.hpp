#include "GarbageCollector.cpp"

using namespace std;

template <typename T>
class VSPTR{
private:
    T *dato;
    int id;  
    
public:

    VSPTR(){
        dato = new T();
        cout<<"nuevo espacio de memoria "<<dato<<"\n";
        id = -1;
        Collector::myCollector(); 
    };
    static VSPTR<T> New(){
        return VSPTR<T>();
    };
    
    ~VSPTR(){
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
            this->id = Collector::myCollector()->addPtr(this->dato);
           
            
            
            //cout<<"ID operador ="<<this->id<<"\n";
            
            //Collector::myCollector()->reference(this->id);
        }else
        {
            *this->dato = dato;
        }
        
    };


    T operator&(){
        return *(dato);
    };

    

};

