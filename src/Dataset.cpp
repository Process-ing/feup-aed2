#include <fstream>
#include <limits>
#include <sstream>
#include <set>
#include <iostream>
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
    if (airlinesFile.fail()) {
        ostringstream errorMsg;
        errorMsg << "Could not open file \"" << AIRLINES_FILEPATH << '"';
        throw ios_base::failure(errorMsg.str());
    }
    string code, name, callsign, countryName;
    airlinesFile.ignore(numeric_limits<streamsize>::max(), '\n');
    while (getline(airlinesFile, code, ',')) {
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

vector<AirlineRef> Dataset::getAirlinesFromCountry(const CountryRef &country) {
    vector<AirlineRef> airlines;
    for (const auto& airline : country.lock()->getAirlines()) {
        airlines.push_back(airline);
    }
    return airlines;
}

vector<CityRef> Dataset::getCitiesFromCountry(const CountryRef &country) {
    vector<CityRef> cities;
    for (const auto& city : country.lock()->getCities()) {
        cities.push_back(city);
    }
    return cities;
}

vector<AirportRef> Dataset::getAirportsFromCountry(const CountryRef &country) {
    vector<AirportRef> airports;
    for (CityRef city: country.lock()->getCities()) {
        for (const AirportRef& airport : city.lock()->getAirports())
            airports.push_back(airport);
    }
    return airports;
}

vector<AirportRef> Dataset::getAirportsFromCity(const CityRef &city) {
    vector<AirportRef> airports;
    for (const auto& airport : city.lock()->getAirports()) {
        airports.push_back(airport);
    }
    return airports;
}

vector<CountryRef> Dataset::getCountriesCityFliesTo(const CityRef &city) const {
    CountryRefSet countries;
    for (const auto& airport : city.lock()->getAirports()) {
        vector<CountryRef> moreCountries = searchReachableCountriesFromAirport(airport);
        countries.insert(moreCountries.begin(), moreCountries.end());
    }
    return { countries.begin(), countries.end() };
}

vector<AirportRef> Dataset::getReachableAirportsFromAirport(const AirportRef& airport, int x) const {
    vector<AirportRef> airports;
    for (const auto& v : network_.getVertexSet()) {
        v->setVisited(false);
    }

    queue<AirportRef> airportQueue, newQueue;
    airportQueue.push(airport);
    airport.lock()->setVisited(true);
    for (int i = 0; i <= x; i++) {
        while (!airportQueue.empty()) {
            AirportRef src = airportQueue.front();
            airportQueue.pop();
            for (const Flight& flight: src.lock()->getAdj()) {
                AirportRef dest = flight.getDest();
                if (!dest.lock()->isVisited()) {
                    newQueue.push(dest);
                    dest.lock()->setVisited(true);
                    airports.push_back(dest);
                }
            }
        }
        airportQueue = newQueue;
        newQueue = queue<AirportRef>();
    }

    return airports;
}

vector<CityRef> Dataset::getReachableCitiesFromAirport(const AirportRef& airport, int x) const {
    CitySet cities;
    auto airports = getReachableAirportsFromAirport(airport, x);
    for (const auto& air : airports) {
        cities.insert(air.lock()->getInfo().getCity());
    }
    return { cities.begin(), cities.end() };
}

vector<CountryRef> Dataset::getReachableCountriesFromAirport(const AirportRef& airport, int x) const {
    CountryRefSet countries;
    auto cities = getReachableCitiesFromAirport(airport, x);
    for (const auto& city : cities) {
        countries.insert(city.lock()->getCountry());
    }
    vector<CountryRef> countries1(countries.begin(), countries.end());
    return countries1;
}

vector<Flight> Dataset::searchFlightsFromAirport(const AirportRef &airport) {
    return airport.lock()->getAdj();
}

float Dataset::numberOfFlightsByCity() const {
    auto cities = (float)getCities().size();
    float flights = 0;
    for (const auto& airport : getAirports()){
        flights += (float)airport->getAdj().size();
    }
    return flights / cities;
}

float Dataset::numberOfFlightsByAirline() const {
    auto airlines = (float)getAirlines().size();
    float flights = 0;
    for (const auto& airport : getAirports()){
        flights += (float)airport->getAdj().size();
    }
    return flights / airlines;
}

int Dataset::numberOfFlights() const{
    int flights = 0;
    for (const auto& airport : getAirports()){
        flights += airport->getAdj().size();
    }
    return flights;
}

vector<AirportRef> Dataset::searchReachableAirportsFromAirport(const AirportRef& airport) const {
    vector<AirportRef> airports;

    for (AirportRef other: getAirports())
        other.lock()->setVisited(false);


    for (const auto& flight : airport.lock()->getAdj()) {
        AirportRef dest = flight.getDest();
        if (!dest.lock()->isVisited()) {
            dest.lock()->setVisited(true);
            airports.push_back(dest);
        }
    }
    return airports;
}

vector<CityRef> Dataset::searchReachableCitiesFromAirport(const AirportRef& airport) const {
    CitySet cities;
    auto airports = searchReachableAirportsFromAirport(airport);
    for (const auto& air : airports) {
        cities.insert(air.lock()->getInfo().getCity());
    }
    vector<CityRef> cities1(cities.begin(), cities.end());
    return cities1;
}

vector<CountryRef> Dataset::searchReachableCountriesFromAirport(const AirportRef& airport) const {
    CountryRefSet countries;
    auto cities = searchReachableCitiesFromAirport(airport);
    for (const auto& city : cities) {
        countries.insert(city.lock()->getCountry());
    }
    vector<CountryRef> countries1(countries.begin(), countries.end());
    return countries1;
}

/**
 * @brief Auxiliary function to getessentialAirports, performing a depth-first search according to the Tarjan's
 *        algorithm for articulation points.
 * Complexity: O(E), where V is the total number of flights.
 * @param airports Result vector, to contain the essential airports
 * @param src The airport from which to execute the search
 * @param i Index
 * @param isRoot Whether src is the root or not
 */
void essentialAirportDfs(vector<AirportRef> &airports, const AirportRef &src, int &i, bool isRoot) {
    src.lock()->setNum(i);
    src.lock()->setLow(i);
    src.lock()->setVisited(true);
    src.lock()->setProcessing(true);
    i++;
    bool isEssential = false;
    int childCount = 0;

    for (const Flight& flight: src.lock()->getAdj()) {
        AirportRef dest = flight.getDest();
        if (!dest.lock()->isVisited()) {
            childCount++;
            essentialAirportDfs(airports, dest, i, false);
            src.lock()->setLow(min(src.lock()->getLow(), dest.lock()->getLow()));
            if (!isRoot && dest.lock()->getLow() >= src.lock()->getNum())
                isEssential = true;
        } else if (dest.lock()->isProcessing()) {
            src.lock()->setLow(min(src.lock()->getLow(), dest.lock()->getNum()));
        }
    }

    if (isRoot && childCount > 1)
        isEssential = true;
    if (isEssential)
        airports.push_back(src);

    src.lock()->setProcessing(false);
}

vector<AirportRef> Dataset::getessentialAirports() const{
    vector<AirportRef> airports;
    int i = 1;
    for (AirportRef airport: network_.getVertexSet()) {
        airport.lock()->setVisited(false);
        airport.lock()->setProcessing(false);
    }

    for (AirportRef airport: network_.getVertexSet()) {
        if (!airport.lock()->isVisited())
            essentialAirportDfs(airports, airport, i, true);
    }

    return airports;
}

vector<AirportRef> Dataset::searchTopNAirportsWithGreatestTraffic(int n) const {
    vector<AirportRef> airportsList;
    for (const auto& airport : network_.getVertexSet()) {
        airportsList.push_back(airport);
    }

    sort(airportsList.begin(), airportsList.end(), [](const AirportRef &a, const AirportRef &b) {
        return a.lock()->getAdj().size() + a.lock()->getIndegree() > b.lock()->getAdj().size() + b.lock()->getIndegree();
    });

    return { airportsList.begin(), airportsList.begin() + n };
}

pair<AirportRef, AirportRef> Dataset::diameterBFS(const AirportRef& airport, int &diameter) const {
    diameter = 0;
    for (const auto& v : network_.getVertexSet()) {
        v->setVisited(false);
        v->setDepth(0);
    }
    queue<AirportRef> q;
    AirportRef final;
    q.push(airport);
    airport.lock()->setDepth(0);
    airport.lock()->setVisited(true);
    while (!q.empty()) {
        AirportRef curr = q.front();
        q.pop();
        for (const auto& flight: curr.lock()->getAdj()) {
            auto dest = flight.getDest();
            if (!dest.lock()->isVisited()) {
                dest.lock()->setDepth(curr.lock()->getDepth() + 1);
                if (dest.lock()->getDepth() > diameter) {
                    diameter = dest.lock()->getDepth();
                    final = dest;
                }
                q.push(dest);
                dest.lock()->setVisited(true);
            }
        }
    }
    return {airport, final};
}

vector<pair<AirportRef, AirportRef>> Dataset::getMaxTrips(int &diameter) const {
    vector<pair<AirportRef, AirportRef>> pairs;
    int max = 0;

    for(const auto& airport : network_.getVertexSet()) {
        int current;
        pair<AirportRef, AirportRef> new_pair = diameterBFS(airport, current);
        if (current > max) {
            pairs.clear();
            pairs.push_back(new_pair);
            max = current;
        } else if (current == max) pairs.push_back(new_pair);
    }
    diameter = max;
    return pairs;
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

void dfs(const AirportRef& airport);
void dfs(const AirportRef& airport) {
    airport.lock()->setVisited(true);

    for (auto flight : airport.lock()->getAdj()) {
        auto neighbour = flight.getDest();
        if (!neighbour.lock()->isVisited()) {
            dfs(neighbour);
        }
    }
}

FlightPath Dataset::getBestFlightPath(const std::vector<AirportRef> &srcs, const std::vector<AirportRef> &dests,
                                      const std::unordered_set<std::string> &availableAirports, const std::unordered_set<std::string> &availableAirlines) const {
    int minFlights = numeric_limits<int>::max();
    double minDist = numeric_limits<double>::infinity();
    FlightPath res;

    for (const AirportRef &src: srcs) {
        if (availableAirports.find(src.lock()->getInfo().getCode()) == availableAirports.end())
            continue;

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

            for (const Flight& flight: parent.lock()->getAdj()) {
                if (availableAirlines.find(flight.getInfo().getAirline().lock()->getCode()) == availableAirlines.end())
                    continue;
                AirportRef child = flight.getDest();
                if (!child.lock()->isVisited() && availableAirports.find(child.lock()->getInfo().getCode()) != availableAirports.end()) {
                    airportQueue.push(child);
                    child.lock()->setVisited(true);
                    child.lock()->setParent(parent);
                }
            }
        }

        for (const AirportRef &dest: dests) {
            if (!dest.lock()->isVisited())
                return {};

            FlightPath path;
            double distance = 0.0;
            path.getAirports().push_back(dest);
            AirportRef curr = dest;
            while (curr.lock()->getInfo().getCode() != src.lock()->getInfo().getCode()) {
                AirportRef next = curr.lock()->getParent();
                distance += calculateDistance(
                        curr.lock()->getInfo().getLatitude(),
                        curr.lock()->getInfo().getLongitude(),
                        next.lock()->getInfo().getLatitude(),
                        next.lock()->getInfo().getLongitude()
                );
                curr = next;
                path.getAirports().push_back(curr);
            }
            if (path.getAirports().empty())
                continue;
            reverse(path.getAirports().begin(), path.getAirports().end());
            path.setDistance(distance);

            int flights = path.getFlights();
            if (flights < minFlights || (flights == minFlights && distance < minDist)) {
                res = path;
                minFlights = flights;
                minDist = distance;
            }
        }
    }

    return res;
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

vector<AirportRef> Dataset::getClosestAirports(double latitude, double longitude) const {
    double minDist = numeric_limits<double>::infinity();
    vector<AirportRef> airports;
    for (AirportRef airport: network_.getVertexSet()) {
        double dist = calculateDistance(
            latitude,
            longitude,
            airport.lock()->getInfo().getLatitude(),
            airport.lock()->getInfo().getLongitude()
        );
        if (dist < minDist) {
            minDist = dist;
            airports.clear();
            airports.push_back(airport);
        } else if (dist == minDist) {
            airports.push_back(airport);
        }
    }

    return airports;
}
