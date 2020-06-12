#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H

#include "Lista.hpp"


//template <typename T>
using namespace rapidjson;

class Collector{
    private:
        // primer espacio memEspc, segundo espacio
        int referenceCnt;
        static Collector *garbageColector;

    public:
        /*int *memSps[3];
        int referencias[3];*/
        static bool collector_activado;
        Lista<int> *lista = new Lista<int>();
        Lista<double> *listaD = new Lista<double>();
        Lista<long> *listaL = new Lista<long>();
        Lista<float> *listaF = new Lista<float>();
        Lista<char> *listaC = new Lista<char>();

        Collector();

        ~Collector();

        void llamador();

        static Collector *myCollector();

        int addPtr(int *memEspc);
        
        int addPtr(double *memEspc);

        int addPtr(float *memEspc);

        int addPtr(long *memEspc);

        int addPtr(char *memEspc);

        void dereference(int id);

        void reference(int id);

        void garbage();

        void addJsonObj(string espacio,string dato, string id, string ref, string tipo);

        static void vaciarJson();

        void modificarJson(string id, string referencias);

        void delJson(string id);

};   
#endif