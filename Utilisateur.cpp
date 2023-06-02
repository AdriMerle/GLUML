#include "Utilisateur.h"

float Utilisateur::MoyenneIQARegion (const Point & coord,  const vector<Capteur> & capteurs, float rayon) const
{
float IQA = 0;
if (rayon!=0)
{
    //int compteur=0;
    //vector<Capteur>::const_iterator it;
    // for (it = capteurs.begin();it!=capteurs.end();it++)
    // {
    //     if(it->valide && it->position.Distance(coord)<=rayon)
    //     {
    //         IQA+=CalculIQA(*it,time(0),time(0));
    //         compteur++;
    //     }
    // }
    // IQA=IQA/compteur;

}
else
{
    int diviseur=0;
    vector<Capteur>::const_iterator it;
    for (it = capteurs.begin();it!=capteurs.end();it++)
    {
        if(it->valide && it->position.Distance(coord)<=10)
        {
            // if(it->position==coord)
            // {
            //     IQA=CalculIQA(*it,time(0),time(0));
            //     diviseur = 1;
            //     break;
            // }
            // else
            // {
            //     IQA+=CalculIQA(*it,time(0),time(0))*(1/(it->position.Distance(coord)));
            //     diviseur += 1/(it->position.Distance(coord));
            // }
            
        }
    }
    IQA=IQA/diviseur;
}
    return IQA;
}

/*map<int,float> Utilisateur::ObtenirCapteursParSimilarite(const Capteur & c) const{
    map<int,float> Capteurs;
    return Capteurs;
}*/



double Utilisateur::CalculIQA(const Capteur & c, const vector <Mesure> & mesures,time_t debut,time_t fin) const{

    double IQA=0;

    vector <Mesure>::const_iterator it;

    for(it=mesures.begin() ; it!=mesures.end() ; it++){
        if(it->idCapteur==c.id && it->timestamp>=debut && it->timestamp<=fin ){
            IQA+= (*it).calculIQAJournee();
        }
    }

    float nbSecondes=difftime(fin,debut);
    int nbJours= (int)(nbSecondes/(3600*24));

    return (IQA/nbJours);

    
}

Utilisateur::Utilisateur() {
    
}

Utilisateur::~Utilisateur() {
    
}