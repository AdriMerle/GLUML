#if ! defined ( MESURE_H )
#define MESURE_H

#include <time.h>
#include <string>
#include <ctime>

using namespace std;
class Mesure {
public:
    
    //constructeur vide
    inline Mesure(){}

    //constructeur
    Mesure(time_t _timestamp, string _idCapteur, float _O3, float _SO2, float _NO2, float _PM10 ) : timestamp(_timestamp), idCapteur(_idCapteur), O3(_O3), SO2(_SO2), NO2(_NO2), PM10(_PM10) {};


    int valeurToIndiceO3() const;
    int valeurToIndiceSO2() const;
    int valeurToIndiceNO2() const;
    int valeurToIndicePM10() const;

    float calculIQAJournee() const;

    //virtual ~Mesure();

    //attributs
    time_t timestamp;
    string idCapteur;
    float O3;
    float SO2;
    float NO2;
    float PM10;

};

#endif // MESURE_H