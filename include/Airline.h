/**
 * @file
 * @brief Header file for class Airline.
 */

#ifndef FEUP_AED2_AIRLINE_H
#define FEUP_AED2_AIRLINE_H


#include <string>
#include <memory>
#include "Country.h"

class Country;
typedef std::weak_ptr<Country> CountryRef;

/**
 * @brief Class that contains all the info about an airline.
 */
class Airline {
  public:
    /**
     * @brief Constructs an Airline object.
     * @param code Airline's code
     * @param name Airline's name
     * @param callsign Airline's callsign
     * @param country Airline's country
     */
    Airline(std::string code, std::string name, std::string callsign, CountryRef country);

    /**
     * @brief Returns the airline's code.
     * @return Airline's code
     */
    const std::string &getCode() const;

    /**
     * @brief Returns the airline's name.
     * @return Airline's name
     */
    const std::string &getName() const;

    /**
     * @brief Returns the airline's callsign.
     * @return Airline's callsign
     */
    const std::string &getCallsign() const;

    /**
     * @brief Returns the airline's country.
     * @return Airline's country
     */
    CountryRef getCountry() const;

  private:
    std::string code_;
    std::string name_;
    std::string callsign_;
    CountryRef country_;
};

/**
 * @brief Reference to an airline.
 */
typedef std::weak_ptr<Airline> AirlineRef;

/**
 * @brief Hash functional class object for Airline objects.
 */
struct AirlineHash {
    /**
     * @brief Returns the hashcode of an airline.
     * @param airline Airline's reference
     * @return Airline's hashcode.
     */
    int operator() (const AirlineRef &airline) const;

    /**
     * @brief Returns if two objects refer to the same airline.
     * @param airline1 Reference to one airline
     * @param airline2 Reference to the other airline
     * @return True if the airline's are the same, false otherwise
     */
    bool operator() (const AirlineRef &airline1, const AirlineRef &airline2) const;
};


#endif //FEUP_AED2_AIRLINE_H
