#if ! defined ( CAPTEUR_H )
#define CAPTEUR_H

#include "Mesure.h"
#include "Point.h"
#include "Capteur.h"
#include <vector>
#include <string>
using namespace std;

class Capteur
{
public :
    
    Capteur (const string _id, const Point & _p, const bool _v ,const vector<Mesure> & _m ) : id(_id), position(_p), valide(_v),mesures(_m) {};
    Capteur(){};
    bool testFiabiliteCapteur(const vector<Capteur> & capteurs, int ecart=20) const;

    string id;
    Point position;
    bool valide;
    vector<Mesure> mesures;
};

vector<Capteur> ObtenirCapteursPotentiellementDefectueux(const vector<Capteur> & listeCapteurs);
#endif // CAPTEUR_H