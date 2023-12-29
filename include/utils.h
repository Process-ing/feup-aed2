#ifndef FEUP_AED2_UTILS_H
#define FEUP_AED2_UTILS_H

#include <vector>
#include "Airline.h"


std::vector<AirlineRef> sortAirlinesByName(std::vector<AirlineRef> airlines);
std::vector<AirlineRef> sortAirlinesByCode(std::vector<AirlineRef> airlines);
std::vector<AirlineRef> sortAirlinesByCountry(std::vector<AirlineRef> airlines);
std::vector<AirlineRef> sortAirlinesByCallsign(std::vector<AirlineRef> airlines);

std::vector<AirportRef> sortAirportsByName(std::vector<AirportRef> airports);
std::vector<AirportRef> sortAirportsByCode(std::vector<AirportRef> airports);
std::vector<AirportRef> sortAirportsByCountry(std::vector<AirportRef> airports);
std::vector<AirportRef> sortAirportsByCity(std::vector<AirportRef> airports);


#endif //FEUP_AED2_UTILS_H
