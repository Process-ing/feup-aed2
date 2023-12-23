#include "Airport.h"

#include <utility>

using namespace std;

AirportInfo::AirportInfo(string code, string name, CityRef city, double latitude,double longitude)
    : code_(std::move(code)), name_(std::move(name)), city_(std::move(city)),
      latitude_(latitude), longitude_(longitude) {}

const string &AirportInfo::getCode() const {
    return code_;
}

const string &AirportInfo::getName() const {
    return name_;
}

const CityRef &AirportInfo::getCity() const {
    return city_;
}

double AirportInfo::getLatitude() const {
    return latitude_;
}

double AirportInfo::getLongitude() const {
    return longitude_;
}

int AirportInfoHash::operator()(const AirportInfo &airport) const {
    return (int)hash<string>()(airport.getCode());
}

bool AirportInfoHash::operator()(const AirportInfo &airport1, const AirportInfo &airport2) const {
    return airport1.getCode() == airport2.getCode();
}

