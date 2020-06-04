#include<iostream>
#include "Server.cpp"

using std::cout; using std::endl;using std::cerr;
int main(){
    if(MServer()!=0){
        cerr<<"El server no funciona";
    }
}