#include "DataParser.h"
#include "Utilisateur.h"
#include "Capteur.h"
#include <iostream>
#include <string>
using namespace std;

DataParser parser;

//test

// Clock
clock_t ta;
clock_t tb = 0;

void cstart() { ta = clock(); }
void cstop() { tb = tb==0 ? clock() : tb; }
void cprint() { if (ta != 0 && tb != 0) cout << (tb - ta)/1000 << " ms" << endl; }
void creset() {ta = 0; tb = 0;}

void printTest(bool res) {cout << "Résultat du test : ";
    if(res) cout << "validé" << endl;
    else cout << "échoué" << endl;
}


bool check_number(string str) {
    for (long unsigned int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)   return false;
    return true;
}

void testerParser() {
    for (const Purificateur & cleaner : parser.obtenirPurificateurs()) {
        cout << "CleanerID: " << cleaner.id << endl;
        cout << "Latitude: " << cleaner.position.lat << endl;
        cout << "Longitude: " << cleaner.position.lng << endl;
        cout << "Timestamp(start): " << cleaner.debut << endl;
        cout << "Timestamp(stop): " << cleaner.fin << endl;
        cout << endl;
    }
    
    for (const Capteur & capteur : parser.obtenirCapteurs()) {
        cout << "SensorID: " << capteur.id << endl;
        cout << "Latitude: " << capteur.position.lat << endl;
        cout << "Longitude: " << capteur.position.lng << endl;
        int i=0;
        for (const Mesure & mesure : capteur.mesures){
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

    for(const Attribut & attribut : parser.obtenirAttributs()) {
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
        cout << "\t3: Calculer l'IQA sur une région donnée avec rayon positif" << endl;
        cout << "\t4: Calculer l'IQA sur une région donnée avec rayon négatif" << endl;
        cout << "\t5: Tester la fiabilité d'un capteur fiable" << endl; 
        cout << "\t6: Tester la fiabilité d'un capteur non fiable " << endl;
        cout << "\t7: Test de la fonction ObtenirCapteursPotentiellementDefectueux() avec un capteur potentiellement defecteux" << endl;  
        cout << "\t8: Test de la fonction ObtenirCapteursPotentiellementDefectueux() avec un capteur non defecteux " << endl;
        string input;
        string id;
        vector<Capteur> capteurs;
        vector<Capteur> capteurs_def;
        map<string, float> resultats;
        Capteur cap;
        bool fonctionnel = true;
        float moyenneAttendue;
        float moyenneCalculee;
        Point p;
        int rayon;
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
                resultats["Sensor3"] = 1.0137f;
                resultats["Sensor2"] = 1.34247f;
                resultats["Sensor7"] = 1.93151f;
                resultats["Sensor8"] = 5.77397f;
                resultats["Sensor9"] = 10.3973f;
                resultats["Sensor4"] = 11.2123f;
                resultats["Sensor1"] = 11.274f;
                resultats["Sensor5"] = 37.6575f;
                resultats["Sensor6"] = 38.5069f;

                cout << "Test de similarité au capteur " << id << " sur les 10 premiers capteurs de la liste." << endl;
                for (const Capteur & capteur : capteurs) {
                    if(capteur.id==id){
                        vector<pair<string,float>> vec = utilisateur.ObtenirCapteursParSimilarite(capteur, capteurs);
                        for(const auto & cap: vec){
                            if(cap.second!=0) {
                                if(abs(resultats[cap.first]-cap.second)>0.01) {
                                    fonctionnel=false;
                                }
                            }
                        }
                        break;
                    }
                }
                printTest(fonctionnel);
                break;
            
            case 3:
                p = Point(47.f, 4.f);
                rayon = 5; 
                cout << "Test du calcul de la moyenne d'IQA autour du point " << p;
                cout << " avec un rayon de " << rayon << "."<< endl;
                moyenneAttendue = 70.4886f;
                moyenneCalculee = utilisateur.MoyenneIQARegion(p,parser.obtenirCapteurs(),rayon);
                fonctionnel = abs(moyenneAttendue - moyenneCalculee) < 0.01;
                printTest(fonctionnel);
                break;
            case 4:
                p = Point(47.f, 4.f);
                rayon = -5; 
                cout << "Test du calcul de la moyenne d'IQA autour du point " << p;
                cout << " avec un rayon de " << rayon << "."<< endl;
                fonctionnel = (utilisateur.MoyenneIQARegion(p,parser.obtenirCapteurs(),rayon)==-1);
                printTest(fonctionnel);
                break;
            case 5:
                capteurs = parser.obtenirCapteurs();
                cap = capteurs[2];
                cout << "Test du calcul de la fiabilité du capteur  " << cap << endl;
                fonctionnel = cap.testFiabiliteCapteur(capteurs)==1; 
                printTest(fonctionnel);
                break;
            case 6:
                capteurs = parser.obtenirCapteurs();
                cap = capteurs[5];
                cout << "Test du calcul de la fiabilité du capteur  " << cap << endl;
                fonctionnel = cap.testFiabiliteCapteur(capteurs)==0; 
                printTest(fonctionnel);
                break;
            case 7:
                capteurs = parser.obtenirCapteurs();
                cap = capteurs[5];
                capteurs.resize(10);
                cout << "Test que le capteur  " << cap << " se retrouve bien dans la liste des capteurs défectueux" << endl;
                capteurs_def = ObtenirCapteursPotentiellementDefectueux(capteurs);
                fonctionnel=0;
                for (int i =0;i<10;i++){
                    if (capteurs_def[i].id==cap.id){
                        fonctionnel = 1;
                        break;
                    }

                }
                printTest(fonctionnel);
                break;
            case 8:
                capteurs = parser.obtenirCapteurs();
                cap = capteurs[2];
                capteurs.resize(10);
                cout << "Test que le capteur  " << cap << " ne se retrouve pas dans la liste des capteurs défectueux" << endl;
                capteurs_def = ObtenirCapteursPotentiellementDefectueux(capteurs);
                fonctionnel=1;
                for (int i =0;i<10;i++){
                    if (capteurs_def[i].id==cap.id){
                        fonctionnel = 0;
                        break;
                    }

                }
                printTest(fonctionnel);
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
                for (const Capteur & capteur : parser.obtenirCapteurs()) {
                    if(capteur.id==id){
                        vector<pair<string,float>> capSimilaires = utilisateur.ObtenirCapteursParSimilarite(capteur, parser.obtenirCapteurs());
                        for(const pair<string,float> & cap : capSimilaires){
                            cout << cap.first << " avec un écart d'IQA de " << cap.second << endl;
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