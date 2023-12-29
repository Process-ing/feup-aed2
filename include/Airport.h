/**
 * @file
 * Header file for class Airport.
 */

#ifndef FEUP_AED2_AIRPORT_H
#define FEUP_AED2_AIRPORT_H


#include <string>
#include "City.h"
#include "Graph.h"
#include "Flight.h"


class City;
typedef std::weak_ptr<City> CityRef;
class FlightInfo;

/**
 * @brief Class that contains all the info about an airport.
 */
class AirportInfo {
  public:
    /**
     * @brief Constructs an AirportInfo object.
     * @param code Airport's code
     * @param name Airport's name
     * @param city Airport's city
     * @param latitude Airport's latitude
     * @param longitude Airport's longitude
     */
    AirportInfo(std::string code, std::string name, CityRef city, double latitude, double longitude);

    /**
     * @brief Returns the airport's code.
     * @return Airport's code
     */
    const std::string &getCode() const;

    /**
     * @brief Returns the airport's name.
     * @return Airport's name
     */
    const std::string &getName() const;

    /**
     * @brief Returns the airport's city.
     * @return Airport's code
     */
    const CityRef &getCity() const;

    /**
     * @brief Returns the airport's latitude.
     * @return Airport's latitude
     */
    double getLatitude() const;

    /**
     * @brief Returns the airport's longitude.
     * @return Airport's longitude
     */
    double getLongitude() const;

  private:
    std::string code_;
    std::string name_;
    CityRef city_;
    double latitude_;
    double longitude_;
};


/**
 * @brief Hash functional class for AirportInfo objects.
 */
struct AirportInfoHash {
    /**
     * @brief Returns the hashcode of an airport, based on it's code.
     * @param airport Reference to an AirportInfo object
     * @return Object's hashcode
     */
    int operator() (const AirportInfo& airport) const;

    /**
     * @brief Returns if two AirportInfo objects refer to the same airport, based on their codes.
     * @param airport1 Reference to an AirportInfo object
     * @param airport2 Reference to other AirportInfo object
     * @return True if they are the same, false otherwise
     */
    bool operator() (const AirportInfo& airport1, const AirportInfo& airport2) const;
};

/**
 * @brief Vertex in the aerial network.
 */
typedef Vertex<AirportInfo, FlightInfo> Airport;

/**
 * @brief Reference to an airport in the network.
 */
typedef VertexRef<AirportInfo, FlightInfo> AirportRef;


#endif //FEUP_AED2_AIRPORT_H
