#include "Capteur.h"
#include "Utilisateur.h"
#include <cmath>
#include <string>
using namespace std;

bool Capteur::testFiabiliteCapteur(const vector<Capteur> & capteurs, int ecart) const
{
    time_t dateDebut = 0;
    vector<Capteur>::const_iterator it;
    float IQA;
    IQA = CalculIQA(*this,dateDebut,time(nullptr));
    float moyenneIQA = 0; 
    int compteur =0;
    for(it = capteurs.begin();it!=capteurs.end();it++)
    {
        if(it->valide && this->position.Distance(it->position)<=10)
        {        
            moyenneIQA += CalculIQA(*it,dateDebut,time(nullptr));
            compteur++;
        }
    }
    moyenneIQA/=compteur;
    // cout << "compteur :"<< compteur << endl;
    // cout << "moyIQA :"<< moyenneIQA << endl;
    // cout << "différence : " << abs(moyenneIQA-IQA) << endl;
    return abs(moyenneIQA-IQA)<ecart;
}

vector<Capteur> ObtenirCapteursPotentiellementDefectueux(const vector<Capteur> & listeCapteurs){
    vector<Capteur> capteursDef;
    for(const auto & capteur : listeCapteurs) {
        if(!(capteur.testFiabiliteCapteur(listeCapteurs))){
            capteursDef.push_back(capteur);
        }
    }
    return capteursDef;
}

ostream& operator<<(ostream& os, const Capteur& c)
{
    
    os << c.id << c.position;
    return os;
}


