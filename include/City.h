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

/**
 * @brief Class that contains all the info about a city.
 */
class City {
  public:
    /**
     * @brief Constructs a City object.
     * @param name City's name
     * @param country Reference to the city's country
     */
    City(std::string name, CountryRef country);

    /**
     * @brief Returns the city's name.
     * @return City's name
     */
    const std::string &getName() const;

    /**
     * @brief Returns a reference to the city's country.
     * @return City's country
     */
    const CountryRef &getCountry() const;

    /**
     * @brief Returns the city's airports.
     * @return City's airports
     */
    const std::vector<AirportRef> &getAirports() const;

    /**
     * @brief Places an airport to the city.
     * @param airport Reference to airport
     */
    void addAirport(const AirportRef &airport);

  private:
    std::string name_;
    CountryRef country_;
    std::vector<AirportRef> airports_;
};

/**
 * @brief Reference to a city.
 */
typedef std::weak_ptr<City> CityRef;

/**
 * @brief Hash functional object for City objects.
 */
struct CityHash {
    /**
     * @brief Returns the hashcode of a City object, based on its name and country.
     * @param city Reference to City object
     * @return City's hashcode
     */
    int operator() (const CityRef &city) const;

    /**
     * @brief Checks if two City objects are the same, based on its name and country.
     * @param city1 Reference to a City object
     * @param city2 Reference to the other City objects
     * @return True if the two objects are the same, false otherwise
     */
    bool operator() (const CityRef &city1, const CityRef &city2) const;
};


#endif //FEUP_AED2_CITY_H
