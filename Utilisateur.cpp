#include "Utilisateur.h"

float Utilisateur::MoyenneIQARegion(const Point & coord, const vector<Capteur> & capteurs, float rayon) const
{
    float IQA = 0;
    time_t now = time(nullptr);
    tm date = *localtime(&now);

    date.tm_mday -= 1;
    std::time_t modifiedTime = 0; //std::mktime(&date)

    if (rayon>0)
    {
        int compteur=0;
        for (const auto & c : capteurs)
        {
            
            if(c.valide && c.position.Distance(coord)<=rayon)
            {
                IQA+=CalculIQA(c,modifiedTime,time(nullptr));
                compteur++;
            }
        }
        IQA=IQA/compteur;

    }
    else if (rayon==0)
    {
        int diviseur=0;
        for(const auto & c : capteurs) {
            if(c.valide && c.position.Distance(coord)<=10) {
                if(c.position==coord) {
                    IQA=CalculIQA(c,modifiedTime,time(nullptr));
                    diviseur = 1;
                    break;
                }
                else {
                    IQA+=CalculIQA(c,modifiedTime,time(nullptr))*(1/(c.position.Distance(coord)));
                    diviseur += 1/(c.position.Distance(coord));
                }
            }
        }
    IQA=IQA/diviseur;
    }
    else
    {
        cerr<<"ERREUR : rayon négatif" << endl;
        return -1;
    }
    return IQA;
}

 bool Utilisateur::sortByValue(const pair<string,float> p1, const pair<string,float> p2){

    return (p1.second<p2.second);
 }

vector<pair<string,float>> Utilisateur::ObtenirCapteursParSimilarite(const Capteur & ref, const vector<Capteur> & capteurs)const {
    map<string,float> Capteurs;
    time_t now = time(nullptr);
    tm date = *localtime(&now);

    date.tm_mday -= 1;
    std::time_t modifiedTime = 0; // std::mktime(&date); //obtenir la date du jour précédent
    double IQAref=CalculIQA(ref,modifiedTime,time(nullptr));

    date.tm_mday -= 10;
    modifiedTime = 0;// std::mktime(&date);

    for(const auto & c :capteurs){
        if(c.valide && c.id != ref.id){
            Capteurs[c.id]=abs(CalculIQA(c, modifiedTime, time(nullptr)) - IQAref);
        }
    }

    vector<pair<string,float>> vec;
    map<string,float>::const_iterator ita;
    for(const auto & c: Capteurs){
        vec.push_back(make_pair(c.first, c.second));
    }

    sort(vec.begin(),vec.end(),sortByValue);
    vec.resize(20);
    return vec;
}

double CalculIQA(const Capteur & c, time_t debut, time_t fin) {
    double IQA=0;
    int compteur=0;
    
    for(const auto & m : c.mesures) {
        if(m.timestamp>=debut && m.timestamp<=fin ){
            IQA += m.calculIQAJournee();
            compteur++;
        }
    }
    
    // float nbSecondes=difftime(fin,debut);
    // int nbJours= (int)(nbSecondes/(3600*24));
    // if(nbJours==0){
    //     nbJours=1;
    // }
    return (IQA/compteur);
}