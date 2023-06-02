#include <stdbool.h>
#include "Capteur.h"
#include "Particulier.h"
#include <vector>
#include <iostream>
using namespace std;



Capteur Particulier::listerMonCapteur() const{
    return monCapteur;
}

void Particulier::afficherScore() const{
    cout<<"Le score de "<< id <<" est de "<<score<<endl;
}

void Particulier::ajouterCapteur(Capteur c){
    monCapteur=c;
}

// Particulier::~Particulier(){
//     delete monCapteur;
// }

    