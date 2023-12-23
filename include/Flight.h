/**
 * @file
 * Header file for class Flight.
 */

#ifndef FEUP_AED2_FLIGHT_H
#define FEUP_AED2_FLIGHT_H


#include "Airline.h"


class Airline;
typedef std::weak_ptr<Airline> AirlineRef;
class AirportInfo;

class FlightInfo {
public:
    explicit FlightInfo(AirlineRef airline, const AirportInfo& src, const AirportInfo& dest);

    const AirlineRef &getAirline() const;
    double getDistance() const;

private:
    AirlineRef airline_;
    double distance_;

    static double calculateDistance(const AirportInfo& src, const AirportInfo& dest);
};

typedef Edge<AirportInfo, FlightInfo> Flight;


#endif //FEUP_AED2_FLIGHT_H
