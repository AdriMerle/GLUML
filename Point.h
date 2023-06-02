#if ! defined ( POINT_H )
#define POINT_H
using namespace std;

class Point
{
public :
    float lat, lng;

    Point(float _lat, float _lng):lat(_lat),lng(_lng){};
    Point(){};

    float Distance(const Point& p) const;

    bool operator == (const Point & p) const;

};
#endif // POINT_H