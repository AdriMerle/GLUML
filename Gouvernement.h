#if ! defined ( GOUVERNEMENT_H )
#define GOUVERNEMENT_H

#include "Utilisateur.h"
#include <vector>
#include <iostream>
using namespace std;

class Gouvernement : public Utilisateur{

    public:

    inline Gouvernement(){}
    void consulterCapteursDefectueux() const;
    vector<Purificateur> listerDonneesPurificateurs() const;
    void observerImpactPurificateur(const Purificateur & p) const;

    virtual inline ~Gouvernement(){}
};

#endif // GOUVERNEMENT_H