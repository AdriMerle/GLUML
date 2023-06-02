#if ! defined (UTILISATEUR_H)
#define UTILISATEUR_H

#include <string>
#include <vector>
#include "Capteur.h"
#include "Mesure.h"
#include "Point.h"
#include<map>
#include<ctime>

using namespace std;

class Utilisateur
{
public:

    float MoyenneIQARegion (const Point & coord, const vector<Capteur> & capteurs, float rayon =0) const;

    vector<Capteur> ListerDonneesCapteurs() const;

    vector<Mesure> ListerDonneesUnCapteur(const Capteur & c ) const;

    map<int,float> ObtenirCapteursParSimilarite(const Capteur & c) const;

    double CalculIQA(const Capteur & c, const vector <Mesure> & mesures,time_t debut,time_t fin) const;

    Utilisateur();

    Utilisateur(int _id,string _mail,string _mdp):id(_id),mail(_mail),mdp(_mdp){};

    virtual ~Utilisateur();


    int id;
    string mail;
    string mdp;

};

#endif