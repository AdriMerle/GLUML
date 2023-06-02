#if ! defined ( DATAPARSER_H )
#define DATAPARSER_H

#include "Purificateur.h"
#include "Capteur.h"
#include "Particulier.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <iomanip>
using namespace std;

struct Attribut {
    string id, unit, description;
};

class DataParser
{
public:
    const vector<Purificateur>& obtenirPurificateurs() const {return purificateurs;}
    const vector<Capteur>& obtenirCapteurs() const {return capteurs;}
    const vector<Attribut>& obtenirAttributs() const {return attributs;}
    const vector<Particulier>& obtenirUtilisateurs() const {return utilisateurs;}

    // Constructeur
    DataParser(string datapath = "dataset/");

private:
    string datapath;
    vector<Purificateur> purificateurs;
    vector<Capteur> capteurs;
    vector<Particulier> utilisateurs;
    vector<Attribut> attributs;
    void parserPurificateurs();
    void parserCapteurs();
    void parserMesures();
    void parserUtilisateurs();
    void parserAttributs();
};

#endif // DATAPARSER_H

