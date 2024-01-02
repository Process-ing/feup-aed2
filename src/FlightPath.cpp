#include "FlightPath.h"

#include <utility>

using namespace std;

FlightPath::FlightPath(AirportRef initialAirport, std::vector<std::vector<Flight>> flights)
    : initialAirport_(std::move(initialAirport)), flights_(std::move(flights)) {
    distance_ = 0;
    for (const vector<Flight>& flight: flights_)
        distance_ += flight[0].getInfo().getDistance();
}

const AirportRef &FlightPath::getInitialAirport() const {
    return initialAirport_;
}

const std::vector<std::vector<Flight>> &FlightPath::getFlights() const {
    return flights_;
}

double FlightPath::getDistance() const {
    return distance_;
}
