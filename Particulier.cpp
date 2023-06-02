#include <stdbool.h>
#include "Capteur.h"
#include "Particulier.h"
#include <vector>
#include <iostream>
using namespace std;



Capteur Particulier::listerMonCapteur()const{
    return *monCapteur;
}

void Particulier::afficherScore() const{
    cout<<"Le score de "<<mail<<" est de "<<score<<endl;
}

void Particulier::ajouterCapteur(Capteur & c){
    if(monCapteur==NULL){
        monCapteur=(Capteur*)malloc(sizeof(Capteur));
        *monCapteur=c;
    }
}

// Particulier::~Particulier(){
//     delete monCapteur;
// }

    