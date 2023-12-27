#include <iostream>
#include <limits>
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

vector<string> Program::displayCountries(){
    vector<string> countries;
    for(const auto& country: dataset_.getCountries()){
        countries.push_back("Country : " + country->getName());
    }
    return countries;
}

vector<string> Program::displayAirports() {
    vector<string> airports;
    for(const auto& airport: dataset_.getNetwork().getVertexSet()){
        airports.push_back("Name : " + airport->getInfo().getName() + ", Code : " + airport->getInfo().getCode());
    }
    return airports;
}

vector<string> Program::displayAirlines() {
    vector<string> airlines;
    for(const auto& airline: dataset_.getAirlines()){
        airlines.push_back("Name : " + airline.lock()->getName() + ", Code : " + airline.lock()->getCode() + ", Callsign : " + airline.lock()->getCallsign() + ", Country : " + airline.lock()->getCountry().lock()->getName());
    }
    return airlines;
}

vector<string> Program::displayFlightsFromAirport(string airPortCode) {
    AirportRef airport = dataset_.getAirport(airPortCode);
    vector<string> flightStrings;
    if (airport.lock()) {
        for (const auto& edge : airport.lock()->getAdj()){
            const AirportInfo& targetAirport = edge.getDest().lock()->getInfo();

            flightStrings.push_back("Airline : " + edge.getInfo().getAirline().lock()->getName() + ", Source : " + airport.lock()->getInfo().getName() + ", Destination : " + targetAirport.getName());
        }
    } else {
        ostringstream error_msg;
        error_msg << "Airport with code " << airPortCode << " not found" << endl;
        throw ios_base::failure(error_msg.str());
    }
    return flightStrings;
}

int Program::displayFlightsByCityAndAirline(const string& countryName, const string& cityName) {
    int flights=0;
    CityRef city = dataset_.getCity(cityName, countryName);
    if (!city.lock()) {
        ostringstream error_msg;
        error_msg << "City" << cityName << "," << countryName << " not found" << endl;
        throw ios_base::failure(error_msg.str());
    }
    for(const auto& airport : city.lock()->getAirports()){
        for(const auto& flight : airport.lock()->getAdj()){
            flights++;
        }
    }
    return flights;
}

vector<string> Program::displayDestinationsFromAirport(string airPortCode) {
    AirportRef airport = dataset_.getAirport(airPortCode);
    vector<string> flightStrings;
    if (airport.lock()) {
        for (const auto& edge : airport.lock()->getAdj()){
            const AirportInfo& targetAirport = edge.getDest().lock()->getInfo();
            flightStrings.push_back("Destination Airport: " + targetAirport.getName() + ", Destination City: " + targetAirport.getCity().lock()->getName() + ", Destination Country: " + targetAirport.getCity().lock()->getCountry().lock()->getName());
        }
    } else {
        ostringstream error_msg;
        error_msg << "Airport with code " << airPortCode << " not found" << endl;
        throw ios_base::failure(error_msg.str());
    }
    return flightStrings;
}

vector<string> Program::displayTopNAirPortsWithGreatestTraffic(int n) {
    vector<pair<AirportRef, int>> airportTrafficList;

    for (const auto& airport : dataset_.getNetwork().getVertexSet()) {
        int flights = 0;

        for (const auto& flight : airport->getAdj()) {
            flights++;
        }

        if (airportTrafficList.size() < n) {
            airportTrafficList.push_back(make_pair(airport, flights));
        }
    }
    vector<string> result;
    sort(airportTrafficList.begin(), airportTrafficList.end(), [](const pair<AirportRef, int>& a, const pair<AirportRef, int>& b) {
        return a.second > b.second;
    });
    for (int i = 0; i < min(n, static_cast<int>(airportTrafficList.size())); ++i) {
        const AirportRef& airport = airportTrafficList[i].first;
        int traffic = airportTrafficList[i].second;

        result.push_back("Airport: " + airport.lock()->getInfo().getName() + ", City: " +airport.lock()->getInfo().getCity().lock()->getName() + ", Country: " +airport.lock()->getInfo().getCity().lock()->getCountry().lock()->getName() +", Traffic: " + to_string(traffic));
    }
    return result;
}