#include "DataParser.h"
#include <iostream>
#include <string>
using namespace std;

DataParser parser;

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
    while(1){
        cout << "=== MENU TESTS ===" << endl; 
        cout << "\t1: Tester le parser" << endl; 
        cout << "\t0: Retourner au menu principal" << endl;
        string input;
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
    parser = DataParser();
    while(1){
        cout << "=== MENU PRINCIPAL ===" << endl; 
        cout << "\t0: Quit" << endl;
        cout << "\t1: Calculer l'IQA" << endl; 
        cout << "\t100: Menu Tests" << endl;
        string input;
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
                // Calculer l'IQA
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