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
class Airline;


class Country {
  public:
    explicit Country(std::string name);

    const std::string &getName() const;
    const std::vector<City> &getCities() const;
    void addCity(const City& city);
    const std::vector<Airline> &getAirlines() const;
    void addAirline(const Airline& airline);

  private:
    std::string name_;
    std::vector<City> cities_;
    std::vector<Airline> airlines_;
};

#endif //FEUP_AED2_COUNTRY_H
