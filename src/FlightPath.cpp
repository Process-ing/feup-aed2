#include "FlightPath.h"

FlightPath::FlightPath(): airports_(), distance_(0.0) {}

FlightPath::FlightPath(const std::vector<AirportRef> &airports, double distance)
    : airports_(airports), distance_(distance) {}

const std::vector<AirportRef> &FlightPath::getAirports() const {
    return airports_;
}

std::vector<AirportRef> &FlightPath::getAirports() {
    return airports_;
}

double FlightPath::getDistance() const {
    return distance_;
}

void FlightPath::setDistance(double distance) {
    distance_ = distance;
}

int FlightPath::getFlights() const {
    return (int)airports_.size() - 1;
}
