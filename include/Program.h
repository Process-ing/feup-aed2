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
  private:
    Dataset dataset_;

    void displayMainMenu();
    void chooseBestFlight();
    std::vector<AirportRef> chooseAirportsForBestFlight();
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
};


#endif //FEUP_AED2_PROGRAM_H
