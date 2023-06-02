#if ! defined (UTILISATEUR_H)
#define UTILISATEUR_H

#include <string>
#include <vector>
#include "Capteur.h"
#include "Mesure.h"
#include "Point.h"
#include<map>
#include<ctime>
#include <algorithm>
#include <utility>

using namespace std;

double CalculIQA(const Capteur & c,time_t debut,time_t fin);

class Utilisateur
{
public:

    float MoyenneIQARegion (const Point & coord, const vector<Capteur> & capteurs,float rayon =0) const;

    vector<Capteur> ListerDonneesCapteurs() const;

    vector<Mesure> ListerDonneesUnCapteur(const Capteur & c ) const;

    static bool sortByValue(const pair<string,float> p1, const pair<string,float> p2);

    vector<pair<string,float>> ObtenirCapteursParSimilarite(const Capteur & c,const vector<Capteur> & capteurs)const ;

    Utilisateur(){};

    Utilisateur(string _id, string _mail,string _mdp):id(_id),mail(_mail),mdp(_mdp){};

    virtual ~Utilisateur(){};


    string id;
    string mail;
    string mdp;

};

#endif