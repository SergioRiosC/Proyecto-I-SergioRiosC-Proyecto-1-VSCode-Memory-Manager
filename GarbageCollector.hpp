#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H


//template <typename T>

class Collector{
    private:
        // primer espacio memEspc, segundo espacio
        int referenceCnt;
        static Collector *garbageColector;

    public:
        int *memSps[3];
        int referencias[3];

        Collector();

        ~Collector();

        void llamador();

        static Collector *myCollector();

        int addPtr(int *memEspc);

        void dereference(int id);

        void reference(int id);

        void garbage();

};

#endif