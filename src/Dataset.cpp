#include <fstream>
#include <limits>
#include <sstream>
#include "Dataset.h"

using namespace std;

Dataset::Dataset() = default;

void Dataset::readFiles() {
    readAirports();
    readAirlines();
    readFlights();
}

void Dataset::readAirports() {
    static const string AIRPORTS_FILEPATH = "dataset/airports.csv";

    ifstream airportsFile(AIRPORTS_FILEPATH);
    if (airportsFile.fail()) {
        ostringstream errorMsg;
        errorMsg << "Could not open file \"" << AIRPORTS_FILEPATH << '"';
        throw ios_base::failure(errorMsg.str());
    }

    string code, name, cityName, countryName, latitudeStr, longitudeStr;
    airportsFile.ignore(numeric_limits<streamsize>::max(), '\n');
    while (getline(airportsFile, code, ',')) {
        getline(airportsFile, name, ',');
        getline(airportsFile, cityName, ',');
        getline(airportsFile, countryName, ',');
        getline(airportsFile, latitudeStr, ',');
        getline(airportsFile, longitudeStr);

        CityRef city = getOrInsertCity(cityName, countryName);
        double latitude = stod(latitudeStr), longitude = stod(longitudeStr);
        AirportInfo info(code, name, city, latitude, longitude);
        network_.addVertex(info);
        city.lock()->addAirport(network_.findVertex(info));
    }
}

void Dataset::readAirlines(){
    static const string AIRLINES_FILEPATH = "dataset/airlines.csv";

    ifstream airlinesFile(AIRLINES_FILEPATH);
    if(airlinesFile.fail()){
        ostringstream errorMsg;
        errorMsg << "Could not open file \"" << AIRLINES_FILEPATH << '"';
        throw ios_base::failure(errorMsg.str());
    }
    string code, name, callsign, countryName;
    airlinesFile.ignore(numeric_limits<streamsize>::max(), '\n');
    while(getline(airlinesFile, code, ',')){
        getline(airlinesFile, name, ',');
        getline(airlinesFile, callsign, ',');
        getline(airlinesFile, countryName);

        CountryRef country = getOrInsertCountry(countryName);
        AirlineRef airline = country.lock()->addAirline(Airline(code, name, callsign, country));
        airlineSet_.insert(airline);
    }

}

void Dataset::readFlights() {
    static const string FLIGHTS_FILEPATH = "dataset/flights.csv";
    ifstream flightsFile(FLIGHTS_FILEPATH);
    if (flightsFile.fail()) {
        ostringstream errorMsg;
        errorMsg << "Could not open file \"" << FLIGHTS_FILEPATH << '"';
        throw ios_base::failure(errorMsg.str());
    }
    string source, target, airlineCode;
    flightsFile.ignore(numeric_limits<streamsize>::max(), '\n');
    while (getline(flightsFile, source, ',')) {
        getline(flightsFile, target, ',');
        getline(flightsFile, airlineCode);

        AirportInfo sourceAirport = getAirport(source).lock()->getInfo();
        AirportInfo targetAirport = getAirport(target).lock()->getInfo();
        AirlineRef airline = getAirline(airlineCode);
        FlightInfo flightInfo(airline, sourceAirport, targetAirport);
        network_.addEdge(sourceAirport, targetAirport, flightInfo);
    }
}

CityRef Dataset::getOrInsertCity(const std::string& name, const std::string& countryName) {
    auto city = citySet_.find(make_shared<City>(City(name, getOrInsertCountry(countryName))));
    if (city == citySet_.end()) {
        CountryRef country = getOrInsertCountry(countryName);
        city = citySet_.insert(country.lock()->addCity(City(name, getOrInsertCountry(countryName)))).first;
    }
    return *city;
}

CountryRef Dataset::getOrInsertCountry(const std::string& name) {
    auto country = countrySet_.find(make_shared<Country>(Country(name)));
    if (country == countrySet_.end())
        country = countrySet_.insert(make_shared<Country>(Country(name))).first;
    return *country;
}

CountryRef Dataset::getCountry(const std::string &name) const {
    auto country = countrySet_.find(make_shared<Country>(Country(name)));
    return country != countrySet_.end() ? *country : CountryRef();
}

CityRef Dataset::getCity(const std::string &name, const std::string &countryName) const {
    CountryRef country = getCountry(countryName);
    if (!country.lock())
        return {};
    auto city = citySet_.find(make_shared<City>(name, country));
    return city != citySet_.end() ? *city : CityRef();
}

AirportRef Dataset::getAirport(const string& code) const {
    return network_.findVertex(AirportInfo(code, "", CityRef(), 0, 0));;
}

AirlineRef Dataset::getAirline(const string& code) const {
    auto airline = airlineSet_.find(make_shared<Airline>(Airline(code, "", "", CountryRef())));
    return airline != airlineSet_.end() ? *airline : AirlineRef();
}

vector<AirlineRef> Dataset::getAirlinesFromCountry(const Country& country) {
    vector<AirlineRef> airlines;
    for (const auto& airline : country.getAirlines()) {
        airlines.push_back(airline);
    }
    return airlines;
}

vector<CityRef> Dataset::getCitiesFromCountry(const Country& country) {
    vector<CityRef> cities;
    for (const auto& city : country.getCities()) {
        cities.push_back(city);
    }
    return cities;
}

vector<AirportRef> Dataset::getAirportsFromCity(const City& city) {
    vector<AirportRef> airports;
    for (const auto& airport : city.getAirports()) {
        airports.push_back(airport);
    }
    return airports;
}

vector<CountryRef> Dataset::getCountriesAirportFliesTo(const Airport& airport) {
    CountryRefSet countries;
    for (const auto& flight : airport.getAdj()) {
        auto destination = flight.getDest();
        countries.insert(countries.end(), destination.lock()->getInfo().getCity().lock()->getCountry());
    }
    vector<CountryRef> countries1(countries.begin(), countries.end());
    return countries1;
}

vector<CountryRef> Dataset::getCountriesCityFliesTo(const City& city) {
    CountryRefSet countries;
    for (const auto& airport : city.getAirports()) {
        vector<CountryRef> moreCountries = getCountriesAirportFliesTo(*airport.lock());
        countries.insert(moreCountries.begin(), moreCountries.end());
    }
    vector<CountryRef> countries1(countries.begin(), countries.end());
    return countries1;
}

vector<Flight> Dataset::searchFlightsFromAirport(string airPortCode) {
    AirportRef airport = getAirport(airPortCode);
    vector<Flight> flights;
    if (airport.lock()) {
        for (const auto& flight : airport.lock()->getAdj()){
            flights.push_back(flight);
        }
    }
    return flights;
}

float Dataset::numberOfFlightsByCity() {
    int cities = getCities().size();
    int flights = 0;
    for(const auto& city : getCities()){
        for(const auto& airport : city.lock()->getAirports()){
            flights += airport.lock()->getAdj().size();
        }
    }
    return flights/cities;
}

float Dataset::numberOfFlightsByAirline() {
    int airlines = getAirlines().size();
    int flights = 0;
    for(const auto& airport : getAirports()){
        flights += airport->getAdj().size();
    }
    return flights/airlines;
}

vector<AirportInfo> Dataset::searchDestinationsFromAirport(string airPortCode) {
    AirportRef airport = getAirport(airPortCode);
    vector<AirportInfo> flights;
    if (airport.lock()) {
        for (const auto& flight : airport.lock()->getAdj()){
            const AirportInfo& targetAirport = flight.getDest().lock()->getInfo();
            flights.push_back(targetAirport);
        }
    }
    return flights;
}

vector<AirportRef> Dataset::searchTopNAirPortsWithGreatestTraffic(int n) {
    vector<AirportRef> airportTrafficList;
    vector<AirportRef> airportsList;
    sort(airportTrafficList.begin(), airportTrafficList.end(), [](const AirportRef& a, const AirportRef& b) {
        return a.lock()->getAdj().size() > b.lock()->getAdj().size();
    });
    for(int i = 0; i < n; i++){
        airportsList.push_back(airportTrafficList[i]);
    }
    return airportsList;
}

const AirlineSet& Dataset::getAirlines() const {
    return airlineSet_;
}

const Network &Dataset::getNetwork() const {
    return network_;
}

const CountrySet &Dataset::getCountries() const {
    return countrySet_;
}

const CitySet &Dataset::getCities() const {
    return citySet_;
}

const AirportSet &Dataset::getAirports() const {
    return network_.getVertexSet();
}
