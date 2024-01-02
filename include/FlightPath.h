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
     * Complexity: O(N), where N is the number of stages of the path (flights.size()).
     * @param initialAirport Initial airport
     * @param flights Sequence of available flights in each stage
     */
    FlightPath(AirportRef initialAirport, std::vector<std::vector<Flight>> flights);

    /**
     * @brief Returns the initial airport of the path.
     * @return Initial airport
     */
    const AirportRef &getInitialAirport() const;

    /**
     * @brief Returns the sequence of available flights in each stage of the path.
     * @return Vector of vector of flights
     */
    const std::vector<std::vector<Flight>> &getFlights() const;

    /**
     * @brief Return the flight path's total travel distance.
     * @return Travel distance
     */
    double getDistance() const;

  private:
    AirportRef initialAirport_;
    std::vector<std::vector<Flight>> flights_;
    double distance_;
};


#endif //FEUP_AED2_FLIGHTPATH_H
