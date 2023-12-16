/**
 * Header file for class Flight.
 */

#ifndef FEUP_AED2_FLIGHT_H
#define FEUP_AED2_FLIGHT_H


#include "Airline.h"


class Airline;
class AirportInfo;

class FlightInfo {
public:
    explicit FlightInfo(Airline *airline, const AirportInfo& src, const AirportInfo& dest);

    Airline *getAirline() const;
    double getDistance() const;

private:
    Airline* airline_;
    double distance_;

    static double calculateDistance(const AirportInfo& src, const AirportInfo& dest);
};

typedef Edge<AirportInfo, FlightInfo> Flight;


#endif //FEUP_AED2_FLIGHT_H
