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
            case Option::SEARCH_MAXIMUM_TRIP:
                displayMaximumTrip();
                break;
            case Option::SEARCH_TOP_N_AIRPORTS_WITH_GREATEST_TRAFFIC:
                displayTopNAirportsWithGreatestTraffic();
                break;
            case Option::SEARCH_AIRPORTS_ESSENTIAL_TO_NETWORK_CIRCULATION:
                displayAirportsEssentialToNetworkCirculation();
                break;
        }
}

void Program::statisticsMenu(){

}
void Program::sortAirportMenu(){
    static const int NUM_OPTIONS = 3;
    enum Option {
        SORT_BY_AIRPORT_NAME = 1,
        SORT_BY_AIRPORT_CODE = 2,
        SORT_BY_AIRPORT_CITY = 3
    };
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

void Program::displayAllCountries() {
    static const int RESULTS_PER_PAGE = 10;
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) dataset_.getCountries().size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                       │\n";

        int count = 0;
        for (auto it = dataset_.getCountries().begin(); it != dataset_.getCountries().end(); ++it) {
            if (count >= (page - 1) * RESULTS_PER_PAGE && count < page * RESULTS_PER_PAGE) {
                cout << " │  " << left << setw(85) << (*it)->getName() << "│\n";
            }
            ++count;
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
void Program::displayAllAirports(){
    static const int RESULTS_PER_PAGE = 10;
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) dataset_.getAirports().size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                       │\n";

        int count = 0;
        for (auto it = dataset_.getAirports().begin(); it != dataset_.getAirports().end(); ++it) {
            if (count >= (page - 1) * RESULTS_PER_PAGE && count < page * RESULTS_PER_PAGE) {
                cout << " │  " << left << setw(60) << "Name: " + (*it)->getInfo().getName()
                     << left << setw(25) << " Code: " + (*it)->getInfo().getCode()
                     << "│\n";
            }
            ++count;
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
void Program::displayAllAirlines(){
    static const int RESULTS_PER_PAGE = 10;
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) dataset_.getAirlines().size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                                                                                      │\n";

        int count = 0;
        for (auto it = dataset_.getAirlines().begin(); it != dataset_.getAirlines().end(); ++it) {
            if (count >= (page - 1) * RESULTS_PER_PAGE && count < page * RESULTS_PER_PAGE) {
                cout << " │  " << left << setw(49) << "Name: " + (*it).lock()->getName()
                     << left << setw(12) << " Code: " + (*it).lock()->getCode()<< left <<setw(40) << " Callsign: " + (*it).lock()->getCallsign()
                     <<left <<setw(47) << " Country: " + (*it).lock()->getCountry().lock()->getName()
                     << "│\n";
            }
            ++count;
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
                    displayMainMenu();
                    return;
            }
            if (valid_option)
                break;
            cout << "Invalid option. Please choose another option: ";
        }

    }

}
void Program::displayAirlinesByCountry(){
    static const int RESULTS_PER_PAGE = 10;
    CountryRef country = receiveCountry();
    if(country.expired())
        return;
    vector<AirlineRef> airlines = dataset_.getAirlinesFromCountry(*country.lock());
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) dataset_.getAirlines().size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                                                                                      │\n";
        for(auto it = airlines.begin(); it != airlines.end(); ++it){
            cout << " │  " << left << setw(49) << "Name: " + (*it).lock()->getName()
                 << left << setw(12) << " Code: " + (*it).lock()->getCode()<< left <<setw(40) << " Callsign: " + (*it).lock()->getCallsign()
                 <<left <<setw(47) << " Country: " + (*it).lock()->getCountry().lock()->getName()
                 << "│\n";
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
                    displayMainMenu();
                    return;
            }
            if (valid_option)
                break;
            cout << "Invalid option. Please choose another option: ";
        }

    }

}
void Program::displayCitiesByCountry() {
    CountryRef country = receiveCountry();
    if(country.expired())
        return;
    vector<CityRef> cities = dataset_.getCitiesFromCountry(*country.lock());
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                       │\n";
        for(const auto& city : cities){
            cout << " │  " << left << setw(85) << city.lock()->getName() << "│\n";
        }
        cout << " │                                                                                       │\n"
                " └───────────────────────────────────────────────────────────────────────────────────────┘\n\n";
        waitForEnter();
        displayMainMenu();
    }
}

void Program::displayAirportsByCity() {
    static const int RESULTS_PER_PAGE = 10;
    CityRef city = receiveCity();
    if(city.expired())
        return;
    vector<AirportRef> airports = dataset_.getAirportsFromCity(*city.lock());
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) dataset_.getAirlines().size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                       │\n";

        int count = 0;
        for (auto it = airports.begin(); it != airports.end(); ++it) {
            if (count >= (page - 1) * RESULTS_PER_PAGE && count < page * RESULTS_PER_PAGE) {
                cout << " │  " << left << setw(60) << "Name: " + (*it).lock()->getInfo().getName()
                     << left << setw(25) << " Code: " + (*it).lock()->getInfo().getCode()
                     << "│\n";
            }
            ++count;
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

void Program::displayFlightsFromAirport() {
    static const int RESULTS_PER_PAGE = 10;
    AirportRef airport = receiveAirportByCode();
    if(airport.expired())
        return;
    vector<Flight> flights = dataset_.searchFlightsFromAirport(airport.lock()->getInfo().getCode());
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };
    int page = 1;
    int total_pages = ceil((double) dataset_.getAirlines().size() / RESULTS_PER_PAGE);
    while (true) {
        clearScreen();
        cout << "\n"
                " ┌─ Search results ──────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                                                               │\n";

        int count = 0;
        for (auto it = flights.begin(); it != flights.end(); ++it) {
            if (count >= (page - 1) * RESULTS_PER_PAGE && count < page * RESULTS_PER_PAGE) {
                cout << " │  " << left << setw(55) << "Destination: " + (*it).getDest().lock()->getInfo().getName()
                     << left << setw(15) << " Code: " + (*it).getDest().lock()->getInfo().getCode() << left << setw(55) << " Airline: " + (*it).getInfo().getAirline().lock()->getName()
                     << "│\n";
            }
            ++count;
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
                    displayMainMenu();
                    return;
            }
            if (valid_option)
                break;
            cout << "Invalid option. Please choose another option: ";
        }

    }
}

void Program::displayCountriesFlyingToAirport() {
    static const int RESULTS_PER_PAGE = 10;
    AirportRef airport = receiveAirportByCode();
    if(airport.expired())
        return;
    vector<CountryRef> countries = dataset_.getCountriesAirportFliesTo(*airport.lock());
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

        int count = 0;
        for (auto it = countries.begin(); it != countries.end(); ++it) {
            if (count >= (page - 1) * RESULTS_PER_PAGE && count < page * RESULTS_PER_PAGE) {
                cout << " │  " << left << setw(85) << (*it).lock()->getName() << "│\n";
            }
            ++count;
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
void Program::displayCountriesFlyingToCity() {
static const int RESULTS_PER_PAGE = 10;
    CityRef city = receiveCity();
    if(city.expired())
        return;
    vector<CountryRef> countries = dataset_.getCountriesCityFliesTo(*city.lock());
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

        int count = 0;
        for (auto it = countries.begin(); it != countries.end(); ++it) {
            if (count >= (page - 1) * RESULTS_PER_PAGE && count < page * RESULTS_PER_PAGE) {
                cout << " │  " << left << setw(85) << (*it).lock()->getName() << "│\n";
            }
            ++count;
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
void Program::displayDestinationsFromAirport() {
    static const int RESULTS_PER_PAGE = 10;
    AirportRef airport = receiveAirportByCode();
    if(airport.expired())
        return;
    vector<AirportInfo> airports = dataset_.searchDestinationsFromAirport(airport.lock()->getInfo().getCode());
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
                " ┌─ Search results ────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                                                                 │\n";

        int count = 0;
        for (auto it = airports.begin(); it != airports.end(); ++it) {
            if (count >= (page - 1) * RESULTS_PER_PAGE && count < page * RESULTS_PER_PAGE) {
                cout << " │  " << left << setw(57)<< "Name: " + (*it).getName()
                     << left << setw(15) << " Code: " + (*it).getCode() << left << setw(55) << " Country: " + (*it).getCity().lock()->getCountry().lock()->getName()
                     << "│\n";
            }
            ++count;
        }

        cout << " │                                                                                                                                 │\n"
                " │  Page " << setw(122) << to_string(page) + " of " + to_string(total_pages) << "│\n";
        if (page < total_pages)
            cout << " │     [1] Next page                                                                                                               │\n";

        if (page > 1)
            cout << " │     [2] Previous page                                                                                                           │\n";

        cout << " │     [3] Go back                                                                                                                 │\n"
                " │                                                                                                                                 │\n"
                " └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n\n";
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
void Program::displayReachableDestinationsFromAirportInNStops() {
    static const int RESULTS_PER_PAGE = 10;
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
                " ┌─ Search results ────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n"
                " │                                                                                                                                 │\n";

        int count = 0;
        for (auto it = airports.begin(); it != airports.end(); ++it) {
            if (count >= (page - 1) * RESULTS_PER_PAGE && count < page * RESULTS_PER_PAGE) {
                cout << " │  " << left << setw(67)<< "Name: " + (*it).lock()->getInfo().getName()
                     << left << setw(15) << " Code: " + (*it).lock()->getInfo().getCode() << left << setw(45) << " Country: " + (*it).lock()->getInfo().getCity().lock()->getCountry().lock()->getName()
                     << "│\n";
            }
            ++count;
        }

        cout << " │                                                                                                                                 │\n"
                " │  Page " << setw(122) << to_string(page) + " of " + to_string(total_pages) << "│\n";
        if (page < total_pages)
            cout << " │     [1] Next page                                                                                                               │\n";

        if (page > 1)
            cout << " │     [2] Previous page                                                                                                           │\n";

        cout << " │     [3] Go back                                                                                                                 │\n"
                " │                                                                                                                                 │\n"
                " └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n\n";
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

void Program::displayMaximumTrip() {

}

void Program::displayTopNAirportsWithGreatestTraffic() {
    static const int RESULTS_PER_PAGE = 10;
    int n;
    cout << "Please enter the number of airports: ";
    while (!(cin >> n) || n < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number of airports. Please enter another number: ";
    }
    vector<AirportRef> airports = dataset_.searchTopNAirPortsWithGreatestTraffic(n);
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

        int count = 0;
        for (auto it = airports.begin(); it != airports.end(); ++it) {
            if (count >= (page - 1) * RESULTS_PER_PAGE && count < page * RESULTS_PER_PAGE) {
                cout << " │  " << left << setw(50) << "Name: " + (*it).lock()->getInfo().getName()
                     << left << setw(15) << " Code: " + (*it).lock()->getInfo().getCode() <<left << setw(20) << "Traffic :" + to_string((*it).lock()->getAdj().size())
                     << "│\n";
            }
            ++count;
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

void Program::displayAirportsEssentialToNetworkCirculation() {

}

CountryRef Program::receiveCountry() const {
    string name;
    cout << "Please enter the country's name: ";
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
    if (country.expired()) {
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
    getline(cin, name);
    for (AirportRef airport: dataset_.getAirports()) {
        if (airport.lock()->getInfo().getName() == name)
            return airport;
    }
    cout << "The airline could not be found. ";
    waitForEnter();
    return {};
}







