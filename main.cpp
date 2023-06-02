#include "DataParser.h"
#include "Utilisateur.h"
#include "Capteur.h"
#include <iostream>
#include <string>
using namespace std;

DataParser parser;

// Clock
clock_t ta;
clock_t tb = NULL;

void cstart() { ta = clock(); }
void cstop() { tb = tb==NULL ? clock() : tb; }
void cprint() { if (ta != 0 && tb != 0) cout << (tb - ta)/1000 << " ms" << endl; }
void creset() {ta = 0; tb = NULL;}


bool check_number(string str) {
    for (long unsigned int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)   return false;
    return true;
}

void testerParser() {
    for (const auto & cleaner : parser.obtenirPurificateurs()) {
        cout << "CleanerID: " << cleaner.id << endl;
        cout << "Latitude: " << cleaner.position.lat << endl;
        cout << "Longitude: " << cleaner.position.lng << endl;
        cout << "Timestamp(start): " << cleaner.debut << endl;
        cout << "Timestamp(stop): " << cleaner.fin << endl;
        cout << endl;
    }
    
    for (const auto & capteur : parser.obtenirCapteurs()) {
        cout << "SensorID: " << capteur.id << endl;
        cout << "Latitude: " << capteur.position.lat << endl;
        cout << "Longitude: " << capteur.position.lng << endl;
        int i=0;
        for (const auto & mesure : capteur.mesures){
            cout << "SensorID: " << mesure.idCapteur << endl;
            cout << "Timestamp: " << mesure.timestamp << endl;
            cout << "Date: " << ctime(&mesure.timestamp) << endl;
            cout << "O3: " << mesure.O3 << endl;
            cout << "SO2: " << mesure.SO2 << endl;
            cout << "NO2: " << mesure.NO2 << endl;
            cout << "PM10: " << mesure.PM10 << endl;
            cout << endl;
            i++;
            if(i>=5) break;
        }
    }

    for(const auto & attribut : parser.obtenirAttributs()) {
        cout << "AttributID: " << attribut.id << endl;
        cout << "Unit: " << attribut.unit << endl;
        cout << "Description: " << attribut.description << endl;
        cout << endl;
    }

    Capteur c;
    for(const Particulier & utilisateur : parser.obtenirUtilisateurs()) {
        utilisateur.afficherScore();
        cout << "Fiable: " << utilisateur.getFiable() << endl;
        cout << "Capteur: " << endl;
        c = utilisateur.listerMonCapteur();
        cout << "   " << c.id << endl;
        cout << "   " << c.position << endl;
        cout << endl;
    }
}

void menuTests() {
    system("clear");
    Utilisateur utilisateur = Utilisateur();

    while(1){
        cout << "=== MENU TESTS ===" << endl;
        cout << "\t0: Retourner au menu principal" << endl;
        cout << "\t1: Tester le parser" << endl; 
        cout << "\t2: Obtenir liste capteurs par similarité" << endl;
        string input;
        string id;
        vector<Capteur> capteurs;
        map<string, float> resultats;
        bool fonctionnel;
        cout<<"Choix: ";
        cin>>input;
        while(!check_number(input)){
            cout << "Entrée invalide. Veuillez recommencer." << endl;
            cout<<"Choix : ";
            cin>>input;
        }
        int choix = stoi(input);
        switch(choix) {
            case 0:
                goto fin;
            case 1:
                testerParser();
                break;
            case 2:
                id = "Sensor0";
                capteurs = parser.obtenirCapteurs();
                capteurs.resize(10);
                resultats["Sensor3"] = 1.0137;
                resultats["Sensor2"] = 1.34247;
                resultats["Sensor7"] = 1.93151;
                resultats["Sensor8"] = 5.77397;
                resultats["Sensor9"] = 10.3973;
                resultats["Sensor4"] = 11.2123;
                resultats["Sensor1"] = 11.274;
                resultats["Sensor5"] = 37.6575;
                resultats["Sensor6"] = 38.5069;
                fonctionnel = true;
                for (const auto & capteur : capteurs) {
                    if(capteur.id==id){
                        vector<pair<string,float>> vec = utilisateur.ObtenirCapteursParSimilarite(capteur, capteurs);
                        for(const auto & cap: vec){
                            if(cap.second!=0) {
                                cout << cap.first << " écart " << cap.second << " != " << resultats[cap.first] << endl;
                                if(abs(resultats[cap.first]-cap.second)>0.01) {
                                    fonctionnel=false;
                                }
                            }
                        }
                        break;
                    }
                }
                cout << "Résultat du test : " << fonctionnel << endl;
                break;
            default:
                system("clear");
                cout << "Mauvais input, veuillez recommencer" << endl;
                continue; // revenir au menu
        }
    }
    fin:
        system("clear");
}

int main() {
    system("clear");

    cstart();
    parser = DataParser();
    Utilisateur utilisateur = Utilisateur();
    
    cstop(); 
    cout << "Performance du parser : ";
    cprint(); creset();
    while(1){
        cout << "=== MENU PRINCIPAL ===" << endl; 
        cout << "\t0: Quit" << endl;
        cout << "\t1: Calculer l'IQA" << endl; 
        cout << "\t2: Obtenir liste capteurs par similarité" << endl; 
        cout << "\t3: Obtenir liste actuelle des capteurs défectueux" << endl;
        cout << "\t100: Menu Tests" << endl;
        string input;
        string id;
        cout<<"Choix: ";
        cin>>input;
        while(!check_number(input)){
            cout << "Entrée invalide. Veuillez recommencer." << endl;
            cout<<"Choix : ";
            cin>>input;
        }
        int choix = stoi(input);
        switch(choix) {
            case 0:
                goto fin;
            case 100:
                menuTests();
                break;
            case 1:
                cout << "Moyenne IQA"<< endl;
                cout << utilisateur.MoyenneIQARegion(Point(40.5f, 3.5f),parser.obtenirCapteurs(),15) << endl;
                break;
            case 2:
                cout << "Veuillez renseigner un numéro d'identification pour le capteur à partir duquel la liste sera générée :" << endl; 
                cin>>id;
                for (const auto & capteur : parser.obtenirCapteurs()) {
                    if(capteur.id==id){
                        vector<pair<string,float>> vec=utilisateur.ObtenirCapteursParSimilarite(capteur, parser.obtenirCapteurs());
                        for(const auto & cap: vec){
                            cout << cap.first << " avec un écart d'IQA de " <<cap.second << endl;
                        }
                        break;
                    }
                }
                break;
            case 3:        
                cout << "Les capteurs défectueux sont :" << endl;
                for (const auto & c : ObtenirCapteursPotentiellementDefectueux(parser.obtenirCapteurs())) {
                    cout << c.id << " ";
                    
                }
                cout << endl;
                break;
            default:
                system("clear");
                cout << "Mauvais input, veuillez recommencer" << endl;
                continue; // revenir au menu
        }
    }
    fin:
        system("clear");
        cout << "Au revoir." << endl;
    return 0;
}