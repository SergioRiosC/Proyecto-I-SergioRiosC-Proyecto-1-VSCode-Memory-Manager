#include <iostream>
#include<fstream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "md5.h"
#include "md5.cpp"
#include "Server.cpp"
#define MAX 100
using namespace std;

void rec(int sock){
    char buf[MAX];
    FILE *fp=fopen("C.json","a");
    if(!fp){cerr<<"error abriendo el archivo ";return;}
    int fs_block=recv(sock, buf,MAX,0);
    
    while( fs_block>0 ){
        
        int wrt=fwrite(buf, sizeof(char), fs_block, fp);
        if(wrt<fs_block){cout<<"Error escribiendo en Cli"<<endl;break;}
        bzero(buf,MAX);
        if(fs_block==0 || fs_block!=512){break;}
    }
    fclose(fp);
}

void sendFile(int sock){
    string line;
    char buf[MAX];
    FILE * fp=fopen("Cliente.json","r");
    if(fp!=NULL){
        bzero(buf,MAX);
        int fs_block;
        while((fs_block=fread(buf, sizeof(char), MAX, fp) )){
            if(send(sock, buf, fs_block, 0)<0 ){
                cout<<"error enviando el archivo Cliente"<<endl;
                break;
            }
            bzero(buf,MAX);
        }
    }
    fclose(fp);
}
int main(){
    cout<<"Cli\n";
   string ipAddress = "127.0.0.1";
   string p;
   string ip;
  cout<<"Ingrese el puerto del Servidor: "<<endl;
   cout<<">";
   while(true){
       getline(cin,p);
       if(p=="5400"){
           break;
       }else{cout<<"Puerto vacio, intente de nuevo"<<endl;cout<<">";}
   }
    cout<<"Ingrese la direccion IP del Servidor"<<endl;
    cout<<">";
    while(true){
       getline(cin,ip);
       if(ip==ipAddress){
           break;
       }else{cout<<"IP incorrecta, intente de nuevo"<<endl;cout<<">";}
   }
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        cout<<"FALLO EN SOCKEY";
        return 1;
    }
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(5400);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Conecta al servidor en el socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1){
        cout<<"FALLO AL CONECTAR";
        return 2;
    }
    
    char buf[4096];
    string userInput;
    int b=0;
    int c=0;
    bool e=true;
    int bytesReceived;
    do {
        if(b==0){
            int bytesReceived = recv(sock, buf, 4096, 0);
            cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
            b=1;
        }
        cout << "> ";
        getline(cin, userInput);
        if(c==0){
            userInput=md5(userInput);
            c=1;
        }
        //	Envia al servidor
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1){
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }
        if(userInput[0]=='I' && userInput[1]=='D'){
            rec(sock);
            userInput="";
        }else{
            
            //	Espera la respuesta
            memset(buf, 0, 4096);
            bytesReceived = recv(sock, buf, 4096, 0);
            }
        if (bytesReceived == -1){
            cout << "There was an error getting response from server\r\n";
        }
        else{
            
            // Muestra la respuesta
            cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
        }
        if(userInput=="ENV"){
            sendFile(sock);
            //e=false;
            userInput="";
            }
        
    } while(true);
    //	Cierra el socket
    close(sock);
    return 0;
}
