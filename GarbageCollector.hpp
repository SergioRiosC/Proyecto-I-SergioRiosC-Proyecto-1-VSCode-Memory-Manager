#include <iostream>
#include <random>

template <typename T>

class Collector{
    private:
        // primer espacio memEspc, segundo espacio
        int referencias[3][2];
        int referenceCnt = 0;
        Collector *garbageColector;
        
    public:
        Collector(){
            garbage = NULL; 
        }


        int addPtr(int memEspc){
            if(referenceCnt != 3){
                referencias[referenceCnt][0] = memEspc;
                return referenceCnt++;
            }
            return -1;

        };
        void dereference(int id){
            if (id != -1)
            {
                if(referencias[id][1] == 1)
                    referencias[id][1] -= 2;
                else
                    referencias[id][1]--;
            }
            
        };
        void reference(int id){
            if (id != -1)
            {
                referencias[id][1]++;
            }
            
            
        };
        void garbage(){
            for(int i=0;i<referenceCnt;i++){
                if (referencias[i][1] == -1)
                {
                    cout<<"se intenta borrar "<<i;
                    T ptr = referencias[i][0] 
                    delete ptr;

                }
                
            }
        }

};
