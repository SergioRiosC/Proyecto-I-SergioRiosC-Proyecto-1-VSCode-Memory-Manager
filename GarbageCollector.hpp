#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H


//template <typename T>

class Collector{
    private:
        // primer espacio memEspc, segundo espacio
        int referencias[3][2];
        int referenceCnt;
        static Collector *garbageColector;

    public:
        Collector();

        static Collector *myCollector(){}


        int addPtr(int *memEspc){}

        void dereference(int id){}

        void reference(int id){}

        void garbage(){}

};

#endif