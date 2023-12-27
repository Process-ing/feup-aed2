#include <iostream>
#include <limits>
#include <iomanip>
#include <cmath>
#include "Program.h"

using namespace std;

Program::Program() {
    dataset_.readFiles();
}

void Program::launch() {
    displayMainMenu();
}

void Program::displayMainMenu() {
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
            case Option::EXIT:
                leave();
                return;
            case Option::SEARCH:
                searchMenu();
                break;
            case Option::STATISTICS:
                statisticsMenu();
                break;
            case Option::BEST_FLIGHT:
                break;
        }
    }
}

void Program::searchMenu() {
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
        SEARCH_MAXIMUM_TRIP = 12,
        SEARCH_TOP_N_AIRPORTS_WITH_GREATEST_TRAFFIC = 13,
        SEARCH_AIRPORTS_ESSENTIAL_TO_NETWORK_CIRCULATION = 14
    };
    cout << "\n"
            " ┌─ Search ─────────────────────────────────────────────────────────────────────┐\n"
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
            " │    [12] Search maximum trip                                                 │\n"
            " │    [13] Search top n airports with greatest traffic                         │\n"
            " │    [14] Search airports essential to network circulation                    │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
        switch(receiveOption(NUM_OPTIONS)){
            case Option::SEARCH_ALL_COUNTRIES:
                displayAllCountries();
                break;
            case Option::SEARCH_ALL_AIRPORTS:
                break;
            case Option::SEARCH_ALL_AIRLINES:
                break;
            case Option::SEARCH_AIRLINES_BY_COUNTRY:
                break;
            case Option::SEARCH_CITIES_IN_COUNTRY:
                break;
            case Option::SEARCH_AIRPORTS_IN_CITY:
                break;
            case Option::SEARCH_FLIGHTS_FROM_AIRPORT:
                break;
            case Option::SEARCH_COUNTRIES_FLYING_TO_AIRPORT:
                break;
            case Option::SEARCH_COUNTRIES_FLYING_TO_CITY:
                break;
            case Option::SEARCH_DESTINATIONS_FROM_AIRPORT:
                break;
            case Option::SEARCH_REACHABLE_DESTINATIONS_FROM_AIRPORT_IN_N_STOPS:
                break;
            case Option::SEARCH_MAXIMUM_TRIP:
                break;
            case Option::SEARCH_TOP_N_AIRPORTS_WITH_GREATEST_TRAFFIC:
                break;
            case Option::SEARCH_AIRPORTS_ESSENTIAL_TO_NETWORK_CIRCULATION:
                break;
        }
}

void Program::statisticsMenu(){

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

vector<AirportInfo> Program::searchFlightsFromAirport(string airPortCode) {
    AirportRef airport = dataset_.getAirport(airPortCode);
    vector<AirportInfo> flightStrings;
    if (airport.lock()) {
        for (const auto& flight : airport.lock()->getAdj()){
            const AirportInfo& targetAirport = flight.getDest().lock()->getInfo();

            flightStrings.push_back(targetAirport);
        }
    }
    return flightStrings;
}

float Program::numberOfFlightsPerCity() {
    int flights=0;
    int cities=0;
    for(const auto& city : dataset_.getCities()){
        cities++;
        for(const auto& airport : city.lock()->getAirports()){
            flights+=airport.lock()->getAdj().size();
        }
    }
    float average = flights/cities;
    return average;
}


vector<AirportInfo> Program::searchDestinationsFromAirport(string airPortCode) {
    AirportRef airport = dataset_.getAirport(airPortCode);
    vector<AirportInfo> flights;
    if (airport.lock()) {
        for (const auto& flight : airport.lock()->getAdj()){
            const AirportInfo& targetAirport = flight.getDest().lock()->getInfo();
            flights.push_back(targetAirport);
        }
    }
    return flights;
}

vector<AirportRef> Program::searchTopNAirPortsWithGreatestTraffic(int n) {
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
void Program::displayAllCountries() {
    static const int RESULTS_PER_PAGE = 10;
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double)dataset_.getCountries().size() / RESULTS_PER_PAGE);
    auto countries = dataset_.getCountries();
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                       │\n";

        for (int i = (page - 1) * RESULTS_PER_PAGE; i < min(page * RESULTS_PER_PAGE, (int)dataset_.getCountries().size()); i++) {
            cout << " │  "<< left << setw(85) << ->getName() << "│\n";
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
                    displayMainMenu();
                    return;
            }
            if (valid_option)
                break;
            cout << "Invalid option. Please choose another option: ";
        }
    }
}
