/**
 * @file
 * Header file for class Country.
 */

#ifndef FEUP_AED2_COUNTRY_H
#define FEUP_AED2_COUNTRY_H


#include <string>
#include <unordered_set>
#include <vector>
#include "City.h"
#include "Airline.h"


class City;
typedef std::weak_ptr<City> CityRef;
class Airline;
typedef std::weak_ptr<Airline> AirlineRef;

/**
 * @brief Class that contains all the info about a country.
 */
class Country {
  public:
    /**
     * @brief Constructs a Country object.
     * @param name Country's name
     */
    explicit Country(std::string name);

    /**
     * @brief Returns the country's name.
     * @return Country's name
     */
    const std::string &getName() const;

    /**
     * @brief Returns the country's cities.
     * @return Country's cities
     */
    const std::vector<std::shared_ptr<City>> &getCities() const;

    /**
     * @brief Places a city in the country.
     * @param city City
     * @return Reference to the added city
     */
    CityRef addCity(const City& city);

    /**
     * @brief Returns the country's airlines.
     * @return City's airlines
     */
    const std::vector<std::shared_ptr<Airline>> &getAirlines() const;

    /**
     * @brief Places an airline in the country.
     * @param airline Airline to add
     * @return Reference to the airline
     */
    AirlineRef addAirline(const Airline& airline);

  private:
    std::string name_;
    std::vector<std::shared_ptr<City>> cities_;
    std::vector<std::shared_ptr<Airline>> airlines_;
};

/**
 * @brief Reference to a country.
 */
typedef std::weak_ptr<Country> CountryRef;

/**
 * @brief Hash functional class for Country objects.
 */
struct CountryHash {
    /**
     * @brief Returns the hashcode of a country, based on its name.
     * @param country Reference to Country object
     * @return Country's hashcode
     */
    int operator()(const CountryRef &country) const;

    /**
     * @brief Checks if two countries are the same, based on its name.
     * @param country1 Reference to a Country's object
     * @param country2 Reference to the other Country's object
     * @return True if the two objects are the same, false otherwise
     */
    bool operator()(const CountryRef &country1, const CountryRef &country2) const;
};


#endif //FEUP_AED2_COUNTRY_H
