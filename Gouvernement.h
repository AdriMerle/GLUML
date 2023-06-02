#if ! defined ( GOUVERNEMENT_H )
#define GOUVERNEMENT_H

#include "Utilisateur.h"
#include <vector>
#include <iostream>
#include "Capteur.h"
using namespace std;

class Gouvernement : public Utilisateur{

    public:

    inline Gouvernement(){}
    void consulterCapteursDefectueux() const;
    vector<Purificateur> listerDonneesPurificateurs() const;
    void observerImpactPurificateur(const Purificateur & p) const;
    void bannirCapteur(Capteur c, vector<Particulier> & listeParticuliers);

    virtual inline ~Gouvernement(){}
};

#endif // GOUVERNEMENT_H