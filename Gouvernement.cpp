#include <iostream>
using namespace std;
#include <vector>
#include "Utilisateur.h"
#include "DataParser.h"
#include "Gouvernement.h"


void Gouvernement::consulterCapteursDefectueux() const{

}

vector<Purificateur> Gouvernement::listerDonneesPurificateurs() const{
    // vector<Purificateur>purificateurs = obtenirPurificateurs();
    // return purificateurs
}
void Gouvernement::observerImpactPurificateur(const Purificateur & p) const{

}

void Gouvernement::bannirCapteur(Capteur c, vector<Particulier> & listeParticuliers) {
    c.valide=false;
    for(auto & u : listeParticuliers){
        if(u.listerMonCapteur().id==c.id){          
            u.setFiable(false);
            break;
        }
    } 
}