#if ! defined ( PURIFICATEUR_H )
#define PURIFICATEUR_H

#include "Point.h"
#include <time.h>
#include <string>
#include <ctime>
using namespace std;

class Purificateur {
public:
    Purificateur(){};
    Purificateur(string _id, Point _pos, time_t _d, time_t _f) : id(_id), position(_pos), debut(_d), fin(_f) {};

    //virtual ~Purificateur();

    //attributs
    string id;
    Point position;
    time_t debut; //time_t
    time_t fin;
};

#endif // PURIFICATEUR_H