#include <utility>
#include "Flight.h"

FlightInfo::FlightInfo(AirlineRef airline, double distance)
    : airline_(std::move(airline)), distance_(distance) {}

const AirlineRef &FlightInfo::getAirline() const {
    return airline_;
}


double FlightInfo::getDistance() const {
    return distance_;
}
