#include "Airline.h"

#include <utility>

using namespace std;

Airline::Airline(std::string code, std::string name, Country *country, std::string callsign)
    : code_(std::move(code)), name_(std::move(name)), country_(country), callsign_(std::move(callsign)) {}

const string &Airline::getCode() const {
    return code_;
}

const string &Airline::getName() const {
    return name_;
}

const string &Airline::getCallsign() const {
    return callsign_;
}

Country *Airline::getCountry() const {
    return country_;
}

int AirlineHash::operator()(const Airline *airline) const {
    return (int)hash<string>()(airline->getCode());
}

bool AirlineHash::operator()(const Airline *airline1, const Airline *airline2) const {
    return airline1->getCode() == airline2->getCode();
}

