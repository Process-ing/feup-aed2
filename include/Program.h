/**
 * @file
 * @brief Header file for class Program.
 */

#ifndef FEUP_AED2_PROGRAM_H
#define FEUP_AED2_PROGRAM_H


#include "Dataset.h"

/**
 * @brief Class responsible for the interaction with the user.
 */
class Program {
  public:
    /**
     * @brief Constructs a Program object.
     */
    Program();

    /**
     * @brief Launches the application.
     */
    void launch() const;

  private:
    Dataset dataset_;

    /**
     * @brief Displays the main menu.
     */
    void displayMainMenu() const;

    /**
     * @brief Displays the search menu.
     */
    void searchMenu() const;

    /**
     * @brief Displays the destinations from an airport, after choosing the appropriate destination type.
     */
    void destinationsFromAirportMenu() const;

    /**
     * @brief Displays the reachable destinations from an airport in N stops, after choosing the appropriate
     *        destination type and number of stops.
     */
    void reachableDestinationsFromAirportMenu() const;

    /**
     * @brief Displays the statistics menu.
     */
    void statisticsMenu() const;

    /**
     * @brief Displays a menu to choose the sorting method for a vector of airports.
     * @param airports Vector of airports
     * @return Sorted vector
     */
    static std::vector<AirportRef> sortAirportsMenu(const std::vector<AirportRef>& airports) ;

    /**
     * @brief Displays a menu to choose the sorting method for a vector of airlines.
     * @param airports Vector of airlines
     * @return Sorted vector
     */
    static std::vector<AirlineRef> sortAirlinesMenu(const std::vector<AirlineRef>& airlines) ;

    /**
     * @brief Displays a menu to choose the sorting method for a vector of airports on a single city.
     * @param airports Vector of airports
     * @return Sorted vector
     */
    static std::vector<AirportRef> sortAirportsCityMenu(const std::vector<AirportRef>& airports) ;

    /**
     * @brief Displays a menu to choose the sorting method for a vector of airlines of a single country.
     * @param airports Vector of airlines
     * @return Sorted vector
     */
    static std::vector<AirlineRef> sortAirlinesCountryMenu(const std::vector<AirlineRef>& airlines) ;

    /**
     * @brief Displays a menu to choose the best flight path.
     */
    void chooseBestFlight() const;

    /**
     * @brief Receives the airport options for the best flight path.
     * @return Vector of airports chosen
     */
    std::vector<AirportRef> chooseAirportsForBestFlight() const;

    /**
     * @brief Displays the details about the flight path.
     * @param paths Flight path
     */
    static void displayBestFlight(const std::vector<FlightPath> &paths);

    /**
     * @brief Receives a filter for the airports to use in obtaining best flight.
     * @return Available airports
     */
    std::unordered_set<std::string> chooseAirportFilter() const;

    /**
     * @brief Receives a filter for the airlines to use in obtaining best flight.
     * @return Available airlines
     */
    std::unordered_set<std::string> chooseAirlineFilter() const;

    /**
     * @brief Receives an option from the user, validating it against a maximum value.
     * @param max The maximum value for a valid option.
     * @return The user's chosen option.
     */
    static int receiveOption(int max);

    /**
     * @brief Receives a country chosen by the user.
     * @return Reference to the chosen country, or an empty reference if there is none
     */
    CountryRef receiveCountry() const;

    /**
     * @brief Receives a city chosen by the user.
     * @return Reference to the chosen city, or an empty reference if there is none
     */
    CityRef receiveCity() const;

    /**
     * @brief Opens a menu to choose an airport with a code or a name
     * @return Reference to the chosen airport, or an empty reference if there is none
     */
    AirportRef receiveAirport() const;

    /**
     * @brief Receives an airport chosen by the user by its code.
     * @return Reference to the chosen airport, or an empty reference if there is none
     */
    AirportRef receiveAirportByCode() const;

    /**
     * @brief Receives a country chosen by the user by its name.
     * @return Reference to the chosen airport, or an empty reference if there is none
     */
    AirportRef receiveAirportByName() const;

    /**
     * @brief Receives a series of strings from the user, separated by commas.
     * @return Set of strings received
     */
    static std::unordered_set<std::string> receiveStrings();

    /**
     * @brief Waits for the user to press Enter before continuing.
     */
    static void waitForEnter();

    /**
     * @brief Clears the terminal where the program is running.
     */
    static void clearScreen();

    /**
     * @brief Sends a message to the user, pointing to the user that he's about to leave.
     */
    static void leave();

    /**
     * @brief Displays the destinations from an airport.
     */
    void displayAirportsAirportFliesTo() const;

    /**
     * @brief Displays the reachable airports from an airport in a number of stops.
     */
    void displayReachableAirportsFromAirportInNStops() const;

    /**
     * @brief Displays the reachable cities from an airport in a number of stops.
     */
    void displayReachableCitiesFromAirportInNStops() const;

    /**
     * @brief Displays the reachable countries from an airport in a number of stops.
     */
    void displayReachableCountriesFromAirportInNStops() const;

    /**
     * @brief Displays the top airports with the greatest air traffic.
     */
    void displayTopNAirportsWithGreatestTraffic() const;

    /**
     * @brief Displays the essential airports in the network.
     */
    void displayAirportsEssentialToNetworkCirculation() const;

    /**
     * @brief Displays all the countries and their related info.
     */
    void displayAllCountries() const;

    /**
     * @brief Displays the airports in the network and their respective info.
     */
    void displayAllAirports() const;

    /**
     * @brief Displays all the airlines in the network and their respective
     */
    void displayAllAirlines() const;

    /**
     * @brief Displays the airlines of a specified country.
     */
    void displayAirlinesByCountry() const;

    /**
     * @brief Displays the cities in a specified country.
     */
    void displayCitiesByCountry() const;

    /**
     * @brief Displays the airports in a specified city.
     */
    void displayAirportsByCity() const;

    /**
     * @brief Displays the flights going out of an airport an their respective info.
     */
    void displayFlightsFromAirport() const;

    /**
     * @brief Displays the countries an airport flies to.
     */
    void displayCountriesAirportFliesTo() const;

    /**
     * @brief Displays the countries a city flies to.
     */
    void displayCountriesCityFliesTo() const;

    /**
     * @brief Displays the cities an airport flies to.
     */
    void displayCitiesAirportFliesTo() const;

    /**
     * @brief Displays the information about the given countries.
     * @param countries Set of countries
     */
    void displayCountries(const std::vector<CountryRef> &countries) const;

    /**
     * @brief Displays the information about the given cities.
     * @param cities Set of cities
     */
    void displayCities(const std::vector<CityRef> &cities) const;

    /**
     * @brief Displays the information about the given airlines.
     * @param cities Set of airlines
     */
    void displayAirlines(const std::vector<AirlineRef> &airlines) const;

    /**
     * @brief Displays the information about the given airports.
     * @param cities Set of airports
     */
    void displayAirports(const std::vector<AirportRef> &airports) const;

    /**
     * @brief Displays the information about the given flights.
     * @param cities Set of flights
     */
    void displayFlights(const std::vector<Flight> &flights) const;

    /**
     * @brief Displays the number of airports an airport flies to.
     */
    void displayNumberOfDifferentAirportsAirportFliesTo() const;

    /**
     * @brief Displays the number of different reachable destinations from an airport.
     */
    void displayNumberOfReachableDestinationsInNStopsFromAirport() const;

    /**
     * @brief Displays the details about the longest trips (in number of stops).
     */
    void displayMaxTrips() const;

    /**
     * @brief Displays all the global statistics of the networks.
     */
    void displayGlobalStatistics() const;

    /**
     * @brief Displays the statistics of a given city.
     */
    void displayCityStatistics() const;

    /**
     * @brief Displays the menu to select the wanted airport's statistics.
     */
    void airportStatisticsMenu() const;

    /**
     * @brief Displays the statistics about the flights out of an airport.
     */
    void displayFlightsOutOfAnAirport() const;
};


#endif //FEUP_AED2_PROGRAM_H
