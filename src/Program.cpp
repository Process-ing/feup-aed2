#include <iostream>
#include <limits>
#include <iomanip>
#include <cmath>
#include "utils.h"
#include "Program.h"

using namespace std;

Program::Program() {
    dataset_.readFiles();
}

void Program::launch() const {
    displayMainMenu();
}

void Program::displayMainMenu() const {
    const static int NUM_OPTIONS = 4;
    enum Option {
        SEARCH = 1,
        STATISTICS = 2,
        BEST_FLIGHT = 3,
        EXIT = 4,
    };

    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Welcome to ────────────────────────────────────────────────────────────────┐\n"
                " │                                                                             │\n"
                " │   ███╗   ██╗ █████╗ ██╗   ██╗██╗ ██████╗ ██████╗  █████╗ ██████╗ ██╗  ██╗   │\n"
                " │   ████╗  ██║██╔══██╗██║   ██║██║██╔════╝ ██╔══██╗██╔══██╗██╔══██╗██║  ██║   │\n"
                " │   ██╔██╗ ██║███████║██║   ██║██║██║  ███╗██████╔╝███████║██████╔╝███████║   │\n"
                " │   ██║╚██╗██║██╔══██║╚██╗ ██╔╝██║██║   ██║██╔══██╗██╔══██║██╔═══╝ ██╔══██║   │\n"
                " │   ██║ ╚████║██║  ██║ ╚████╔╝ ██║╚██████╔╝██║  ██║██║  ██║██║     ██║  ██║   │\n"
                " │   ╚═╝  ╚═══╝╚═╝  ╚═╝  ╚═══╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝   │\n"
                " │                                                                             │\n"
                " │  Options:                                                                   │\n"
                " │    [1] Search                                                               │\n"
                " │    [2] Statistics                                                           │\n"
                " │    [3] Search best flight                                                   │\n"
                " │    [4] Exit                                                                 │\n"
                " │                                                                             │\n"
                " └─────────────────────────────────────────────────────────────────────────────┘\n"
                "\n";

        switch (receiveOption(NUM_OPTIONS)) {
            case BEST_FLIGHT:
                chooseBestFlight();
                break;
            case EXIT:
                leave();
                return;
            case SEARCH:
                searchMenu();
                break;
            case STATISTICS:
                statisticsMenu();
                break;
        }
    }
}

void Program::searchMenu() const {
    static const int NUM_OPTIONS = 14;
    enum Option {
        SEARCH_ALL_COUNTRIES = 1,
        SEARCH_ALL_AIRPORTS = 2,
        SEARCH_ALL_AIRLINES = 3,
        SEARCH_AIRLINES_BY_COUNTRY = 4,
        SEARCH_CITIES_IN_COUNTRY = 5,
        SEARCH_AIRPORTS_IN_CITY = 6,
        SEARCH_FLIGHTS_FROM_AIRPORT = 7,
        SEARCH_COUNTRIES_FLYING_TO_AIRPORT = 8,
        SEARCH_COUNTRIES_FLYING_TO_CITY = 9,
        SEARCH_DESTINATIONS_FROM_AIRPORT = 10,
        SEARCH_REACHABLE_DESTINATIONS_FROM_AIRPORT_IN_N_STOPS = 11,
        SEARCH_TOP_N_AIRPORTS_WITH_GREATEST_TRAFFIC = 12,
        SEARCH_AIRPORTS_ESSENTIAL_TO_NETWORK_CIRCULATION = 13,
        GO_BACK = 14
    };
    cout << "\n"
            " ┌─ Search ────────────────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Search all countries                                                 │\n"
            " │    [2] Search all airports                                                  │\n"
            " │    [3] Search all airlines                                                  │\n"
            " │    [4] Search airlines by country                                           │\n"
            " │    [5] Search cities in country                                             │\n"
            " │    [6] Search airports in city                                              │\n"
            " │    [7] Search flights from airport                                          │\n"
            " │    [8] Search countries flying to airport                                   │\n"
            " │    [9] Search countries flying to city                                      │\n"
            " │    [10] Search destinations from airport                                    │\n"
            " │    [11] Search reachable destinations from airport in n stops               │\n"
            " │    [12] Search top n airports with greatest traffic                         │\n"
            " │    [13] Search airports essential to network circulation                    │\n"
            " │    [14] Go Back                                                             │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
        switch(receiveOption(NUM_OPTIONS)){
            case SEARCH_ALL_COUNTRIES:
                displayAllCountries();
                break;
            case SEARCH_ALL_AIRPORTS:
                displayAllAirports();
                break;
            case SEARCH_ALL_AIRLINES:
                displayAllAirlines();
                break;
            case SEARCH_AIRLINES_BY_COUNTRY:
                displayAirlinesByCountry();
                break;
            case SEARCH_CITIES_IN_COUNTRY:
                displayCitiesByCountry();
                break;
            case SEARCH_AIRPORTS_IN_CITY:
                displayAirportsByCity();
                break;
            case SEARCH_FLIGHTS_FROM_AIRPORT:
                displayFlightsFromAirport();
                break;
            case SEARCH_COUNTRIES_FLYING_TO_AIRPORT:
                displayCountriesFlyingToAirport();
                break;
            case SEARCH_COUNTRIES_FLYING_TO_CITY:
                displayCountriesFlyingToCity();
                break;
            case SEARCH_DESTINATIONS_FROM_AIRPORT:
                destinationsFromAirportMenu();
                break;
            case SEARCH_REACHABLE_DESTINATIONS_FROM_AIRPORT_IN_N_STOPS:
                reachableDestinationsFromAirportMenu();
                break;
            case SEARCH_TOP_N_AIRPORTS_WITH_GREATEST_TRAFFIC:
                displayTopNAirportsWithGreatestTraffic();
                break;
            case SEARCH_AIRPORTS_ESSENTIAL_TO_NETWORK_CIRCULATION:
                displayAirportsEssentialToNetworkCirculation();
                break;
            case GO_BACK:
                return;
        }
}

void Program::statisticsMenu() const {
    static const int NUM_OPTIONS = 14;
    enum Option {
        NUMBER_OF_AIRPORTS = 1,
        NUMBER_OF_COUNTRIES = 2,
        NUMBER_OF_CITIES = 3,
        NUMBER_OF_AIRLINES = 4,
        NUMBER_OF_AVAILABLE_FLIGHTS = 5,
        NUMBER_OF_FLIGHTS_PER_CITY = 6,
        NUMBER_OF_FLIGHTS_PER_AIRLINE =7,
        NUMBER_OF_DIFFERENT_COUNTRIES_THAT_FLY_TO_AIRPORT = 8,
        NUMBER_OF_DIFFERENT_COUNTRIES_THAT_FLY_TO_CITY = 9,
        NUMBER_OF_DIFFERENT_DESTINATIONS_FROM_AIRPORT = 10,
        NUMBER_OF_REACHABLE_DESTINATIONS_IN_N_STOPS_FROM_AIRPORT = 11,
        MAXIMUM_TRIP = 12,
        NUMBER_OF_AIRPORTS_ESSENTIAL_TO_NETWORK_CIRCULATION = 13,
        GO_BACK = 14
    };
    cout << "\n"
            " ┌─ Statistics ────────────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Number of airports                                                   │\n"
            " │    [2] Number of countries                                                  │\n"
            " │    [3] Number of cities                                                     │\n"
            " │    [4] Number of airlines                                                   │\n"
            " │    [5] Number of available flights                                          │\n"
            " │    [6] Number of flights per city                                           │\n"
            " │    [7] Number of flights per airline                                        │\n"
            " │    [8] Number of different countries that fly to airport                    │\n"
            " │    [9] Number of different countries that fly to city                       │\n"
            " │    [10] Number of different destinations from airport                       │\n"
            " │    [11] Number of reachable destinations in n stops from airport            │\n"
            " │    [12] Maximum trip                                                        │\n"
            " │    [13] Number of airports essential to network circulation                 │\n"
            " │    [14] Go Back                                                             │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    switch(receiveOption(NUM_OPTIONS)){
        case NUMBER_OF_AIRPORTS:
            displayNumberOfAirports();
            break;
        case NUMBER_OF_COUNTRIES:
            displayNumberOfCountries();
            break;
        case NUMBER_OF_CITIES:
            displayNumberOfCities();
            break;
        case NUMBER_OF_AIRLINES:
            displayNumberOfAirlines();
            break;
        case NUMBER_OF_AVAILABLE_FLIGHTS:
            displayNumberOfAvailableFlights();
            break;
        case NUMBER_OF_FLIGHTS_PER_CITY:
            displayNumberOfFlightsPerCity();
            break;
        case NUMBER_OF_FLIGHTS_PER_AIRLINE:
            displayNumberOfFlightsPerAirline();
            break;
        case NUMBER_OF_DIFFERENT_COUNTRIES_THAT_FLY_TO_AIRPORT:
            displayNumberOfDifferentCountriesThatFlyToAirport();
            break;
        case NUMBER_OF_DIFFERENT_COUNTRIES_THAT_FLY_TO_CITY:
            displayNumberOfDifferentCountriesThatFlyToCity();
            break;
        case NUMBER_OF_DIFFERENT_DESTINATIONS_FROM_AIRPORT:
            displayNumberOfDifferentDestinationsFromAirport();
            break;
        case NUMBER_OF_REACHABLE_DESTINATIONS_IN_N_STOPS_FROM_AIRPORT:
            displayNumberOfReachableDestinationsInNStopsFromAirport();
            break;
        case MAXIMUM_TRIP:
            displayMaximumTrip();
            break;
        case NUMBER_OF_AIRPORTS_ESSENTIAL_TO_NETWORK_CIRCULATION:
            displayNumberOfAirportsEssentialToNetworkCirculation();
            break;
        case GO_BACK:
            return;
    }
}

void Program::destinationsFromAirportMenu() const {
    static const int NUM_OPTIONS = 3;
    enum Option{
        AIRPORT = 1,
        COUNTRY = 2,
        CITY = 3
    };
    cout << "\n"
            " ┌─ Destination Type ──────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Airport                                                              │\n"
            " │    [2] Country                                                              │\n"
            " │    [3] City                                                                 │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    switch(receiveOption(NUM_OPTIONS)) {
        case AIRPORT:
            displayDestinationsFromAirport();
            break;
        case COUNTRY:
            displayCountriesFromAirport();
            break;
        case CITY:
            displayCitiesFromAirport();
            break;
    }
}

void Program::reachableDestinationsFromAirportMenu() const {
    static const int NUM_OPTIONS = 3;
    enum Option{
        AIRPORT = 1,
        COUNTRY = 2,
        CITY = 3
    };
    cout << "\n"
            " ┌─ Destination Type ──────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Airport                                                              │\n"
            " │    [2] Country                                                              │\n"
            " │    [3] City                                                                 │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    switch(receiveOption(NUM_OPTIONS)) {
        case AIRPORT:
            displayReachableAirportsFromAirportInNStops();
            break;
        case COUNTRY:
            displayReachableCountriesFromAirportInNStops();
            break;
        case CITY:
            displayReachableCitiesFromAirportInNStops();
            break;
    }
}

vector<AirportRef> Program::sortAirportsMenu(vector<AirportRef> airports) {
    static const int NUM_OPTIONS = 3;
    enum Option {
        SORT_BY_AIRPORT_NAME = 1,
        SORT_BY_AIRPORT_CODE = 2,
        SORT_BY_AIRPORT_CITY = 3,
        SORT_BY_AIRPORT_COUNTRY = 4
    };
    cout << "\n"
            " ┌─ Sort airports by ──────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Airport name                                                         │\n"
            " │    [2] Airport code                                                         │\n"
            " │    [3] Airport city                                                         │\n"
            " │    [4] Airport country                                                      │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    switch(receiveOption(NUM_OPTIONS)) {
        case SORT_BY_AIRPORT_NAME:
             return sortAirportsByName(airports);
        case SORT_BY_AIRPORT_CODE:
             return sortAirportsByCode(airports);
        case SORT_BY_AIRPORT_CITY:
             return sortAirportsByCity(airports);
        case SORT_BY_AIRPORT_COUNTRY:
             return sortAirportsByCountry(airports);
    }
}

vector<AirportRef> Program::sortAirportsCityMenu(vector<AirportRef> airports) {
    static const int NUM_OPTIONS = 3;
    enum Option {
        SORT_BY_AIRPORT_NAME = 1,
        SORT_BY_AIRPORT_CODE = 2
    };
    cout << "\n"
            " ┌─ Sort airports by ──────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Airport name                                                         │\n"
            " │    [2] Airport code                                                         │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    switch(receiveOption(NUM_OPTIONS)) {
        case SORT_BY_AIRPORT_NAME:
            return sortAirportsByName(airports);
        case SORT_BY_AIRPORT_CODE:
            return sortAirportsByCode(airports);
    }
}

vector<CountryRef> Program::sortCountries(vector<CountryRef> countries) const {
    sort(countries.begin(), countries.end(), [](const CountryRef& a, const CountryRef& b) {
        return a.lock()->getName() < b.lock()->getName();
    });
    return countries;
}

vector<CityRef> Program::sortCities(vector<CityRef> cities) const {
    sort(cities.begin(), cities.end(), [](const CityRef& a, const CityRef& b) {
        return a.lock()->getName() < b.lock()->getName();
    });
    return cities;
}

vector<AirlineRef> Program::sortAirlinesMenu(vector<AirlineRef> airlines) const {
    static const int NUM_OPTIONS = 4;
    enum Option {
        SORT_BY_AIRLINE_NAME = 1,
        SORT_BY_AIRLINE_CODE = 2,
        SORT_BY_AIRLINE_COUNTRY = 3,
        SORT_BY_AIRLINE_CALLSIGN = 4
    };
    cout << "\n"
            " ┌─ Sort airlines by ──────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Airline name                                                         │\n"
            " │    [2] Airline code                                                         │\n"
            " │    [3] Airline country                                                      │\n"
            " │    [4] Airline callsign                                                     │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    switch(receiveOption(NUM_OPTIONS)){
        case SORT_BY_AIRLINE_NAME:
            return sortAirlinesByName(airlines);
        case SORT_BY_AIRLINE_CODE:
            return sortAirlinesByCode(airlines);
        case SORT_BY_AIRLINE_COUNTRY:
            return sortAirlinesByCountry(airlines);
        case SORT_BY_AIRLINE_CALLSIGN:
            return sortAirlinesByCallsign(airlines);
    }
}

vector<AirlineRef> Program::sortAirlinesCountryMenu(vector<AirlineRef> airlines) const {
    static const int NUM_OPTIONS = 4;
    enum Option {
        SORT_BY_AIRLINE_NAME = 1,
        SORT_BY_AIRLINE_CODE = 2,
        SORT_BY_AIRLINE_CALLSIGN = 3
    };
    cout << "\n"
            " ┌─ Sort airlines by ──────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Airline name                                                         │\n"
            " │    [2] Airline code                                                         │\n"
            " │    [3] Airline callsign                                                     │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    switch(receiveOption(NUM_OPTIONS)){
        case SORT_BY_AIRLINE_NAME:
            return sortAirlinesByName(airlines);
        case SORT_BY_AIRLINE_CODE:
            return sortAirlinesByCode(airlines);
        case SORT_BY_AIRLINE_CALLSIGN:
            return sortAirlinesByCallsign(airlines);
    }
}


void Program::chooseBestFlight() const {
    clearScreen();
    cout << "\n"
            " ┌─ Choose source ─────────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Airport code                                                         │\n"
            " │    [2] Airport name                                                         │\n"
            " │    [3] City                                                                 │\n"
            " │    [4] Country                                                              │\n"
            " │    [5] Geographical position                                                │\n"
            " │    [6] Go back                                                              │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    vector<AirportRef> srcs = chooseAirportsForBestFlight();
    if (srcs.empty())
        return;

    clearScreen();
    cout << "\n"
            " ┌─ Choose destination ────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Airport code                                                         │\n"
            " │    [2] Airport name                                                         │\n"
            " │    [3] City                                                                 │\n"
            " │    [4] Country                                                              │\n"
            " │    [5] Geographical position                                                │\n"
            " │    [6] Go back                                                              │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    vector<AirportRef> dests = chooseAirportsForBestFlight();
    if (dests.empty())
        return;

    unordered_set<string> availableAirports = chooseAirportFilter();
    unordered_set<string> availableAirlines = chooseAirlineFilter();

    FlightPath path = dataset_.getBestFlightPath(srcs, dests, availableAirports, availableAirlines);
    displayBestFlight(path);
}

unordered_set<string> Program::receiveStrings() {
    unordered_set<string> strings;
    string line, str;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, line);
    istringstream lineStream(line);
    while (getline(lineStream, str, ',')) {
        strings.insert(str);
    }
    return strings;
}

unordered_set<std::string> Program::chooseAirportFilter() const {
    const static int NUM_OPTIONS = 7;
    enum Option {
        BLACKLIST_AIRPORTS = 1,
        WHITELIST_AIRPORTS = 2,
        BLACKLIST_CITIES = 3,
        WHITELIST_CITIES = 4,
        BLACKLIST_COUNTRIES = 5,
        WHITELIST_COUNTRIES = 6,
        CONTINUE = 7,
    };
    unordered_set<string> availableAirports;

    clearScreen();
    cout << "\n"
            " ┌─ Filter airports ───────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Blacklist airports                                                   │\n"
            " │    [2] Whitelist airports                                                   │\n"
            " │    [3] Blacklist cities                                                     │\n"
            " │    [4] Whitelist cities                                                     │\n"
            " │    [5] Blacklist countries                                                  │\n"
            " │    [6] Whitelist countries                                                  │\n"
            " │    [7] Continue                                                             │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";

    unordered_set<string> strings;
    switch (receiveOption(NUM_OPTIONS)) {
        case BLACKLIST_AIRPORTS:
            for (AirportRef airport: dataset_.getAirports())
                availableAirports.insert(airport.lock()->getInfo().getCode());
            cout << "Please insert the codes of the airports you want to blacklist, seperated by comma and without spaces: ";
            for (const string &str: receiveStrings())
                availableAirports.erase(str);
            break;
        case WHITELIST_AIRPORTS:
            cout << "Please insert the codes of the airports you want to whitelist, seperated by comma and without spaces: ";
            for (const string &str: receiveStrings())
                availableAirports.insert(str);
            break;
        case BLACKLIST_CITIES:
            cout << "Please insert the names of the cities you want to blacklist, seperated by comma and without spaces: ";
            strings = receiveStrings();
            for (const CityRef &city: dataset_.getCities()) {
                if (strings.find(city.lock()->getName()) == strings.end()) {
                    for (const AirportRef &airport: city.lock()->getAirports())
                        availableAirports.insert(airport.lock()->getInfo().getCode());
                }
            }
            break;
        case WHITELIST_CITIES:
            cout << "Please insert the names of the cities you want to whitelist, seperated by comma and without spaces: ";
            strings = receiveStrings();
            for (const CityRef &city: dataset_.getCities()) {
                if (strings.find(city.lock()->getName()) != strings.end()) {
                    for (const AirportRef &airport: city.lock()->getAirports())
                        availableAirports.insert(airport.lock()->getInfo().getCode());
                }
            }
            break;
        case BLACKLIST_COUNTRIES:
            cout << "Please insert the names of the countries you want to blacklist, seperated by comma and without spaces: ";
            strings = receiveStrings();
            for (CountryRef country: dataset_.getCountries()) {
                if (strings.find(country.lock()->getName()) == strings.end()) {
                    for (const AirportRef& airport: dataset_.getAirportsFromCountry(country))
                        availableAirports.insert(airport.lock()->getInfo().getCode());
                }
            }
            break;
        case WHITELIST_COUNTRIES:
            cout << "Please insert the names of the countries you want to whitelist, seperated by comma and without spaces: ";
            strings = receiveStrings();
            for (CountryRef country: dataset_.getCountries()) {
                if (strings.find(country.lock()->getName()) != strings.end()) {
                    for (const AirportRef& airport: dataset_.getAirportsFromCountry(country))
                        availableAirports.insert(airport.lock()->getInfo().getCode());
                }
            }
            break;
        case CONTINUE:
            for (AirportRef airport: dataset_.getAirports())
                availableAirports.insert(airport.lock()->getInfo().getCode());
            break;
    }

    return availableAirports;
}

unordered_set<std::string> Program::chooseAirlineFilter() const {
    const static int NUM_OPTIONS = 3;
    enum Option {
        BLACKLIST_AIRLINES = 1,
        WHITELIST_AIRLINES = 2,
        CONTINUE = 3
    };
    unordered_set<string> availableAirlines;

    clearScreen();
    cout << "\n"
            " ┌─ Filter airlines ───────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Blacklist airlines                                                   │\n"
            " │    [2] Whitelist airlines                                                   │\n"
            " │    [3] Continue                                                             │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";

    switch (receiveOption(NUM_OPTIONS)) {
        case BLACKLIST_AIRLINES:
            for (const AirlineRef &airline: dataset_.getAirlines())
                availableAirlines.insert(airline.lock()->getCode());
            cout << "Please insert the codes of the airlines you want to blacklist, seperated by comma and without spaces: ";
            for (const string &str: receiveStrings())
                availableAirlines.erase(str);
            break;
        case WHITELIST_AIRLINES:
            cout << "Please insert the codes of the airlines you want to whitelist, seperated by comma and without spaces: ";
            for (const string &str: receiveStrings())
                availableAirlines.insert(str);
            break;
        case CONTINUE:
            for (const AirlineRef &airline: dataset_.getAirlines())
                availableAirlines.insert(airline.lock()->getCode());
            break;
    }

    return availableAirlines;
}

vector<AirportRef> Program::chooseAirportsForBestFlight() const {
    const static int NUM_OPTIONS = 6;
    enum Option {
        AIRPORT_CODE = 1,
        AIRPORT_NAME = 2,
        CITY = 3,
        COUNTRY = 4,
        COORDINATES = 5,
        GO_BACK = 6,
    };

    vector<AirportRef> airports;
    CityRef city;
    CountryRef country;
    double lat, lon;
    switch (receiveOption(NUM_OPTIONS)) {
        case AIRPORT_CODE:
            airports = { receiveAirportByCode() };
            if (airports[0].expired())
                return {};
            break;
        case AIRPORT_NAME:
            airports = { receiveAirportByName() };
            if (airports[0].expired())
                return {};
            break;
        case CITY:
            city = receiveCity();
            if (city.expired())
                return {};
            airports = dataset_.getAirportsFromCity(city);
            break;
        case COUNTRY:
            country = receiveCountry();
            if (country.expired())
                return {};
            airports = dataset_.getAirportsFromCountry(country);
            break;
        case COORDINATES:
            cout << "Please input the latitude: ";
            while (!(cin >> lat) || lat < -90 || lat > 90) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid value. Please input a valid latitude: ";
            }
            cout << "Please input the longitude: ";
            while (!(cin >> lon) || lon < -180 || lon > 180) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid value. Please input a valid longitude: ";
            }
            airports = dataset_.getClosestAirports(lat, lon);
            break;
        case GO_BACK:
            return {};
    }

    return airports;
}

string getAirportInfoString(const Airport& airport) {
    return "Code: " + airport.getInfo().getCode() + ", Name: " + airport.getInfo().getName();
}

void Program::displayBestFlight(const FlightPath &path) {
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };

    if (path.getAirports().empty()) {
        cout << "No flight paths were found. ";
        waitForEnter();
        return;
    }

    clearScreen();
    cout << "\n"
            " ┌─ Best flight path ──────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Total flights: " << left << setw(60) << path.getFlights() << "│\n"
            " │  Total travel distance: " << setw(52) << to_string(path.getDistance()) + " Km" << "│\n"
            " │                                                                             │\n"
            " │  Travel airports:                                                           │\n";

    for (int i = 0; i < path.getAirports().size(); i++) {
        const AirportRef &airport = path.getAirports()[i];
        cout << " │      " << left << setw(71)
             << to_string(i + 1) + ". " + getAirportInfoString(*airport.lock()) << "│\n";
    }
    cout << " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    waitForEnter();
}

void Program::clearScreen() {
    system("clear || cls");
}

int Program::receiveOption(int max) {
    int option;
    cout << "Please choose an option: ";
    while (!(cin >> option) || option <= 0 || option > max) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid option. Please choose another option: ";
    }
    return option;
}

void Program::waitForEnter() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Press ENTER to continue...";
    getchar();
}

void Program::leave() {
    cout << "Exiting the app. ";
    waitForEnter();
}

void Program::displayAllCountries() const {
    displayCountries(vector<CountryRef>(dataset_.getCountries().begin(), dataset_.getCountries().end()));
}

void Program::displayAllAirports() const {
    displayAirports(sortAirportsMenu(vector<AirportRef>(dataset_.getAirports().begin(), dataset_.getAirports().end())));
}

void Program::displayAllAirlines() const {
    displayAirlines(sortAirlinesMenu(vector<AirlineRef>(dataset_.getAirlines().begin(), dataset_.getAirlines().end())));
}

void Program::displayAirlinesByCountry() const {
    CountryRef country = receiveCountry();
    if (country.expired())
        return;
    vector<AirlineRef> airlines = dataset_.getAirlinesFromCountry(country);
    airlines = sortAirlinesCountryMenu(airlines);
    displayAirlines(airlines);
}

void Program::displayCitiesByCountry() const {
    CountryRef country = receiveCountry();
    if (country.expired())
        return;
    vector<CityRef> cities = dataset_.getCitiesFromCountry(country);
    displayCities(cities);
}

void Program::displayAirportsByCity() const {
    CityRef city = receiveCity();
    if (city.expired())
        return;
    vector<AirportRef> airports = city.lock()->getAirports();
    airports = sortAirportsCityMenu(airports);
    displayAirports(airports);
}

void Program::displayFlightsFromAirport() const {
    AirportRef airport = receiveAirportByCode();
    if (airport.expired())
        return;
    vector<Flight> flights = dataset_.searchFlightsFromAirport(airport);
    displayFlights(flights);
}

void Program::displayCountriesFlyingToAirport() const {
    AirportRef airport = receiveAirportByCode();
    if (airport.expired())
        return;
    vector<CountryRef> countries = dataset_.getCountriesAirportFliesTo(airport);
    displayCountries(countries);
}

void Program::displayCountriesFlyingToCity() const {
    CityRef city = receiveCity();
    if (city.expired())
        return;
    vector<CountryRef> countries = dataset_.getCountriesCityFliesTo(city);
    displayCountries(countries);
}

void Program::displayDestinationsFromAirport() const {
    AirportRef airport = receiveAirportByCode();
    if (airport.expired())
        return;
    vector<AirportRef> airports = dataset_.searchReachableAirportsFromAirport(airport);
    airports = sortAirportsMenu(airports);
    displayAirports(airports);
}

void Program::displayCountriesFromAirport() const {
    AirportRef airport = receiveAirportByCode();
    if (airport.expired())
        return;
    vector<CountryRef> countries = dataset_.searchReachableCountriesFromAirport(airport);
    countries = sortCountries(countries);
    displayCountries(countries);
}

void Program::displayCitiesFromAirport() const {
    AirportRef airport = receiveAirportByCode();
    if (airport.expired())
        return;
    vector<CityRef> cities = dataset_.searchReachableCitiesFromAirport(airport);
    cities = sortCities(cities);
    displayCities(cities);
}

void Program::displayReachableAirportsFromAirportInNStops() const {
    AirportRef airport = receiveAirportByCode();
    if(airport.expired())
        return;
    int n_stops;
    cout << "Please enter the number of stops: ";
    while (!(cin >> n_stops) || n_stops < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number of stops. Please enter another number: ";
    }
    vector<AirportRef> airports = dataset_.getReachableAirportsFromAirport(airport, n_stops);
    airports = sortAirportsMenu(airports);
    displayAirports(airports);
}

void Program::displayReachableCountriesFromAirportInNStops() const {
    AirportRef airport = receiveAirportByCode();
    if(airport.expired())
        return;
    int n_stops;
    cout << "Please enter the number of stops: ";
    while (!(cin >> n_stops) || n_stops < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number of stops. Please enter another number: ";
    }
    vector<CountryRef> countries = dataset_.getReachableCountriesFromAirport(airport, n_stops);
    countries = sortCountries(countries);
    displayCountries(countries);
}

void Program::displayReachableCitiesFromAirportInNStops() const {
    AirportRef airport = receiveAirportByCode();
    if(airport.expired())
        return;
    int n_stops;
    cout << "Please enter the number of stops: ";
    while (!(cin >> n_stops) || n_stops < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number of stops. Please enter another number: ";
    }
    vector<CityRef> cities = dataset_.getReachableCitiesFromAirport(airport, n_stops);
    cities = sortCities(cities);
    displayCities(cities);
}

void Program::displayTopNAirportsWithGreatestTraffic() const {
    int n;
    cout << "Please enter the number of airports: ";
    while (!(cin >> n) || n < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number of airports. Please enter another number: ";
    }
    vector<AirportRef> airports = dataset_.searchTopNAirportsWithGreatestTraffic(n);
    displayAirports(airports);
}

void Program::displayAirportsEssentialToNetworkCirculation() const {

}

CountryRef Program::receiveCountry() const {
    string name;
    cout << "Please enter the country's name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    CountryRef country = dataset_.getCountry(name);
    if (country.expired()) {
        cout << "The country could not be found. ";
        waitForEnter();
    }
    return country;
}

CityRef Program::receiveCity() const {
    string name;
    CountryRef country = receiveCountry();
    if (country.expired())
        return {};
    cout << "Please enter the city's name: ";
    getline(cin, name);
    CityRef city = dataset_.getCity(name, country.lock()->getName());
    if (city.expired()) {
        cout << "The city could not be found. ";
        waitForEnter();
    }
    return city;
}

AirlineRef Program::receiveAirlineByCode() const {
    string code;
    cout << "Please enter the airline's code: ";
    cin >> code;
    AirlineRef airline = dataset_.getAirline(code);
    if (airline.expired()) {
        cout << "The airline could not be found. ";
        waitForEnter();
    }
    return airline;
}

AirlineRef Program::receiveAirlineByName() const {
    string name;
    cout << "Please enter the airline's name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    for (const AirlineRef &airline: dataset_.getAirlines()) {
        if (airline.lock()->getName() == name)
            return airline;
    }
    cout << "The airline could not be found. ";
    waitForEnter();
    return {};
}

AirportRef Program::receiveAirportByCode() const {
    string code;
    cout << "Please enter the airport's code: ";
    cin >> code;
    AirportRef airport = dataset_.getAirport(code);
    if (airport.expired()) {
        cout << "The airport could not be found. ";
        waitForEnter();
    }
    return airport;
}

AirportRef Program::receiveAirportByName() const {
    string name;
    cout << "Please enter the airport's name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    for (AirportRef airport: dataset_.getAirports()) {
        if (airport.lock()->getInfo().getName() == name)
            return airport;
    }
    cout << "The airline could not be found. ";
    waitForEnter();
    return {};
}

void Program::displayCountries(const vector<CountryRef> &countries) const {
    static const int RESULTS_PER_PAGE = 10;
    auto countries1 = sortCountries(countries);
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) countries1.size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                       │\n";

        for (int i = (page - 1) * RESULTS_PER_PAGE; i < min(page * RESULTS_PER_PAGE, (int)countries1.size()); i++)
            cout << " │  " << left << setw(85) << countries1[i].lock()->getName() << "│\n";


        cout << " │                                                                                       │\n"
                " │  Page " << setw(80) << to_string(page) + " of " + to_string(total_pages) << "│\n";
        if (page < total_pages)
            cout << " │     [1] Next page                                                                     │\n";

        if (page > 1)
            cout << " │     [2] Previous page                                                                 │\n";

        cout << " │     [3] Go back                                                                       │\n"
                " │                                                                                       │\n"
                " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";


        int option;
        cout << "Please choose an option: ";
        bool valid_option = false;
        while (true) {
            if (!(cin >> option)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid option. Please choose another option: ";
                continue;
            }

            switch (option) {
                case NEXT_PAGE:
                    if (page < total_pages) {
                        page++;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case PREVIOUS_PAGE:
                    if (page > 1) {
                        page--;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case GO_BACK:
                    return;
            }
            if (valid_option)
                break;
            cout << "Invalid option. Please choose another option: ";
        }
    }
}

void Program::displayCities(const vector<CityRef> &cities) const {
    static const int RESULTS_PER_PAGE = 10;
    auto cities1 = sortCities(cities);
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) cities1.size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                       │\n";

        for (int i = (page - 1) * RESULTS_PER_PAGE; i < min(page * RESULTS_PER_PAGE, (int)cities1.size()); i++) {
                cout << " │  " << left << setw(85) << "Name :" + cities1[i].lock()->getName() << "│\n";
        }
        cout << " │                                                                                       │\n"
                " │  Page " << setw(80) << to_string(page) + " of " + to_string(total_pages) << "│\n";
        if (page < total_pages)
            cout << " │     [1] Next page                                                                     │\n";

        if (page > 1)
            cout << " │     [2] Previous page                                                                 │\n";

        cout << " │     [3] Go back                                                                       │\n"
                " │                                                                                       │\n"
                " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";


        int option;
        cout << "Please choose an option: ";
        bool valid_option = false;
        while (true) {
            if (!(cin >> option)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid option. Please choose another option: ";
                continue;
            }

            switch (option) {
                case NEXT_PAGE:
                    if (page < total_pages) {
                        page++;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case PREVIOUS_PAGE:
                    if (page > 1) {
                        page--;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case GO_BACK:
                    return;
            }
            if (valid_option)
                break;
            cout << "Invalid option. Please choose another option: ";
        }
    }
}

void Program::displayAirlines(const vector<AirlineRef> &airlines) const {
    static const int RESULTS_PER_PAGE = 10;
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) airlines.size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                                                                                      │\n";

        for (int i = (page - 1) * RESULTS_PER_PAGE; i < min(page * RESULTS_PER_PAGE, (int) airlines.size()); i++) {
            const Airline &airline = *airlines[i].lock();
            cout << " │  " << left << setw(49) << "Name: " + airline.getName()
                 << setw(12) << " Code: " + airline.getCode()
                 << setw(40) << " Callsign: " + airline.getCallsign()
                 << setw(47) << " Country: " + airline.getCountry().lock()->getName()<< "│\n";
        }

        cout << " │                                                                                                                                                      │\n"
                " │  Page " << setw(143) << to_string(page) + " of " + to_string(total_pages) << "│\n";
        if (page < total_pages)
            cout << " │     [1] Next page                                                                                                                                    │\n";

        if (page > 1)
            cout << " │     [2] Previous page                                                                                                                                │\n";

        cout << " │     [3] Go back                                                                                                                                      │\n"
                " │                                                                                                                                                      │\n"
                " └──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n\n";


        int option;
        cout << "Please choose an option: ";
        bool valid_option = false;
        while (true) {
            if (!(cin >> option)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid option. Please choose another option: ";
                continue;
            }

            switch (option) {
                case NEXT_PAGE:
                    if (page < total_pages) {
                        page++;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case PREVIOUS_PAGE:
                    if (page > 1) {
                        page--;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case GO_BACK:
                    return;
            }
            if (valid_option)
                break;
            cout << "Invalid option. Please choose another option: ";
        }
    }
}

void Program::displayAirports(const vector<AirportRef> &airports) const {
    static const int RESULTS_PER_PAGE = 10;
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) airports.size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                       │\n";

        for (int i = (page - 1) * RESULTS_PER_PAGE; i < min(page * RESULTS_PER_PAGE, (int) airports.size()); i++) {
            const Airport &airport = *airports[i].lock();
            cout << " │  " << left << setw(60) << "Name: " + airport.getInfo().getName()
                 << setw(25) << " Code: " + airport.getInfo().getCode() << "│\n";
        }

        cout << " │                                                                                       │\n"
                " │  Page " << setw(80) << to_string(page) + " of " + to_string(total_pages) << "│\n";
        if (page < total_pages)
            cout << " │     [1] Next page                                                                     │\n";

        if (page > 1)
            cout << " │     [2] Previous page                                                                 │\n";

        cout << " │     [3] Go back                                                                       │\n"
                " │                                                                                       │\n"
                " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";


        int option;
        cout << "Please choose an option: ";
        bool valid_option = false;
        while (true) {
            if (!(cin >> option)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid option. Please choose another option: ";
                continue;
            }

            switch (option) {
                case NEXT_PAGE:
                    if (page < total_pages) {
                        page++;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case PREVIOUS_PAGE:
                    if (page > 1) {
                        page--;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case GO_BACK:
                    return;
            }
            if (valid_option)
                break;
            cout << "Invalid option. Please choose another option: ";
        }
    }
}

void Program::displayFlights(const std::vector<Flight> &flights) const {
    static const int RESULTS_PER_PAGE = 10;
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) flights.size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                                                               │\n";

        for (int i = (page - 1) * RESULTS_PER_PAGE; i < min(page * RESULTS_PER_PAGE, (int) flights.size()); i++) {
            const Flight &flight = flights[i];
            cout << " │  " << left << setw(55) << "Destination: " + flight.getDest().lock()->getInfo().getName()
                 << setw(15) << " Code: " + flight.getDest().lock()->getInfo().getCode()
                 << setw(55) << " Airline: " + flight.getInfo().getAirline().lock()->getName() << "│\n";
        }

        cout << " │                                                                                                                               │\n"
                " │  Page " << setw(120) << to_string(page) + " of " + to_string(total_pages) << "│\n";
        if (page < total_pages)
            cout << " │     [1] Next page                                                                                                             │\n";

        if (page > 1)
            cout << " │     [2] Previous page                                                                                                         │\n";

        cout << " │     [3] Go back                                                                                                               │\n"
                " │                                                                                                                               │\n"
                " └───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n\n";
        int option;
        cout << "Please choose an option: ";
        bool valid_option = false;
        while (true) {
            if (!(cin >> option)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid option. Please choose another option: ";
                continue;
            }

            switch (option) {
                case NEXT_PAGE:
                    if (page < total_pages) {
                        page++;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case PREVIOUS_PAGE:
                    if (page > 1) {
                        page--;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case GO_BACK:
                    return;
            }
            if (valid_option)
                break;
            cout << "Invalid option. Please choose another option: ";
        }
    }
}

void Program::displayNumberOfAirports() const {
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n"
            " │  Number of airports: " + to_string(dataset_.getAirports().size()) << setw(65)<< "│\n"
            " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Program::displayNumberOfCountries() const {
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n";
    cout << " │  Number of countries: " + to_string(dataset_.getCountries().size()) << setw(65) << "│\n";
    cout << " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Program::displayNumberOfCities() const {
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n";
    cout << " │  Number of cities: " + to_string(dataset_.getCities().size()) << setw(67) << "│\n";
    cout << " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Program::displayNumberOfAirlines() const {
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n";
    cout << " │  Number of airlines: " + to_string(dataset_.getAirlines().size()) << setw(66) << "│\n";
    cout << " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}


void Program::displayNumberOfAvailableFlights() const {
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n";
    cout << " │  Number of available flights: " + to_string(dataset_.numberOfFlights()) << setw(55) << "│\n";
    cout << " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Program::displayNumberOfFlightsPerCity() const {
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n";
    cout << " │  Number of flights per city: " + to_string(dataset_.numberOfFlightsByCity()) << setw(52) << "│\n";
    cout << " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Program::displayNumberOfFlightsPerAirline() const {
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n";
    cout << " │  Number of flights per airline: " + to_string(dataset_.numberOfFlightsByAirline()) << setw(48) << "│\n";
    cout << " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Program::displayNumberOfDifferentCountriesThatFlyToAirport() const {
    AirportRef airport = receiveAirportByCode();
    if (airport.expired())
        return;
    vector<CountryRef> countries = dataset_.getCountriesAirportFliesTo(airport);
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n";
    cout << " │  Number of different countries that fly to airport: " + to_string(countries.size()) <<setw(97-59-to_string(countries.size()).length()) << "│\n";
    cout << " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Program::displayNumberOfDifferentCountriesThatFlyToCity() const {
    CityRef city = receiveCity();
    if (city.expired())
        return;
    vector<CountryRef> countries = dataset_.getCountriesCityFliesTo(city);
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n";
    cout << " │  Number of different countries that fly to city: " + to_string(countries.size()) << setw(97-56-to_string(countries.size()).length()) << "│\n";
    cout << " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Program::displayNumberOfDifferentDestinationsFromAirport() const {
    AirportRef airport = receiveAirportByCode();
    if (airport.expired())
        return;
    vector<AirportRef> airports = dataset_.searchReachableAirportsFromAirport(airport);
    vector<CountryRef> countries = dataset_.searchReachableCountriesFromAirport(airport);
    vector<CityRef> cities = dataset_.searchReachableCitiesFromAirport(airport);
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n";
    cout << " │  Number of airport destinations from airport: " + to_string(airports.size()) << setw(97-53-to_string(airports.size()).length()) << "│\n";
    cout << " │  Number of countries destinations from airport: " + to_string(countries.size()) << setw(97-55-to_string(countries.size()).length()) << "│\n";
    cout << " │  Number of city destinations from airport: " + to_string(cities.size()) << setw(97-50-to_string(cities.size()).length()) << "│\n";
    cout << " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Program::displayNumberOfReachableDestinationsInNStopsFromAirport() const {
    AirportRef airport = receiveAirportByCode();
    if(airport.expired())
        return;
    int n_stops;
    cout << "Please enter the number of stops: ";
    while (!(cin >> n_stops) || n_stops < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number of stops. Please enter another number: ";
    }
    vector<AirportRef> airports = dataset_.getReachableAirportsFromAirport(airport, n_stops);
    vector<CountryRef> countries = dataset_.getReachableCountriesFromAirport(airport, n_stops);
    vector<CityRef> cities = dataset_.getReachableCitiesFromAirport(airport, n_stops);
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n";
    cout << " │  Number of reachable airports from airport in " + to_string(n_stops) + " stops: " + to_string(airports.size()) << setw(97-61-to_string(n_stops).length()-to_string(airports.size()).length()) << "│\n";
    cout << " │  Number of reachable countries from airport in " + to_string(n_stops) + " stops: " + to_string(countries.size()) << setw(97-62-to_string(n_stops).length()-to_string(countries.size()).length()) << "│\n";
    cout << " │  Number of reachable cities from airport in " + to_string(n_stops) + " stops: " + to_string(cities.size()) << setw(97-59-to_string(n_stops).length()-to_string(cities.size()).length()) << "│\n";
    cout << " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Program::displayMaximumTrip() const {
    clearScreen();
    cout << "Calculating the maximum trip, this might take a while...\n";

    int diameter;
    dataset_.getMaxTrips(diameter);  // TODO: Display also the source-destination pairs

    clearScreen();
    cout << "\n"
            " ┌─ Statistics results ──────────────────────────────────────────────────────────────────┐\n"
            " │                                                                                       │\n";
    cout << " │  Maximum trip: " << left << setw(71) << to_string(diameter) + " flights" << "│\n";
    cout << " │                                                                                       │\n"
            " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
    waitForEnter();
}

void Program::displayNumberOfAirportsEssentialToNetworkCirculation() const {

}





