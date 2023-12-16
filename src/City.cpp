#include "City.h"

#include <utility>

using namespace std;

City::City(string name, Country *country) : name_(std::move(name)), country_(country) {}

const string &City::getName() const {
    return name_;
}

Country *City::getCountry() const {
    return country_;
}

const vector<Airport *> &City::getAirports() const {
    return airports_;
}

void City::addAirport(Airport *airport) {
    airports_.push_back(airport);
}

int CityHash::operator()(const City *city) const {
    hash<string> stringHash;
    return (int)stringHash(city->getName()) * 37 + (int)stringHash(city->getCountry()->getName());
}

bool CityHash::operator()(const City *city1, const City *city2) const {
    return city1->getName() == city2->getName() && city1->getCountry()->getName() == city2->getCountry()->getName();
}
