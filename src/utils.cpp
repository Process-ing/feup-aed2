#include "utils.h"
#include "Program.h"
#include "Airline.h"
using namespace std;


void sortAirlinesByName(vector<AirlineRef>& airlines) {
    sort(airlines.begin(), airlines.end(), [](const AirlineRef& a, const AirlineRef& b) {
        return a.lock()->getName() < b.lock()->getName();
    });
}

void sortAirlinesByCode(vector<AirlineRef>& airlines) {
    sort(airlines.begin(), airlines.end(), [](const AirlineRef& a, const AirlineRef& b) {
        return a.lock()->getCode() < b.lock()->getCode();
    });
}

void sortAirlinesByCountry(vector<AirlineRef>& airlines) {
    sort(airlines.begin(), airlines.end(), [](const AirlineRef& a, const AirlineRef& b) {
        return a.lock()->getCountry().lock()->getName() < b.lock()->getCountry().lock()->getName();
    });
}

void sortAirportsByCode(vector<AirportRef>& airports) {
    sort(airports.begin(), airports.end(), [](const AirportRef& a, const AirportRef& b) {
        return a.lock()->getInfo().getCode() < b.lock()->getInfo().getCode();
    });
}

void sortAirportsByName(vector<AirportRef>& airports) {
    sort(airports.begin(), airports.end(), [](const AirportRef& a, const AirportRef& b) {
        return a.lock()->getInfo().getName() < b.lock()->getInfo().getName();
    });
}

void sortAirportsByCountry(vector<AirportRef>& airports) {
    sort(airports.begin(), airports.end(), [](const AirportRef& a, const AirportRef& b) {
        return a.lock()->getInfo().getCity().lock()->getCountry().lock()->getName() <
               b.lock()->getInfo().getCity().lock()->getCountry().lock()->getName();
    });
}

void sortAirportsByCity(vector<AirportRef>& airports) {
    sort(airports.begin(), airports.end(), [](const AirportRef& a, const AirportRef& b) {
        return a.lock()->getInfo().getCity().lock()->getName() < b.lock()->getInfo().getCity().lock()->getName();
    });
}
