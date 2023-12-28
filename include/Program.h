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
    void statisticsMenu() const;
    void sortAirportsMenu() const;
    void sortAirlinesMenu() const;
    void sortAirports(std::vector<AirportRef>& airports, int sortOption) const;
    void sortAirlines(std::vector<AirlineRef>& airlines, int sortOption) const;
    void sortCountries(std::vector<CountryRef> countries) const;
    void sortCities(std::vector<CityRef> cities) const;
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
    void displayReachableDestinationsFromAirportInNStops() const;
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

    void displayCountries(const std::vector<CountryRef> &countries) const;
    void displayCities(const std::vector<CityRef> &cities) const;
    void displayAirlines(const std::vector<AirlineRef> &airlines) const;
    void displayAirports(const std::vector<AirportRef> &airports) const;
    void displayFlights(const std::vector<Flight> &flights) const;
};


#endif //FEUP_AED2_PROGRAM_H
