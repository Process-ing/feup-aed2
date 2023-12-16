/**
 * Header file for class Dataset,
 */

#ifndef FEUP_AED2_DATASET_H
#define FEUP_AED2_DATASET_H

#include <unordered_set>
#include "City.h"

typedef Graph<AirportInfo, AirportHash, FlightInfo> Network;
typedef std::unordered_set<City*, CityHash, CityHash> CitySet;
typedef std::unordered_set<Airline*, AirlineHash, AirportHash> AirlineSet;


class Dataset {
  public:
    Dataset();

  private:
    std::vector<Country> countries_;
    CitySet citySet_;
    AirlineSet airlineSet_;
    Network network_;
};


#endif //FEUP_AED2_DATASET_H
