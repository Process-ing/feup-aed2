/**
 * @file
 * Header file for class Airline.
 */

#ifndef FEUP_AED2_AIRLINE_H
#define FEUP_AED2_AIRLINE_H


#include <string>
#include <memory>
#include "Country.h"

class Country;
typedef std::weak_ptr<Country> CountryRef;

class Airline {
  public:
    Airline(std::string code, std::string name, std::string callsign, CountryRef country);

    const std::string &getCode() const;
    const std::string &getName() const;
    const std::string &getCallsign() const;
    CountryRef getCountry() const;

  private:
    std::string code_;
    std::string name_;
    std::string callsign_;
    CountryRef country_;
};

typedef std::weak_ptr<Airline> AirlineRef;


struct AirlineHash {
    int operator() (const AirlineRef &airline) const;
    bool operator() (const AirlineRef &airline1, const AirlineRef &airline2) const;
};


#endif //FEUP_AED2_AIRLINE_H
