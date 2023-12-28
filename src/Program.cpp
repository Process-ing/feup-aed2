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
            case BEST_FLIGHT:
                chooseBestFlight();
                break;
            case EXIT:
                leave();
                return;
        }
    }
}

void Program::chooseBestFlight() {
    clearScreen();
    cout << "\n"
            " ┌─ Choose source ─────────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Options:                                                                   │\n"
            " │    [1] Airport code                                                         │\n"
            " │    [2] Airport name                                                         │\n"
            " │    [3] City                                                                 │\n"
            " │    [4] Geographical position                                                │\n"
            " │    [5] Go back                                                              │\n"
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
            " │    [4] Geographical position                                                │\n"
            " │    [5] Go back                                                              │\n"
            " │                                                                             │\n"
            " └─────────────────────────────────────────────────────────────────────────────┘\n"
            "\n";
    vector<AirportRef> dests = chooseAirportsForBestFlight();
    if (dests.empty())
        return;

    unordered_set<string> availableAirports = chooseAirportFilter();
    unordered_set<string> availableAirlines = chooseAirlineFilter();

    vector<FlightPath> paths = dataset_.getBestFlightPaths(srcs, dests, availableAirports, availableAirlines);
    displayBestFlight(paths);
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

unordered_set<std::string> Program::chooseAirportFilter() {
    const static int NUM_OPTIONS = 5;
    enum Option {
        BLACKLIST_AIRPORTS = 1,
        WHITELIST_AIRPORTS = 2,
        BLACKLIST_CITIES = 3,
        WHITELIST_CITIES = 4,
        CONTINUE = 5
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
            " │    [5] Continue                                                             │\n"
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
        case CONTINUE:
            for (AirportRef airport: dataset_.getAirports())
                availableAirports.insert(airport.lock()->getInfo().getCode());
            break;
    }

    return availableAirports;
}

unordered_set<std::string> Program::chooseAirlineFilter() {
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

vector<AirportRef> Program::chooseAirportsForBestFlight() {
    const static int NUM_OPTIONS = 5;
    enum Option {
        AIRPORT_CODE = 1,
        AIRPORT_NAME = 2,
        CITY = 3,
        COORDINATES = 4,
        GO_BACK = 5,
    };

    vector<AirportRef> airports;
    CityRef city;
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
            airports = dataset_.getAirportsFromCity(*city.lock());
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

void Program::displayBestFlight(const vector<FlightPath> &paths) {
    enum Option {
        NEXT_PAGE = 1,
        PREVIOUS_PAGE = 2,
        GO_BACK = 3,
    };

    if (paths.empty()) {
        cout << "No flight paths were found. ";
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
