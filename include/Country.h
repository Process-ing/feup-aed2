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

class Country {
  public:
    explicit Country(std::string name);

    const std::string &getName() const;
    const std::vector<std::shared_ptr<City>> &getCities() const;
    CityRef addCity(const City& city);
    const std::vector<std::shared_ptr<Airline>> &getAirlines() const;
    AirlineRef addAirline(const Airline& airline);

    bool operator==(const Country& other) const;

  private:
    std::string name_;
    std::vector<std::shared_ptr<City>> cities_;
    std::vector<std::shared_ptr<Airline>> airlines_;
};

typedef std::weak_ptr<Country> CountryRef;


struct CountryHash {
    int operator()(const CountryRef &country) const;
    bool operator()(const CountryRef &country1, const CountryRef &country2) const;
};


#endif //FEUP_AED2_COUNTRY_H
