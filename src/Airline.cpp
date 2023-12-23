#include "Airline.h"

#include <utility>

using namespace std;

Airline::Airline(std::string code, std::string name, std::string callsign, CountryRef country)
    : code_(std::move(code)), name_(std::move(name)), country_(std::move(country)), callsign_(std::move(callsign)) {}

const string &Airline::getCode() const {
    return code_;
}

const string &Airline::getName() const {
    return name_;
}

const string &Airline::getCallsign() const {
    return callsign_;
}

CountryRef Airline::getCountry() const {
    return country_;
}

int AirlineHash::operator()(const AirlineRef &airline) const {
    return (int)hash<string>()(airline.lock()->getCode());
}

bool AirlineHash::operator()(const AirlineRef &airline1, const AirlineRef &airline2) const {
    return airline1.lock()->getCode() == airline2.lock()->getCode();
}

