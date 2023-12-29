/**
 * @file
 * Header file for class Program.
 */

#ifndef FEUP_AED2_PROGRAM_H
#define FEUP_AED2_PROGRAM_H


#include "Dataset.h"

class Program {
  public:
    Program();

    void launch() const;

  private:
    Dataset dataset_;
    void displayMainMenu() const;
    void searchMenu() const;
    void destinationsFromAirportMenu() const;
    void reachableDestinationsFromAirportMenu() const;
    void statisticsMenu() const;
    static std::vector<AirportRef> sortAirportsMenu(std::vector<AirportRef> airports) ;
    std::vector<AirlineRef> sortAirlinesMenu(std::vector<AirlineRef> airlines) const;
    static std::vector<AirportRef> sortAirportsCityMenu(std::vector<AirportRef> airports) ;
    std::vector<AirlineRef> sortAirlinesCountryMenu(std::vector<AirlineRef> airlines) const;
    std::vector<CountryRef> sortCountries(std::vector<CountryRef> countries) const;
    std::vector<CityRef> sortCities(std::vector<CityRef> cities) const;
    void chooseBestFlight() const;
    std::vector<AirportRef> chooseAirportsForBestFlight() const;
    static void displayBestFlight(const std::vector<FlightPath> &paths);
    static int receiveOption(int max);
    CountryRef receiveCountry() const;
    CityRef receiveCity() const;
    AirlineRef receiveAirlineByCode() const;
    AirlineRef receiveAirlineByName() const;
    AirportRef receiveAirportByCode() const;
    AirportRef receiveAirportByName() const;
    static void waitForEnter();
    static void clearScreen();
    static void leave();

    void displayDestinationsFromAirport() const;
    void displayReachableAirportsFromAirportInNStops() const;
    void displayReachableCitiesFromAirportInNStops() const;
    void displayReachableCountriesFromAirportInNStops() const;
    void displayTopNAirportsWithGreatestTraffic() const;
    void displayAirportsEssentialToNetworkCirculation() const;
    void displayAllCountries() const;
    void displayAllAirports() const;
    void displayAllAirlines() const;
    void displayAirlinesByCountry() const;
    void displayCitiesByCountry() const;
    void displayAirportsByCity() const;
    void displayFlightsFromAirport() const;
    void displayCountriesFlyingToAirport() const;
    void displayCountriesFlyingToCity() const;
    void displayCountriesFromAirport() const;
    void displayCitiesFromAirport() const;
    void displayCountries(const std::vector<CountryRef> &countries) const;
    void displayCities(const std::vector<CityRef> &cities) const;
    void displayAirlines(const std::vector<AirlineRef> &airlines) const;
    void displayAirports(const std::vector<AirportRef> &airports) const;
    void displayFlights(const std::vector<Flight> &flights) const;

    void displayNumberOfAirports() const;
    void displayNumberOfAvailableFlights() const;
    void displayNumberOfFlightsPerCity() const;
    void displayNumberOfFlightsPerAirline() const;
    void displayNumberOfDifferentCountriesThatFlyToAirport() const;
    void displayNumberOfDifferentCountriesThatFlyToCity() const;
    void displayNumberOfDifferentDestinationsFromAirport() const;
    void displayNumberOfReachableDestinationsInNStopsFromAirport() const;
    void displayMaximumTrip() const;
    void displayNumberOfAirportsEssentialToNetworkCirculation() const;
    void displayNumberOfCountries() const;
    void displayNumberOfCities() const;
    void displayNumberOfAirlines() const;
};


#endif //FEUP_AED2_PROGRAM_H
