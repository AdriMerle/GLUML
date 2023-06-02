#include <iostream>
using namespace std;
#include "Fournisseur.h"
#include "Point.h"


    vector<Purificateur> Fournisseur::listerDonneesPurificateurs() const{
        return this->mesPurificateurs;
    }

    //void Fournisseur::observerImpactPurificateur(const Purificateur & p) const{
    //  Point x =p->position;
    //  float moy=MoyenneIQARegion(x);
    //}
