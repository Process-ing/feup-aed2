#include "FlightPath.h"

#include <utility>

FlightPath::FlightPath(AirportRef initialAirport, std::vector<Flight> flights)
    : initialAirport_(std::move(initialAirport)), flights_(std::move(flights)) {}

const AirportRef &FlightPath::getInitialAirport() const {
    return initialAirport_;
}

const std::vector<Flight> &FlightPath::getFlights() const {
    return flights_;
}

double FlightPath::getDistance() const {
    double res = 0;
    for (const Flight& flight: flights_)
        res += flight.getInfo().getDistance();
    return res;
}
