/**
 * @file
 * Header file for class Airline.
 */

#ifndef FEUP_AED2_AIRLINE_H
#define FEUP_AED2_AIRLINE_H


#include <string>
#include "Country.h"

class Country;

class Airline {
  public:
    Airline(std::string code, std::string name, Country* country, std::string callsign = "_");

    const std::string &getCode() const;
    const std::string &getName() const;
    const std::string &getCallsign() const;
    Country *getCountry() const;

  private:
    std::string code_;
    std::string name_;
    std::string callsign_;
    Country* country_;
};


struct AirlineHash {
    int operator() (const Airline* airline) const;
    bool operator() (const Airline* airline1, const Airline* airline2) const;
};


#endif //FEUP_AED2_AIRLINE_H
