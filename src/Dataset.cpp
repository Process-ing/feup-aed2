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

void AirportDFS(AirportRef start, vector<AirportRef>& reachable, int depth, int max);
vector<AirportRef> Dataset::getReachableAirportsfromAirport(AirportRef airport, int x) {
    vector<AirportRef> airports;
    for (const auto& v : network_.getVertexSet()) {
        v->setVisited(false);
    }
    AirportDFS(airport, airports, 0, x);
    return airports;
}

void AirportDFS(AirportRef start, vector<AirportRef>& reachable, int depth, int max) {
    start.lock()->setVisited(true);
    reachable.push_back(start);

    if (depth > max) {
        return;
    }

    for (const auto& adjacent : start.lock()->getAdj()) {
        auto dest = adjacent.getDest().lock();
        if (!dest->isVisited()) {
            AirportDFS(dest, reachable, depth + 1, max);
        }
    }
}

vector<CityRef> Dataset::getReachableCitiesfromAirport(AirportRef airport, int x) {
    CitySet cities;
    auto airports = getReachableAirportsfromAirport(airport, x);
    for (auto airport : airports) {
        cities.insert(airport.lock()->getInfo().getCity());
    }
    vector<CityRef> cities1(cities.begin(), cities.end());
    return cities1;
}

vector<CountryRef> Dataset::getReachableCountriesfromAirport(AirportRef airport, int x) {
    CountryRefSet countries;
    auto cities = getReachableCitiesfromAirport(airport, x);
    for (auto city : cities) {
        countries.insert(city.lock()->getCountry());
    }
    vector<CountryRef> countries1(countries.begin(), countries.end());
    return countries1;
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
