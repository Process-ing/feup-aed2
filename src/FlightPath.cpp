#include "FlightPath.h"

#include <utility>

using namespace std;

FlightPath::FlightPath(AirportRef initialAirport, vector<pair<Flight, vector<AirlineRef>>> flights)
    : initialAirport_(std::move(initialAirport)), flights_(std::move(flights)) {}

const AirportRef &FlightPath::getInitialAirport() const {
    return initialAirport_;
}

const vector<pair<Flight, vector<AirlineRef>>> &FlightPath::getFlights() const {
    return flights_;
}

double FlightPath::getDistance() const {
    double res = 0;
    for (const pair<Flight, vector<AirlineRef>>& flight: flights_)
        res += flight.first.getInfo().getDistance();
    return res;
}
