#include "Country.h"

#include <utility>

using namespace std;


Country::Country(std::string name) : name_(std::move(name)) {}

const string &Country::getName() const {
    return name_;
}

const vector<shared_ptr<City>> &Country::getCities() const {
    return cities_;
}

CityRef Country::addCity(const City &city) {
    return *cities_.insert(cities_.end(), make_shared<City>(city));
}

const vector<shared_ptr<Airline>> &Country::getAirlines() const {
    return airlines_;
}

AirlineRef Country::addAirline(const Airline &airline) {
    return *airlines_.insert(airlines_.end(), make_shared<Airline>(airline));
}

int CountryHash::operator()(const CountryRef &country) const {
    return (int)hash<string>()(country.lock()->getName());
}

bool CountryHash::operator()(const CountryRef &country1, const CountryRef &country2) const {
    return country1.lock()->getName() == country2.lock()->getName();
}
