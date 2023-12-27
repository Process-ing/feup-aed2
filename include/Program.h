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
    std::vector<AirportInfo> searchDestinationsFromAirport(std::string airPortCode);
    std::vector<AirportRef> searchTopNAirPortsWithGreatestTraffic(int n);
    void displayAllCountries();
  private:
    Dataset dataset_;

    void displayMainMenu();
    void searchMenu();
    void statisticsMenu();
    int receiveOption(int max);
    static void waitForEnter();
    static void clearScreen();
    void leave();
};


#endif //FEUP_AED2_PROGRAM_H
