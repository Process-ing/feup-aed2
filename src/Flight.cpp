#include <cmath>
#include "Flight.h"

FlightInfo::FlightInfo(Airline *airline, const AirportInfo& src, const AirportInfo& dest)
    : airline_(airline), distance_(calculateDistance(src, dest)) {}

Airline *FlightInfo::getAirline() const {
    return airline_;
}

double FlightInfo::getDistance() const {
    return distance_;
}

double hav(double x) {
    double sinVal = sin(x / 2);
    return sinVal * sinVal;
}

double FlightInfo::calculateDistance(const AirportInfo &src, const AirportInfo &dest) {
    static const double EARTH_DIAMETER = 2 * 6356.7523;
    static const double DEG_TO_RAD_FACTOR = M_PI / 180.0;
    double lat1 = src.getLatitude() * DEG_TO_RAD_FACTOR, lat2 = dest.getLatitude() * DEG_TO_RAD_FACTOR,
        lon1 = src.getLongitude() * DEG_TO_RAD_FACTOR, lon2 = dest.getLongitude() * DEG_TO_RAD_FACTOR;

    return EARTH_DIAMETER * asin(hav(lat2 - lat1) + cos(lat1) * cos(lat2) * hav(lon2 - lon1));
}
