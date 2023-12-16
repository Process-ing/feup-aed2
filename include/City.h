/**
 * @file
 * Header file for class City.
 */

#ifndef FEUP_AED2_CITY_H
#define FEUP_AED2_CITY_H


#include <string>
#include <unordered_set>
#include "Country.h"
#include "Airport.h"


class Country;
template<class T, class U> class Vertex;
class AirportInfo;
class FlightInfo;
typedef Vertex<AirportInfo, FlightInfo> Airport;

class City {
  public:
    City(std::string name, Country *country);

    const std::string &getName() const;
    Country *getCountry() const;
    const std::vector<Airport *> &getAirports() const;
    void addAirport(Airport* airport);

  private:
    std::string name_;
    Country* country_;
    std::vector<Airport*> airports_;
};


struct CityHash {
    int operator() (const City* city) const;
    bool operator() (const City* city1, const City* city2) const;
};


#endif //FEUP_AED2_CITY_H
