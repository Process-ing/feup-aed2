/**
 * @file FlightPath.h
 * @brief Header file for class FlightPath.
 */

#ifndef FEUP_AED2_FLIGHTPATH_H
#define FEUP_AED2_FLIGHTPATH_H


#include <vector>
#include "Airport.h"

/**
 * @brief Class that represents a flight path, with the respective airports in sequence and the total travel distance.
 */
class FlightPath {
  public:
    /**
     * @brief Constructs a FlightPath object.
     * @param initialAirport Initial airport
     * @param flights Flights in the path, with the respective available alternative airlines
     */
    FlightPath(AirportRef initialAirport, std::vector<std::pair<Flight, std::vector<AirlineRef>>> flights);

    /**
     * @brief Returns the initial airport of the path.
     * @return Initial airport
     */
    const AirportRef &getInitialAirport() const;

    /**
     * @brief Returns the flights in the flight path, with their respective available alternative airlines.
     * @return Vector of flights, in the respective sequence, paired with the available airlines
     */
    const std::vector<std::pair<Flight, std::vector<AirlineRef>>> &getFlights() const;

    /**
     * @brief Return the flight path's total travel distance.
     * @return Travel distance
     */
    double getDistance() const;

  private:
    AirportRef initialAirport_;
    std::vector<std::pair<Flight, std::vector<AirlineRef>>> flights_;
};


#endif //FEUP_AED2_FLIGHTPATH_H
