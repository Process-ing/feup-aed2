/**
 * @file
 * @brief Useful functions for the program.
 */

#ifndef FEUP_AED2_UTILS_H
#define FEUP_AED2_UTILS_H

#include <vector>
#include "Airline.h"

/**
 * @brief Sorts a vector of airlines by name.
 * Complexity: O(N*log(N)), where N is airlines.size().
 * @param airlines Airline vector
 * @return Sorted vector
 */
std::vector<AirlineRef> sortAirlinesByName(std::vector<AirlineRef> airlines);

/**
 * @brief Sorts a vector of airlines by code.
 * Complexity: O(N*log(N)), where N is the airlines.size().
 * @param airlines Airline vector
 * @return Sorted vector
 */
std::vector<AirlineRef> sortAirlinesByCode(std::vector<AirlineRef> airlines);

/**
 * @brief Sorts a vector of airlines by country's name.
 * Complexity: O(N*log(N)), where N is airlines.size().
 * @param airlines Airline vector
 * @return Sorted vector
 */
std::vector<AirlineRef> sortAirlinesByCountry(std::vector<AirlineRef> airlines);

/**
 * @brief Sorts a vector of airlines by callsign.
 * Complexity: O(N*log(N)), where N is airlines.size().
 * @param airlines Airline vector
 * @return Sorted vector
 */
std::vector<AirlineRef> sortAirlinesByCallsign(std::vector<AirlineRef> airlines);


/**
 * @brief Sorts a vector of airports by code.
 * Complexity: O(N*log(N)), where N is airports.size().
 * @param airports Airport vector
 * @return Sorted vector
 */
std::vector<AirportRef> sortAirportsByCode(std::vector<AirportRef> airports);

/**
 * @brief Sorts a vector of airports by name.
 * Complexity: O(N*log(N)), where N is airports.size().
 * @param airports Airport vector
 * @return Sorted vector
 */
std::vector<AirportRef> sortAirportsByName(std::vector<AirportRef> airports);

/**
 * @brief Sorts a vector of airports by country's name.
 * Complexity: O(N*log(N)), where N is airports.size().
 * @param airports Airport vector
 * @return Sorted vector
 */
std::vector<AirportRef> sortAirportsByCountry(std::vector<AirportRef> airports);

/**
 * @brief Sorts a vector of airports by city's name.
 * Complexity: O(N*log(N)), where N is airports.size().
 * @param airports Airport vector
 * @return Sorted vector
 */
std::vector<AirportRef> sortAirportsByCity(std::vector<AirportRef> airports);

/**
 * @brief Sorts a vector of cities by name.
 * Complexity: O(N*log(N)), where N is cities.size().
 * @param airports City vector
 * @return Sorted vector
 */
std::vector<CityRef> sortCities(std::vector<CityRef> cities);

/**
 * @brief Sorts a vector of countries by name.
 * Complexity: O(N*log(N)), where N is country.size().
 * @param airports Country vector
 * @return Sorted vector
 */
std::vector<CountryRef> sortCountries(std::vector<CountryRef> countries);

#endif //FEUP_AED2_UTILS_H
