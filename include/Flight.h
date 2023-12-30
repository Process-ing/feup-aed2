/**
 * @file
 * @brief Header file for class Flight.
 */

#ifndef FEUP_AED2_FLIGHT_H
#define FEUP_AED2_FLIGHT_H


#include "Airline.h"


class Airline;
typedef std::weak_ptr<Airline> AirlineRef;
class AirportInfo;

/**
 * @brief Class that contains all the info about a flight.
 */
class FlightInfo {
  public:
    /**
     * @brief Constructs a FlightInfo objects
     * @param airline Flight's airline
     * @param distance Flight's travel distance
     */
    explicit FlightInfo(AirlineRef airline, double distance);

    /**
     * @brief Returns the flight's airline.
     * @return Flight's airline
     */
    const AirlineRef &getAirline() const;

    /**
     * @brief Returns the flight's travel distance.
     * @return Travel distance
     */
    double getDistance() const;

  private:
    AirlineRef airline_;
    double distance_;
};

/**
 * @brief Edge in the network, containing the respective flight's info.
 */
typedef Edge<AirportInfo, FlightInfo> Flight;


#endif //FEUP_AED2_FLIGHT_H
