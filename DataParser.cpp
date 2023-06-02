#include "DataParser.h"


time_t StringToTimeT(const string& dateString) {
    tm tm = {};
    istringstream iss(dateString);
    iss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");

    if (iss.fail()) {
        cerr << "Error converting string to time_t" << endl;
        return 0; 
    }
    time_t time = mktime(&tm);
    return time;
}

void DataParser::parserPurificateurs() {
    string filename = datapath + "cleaners.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    } 

    string line;
    while (getline(file, line)) {
        Purificateur cleaner;
        istringstream iss(line);
        string field;

        // CleanerID
        if (getline(iss, field, ';')) {
            cleaner.id = field;
        } else {
            cerr << "Error parsing CleanerID" << endl;
            continue;
        }

        // Latitude
        if (getline(iss, field, ';')) {
            cleaner.position.lat = stof(field);
        } else {
            cerr << "Error parsing Latitude" << endl;
            continue;
        }

        // Longitude
        if (getline(iss, field, ';')) {
            cleaner.position.lng = stof(field);
        } else {
            cerr << "Error parsing Longitude" << endl;
            continue;
        }

        // Timestamp(start)
        if (getline(iss, field, ';')) {
            cleaner.debut = StringToTimeT(field);
        } else {
            cerr << "Error parsing Timestamp(start)" << endl;
            continue;
        }

        // Timestamp(stop)
        if (getline(iss, field, ';')) {
            cleaner.fin = StringToTimeT(field);
        } else {
            cerr << "Error parsing Timestamp(stop)" << endl;
            continue;
        }

        purificateurs.push_back(cleaner);
    }

    file.close();
}

void DataParser::parserCapteurs() {
    string filename = datapath + "sensors.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    } 

    string line;
    while (getline(file, line)) {
        Capteur capteur;
        istringstream iss(line);
        string field;

        // SensorID
        if (getline(iss, field, ';')) {
            capteur.id = field;
        } else {
            cerr << "Error parsing SensorID" << endl;
            continue;
        }

        // Latitude
        if (getline(iss, field, ';')) {
            capteur.position.lat = stof(field);
        } else {
            cerr << "Error parsing Latitude" << endl;
            continue;
        }

        // Longitude
        if (getline(iss, field, ';')) {
            capteur.position.lng = stof(field);
        } else {
            cerr << "Error parsing Longitude" << endl;
            continue;
        }

        capteurs.push_back(capteur);
        
    }

    file.close();
}

void DataParser::parserMesures() {
    string filename = datapath + "measurements.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    } 

    string line;
    while (getline(file, line)) {
        Mesure mesure;
        istringstream iss(line);
        string field;

        // Timestamp
        if (getline(iss, field, ';')) {
            mesure.timestamp = StringToTimeT(field);
        } else {
            cerr << "Error parsing Timestamp" << endl;
            continue;
        }

        // SensorID
        vector<Capteur>::iterator it;
        if (getline(iss, field, ';')) {
            // Trouver capteur par ID
            it = find_if(capteurs.begin(), capteurs.end(), [&field](const Capteur& capteur) {return capteur.id == field;});
            if (it == capteurs.end())    
            {
                cerr << "Mesure trouvée sur un capteur inexistant" << endl;
            }
        } else {
            cerr << "Error parsing SensorID" << endl;
            continue;
        }

        // Gaz
        if (getline(iss, field, ';')) {
            
            if (field.compare("NO2")==0) {
                getline(iss, field, ';');
                mesure.NO2=stof(field);
            }
            else if (field.compare("PM10")==0) {
                getline(iss, field, ';');
                mesure.PM10=stof(field);
            }
            else if (field.compare("SO2")==0){
                getline(iss, field, ';');
                mesure.SO2=stof(field);             
            }
            else if (field.compare("O3")==0) {
                getline(iss, field, ';');
                mesure.O3=stof(field);
            }
            else {
                cerr << "Gaz non trouvé" << endl;
            }
            it->mesures.push_back(mesure);
        } else {
            cerr << "Error parsing Gaz" << endl;
            continue;
        }
    }
    file.close();
}

void DataParser::parserUtilisateurs() {
    string filename = datapath + "users.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Particulier user;
        istringstream iss(line);
        string field;

        // UserID
        if (getline(iss, field, ';')) {
            user.id = stof(field);
        } else {
            cerr << "Error parsing UserID" << endl;
            continue;
        }

        // SensorID
        vector<Capteur>::iterator it;
        if (getline(iss, field, ';')) {
            // Trouver capteur par ID
            it = find_if(capteurs.begin(), capteurs.end(), [&field](const Capteur& capteur) {return capteur.id == field;});
            if (it == capteurs.end()) {
                cerr << "Le capteur n'a pas été trouvé." << endl;
            } else {
                user.ajouterCapteur(*it);
            }
        } else {
            cerr << "Error parsing SensorID" << endl;
            continue;
        }

        utilisateurs.push_back(user);
    }

    file.close();
}

void DataParser::parserAttributs() {
    string filename = datapath + "attributes.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    } 

    string line;
    getline(file, line);
    while (getline(file, line)) {
        Attribut attribut;
        istringstream iss(line);
        string field;

        // AttributeID
        if (getline(iss, field, ';')) {
            attribut.id = field;
        } else {
            cerr << "Error parsing AttributeID" << endl;
            continue;
        }

        // Unit
        if (getline(iss, field, ';')) {
            attribut.unit = field;
        } else {
            cerr << "Error parsing Unit" << endl;
            continue;
        }

        // Description
        if (getline(iss, field, ';')) {
            attribut.description = field;
        } else {
            cerr << "Error parsing Description" << endl;
            continue;
        }

        attributs.push_back(attribut);
    }

    file.close();
}

// Constructeur
DataParser::DataParser(const string path) {
    datapath = path;
    obtenirPurificateurs();
    parserCapteurs();
    // parserUtilisateurs();
    parserAttributs();
    parserMesures();
}