#include "Country.h"

#include <utility>

using namespace std;


Country::Country(std::string name) : name_(std::move(name)) {}

const string &Country::getName() const {
    return name_;
}

const vector<City> &Country::getCities() const {
    return cities_;
}

void Country::addCity(const City &city) {
    cities_.push_back(city);
}

const vector<Airline> &Country::getAirlines() const {
    return airlines_;
}

void Country::addAirline(const Airline &airline) {
    airlines_.push_back(airline);
}
