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
     * @brief Constructs an empty FlightPath object.
     */
    FlightPath();

    /**
     * @brief Returns the airport sequence of the flight path.
     * @return Airport sequence
     */
    const std::vector<AirportRef> &getAirports() const;

    /**
     * @brief Returns the airport sequence of the flight path.
     * @return Airport sequence
     */
    std::vector<AirportRef> &getAirports();

    /**
     * @brief Return the flight path's total travel distance.
     * @return Travel distance
     */
    double getDistance() const;

    /**
     * @brief Sets the flight path's total travel distance.
     * @param distance Travel distance
     */
    void setDistance(double distance);

    /**
     * Calculates the number of flights in the flight path.
     * @return Number of flights
     */
    int getFlights() const;

  private:
    std::vector<AirportRef> airports_;
    double distance_;
};


#endif //FEUP_AED2_FLIGHTPATH_H
