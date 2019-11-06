#include <iostream>

using namespace std;

int main(){
    int nb_hab,nb_barques,nb_ferrys,resultat,reste;
    cin >> nb_hab;
    cin >> nb_barques;
    cin >> nb_ferrys;
    if(nb_hab==0){
        return 0;
    }
    //une barque = 4personnes, 1 ferry= 500personnes
    reste = nb_hab - nb_ferrys*500;
    if(reste>0){
        reste -=nb_barques*4;
        if(reste<0){
            reste = 0;
        }
    }


    return reste;
}