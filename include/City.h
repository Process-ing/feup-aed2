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
typedef std::weak_ptr<Country> CountryRef;

class Airline;
typedef std::weak_ptr<Airline> AirlineRef;

template<class VertexInfo, class EdgeInfo> class Vertex;
template <class VertexInfo, class EdgeInfo>
using VertexRef = std::weak_ptr<Vertex<VertexInfo, EdgeInfo>>;
class AirportInfo;
class FlightInfo;
typedef Vertex<AirportInfo, FlightInfo> Airport;
typedef VertexRef<AirportInfo, FlightInfo> AirportRef;

class City {
  public:
    City(std::string name, CountryRef country);

    const std::string &getName() const;
    const CountryRef &getCountry() const;
    const std::vector<AirportRef> &getAirports() const;
    void addAirport(const AirportRef &airport);

  private:
    std::string name_;
    CountryRef country_;
    std::vector<AirportRef> airports_;
};

typedef std::weak_ptr<City> CityRef;


struct CityHash {
    int operator() (const CityRef &city) const;
    bool operator() (const CityRef &city1, const CityRef &city2) const;
};


#endif //FEUP_AED2_CITY_H
