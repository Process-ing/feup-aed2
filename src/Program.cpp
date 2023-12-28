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
            case Option::SEARCH:
                searchMenu();
                break;
            case Option::STATISTICS:
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
            case Option::SEARCH_ALL_COUNTRIES:
                displayAllCountries();
                break;
            case Option::SEARCH_ALL_AIRPORTS:
                displayAllAirports();
                break;
            case Option::SEARCH_ALL_AIRLINES:
                displayAllAirlines();
                break;
            case Option::SEARCH_AIRLINES_BY_COUNTRY:
                displayAirlinesByCountry();
                break;
            case Option::SEARCH_CITIES_IN_COUNTRY:
                displayCitiesByCountry();
                break;
            case Option::SEARCH_AIRPORTS_IN_CITY:
                displayAirportsByCity();
                break;
            case Option::SEARCH_FLIGHTS_FROM_AIRPORT:
                displayFlightsFromAirport();
                break;
            case Option::SEARCH_COUNTRIES_FLYING_TO_AIRPORT:
                displayCountriesFlyingToAirport();
                break;
            case Option::SEARCH_COUNTRIES_FLYING_TO_CITY:
                displayCountriesFlyingToCity();
                break;
            case Option::SEARCH_DESTINATIONS_FROM_AIRPORT:
                displayDestinationsFromAirport();
                break;
            case Option::SEARCH_REACHABLE_DESTINATIONS_FROM_AIRPORT_IN_N_STOPS:
                displayReachableDestinationsFromAirportInNStops();
                break;
            case Option::SEARCH_TOP_N_AIRPORTS_WITH_GREATEST_TRAFFIC:
                displayTopNAirportsWithGreatestTraffic();
                break;
            case Option::SEARCH_AIRPORTS_ESSENTIAL_TO_NETWORK_CIRCULATION:
                displayAirportsEssentialToNetworkCirculation();
                break;
            case Option::GO_BACK:
                return;
        }
}

void Program::statisticsMenu() const {

}

void Program::sortAirportsMenu() const {
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
    switch(receiveOption(NUM_OPTIONS)){
        case Option::SORT_BY_AIRPORT_NAME:
            sortAirportsByName((vector<AirportRef> &) dataset_.getAirports());
            break;
        case Option::SORT_BY_AIRPORT_CODE:
            sortAirportsByCode((vector<AirportRef> &) dataset_.getAirports());
            break;
        case Option::SORT_BY_AIRPORT_CITY:
            sortAirportsByCity((vector<AirportRef> &) dataset_.getAirports());
            break;
        case Option::SORT_BY_AIRPORT_COUNTRY:
            sortAirportsByCountry((vector<AirportRef> &) dataset_.getAirports());
            break;
    }
}

void Program::sortCountries(vector<CountryRef> countries) const {
    sort(countries.begin(), countries.end(), [](const CountryRef& a, const CountryRef& b) {
        return a.lock()->getName() < b.lock()->getName();
    });
}

void Program::sortCities(vector<CityRef> cities) const{
    sort(cities.begin(), cities.end(), [](const CityRef& a, const CityRef& b) {
        return a.lock()->getName() < b.lock()->getName();
    });
}

void Program::sortAirlinesMenu() const{
    static const int NUM_OPTIONS = 3;
    enum Option {
        SORT_BY_AIRLINE_NAME = 1,
        SORT_BY_AIRLINE_CODE = 2,
        SORT_BY_AIRLINE_COUNTRY = 3
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
        case Option::SORT_BY_AIRLINE_NAME:
            sortAirlinesByName((vector<AirlineRef> &) dataset_.getAirlines());
            break;
        case Option::SORT_BY_AIRLINE_CODE:
            sortAirlinesByCode((vector<AirlineRef> &) dataset_.getAirlines());
            break;
        case Option::SORT_BY_AIRLINE_COUNTRY:
            sortAirlinesByCountry((vector<AirlineRef> &) dataset_.getAirlines());
            break;
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
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    vector<AirportRef> dests = chooseAirportsForBestFlight();
    if (dests.empty())
        return;

    vector<FlightPath> paths = dataset_.getBestFlightPaths(srcs, dests);
    displayBestFlight(paths);
}

vector<AirportRef> Program::chooseAirportsForBestFlight() const {
    const static int NUM_OPTIONS = 2;
    enum Option {
        AIRPORT_CODE = 1,
        AIRPORT_NAME = 2,
    };

    vector<AirportRef> airports;
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
    }

    return airports;
}

string getAirportInfoString(const Airport& airport) {
    return "Code: " + airport.getInfo().getCode() + ", Name: " + airport.getInfo().getName();
}

void Program::displayBestFlight(const vector<FlightPath> &paths) {
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };

    if (paths.empty()) {
        cout << "\nNo flight paths were found. ";
        waitForEnter();
        return;
    }

    int pathIndex = 0;
    while (true) {
        const FlightPath& path = paths[pathIndex];
        clearScreen();
        cout << "\n"
                " ┌─ Best flight paths ─────────────────────────────────────────────────────────┐\n"
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
                " │  Flight path " << left << setw(63) << to_string(pathIndex + 1) + " of " + to_string(paths.size()) <<  "│\n";
        if (pathIndex < paths.size() - 1)
            cout << " │     [1] Next page                                                           │\n";
        if (pathIndex > 0)
            cout << " │     [2] Previous page                                                       │\n";

        cout << " │     [3] Go back                                                             │\n"
                " │                                                                             │\n"
                " └─────────────────────────────────────────────────────────────────────────────┘\n"
                "\n";

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
                    if (pathIndex < paths.size() - 1) {
                        pathIndex++;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case PREVIOUS_PAGE:
                    if (pathIndex > 0) {
                        pathIndex--;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case GO_BACK:
                    return;
                default:
                    break;
            }
            if (valid_option)
                break;
            cout << "Invalid option. Please choose another option: ";
        }
    }
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
    displayAirports(vector<AirportRef>(dataset_.getAirports().begin(), dataset_.getAirports().end()));
}

void Program::displayAllAirlines() const {
    displayAirlines(vector<AirlineRef>(dataset_.getAirlines().begin(), dataset_.getAirlines().end()));
}

void Program::displayAirlinesByCountry() const {
    CountryRef country = receiveCountry();
    if (country.expired())
        return;
    vector<AirlineRef> airlines = dataset_.getAirlinesFromCountry(*country.lock());
    displayAirlines(airlines);
}

void Program::displayCitiesByCountry() const {
    CountryRef country = receiveCountry();
    if (country.expired())
        return;
    vector<CityRef> cities = dataset_.getCitiesFromCountry(*country.lock());
    displayCities(cities);
}

void Program::displayAirportsByCity() const {
    CityRef city = receiveCity();
    if (city.expired())
        return;
    vector<AirportRef> airports = city.lock()->getAirports();
    displayAirports(airports);
}

void Program::displayFlightsFromAirport() const {
    AirportRef airport = receiveAirportByCode();
    if (airport.expired())
        return;
    vector<Flight> flights = dataset_.searchFlightsFromAirport(airport.lock()->getInfo().getCode());
    displayFlights(flights);
}

void Program::displayCountriesFlyingToAirport() const {
    AirportRef airport = receiveAirportByCode();
    if (airport.expired())
        return;
    vector<CountryRef> countries = dataset_.getCountriesAirportFliesTo(*airport.lock());
    displayCountries(countries);
}

void Program::displayCountriesFlyingToCity() const {
    CityRef city = receiveCity();
    if (city.expired())
        return;
    vector<CountryRef> countries = dataset_.getCountriesCityFliesTo(*city.lock());
    sortCountries(countries);
    displayCountries(countries);
}

void Program::displayDestinationsFromAirport() const {
    AirportRef airport = receiveAirportByCode();
    if (airport.expired())
        return;
    vector<AirportRef> airports = dataset_.searchDestinationsFromAirport(airport.lock()->getInfo().getCode());
    sortAirportsMenu();
    displayAirports(airports);
}
void Program::displayReachableDestinationsFromAirportInNStops() const {
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
    vector<AirportRef> airports = dataset_.getReachableAirportsfromAirport(airport, n_stops);
    displayAirports(airports);
}


void Program::displayTopNAirportsWithGreatestTraffic() const {
    int n;
    cout << "Please enter the number of airports: ";
    while (!(cin >> n) || n < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number of airports. Please enter another number: ";
    }
    vector<AirportRef> airports = dataset_.searchTopNAirPortsWithGreatestTraffic(n);
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
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) countries.size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                       │\n";

        for (int i = (page - 1) * RESULTS_PER_PAGE; i < min(page * RESULTS_PER_PAGE, (int)countries.size()); i++)
            cout << " │  " << left << setw(85) << countries[i].lock()->getName() << "│\n";


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
                case Option::NEXT_PAGE:
                    if (page < total_pages) {
                        page++;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case Option::PREVIOUS_PAGE:
                    if (page > 1) {
                        page--;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case Option::GO_BACK:
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
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) cities.size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                       │\n";

        for (int i = (page - 1) * RESULTS_PER_PAGE; i < min(page * RESULTS_PER_PAGE, (int)cities.size()); i++) {
                cout << " │  " << left << setw(85) << "Name :" + cities[i].lock()->getName() << "│\n";
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
                case Option::NEXT_PAGE:
                    if (page < total_pages) {
                        page++;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case Option::PREVIOUS_PAGE:
                    if (page > 1) {
                        page--;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case Option::GO_BACK:
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
                case Option::NEXT_PAGE:
                    if (page < total_pages) {
                        page++;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case Option::PREVIOUS_PAGE:
                    if (page > 1) {
                        page--;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case Option::GO_BACK:
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
                case Option::NEXT_PAGE:
                    if (page < total_pages) {
                        page++;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case Option::PREVIOUS_PAGE:
                    if (page > 1) {
                        page--;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case Option::GO_BACK:
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
                case Option::NEXT_PAGE:
                    if (page < total_pages) {
                        page++;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case Option::PREVIOUS_PAGE:
                    if (page > 1) {
                        page--;
                        valid_option = true;
                    } else {
                        valid_option = false;
                    }
                    break;
                case Option::GO_BACK:
                    return;
            }
            if (valid_option)
                break;
            cout << "Invalid option. Please choose another option: ";
        }
    }
}

