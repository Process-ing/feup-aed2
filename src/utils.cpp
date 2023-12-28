#include "utils.h"
using namespace std;

vector<AirlineRef> sortAirlinesByName(vector<AirlineRef> airlines) {
    sort(airlines.begin(), airlines.end(), [](const AirlineRef& a, const AirlineRef& b) {
        return a.lock()->getName() < b.lock()->getName();
    });
    return airlines;
}

vector<AirlineRef> sortAirlinesByCode(vector<AirlineRef> airlines) {
    sort(airlines.begin(), airlines.end(), [](const AirlineRef& a, const AirlineRef& b) {
        return a.lock()->getCode() < b.lock()->getCode();
    });
    return airlines;
}

vector<AirlineRef> sortAirlinesByCountry(vector<AirlineRef> airlines) {
    sort(airlines.begin(), airlines.end(), [](const AirlineRef& a, const AirlineRef& b) {
        return a.lock()->getCountry().lock()->getName() < b.lock()->getCountry().lock()->getName();
    });
    return airlines;
}

vector<AirlineRef> sortAirlinesByCallsign(vector<AirlineRef> airlines){
    sort(airlines.begin(), airlines.end(), [](const AirlineRef& a, const AirlineRef& b) {
        return a.lock()->getCallsign() < b.lock()->getCallsign();
    });
    return airlines;
}

vector<AirportRef> sortAirportsByCode(vector<AirportRef> airports) {
    sort(airports.begin(), airports.end(), [](const AirportRef& a, const AirportRef& b) {
        return a.lock()->getInfo().getCode() < b.lock()->getInfo().getCode();
    });
    return airports;
}

vector<AirportRef> sortAirportsByName(vector<AirportRef> airports) {
    sort(airports.begin(), airports.end(), [](const AirportRef& a, const AirportRef& b) {
        return a.lock()->getInfo().getName() < b.lock()->getInfo().getName();
    });
    return airports;
}

vector<AirportRef> sortAirportsByCountry(vector<AirportRef> airports) {
    sort(airports.begin(), airports.end(), [](const AirportRef& a, const AirportRef& b) {
        return a.lock()->getInfo().getCity().lock()->getCountry().lock()->getName() <
               b.lock()->getInfo().getCity().lock()->getCountry().lock()->getName();
    });
    return airports;
}

vector<AirportRef> sortAirportsByCity(vector<AirportRef> airports) {
    sort(airports.begin(), airports.end(), [](const AirportRef& a, const AirportRef& b) {
        return a.lock()->getInfo().getCity().lock()->getName() < b.lock()->getInfo().getCity().lock()->getName();
    });
    return airports;
}
