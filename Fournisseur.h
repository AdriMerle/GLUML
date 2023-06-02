#if ! defined(FOURNISSEUR_H)
#define FOURNISSEUR_H

#include"Utilisateur.h"
#include"Purificateur.h"
#include<vector>
using namespace std;


class Fournisseur: public Utilisateur{

    private:
    vector <Purificateur> mesPurificateurs;

    public:

    Fournisseur(Purificateur * purificateur, int t);

    vector<Purificateur> listerDonneesPurificateurs() const;

    void observerImpactPurificateur(const Purificateur & p) const;

    ~Fournisseur();
};

#endif