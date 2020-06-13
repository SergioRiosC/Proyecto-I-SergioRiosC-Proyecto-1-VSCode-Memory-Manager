
#include "VSPtr.hpp"
#include "Cliente.cpp"
//#include "GarbageCollector.hpp"

//using namespace rapidjson;
using namespace std;

void func(){
    VSPTR<long> myPtr = VSPTR<long>::New();
    *myPtr = 7;

}

void func2(){
    VSPTR<float> myPtr = VSPTR<float>::New();
    *myPtr = 10;

}

void activar_thread(){
    Collector *garbage = Collector::myCollector();
    garbage->llamador();

}
/*int main() {
    ifstream url("JSONFiles/prueba.json");
    IStreamWrapper isw(url);
    Document doc;
    doc.ParseStream(isw);
    Value o(kObjectType);
    {
        Value j,k;
        j = "m";
        k = "n";
        o.AddMember("yo", j, doc.GetAllocator());  // deep clone contacts (may be with lots of allocations)
        o.AddMember("el", k, doc.GetAllocator());  // deep clone contacts (may be with lots of allocations)
        // destruct contacts.
    }
    doc.AddMember("contacts",o,doc.GetAllocator());//Agrega al archivo
    //int x = 1;
    /*if(x == 1){
        if(doc.HasMember("valor"))//***
           // doc.EraseMember("valor");//Elimina elementos del doc***
    }*/
    /*ofstream ofs2("JSONFiles/prueba.json");
    OStreamWrapper osw(ofs2);
    Writer<OStreamWrapper> writer2(osw);
    doc.Accept(writer2);
}*/
int main() {
    
    //ifstream url("JSONFiles/prueba.json");
    /*int a;
    const char *b = typeid(a).name();
    if(*b == 'i')
        cout<<"entero";*/
    string resp;
    bool b;
    cout<<"Desea  usar memoria local?\n Si=1\n No=0\n >"<<endl;
    while ((true)){
        getline(cin,resp);
        if(resp=="1"){
            b=true;
            break;
        }else{b=false;break;}
    }
    if(b){
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
    cout<<&myPtr;
    
    thr.join();}
    else
    {
        MCliente();
    }
    
    //cout<<"hola";
}
