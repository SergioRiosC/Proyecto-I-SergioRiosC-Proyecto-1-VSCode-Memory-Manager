/*#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/ostreamwrapper.h"*/
#include "VSPtr.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>

//using namespace rapidjson;
using namespace std;

void func(){
    VSPTR<int> myPtr = VSPTR<int>::New();
    *myPtr = 5;

}

int main() {
    VSPTR<int> myPtr = VSPTR<int>::New();
    cout << "1\n";
    *myPtr = 5;
    cout << "2\n";
    int valor;
    cout << "3\n";
    valor = &myPtr;
    cout << valor;
    func();
}
