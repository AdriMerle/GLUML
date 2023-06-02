#if ! defined (PARTICULIER_H)
#define PARTICULIER_H

#include "Capteur.h"
#include "Utilisateur.h"
#include <vector>
using namespace std;

class Particulier: public Utilisateur
{

private:
    int score;
    bool fiable;
    Capteur* monCapteur;

public:

    Capteur listerMonCapteur()const;

    void afficherScore() const;

    void ajouterCapteur(Capteur & c);

    Particulier() {};

    Particulier(int s, bool f, Capteur * capteur, int taille,int id,string email, string mdp) : Utilisateur(id,mail,mdp),score(s),fiable(f),monCapteur(capteur) {};

    Particulier(int s, bool f, int taille, int id,string email, string mdp):Utilisateur(id,mail,mdp),score(s),fiable(f) {};

    //~Particulier();
};

#endif