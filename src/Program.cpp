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
    const static int NUM_OPTIONS = 2;
    enum Option {
        AIRPORT_CODE = 1,
        AIRPORT_NAME = 2,
    };

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
    AirportRef src;
    switch (receiveOption(NUM_OPTIONS)) {
        case AIRPORT_CODE:
            src = receiveAirportByCode();
            break;
        case AIRPORT_NAME:
            src = receiveAirportByName();
            break;
    }
    if (src.expired())
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
    AirportRef dest;
    switch (receiveOption(NUM_OPTIONS)) {
        case AIRPORT_CODE:
            dest = receiveAirportByCode();
            break;
        case AIRPORT_NAME:
            dest = receiveAirportByName();
            break;
    }
    if (dest.expired())
        return;

    double distance;
    vector<AirportRef> airports = dataset_.getBestFlightPath(src, dest, distance);
    displayBestFlight(airports, distance);
}

string getAirportInfoString(const Airport& airport) {
    return "Code: " + airport.getInfo().getCode() + ", Name: " + airport.getInfo().getName();
}

void Program::displayBestFlight(const std::vector<AirportRef> &airports, double distance) {
    if (airports.empty()) {
        cout << "\nNo flight paths were found. ";
        waitForEnter();
        return;
    }

    int totalFlights = (int)airports.size() - 1;

    clearScreen();
    cout << "\n"
            " ┌─ Best flight ───────────────────────────────────────────────────────────────┐\n"
            " │                                                                             │\n"
            " │  Total flights: " << left << setw(60) << totalFlights <<  "│\n"
            " │  Total travel distance: " << setw(52) << to_string(distance) + " Km" << "│\n"
            " │                                                                             │\n"
            " │  Travel airports:                                                           │\n";

    for (int i = 0; i < airports.size(); i++) {
        const AirportRef &airport = airports[i];
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
