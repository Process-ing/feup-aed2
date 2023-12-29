/**
 * @file
 * Header file for class Dataset,
 */

#ifndef FEUP_AED2_DATASET_H
#define FEUP_AED2_DATASET_H

#include <unordered_set>
#include "City.h"
#include "FlightPath.h"

typedef Graph<AirportInfo, FlightInfo, AirportInfoHash> Network;
typedef VertexSet<AirportInfo, FlightInfo, AirportInfoHash> AirportSet;
typedef std::unordered_set<std::shared_ptr<Country>, CountryHash, CountryHash> CountrySet;
typedef std::unordered_set<CountryRef, CountryHash, CountryHash> CountryRefSet;
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
    const AirportSet& getAirports() const;

    CountryRef getCountry(const std::string& name) const;
    CityRef getCity(const std::string& name, const std::string& countryName) const;
    AirportRef getAirport(const std::string& code) const;
    AirlineRef getAirline(const std::string& code) const;
    std::vector<AirlineRef> getAirlinesFromCountry(const Country& country) const;
    std::vector<CityRef> getCitiesFromCountry(const Country& country) const;
    std::vector<AirportRef> getAirportsFromCity(const City& city) const;
    std::vector<CountryRef> getCountriesAirportFliesTo(const Airport& airport) const;
    std::vector<CountryRef> getCountriesCityFliesTo(const City& city) const;
    std::vector<Flight> searchFlightsFromAirport(const std::string& airportCode) const;
    float numberOfFlightsByCity() const;
    float numberOfFlightsByAirline() const;
    int numberOfFlights() const;
    std::vector<CityRef> searchCitiesFromAirport(const AirportRef& airport) const;
    std::vector<AirportRef> searchAirportsFromAirport(const AirportRef& airport) const;
    std::vector<CountryRef> searchCountriesFromAirport(const AirportRef& airport) const;
    std::vector<AirportRef> searchTopNAirPortsWithGreatestTraffic(int n) const;
    std::vector<AirportRef> getReachableAirportsFromAirport(const AirportRef& airport, int x) const;
    std::vector<CityRef> getReachableCitiesFromAirport(const AirportRef& airport, int x) const;
    std::vector<CountryRef> getReachableCountriesFromAirport(const AirportRef& airport, int x) const;
    std::vector<std::pair<AirportRef, AirportRef>> getMaxTrips(int& diameter);
    std::pair<AirportRef, AirportRef> diameterBFS(const AirportRef& airport, int &diameter);

    FlightPath getBestFlightPath(const AirportRef &src, const AirportRef &dest) const;
    std::vector<FlightPath> getBestFlightPaths(const std::vector<AirportRef> &srcs, const std::vector<AirportRef> &dests) const;

  private:
    CountrySet countrySet_;
    CitySet citySet_;
    AirlineSet airlineSet_;
    Network network_;

    CityRef getOrInsertCity(const std::string& name, const std::string& country);
    CountryRef getOrInsertCountry(const std::string& name);

    static double calculateDistance(double lat1, double lon1, double lat2, double lon2);
};


#endif //FEUP_AED2_DATASET_H
