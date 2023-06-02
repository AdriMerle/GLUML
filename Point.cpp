#include "Point.h"
#include <cmath> 

float Point::Distance(const Point& p) const
{
    return sqrt(pow(this->lat-p.lat,2)+pow(this->lng-p.lng,2));
}

bool Point::operator == (const Point & p) const
{
    return (p.lat==this->lat && p.lng==this->lng);
}

ostream& operator<<(ostream& os, const Point& p)
{
    os << "(" << p.lat << ", " << p.lng << ')';
    return os;
}
