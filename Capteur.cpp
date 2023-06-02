#include "Capteur.h"
#include <cmath>

bool Capteur::testFiabiliteCapteur(const vector<Capteur> & capteurs) const
{
    vector<Capteur>::const_iterator it;
    float IQA;
    // IQA = CalculIQA(*this,DateActuelle,DateActuelle-10) 
    float moyenneIQA = 0;
    int compteur =0;
    for(it = capteurs.begin();it!=capteurs.end();it++)
    {
        if(it->valide && this->position.Distance(it->position)<=10)
        {
            //moyenneIQA+=CalculIQA(*it,DateActuelle,DateActuelle-10)
            compteur++;
        }

    }
    moyenneIQA/=compteur;
    return abs(moyenneIQA-IQA)<15;
}

