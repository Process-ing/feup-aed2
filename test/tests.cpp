#include <gtest/gtest.h>
#include <algorithm>
#include "Dataset.h"
#include "Program.h"

using namespace std;

TEST(FileParseTestSuite, ReadFilesTest) {
    Dataset dataset;

    dataset.readFiles();

    EXPECT_EQ(3019, dataset.getNetwork().getVertexSet().size());
    CountryRef iceland = dataset.getCountry("Iceland");
    EXPECT_TRUE(iceland.lock());
    if (iceland.lock()) {
        EXPECT_EQ(5, iceland.lock()->getCities().size());
    }

    CountryRef russia = dataset.getCountry("Russia");
    EXPECT_TRUE(russia.lock());
    if (russia.lock()) {
        vector<shared_ptr<City>> russia_cities = russia.lock()->getCities();
        CityRef moscow = dataset.getCity("Moscow", "Russia");
        EXPECT_TRUE(moscow.lock());
        if (moscow.lock()) {
            EXPECT_EQ(russia.lock()->getName(), moscow.lock()->getCountry().lock()->getName());
            EXPECT_EQ(3, moscow.lock()->getAirports().size());
            AirportRef domododevo = dataset.getAirport("DME");
            if (domododevo.lock()) {
                EXPECT_EQ(moscow.lock()->getName(), domododevo.lock()->getInfo().getCity().lock()->getName());
                EXPECT_EQ(55.408611, domododevo.lock()->getInfo().getLatitude());
                EXPECT_EQ(37.906111, domododevo.lock()->getInfo().getLongitude());
            }
        }
    }

    EXPECT_EQ(444, dataset.getAirlines().size());
    AirlineRef americanAirlines = dataset.getAirline("AAL");
    EXPECT_EQ(americanAirlines.lock()->getName(), "American Airlines");
    EXPECT_EQ(americanAirlines.lock()->getCountry().lock()->getName(), "United States");
    EXPECT_EQ(americanAirlines.lock()->getCallsign(), "AMERICAN");
    AirlineRef airEuropa = dataset.getAirline("AEA");
    EXPECT_EQ(airEuropa.lock()->getName(), "Air Europa");
    EXPECT_EQ(airEuropa.lock()->getCountry().lock()->getName(), "Spain");
    EXPECT_EQ(airEuropa.lock()->getCallsign(), "EUROPA");
    AirlineRef airCaraibes = dataset.getAirline("FWI");
    EXPECT_EQ(airCaraibes.lock()->getName(), "Air Caraibes");
    EXPECT_EQ(airCaraibes.lock()->getCountry().lock()->getName(), "France");
    EXPECT_EQ(airCaraibes.lock()->getCallsign(), "FRENCH WEST");

    int total = 0;
    for (auto &v: dataset.getNetwork().getVertexSet())
        total += (int) v->getAdj().size();
    EXPECT_EQ(63832, total);

    AirportRef JFKAirport = dataset.getAirport("JFK");
    vector<Flight> flights = JFKAirport.lock()->getAdj();
    auto specific_flight = find_if(flights.begin(), flights.end(), [](const Flight &f) {
        return f.getDest().lock()->getInfo().getCode() == "FRA" && f.getInfo().getAirline().lock()->getCode() == "ETH";
    });
    EXPECT_NE(specific_flight, flights.end());

    AirportRef SCKAirport = dataset.getAirport("SCK");
    EXPECT_TRUE(SCKAirport.lock());
    EXPECT_EQ(1, SCKAirport.lock()->getAdj().size());
    EXPECT_EQ("AAY", SCKAirport.lock()->getAdj()[0].getInfo().getAirline().lock()->getCode());
    EXPECT_EQ("LAS", SCKAirport.lock()->getAdj()[0].getDest().lock()->getInfo().getCode());
    EXPECT_EQ(1, SCKAirport.lock()->getIndegree());
}
TEST(DisplayCountries, DisplayCountriesTest){
    Program program;

    program.launch();
    std::vector<std::string> countries = program.displayCountries();
    ASSERT_EQ(236, countries.size());
    ASSERT_TRUE(std::find(countries.begin(), countries.end(), "Country : France") != countries.end());
    ASSERT_TRUE(std::find(countries.begin(), countries.end(), "Country : Papua New Guinea") != countries.end());
    ASSERT_TRUE(std::find(countries.begin(), countries.end(), "Country : United Kingdom") != countries.end());
}

TEST(ProgramTest, DisplayAirports) {
    Program program;
    program.launch();
    std::vector<std::string> airports = program.displayAirports();
    ASSERT_EQ(3019, airports.size());
    ASSERT_TRUE(std::find(airports.begin(), airports.end(), "Name : Charles De Gaulle, Code : CDG") != airports.end());
    ASSERT_TRUE(std::find(airports.begin(), airports.end(), "Name : La Guardia, Code : LGA") != airports.end());
}

TEST(ProgramTest, DisplayAirlines) {
    Program program;

    program.launch();
    std::vector<std::string> airlines = program.displayAirlines();
    ASSERT_EQ(444, airlines.size());
    ASSERT_TRUE(std::find(airlines.begin(), airlines.end(), "Name : Iberia Airlines, Code : IBE, Callsign : IBERIA, Country : Spain") != airlines.end());
    ASSERT_TRUE(std::find(airlines.begin(), airlines.end(), "Name : Swiss International Air Lines, Code : SWR, Callsign : SWISS, Country : Switzerland") != airlines.end());

}
TEST(ProgramTest, DisplayFlightsFromAirport) {
    Program program;

    program.launch();
    std::string airportCode = "JFK";
    std::vector<std::string> flights = program.displayFlightsFromAirport(airportCode);
    ASSERT_EQ(454, flights.size());
    std::string expectedFlightInfo = "Airline : American Airlines, Source : John F Kennedy Intl, Destination : Charles De Gaulle";
    ASSERT_TRUE(std::find(flights.begin(), flights.end(), expectedFlightInfo) != flights.end());
}
TEST(ProgramTest, DisplayFlightsByCityAndAirline) {
    Program program;
    program.launch();
    std::string countryName = "United States";
    std::string cityName = "New York";
    int number = program.displayFlightsByCityAndAirline(countryName, cityName);
    ASSERT_EQ(612, number);
}
TEST(ProgramTest, DisplayDestinationsFromAirport) {
    Program program;

    program.launch();
    std::string airportCode = "JFK";
    std::vector<std::string> flights = program.displayDestinationsFromAirport(airportCode);
    ASSERT_EQ(454, flights.size());
    std::string expectedFlightInfo = "Destination Airport: Charles De Gaulle, Destination City: Paris, Destination Country: France";
    ASSERT_TRUE(std::find(flights.begin(), flights.end(), expectedFlightInfo) != flights.end());
}
