
template <typename T>
class VSPTR{
private:
    T *dato;
    VSPTR(){
        dato = new T();
    };
    


public:
    static VSPTR<T> New(){
        return VSPTR<T>();
    };
    VSPTR<T> operator *(){
        return *this;
    }
    // T& operator=()
    void  operator =(T dato){
        *this->dato = dato;
    }

    T operator&(){
        return *(dato);
    }
    /*void operator &(VSPTR){
        return this.dato;
    }*/

};

