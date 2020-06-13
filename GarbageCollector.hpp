#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/ostreamwrapper.h"
#include "Lista.hpp"
#include <fstream>
#include <unistd.h>


//template <typename T>
using namespace rapidjson;
/**
 * @brief Clase que inicializa el garbage collector, este gestiona la memoria que usara el programador
 * @author Mat
 * */
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

        void garbage();void addJsonObj(string espacio,string dato, string id, string ref, string tipo);

        static void vaciarJson();

        void modificarJson(string id, string referencias);

        void delJson(string id);
};   
#endif