/*#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/ostreamwrapper.h"*/
#include "VSPtr.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "GarbageCollector.hpp"

//using namespace rapidjson;
using namespace std;

void func(){
    VSPTR<double> myPtr = VSPTR<double>::New();
    *myPtr = 7;

}

void func2(){
    VSPTR<int> myPtr = VSPTR<int>::New();
    *myPtr = 9;

}

void activar_thread(){
    Collector *garbage = Collector::myCollector();
    garbage->llamador();

}

int main() {
    

    /*int a;
    const char *b = typeid(a).name();
    if(*b == 'i')
        cout<<"entero";*/
    
    thread thr(activar_thread);
    VSPTR<int> myPtr = VSPTR<int>::New();
    cout << "1\n";
    *myPtr = 5;
    cout << "2\n";
    int valor;
    cout << "3\n";
    valor = &myPtr;
    cout << valor<<"\n";
    sleep(4);
    func();
    sleep(4);
    func2();
    sleep(4);
    thr.join();
    //cout<<"hola";
}
