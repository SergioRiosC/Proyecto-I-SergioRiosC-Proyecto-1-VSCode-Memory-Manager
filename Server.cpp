#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <fstream>
#define MAX 100
using namespace std;
#pragma comment(lib,"ws2_32.lib")
int listening;
int ClientSocket;
char bufRec[MAX];
char bufEnv[MAX];
int ID=20;

string recFile(){
    bzero(bufRec,MAX);
    string n=to_string(ID)+".json";
    
    char name[n.length()+1];
    strcpy(name,n.c_str());
    cout<<"name: "<<name<<endl;
    FILE *fp=fopen(name,"a");
    if(!fp){cerr<<"error abriendo el archivo ";return "ERROR";}
    int fs_block=recv(ClientSocket, bufRec,MAX,0);
   
    while( fs_block>0 ){
        int wrt=fwrite(bufRec, sizeof(char), fs_block, fp);
        if(wrt<fs_block){cout<<"Error escribiendo en srv"<<endl;break;}
        bzero(bufRec,MAX);
        if(fs_block==0 || fs_block!=512){break;}
    }
    fclose(fp);
    return to_string(ID);
}
void env(string n){
    string line;
    bzero(bufEnv,MAX);
    char name[n.length()+1];
    strcpy(name,n.c_str());
    FILE * fp=fopen(name,"r");
    if(fp!=NULL){
        bzero(bufEnv,MAX);
        int fs_block;
        while((fs_block=fread(bufEnv, sizeof(char), MAX, fp) )>0){
            cout<<"env.json  "<<bufEnv<<endl;
            if(send(ClientSocket, bufEnv, fs_block, 0)<0 ){
                cout<<"error enviando el archivo Server"<<endl;
                break;
            }
            bzero(bufEnv,MAX);
        }
    }
    fclose(fp);
}

int MServer( ) {
    string contra="827ccb0eea8a706c4c34a16891f84e7b"; //Clave "12345" encriptada en MD5
    listening=socket(AF_INET,SOCK_STREAM,0);
    if(listening==-1){
        cerr<<"no se pudo crear el socket";
        return -1;
    }
    sockaddr_in hint;
    hint.sin_family=AF_INET;
    hint.sin_port=htons(5400);
    cout<<"puerto: "<<hint.sin_port<<endl;
    inet_pton(AF_INET,"0.0.0.0",&hint.sin_addr);
    if(bind(listening,(sockaddr*)&hint, sizeof(hint)) == -1){
        cerr<<"no ip "<<endl;
        return -2;
    }
    cout<<"ip: "<<inet_pton<<endl;
    listen(listening,10);
    if(listen(listening,10)==-1){
        cerr<<"el socket no escucha";
        return -3;
    }
    sockaddr_in client;
    socklen_t  clientSize= sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    ClientSocket=accept(listening, (sockaddr*)&client, &clientSize);  
    if(ClientSocket==-1){
        cerr<<"problema con la coneccion";
        return -4;
    }   
    close(listening);
    memset(host, 0, NI_MAXHOST);
    memset(svc,0,NI_MAXSERV);
    int result=getnameinfo((sockaddr*)&client, sizeof(client),host,NI_MAXHOST,svc,NI_MAXSERV,0);
    if(result){
        cout<<"host conectado en "<<svc<<endl;
    }else{
        inet_ntop(AF_INET, &client.sin_addr,host,NI_MAXHOST);
        cout<<host<<" conectado en "<<ntohs(client.sin_port)<<endl;
        string bienvenida="Bienvenido, ingrese la contraseña: ";
        send(ClientSocket,bienvenida.c_str(),bienvenida.size()+1,0);
    }  
    char buf[4096];
    string msg;
    string id;
    int b=0;
    int r=0;
    bool B=false;
    while(true){     
        memset(buf,0,4096);
        msg="";
        int bytesRecv=recv(ClientSocket,buf,4096,0);
        if(bytesRecv==-1){
            cerr<< "Problema de coneccion"<< endl;
            break;
        }
        if(bytesRecv==0){
            cout<<"Desconectado"<<endl;
            break;
        }
        msg=string(buf,0,bytesRecv);
        if(b==0 && msg!=contra){
            msg="contraseña incorrecta, digitela correctamente";
        }else{
            b=1;
            if(msg[0]=='I' && msg[1]=='D'){
            string n=msg.substr(3);
               n=n+".json";
               cout<<"n: "<<n<<endl;
                env(n);
            }else{
                if(B){
                    msg=id;
                    B=false;
                }
                send(ClientSocket,msg.c_str(),msg.size()+1,0);

            }    
            if(msg=="ENV"){
                id="ID: "+recFile();
                ID+=1;
                r=1;
                cout<<"return: "<<id<<endl;
                cout<<"ID: "<<ID<<endl;
                B=true;
            } 
            
        }    
    }
    //Cerrar el socket
    close(ClientSocket);
    close(listening);
    return 0;
}