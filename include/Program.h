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
    std::vector<std::string> displayCountries();
    std::vector<std::string> displayAirports();
    std::vector<std::string> displayAirlines();
    std::vector<std::string> displayFlightsFromAirport(std::string airPortCode);
    int displayFlightsByCityAndAirline(const std::string &countryName, const std::string &cityName);
    std::vector<std::string> displayDestinationsFromAirport(std::string airPortCode);
    std::vector<std::string> displayTopNAirPortsWithGreatestTraffic(int n);

  private:
    Dataset dataset_;
};


#endif //FEUP_AED2_PROGRAM_H
