#include "City.h"

#include <utility>

using namespace std;

City::City(string name, CountryRef country) : name_(std::move(name)), country_(std::move(country)) {}

const string &City::getName() const {
    return name_;
}

const CountryRef &City::getCountry() const {
    return country_;
}

const vector<AirportRef> &City::getAirports() const {
    return airports_;
}

void City::addAirport(const AirportRef &airport) {
    airports_.push_back(airport);
}

int CityHash::operator()(const CityRef &city) const {
    return (int)hash<string>()(city.lock()->getName()) * 37 + CountryHash()(city.lock()->getCountry());
}

bool CityHash::operator()(const CityRef &city1, const CityRef &city2) const {
    return city1.lock()->getName() == city2.lock()->getName() && CountryHash()(city1.lock()->getCountry(), city2.lock()->getCountry());
}
