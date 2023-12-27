/**
 * @file
 * Header file for class Dataset,
 */

#ifndef FEUP_AED2_DATASET_H
#define FEUP_AED2_DATASET_H

#include <unordered_set>
#include "City.h"

typedef Graph<AirportInfo, FlightInfo, AirportInfoHash> Network;
typedef std::unordered_set<std::shared_ptr<Country>, CountryHash, CountryHash> CountrySet;
typedef std::unordered_set<CityRef, CityHash, CityHash> CitySet;
typedef std::unordered_set<AirlineRef, AirlineHash, AirlineHash> AirlineSet;


class Dataset {
  public:
    Dataset();

    void readFiles();
    void readAirports();
    void readAirlines();
    void readFlights();

    const Network &getNetwork() const;
    const CountrySet &getCountries() const;
    const CitySet &getCities() const;
    const AirlineSet& getAirlines() const;
    CountryRef getCountry(const std::string& name) const;
    CityRef getCity(const std::string& name, const std::string& countryName) const;
    AirportRef getAirport(const std::string& code) const;
    AirlineRef getAirline(const std::string& code) const;
    std::vector<AirportRef> getReachableAirportsfromAirport(AirportRef airport, int x);
    std::vector<CityRef> getReachableCitiesfromAirport(AirportRef airport, int x);

  private:
    CountrySet countrySet_;
    CitySet citySet_;
    AirlineSet airlineSet_;
    Network network_;

    CityRef getOrInsertCity(const std::string& name, const std::string& country);
    CountryRef getOrInsertCountry(const std::string& name);
};


#endif //FEUP_AED2_DATASET_H
