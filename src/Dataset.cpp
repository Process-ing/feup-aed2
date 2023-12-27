#include <fstream>
#include <limits>
#include <sstream>
#include <queue>
#include <cmath>
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
        double distance = calculateDistance(sourceAirport.getLatitude(), sourceAirport.getLongitude(),
                                            targetAirport.getLatitude(), targetAirport.getLongitude());
        FlightInfo flightInfo(airline, distance);
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

std::vector<AirportRef> Dataset::getBestFlightPath(const AirportRef& src, const AirportRef& dest, double &distance) const {
    for (AirportRef airport: network_.getVertexSet()) {
        airport.lock()->setVisited(false);
        airport.lock()->setParent(AirportRef());
    }
    queue<AirportRef> airportQueue;
    airportQueue.push(src);
    src.lock()->setVisited(true);
    while (!airportQueue.empty()) {
        AirportRef parent = airportQueue.front();
        airportQueue.pop();
        if (parent.lock()->getInfo().getCode() == dest.lock()->getInfo().getCode())
            break;

        for (const Flight& flight: parent.lock()->getAdj()) {
            AirportRef child = flight.getDest();
            if (!child.lock()->isVisited()) {
                airportQueue.push(child);
                child.lock()->setVisited(true);
                child.lock()->setParent(parent);
            }
        }
    }

    if (!dest.lock()->isVisited())
        return {};

    vector<AirportRef> airports;
    airports.push_back(dest);
    AirportRef curr = dest;
    distance = 0;
    while (curr.lock()->getInfo().getCode() != src.lock()->getInfo().getCode()) {
        AirportRef next = curr.lock()->getParent();
        distance += calculateDistance(
            curr.lock()->getInfo().getLatitude(),
            curr.lock()->getInfo().getLongitude(),
            next.lock()->getInfo().getLatitude(),
            next.lock()->getInfo().getLongitude()
        );
        curr = next;
        airports.push_back(curr);
    }
    reverse(airports.begin(), airports.end());
    return airports;
}

double hav(double x) {
    double sinVal = sin(x / 2);
    return sinVal * sinVal;
}

double Dataset::calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    static const double EARTH_DIAMETER = 12742.0;
    static const double DEG_TO_RAD_FACTOR = M_PI / 180.0;
    double latRad1 = lat1 * DEG_TO_RAD_FACTOR, lonRad1 = lon1 * DEG_TO_RAD_FACTOR,
            latRad2 = lat2 * DEG_TO_RAD_FACTOR, lonRad2 = lon2 * DEG_TO_RAD_FACTOR;

    return EARTH_DIAMETER * asin(hav(latRad2 - latRad1) + cos(latRad1) * cos(latRad2) * hav(lonRad2 - lonRad1));
}
