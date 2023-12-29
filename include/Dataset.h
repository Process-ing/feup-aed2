/**
 * @file
 * Header file for class Dataset,
 */

#ifndef FEUP_AED2_DATASET_H
#define FEUP_AED2_DATASET_H

#include <unordered_set>
#include "City.h"
#include "FlightPath.h"

/**
 * @brief Graph type for the aerial network.
 */
typedef Graph<AirportInfo, FlightInfo, AirportInfoHash> Network;

/**
 * @brief Hash table of airports.
 */
typedef VertexSet<AirportInfo, FlightInfo, AirportInfoHash> AirportSet;

/**
 * @brief Hash table of countries.
 */
typedef std::unordered_set<std::shared_ptr<Country>, CountryHash, CountryHash> CountrySet;

/**
 * @brief Hash table of countries' references.
 */
typedef std::unordered_set<CountryRef, CountryHash, CountryHash> CountryRefSet;

/**
 * @brief Hash table of cities' references.
 */
typedef std::unordered_set<CityRef, CityHash, CityHash> CitySet;

/**
 * @brief Hash table of airlines' references.
 */
typedef std::unordered_set<AirlineRef, AirlineHash, AirlineHash> AirlineSet;

/**
 * @brief Class that contains all the data of the dataset and executes the necessary operations on it.
 */
class Dataset {
  public:
    /**
     * @brief Constructs an empty dataset object.
     */
    Dataset();

    /**
     * @brief Reads the dataset's files and populates this object with them.
     */
    void readFiles();

    /**
     * @brief Reads the file "airports.csv" and populates the dataset object with it.
     * Complexity: O(N), where N is the number of airports.
     */
    void readAirports();

    /**
     * @brief Reads the file "airlines.csv" and populates the dataset object with it.
     * Complexity: O(N), where N is the number of airlines.
     */
    void readAirlines();

    /**
     * @brief Reads the file "flights.csv" and populates the dataset object with it.
     * Complexity: O(N), where N is the number of flights.
     */
    void readFlights();

    /**
     * @brief Returns the network graph.
     * @return Network
     */
    const Network &getNetwork() const;

    /**
     * @brief Returns a hash table with the countries of the dataset.
     * @return Dataset's countries
     */
    const CountrySet &getCountries() const;

    /**
     * @brief Returns a hash table with the cities of the dataset.
     * @return Dataset's cities
     */
    const CitySet &getCities() const;

    /**
     * @brief Returns a hash table with the airlines of the dataset.
     * @return Dataset's airlines
     */
    const AirlineSet& getAirlines() const;

    /**
     * @brief Returns a hash table with the airports of the dataset.
     * @return Dataset's airports
     */
    const AirportSet& getAirports() const;

    /**
     * @brief Returns the country with the given name
     * Complexity: O(1)
     * @param name Country's name
     * @return Reference to the country, or an empty reference if the country does not exist
     */
    CountryRef getCountry(const std::string& name) const;

    /**
     * @brief Returns the city with the given name and country.
     * @param name City's name
     * @param countryName Country's name
     * @return Reference to the city, or an empty reference if the city does not exist
     */
    CityRef getCity(const std::string& name, const std::string& countryName) const;

    /**
     * @brief Returns the airport with the given code.
     * Complexity: O(1)
     * @param code Airport's code
     * @return Reference to the airport, or an empty reference if the airport does not exist
     */
    AirportRef getAirport(const std::string& code) const;

    /**
     * @brief Returns the airline with the given code.
     * Complexity: O(1)
     * @param code Airline's code
     * @return Reference to the airline, or an empty reference if the airline does not exist
     */
    AirlineRef getAirline(const std::string& code) const;

    /**
     * @brief Returns the airlines of a given country.
     * Complexity: O(N), where N is the number of airlines in the country.
     * @param country Reference to the country
     * @return Vector with the country's airlines
     */
    static std::vector<AirlineRef> getAirlinesFromCountry(const CountryRef &country);

    /**
     * @brief Returns the cities of a given country.
     * Complexity: O(N), where N is the number of cities in the country.
     * @param country Reference to the country
     * @return Vector with the country's cities
     */
    static std::vector<CityRef> getCitiesFromCountry(const CountryRef &country);

    /**
     * @brief Returns the airports of a country.
     * Complexity: O(N), where N is the number of airports in the country.
     * @param country Reference to the country
     * @return Vector with the country's airports
     */
    static std::vector<AirportRef> getAirportsFromCountry(const CountryRef &country);

    /**
     * @brief Returns the airports of a city.
     * Complexity: O(N), where N is the number of airports in the city.
     * @param city Reference to the city
     * @return Vector with the city's airports
     */
    static std::vector<AirportRef> getAirportsFromCity(const CityRef &city);

    /**
     * @brief Returns the countries an airport flies to.
     * Complexity: O(N), where N is the number of flights out of the city.
     * @param airport Reference to the airport
     * @return Vector with the countries
     */
    static std::vector<CountryRef> getCountriesAirportFliesTo(const AirportRef &airport);

    /**
     * @brief Returns the countries a city flies to.
     * Complexity: O(M*N), where M is the number of airports in the city and N the number of flights out of each airport.
     * @param city Reference to the city
     * @return Vector with the countries
     */
    static std::vector<CountryRef> getCountriesCityFliesTo(const CityRef &city) ;

    /**
     * @brief Returns the flights out of a given airport.
     * Complexity: O(1)
     * @param airport Reference to the given airport.
     * @return Vector with the flights
     */
    static std::vector<Flight> searchFlightsFromAirport(const AirportRef &airport) ;

    /**
     * @brief Returns the mean number of flights per city.
     * Complexity: O(N), where N is the total number of airports.
     * @return Mean of flights per city
     */
    float numberOfFlightsByCity() const;

    /**
     * @brief Returns the mean number of airlines per airline.
     * Complexity: O(N), where N is the total number of airports.
     * @return Mean of flights per city
     */
    float numberOfFlightsByAirline() const;

    /**
     * @brief Returns the total number of flights.
     * Complexity: O(N), where N is the total number of airports.
     * @return The total number of airports
     */
    int numberOfFlights() const;

    /**
     * @brief Returns the airports directly reachable from a given airport.
     * Complexity: O(N), where N is the number of flights out the given airport
     * @param airport Reference to the source airport
     * @return Vector with the destination airports
     */
    static std::vector<AirportRef> searchReachableAirportsFromAirport(const AirportRef& airport);

    /**
     * @brief Returns the cities directly reachable from a given airport.
     * Complexity: O(N), where N is the number of flights out the given airport
     * @param airport Reference to the source airport
     * @return Vector with the destination cities
     */
    static std::vector<CityRef> searchReachableCitiesFromAirport(const AirportRef& airport);

    /**
     * @brief Returns the countries directly reachable from a given airport.
     * Complexity: O(N), where N is the number of flights out the given airport
     * @param airport Reference to the source airport
     * @return Vector with the destination countries
     */
    static std::vector<CountryRef> searchReachableCountriesFromAirport(const AirportRef& airport);

    /**
     * @brief Returns the top n airports with the greatest air traffic capacity (greatest number of flights in and out).
     * Complexity: O(V*log(V)), where N is the total number of airports.
     * @param n
     * @return Vector with the top airports
     */
    std::vector<AirportRef> searchTopNAirportsWithGreatestTraffic(int n) const;

    /**
     * @brief Returns the airports reachable from a given airport in a maximum of x stops between flights (lay-overs).
     * Complexity: O(V+E), where V is the number of airports and E is the number of flights in the network.
     * @param airport Source airport
     * @param x
     * @return Vector with the reachable airports
     */
    std::vector<AirportRef> getReachableAirportsFromAirport(const AirportRef& airport, int x) const;

    /**
    * @brief Returns the cities reachable from a given airport in a maximum of x stops between flights (lay-overs).
    * Complexity: O(V+E), where V is the number of airports and E is the number of flights in the network.
    * @param airport Source airport
    * @param x
    * @return Vector with the reachable cities
    */
    std::vector<CityRef> getReachableCitiesFromAirport(const AirportRef& airport, int x) const;

    /**
    * @brief Returns the cities reachable from a given airport in a maximum of x stops between flights (lay-overs).
    * Complexity: O(V+E), where V is the number of airports and E is the number of flights in the network.
    * @param airport Source airport
    * @param x
    * @return Vector with the reachable countries
    */
    std::vector<CountryRef> getReachableCountriesFromAirport(const AirportRef& airport, int x) const;

    /**
     * @brief Returns the pairs of source-destination airports with the longest trip, i.e. with the greatest number of
     *        flights between them, with the number of flights being stored in diameter
     * Complexity: O(V*(V+E)), where V is the number of airports and E is the number of flights.
     * @param diameter Variable to store the trip length (in flights)
     * @return Vector of pairs of source-destination airports with the longest trip
     */
    std::vector<std::pair<AirportRef, AirportRef>> getMaxTrips(int& diameter) const;

    /**
     * @brief Returns one of the best flight paths (in terms of number of stops) from one set of airports to the other,
     *        through the given available airports and flights of given available airlines.
     * To choose between equally valid flight path, this function chooses the one with the least travel distance.
     * However, it should not be considered the best flight path in terms of travel distance.
     * Complexity: O(M*(V+E+N*P)), where V is the total number of airports, E is the total number of flights, M is the
     * number of sources, N is the number of destinations and P is the number of airports in the final flight path.
     * @param srcs Set of source airports
     * @param dests Set of destination airports
     * @param availableAirports Set of available airports
     * @param availableAirlines Set of available airlines
     * @return The best flight path found
     */
    FlightPath getBestFlightPath(
        const std::vector<AirportRef> &srcs,
        const std::vector<AirportRef> &dests,
        const std::unordered_set<std::string> &availableAirports,
        const std::unordered_set<std::string> &availableAirlines
    ) const;
    std::vector<AirportRef> getClosestAirports(double latitude, double longitude) const;

  private:
    CountrySet countrySet_;
    CitySet citySet_;
    AirlineSet airlineSet_;
    Network network_;

    /**
     * @brief Returns the city with the given name and country, creating a new city (and possibly country) if it didn't
     *        already exist in the dataset.
     * Complexity: O(1)
     * @param name City's name
     * @param country Country's name
     * @return Reference to the wanted city
     */
    CityRef getOrInsertCity(const std::string& name, const std::string& country);

    /**
     * @brief Returns the country with the given name, creating a new country if it didn't already exist in the dataset.
     * Complexity: O(1)
     * @param name Country's name
     * @return Reference to the wanted country
     */
    CountryRef getOrInsertCountry(const std::string& name);

    /**
     * @brief Calculates the distance between two geographical positions, using the Haversine distance formula.
     * @param lat1 Latitude of the first position, in degrees
     * @param lon1 Longitude of the first position, in degrees
     * @param lat2 Latitude of the second position, in degrees
     * @param lon2 Longitude of the second position, in degrees
     * @return The distance between the two positions
     */
    static double calculateDistance(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Performs a breath-first search from a given airport, to determine which airport is the most distant from it.
     * Complexity: O(V + E), where V is the number of airports and E is the number of flights.
     * @param airport The source airport
     * @param diameter A variable to hold the distance (in flights) between the two airports
     * @return A pair with the source airport and the destination airport
     */
    std::pair<AirportRef, AirportRef> diameterBFS(const AirportRef& airport, int &diameter) const;
};


#endif //FEUP_AED2_DATASET_H
