#ifndef FEUP_AED2_UTILS_H
#define FEUP_AED2_UTILS_H
#include <vector>
#include "Airline.h"

class utils;

void sortAirlinesByName(std::vector<AirlineRef>& airlines);
void sortAirlinesByCode(std::vector<AirlineRef>& airlines);
void sortAirlinesByCountry(std::vector<AirlineRef>& airlines);

void sortAirportsByName(std::vector<AirportRef>& airports);
void sortAirportsByCode(std::vector<AirportRef>& airports);
void sortAirportsByCountry(std::vector<AirportRef>& airports);
void sortAirportsByCity(std::vector<AirportRef>& airports);


#endif //FEUP_AED2_UTILS_H
