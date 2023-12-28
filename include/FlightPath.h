#ifndef FEUP_AED2_FLIGHTPATH_H
#define FEUP_AED2_FLIGHTPATH_H


#include <vector>
#include "Airport.h"

class FlightPath {
  public:
    FlightPath();

    FlightPath(const std::vector<AirportRef> &airports, double distance);

    const std::vector<AirportRef> &getAirports() const;
    std::vector<AirportRef> &getAirports();
    double getDistance() const;
    void setDistance(double distance);
    int getFlights() const;

private:
    std::vector<AirportRef> airports_;
    double distance_;
};


#endif //FEUP_AED2_FLIGHTPATH_H
