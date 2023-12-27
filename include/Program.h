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

    void launch();
    std::vector<AirportInfo> searchFlightsFromAirport(std::string airPortCode);
    float numberOfFlightsByCity();
    float numberOfFlightsByAirline();
    std::vector<AirportInfo> searchDestinationsFromAirport(std::string airPortCode);
    std::vector<AirportRef> searchTopNAirPortsWithGreatestTraffic(int n);
    void displayAllCountries();
    void displayAllAirports();
    void displayAllAirlines();
  private:
    Dataset dataset_;
    void displayMainMenu();
    void searchMenu();
    void statisticsMenu();
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
};


#endif //FEUP_AED2_PROGRAM_H
