
#include "GarbageCollector.hpp"
#include <thread>
#include "pthread.h"
#include <chrono>
#include <sstream>
//#include "Lista.hpp"

using namespace std;

bool  Collector::collector_activado = false;
Collector* Collector::garbageColector = NULL;
/**
 * @brief Constructor del garbage collector
 * @author Mat
 * */
Collector::Collector(){
    referenceCnt = 0;
    garbageColector = NULL;
}

/**
 * @brief Destructor del Garbage collector
 * @author Mat
*/
Collector::~Collector(){
    cout<<"Se dejó de llamar al GarbageCollector";
    collector_activado = false;
}

/**
 * @brief Inicializa el Garbage Collector
 * @author Mat
 */
Collector *Collector::myCollector(){
    if(garbageColector == NULL){
        garbageColector = new Collector();
        cout<<"Se inicializo el Garbage\n";
        collector_activado = true;

    }
    return garbageColector;
}
/**
 * @brief Funcion para vaciar el archivo JSON
 * */
void Collector::vaciarJson(){
    ifstream url("JSONFiles/prueba.json");
    IStreamWrapper isw(url);
    Document doc;
    doc.ParseStream(isw);
    doc.RemoveAllMembers();
    ofstream ofs2("JSONFiles/prueba.json");
    OStreamWrapper osw(ofs2);
    Writer<OStreamWrapper> writer2(osw);
    doc.Accept(writer2);
}
/**
 * @brief Agrega un dato de tipo int a la lista de referencias del Garbage Collector y le nasigna un espacio de memoria
 * @author Mat
 * @param memEspc Puntero hacia el dato del VSPTR
 * @return id del VSPTR
 * @overload
 */
int Collector::addPtr(int *memEspc){
        garbageColector->lista->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        
        ostringstream la;
        static_cast<ostringstream&>(la<<memEspc).str();
        string strEspacio = la.str();
        
        stringstream ssM,ssCnt,ssR;
        ssCnt<<referenceCnt;
        ssR<<1;
        ssM<<*memEspc;

        addJsonObj(strEspacio.c_str(),ssM.str().c_str(), ssCnt.str().c_str(), ssR.str().c_str(), "int");

        return garbageColector->referenceCnt++;
}
/**
 * @brief Agrega un dato de tipo double a la lista de referencias del Garbage Collector y le nasigna un espacio de memoria
 * @author Mat
 * @param memEspc Puntero hacia el dato del VSPTR
 * @return id del VSPTR
 * @overload
 */
int Collector::addPtr(double *memEspc){
        garbageColector->listaD->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        
        ostringstream la;
        static_cast<ostringstream&>(la<<memEspc).str();
        string strEspacio = la.str();
        
        stringstream ssM,ssCnt,ssR;
        ssCnt<<referenceCnt;
        ssR<<1;
        ssM<<*memEspc;

        addJsonObj(strEspacio.c_str(),ssM.str().c_str(), ssCnt.str().c_str(), ssR.str().c_str(), "double");

        
        
        return garbageColector->referenceCnt++;
}
/**
 * @brief Agrega un dato de tipo float a la lista de referencias del Garbage Collector y le nasigna un espacio de memoria
 * @author Mat
* @param memEspc Puntero hacia el dato del VSPTR
 * @return id del VSPTR
 * @overload
 */
int Collector::addPtr(float *memEspc){
        garbageColector->listaF->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        
        ostringstream la;
        static_cast<ostringstream&>(la<<memEspc).str();
        string strEspacio = la.str();
        
        stringstream ssM,ssCnt,ssR;
        ssCnt<<referenceCnt;
        ssR<<1;
        ssM<<*memEspc;

        addJsonObj(strEspacio.c_str(),ssM.str().c_str(), ssCnt.str().c_str(), ssR.str().c_str(), "float");

        return garbageColector->referenceCnt++;
}
/**
 * @brief Agrega un dato de tipo long a la lista de referencias del Garbage Collector y le nasigna un espacio de memoria
 * @author Mat
 * @param memEspc Puntero hacia el dato del VSPTR
 * @return id del VSPTR
 * @overload
 */
int Collector::addPtr(long *memEspc){
        garbageColector->listaL->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        
        ostringstream la;
        static_cast<ostringstream&>(la<<memEspc).str();
        string strEspacio = la.str();
        
        stringstream ssM,ssCnt,ssR;
        ssCnt<<referenceCnt;
        ssR<<1;
        ssM<<*memEspc;

        addJsonObj(strEspacio.c_str(),ssM.str().c_str(), ssCnt.str().c_str(), ssR.str().c_str(), "long");

        return garbageColector->referenceCnt++;
}
/**
 * @brief Agrega un dato de tipo char a la lista de referencias del Garbage Collector y le nasigna un espacio de memoria
 * @author Mat
 * @param memEspc Puntero hacia el dato del VSPTR
 * @return id del VSPTR
 * @overload
 */
int Collector::addPtr(char *memEspc){
        garbageColector->listaC->agregarNodo(memEspc,referenceCnt);
        cout<<"Se agrego "<<garbageColector->referenceCnt<<"\n";
        cout<<"Espacio de memoria " <<memEspc<<"\n";
        cout<<"Referencias a la id " <<referenceCnt <<": " <<1<<"\n";
        
        ostringstream la;
        static_cast<ostringstream&>(la<<memEspc).str();
        string strEspacio = la.str();
        
        stringstream ssM,ssCnt,ssR;
        ssCnt<<referenceCnt;
        ssR<<1;
        ssM<<*memEspc;

        addJsonObj(strEspacio.c_str(),ssM.str().c_str(), ssCnt.str().c_str(), ssR.str().c_str(), "char");

        return garbageColector->referenceCnt++;
}
/**
 * @brief Busca el VSPR en las listas y le decrementa la referencia 
 * @param id Identificador de un VSPTR
 * @author Mat
 * */
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

/**
 * @brief Busca el VSPTR en las listas y le incrementa la referencia
 * @author Mat
 * @param id Identificador de un VSPTR
*/
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

/**
 * @brief Busca en todos los nodos datos que no tengan referencia y los elimina
 * @author Mat
 * */
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
}

/**
 * @brief Funcion encargada de llamar al garbage collector cada segundo
 * @author Mat
 * */
void Collector::llamador(){
    while (collector_activado)
    {        
        cout<<"Se está llamando al GarbageCollector \n";
        garbageColector->garbage();
        std::this_thread::sleep_for(std::chrono::seconds(1));        
    }
    
}

/**
 * @brief Funcion encargada de crear el JSON con los datos de los VSPTR
 * @param espacio Espacio de memoria del dato a almacenar en JSON
 * @param dato Dato a guardar en el JSON
 * @param id Id del VSPTR a almacenar en JSON
 * @param ref Numero de referencias del dato a guardar 
 * @param tipo Tipo de dato a guardar
 * */
void Collector::addJsonObj(string espacio,string dato, string id, string ref, string tipo ){
    
    ifstream url("JSONFiles/prueba.json");
    IStreamWrapper isw(url);
    Document doc;
    doc.ParseStream(isw);
    
    Value o(kObjectType);
    {
        
        Value vEspacio;
        Value vDato;
        Value vRef;
        Value vTipo;
        vEspacio = StringRef(espacio.c_str());
        vDato = StringRef(dato.c_str());
        vRef = StringRef(ref.c_str());
        vTipo = StringRef(tipo.c_str());

        o.AddMember("Dato", vDato, doc.GetAllocator());  // deep clone contacts (may be with lots of allocations)
        o.AddMember("Tipo de dato", vTipo, doc.GetAllocator());  // deep clone contacts (may be with lots of allocations)
        o.AddMember("Espacio en memoria", vEspacio, doc.GetAllocator());  // deep clone contacts (may be with lots of allocations)
        o.AddMember("Referncias", vRef, doc.GetAllocator());  // deep clone contacts (may be with lots of allocations)
        
    }

    
    //Value name;
    //name = StringRef();
    doc.AddMember(StringRef(id.c_str()),o,doc.GetAllocator());//Agrega al archivo
    //int x = 1;
    /*if(x == 1){
        if(doc.HasMember("valor"))//***
           // doc.EraseMember("valor");//Elimina elementos del doc***
    }*/
    ofstream ofs2("JSONFiles/prueba.json");
    OStreamWrapper osw(ofs2);
    Writer<OStreamWrapper> writer2(osw);
    doc.Accept(writer2);
}