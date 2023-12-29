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

TEST(BestFlightTestSuite, GetBestFlightPathTest) {
    Dataset dataset;
    dataset.readFiles();

    AirportRef JFK = dataset.getAirport("JFK");
    AirportRef CDG = dataset.getAirport("CDG");
    ASSERT_FALSE(JFK.expired());
    ASSERT_FALSE(CDG.expired());
    vector<FlightPath> paths = dataset.getBestFlightPaths({ JFK }, { CDG });
    ASSERT_EQ(1, paths.size());
    FlightPath path = paths[0];

    ASSERT_EQ(2, path.getAirports().size());
    EXPECT_EQ(JFK.lock(), path.getAirports()[0].lock());
    EXPECT_EQ(CDG.lock(), path.getAirports()[1].lock());
}

TEST(Issue16Test, GetAirlinesFromCountry) {
    Dataset dataset;

    dataset.readFiles();

    CountryRef portugal = dataset.getCountry("Portugal");
    auto airlines = dataset.getAirlinesFromCountry(*portugal.lock());
    EXPECT_EQ(5, airlines.size());
}

TEST(Issue16Test, GetCitiesFromCountry) {
    Dataset dataset;

    dataset.readFiles();

    CountryRef portugal = dataset.getCountry("Portugal");
    auto cities = dataset.getCitiesFromCountry(*portugal.lock());
    EXPECT_EQ(14, cities.size());
}

TEST(Issue16Test, GetAirportsFromCity) {
    Dataset dataset;

    dataset.readFiles();

    CityRef faro = dataset.getCity("Faro", "Portugal");
    auto airports = dataset.getAirportsFromCity(*faro.lock());
    EXPECT_EQ(1, airports.size());
}

TEST(Issue17Test, GetCountriesCityFliesTo) {
    Dataset dataset;

    dataset.readFiles();

    CityRef faro = dataset.getCity("Faro", "Portugal");
    auto countries = dataset.getCountriesCityFliesTo(*faro.lock());
    EXPECT_EQ(14, countries.size());
}

TEST(Issue25Test, GetReachableAirportsFromAirport) {
    Dataset dataset;

    dataset.readFiles();

    auto fao = dataset.getAirport("FAO");
    auto airports = dataset.getReachableAirportsFromAirport(fao, 0);
    EXPECT_EQ(63, airports.size());
}

TEST(Issue25Test, GetReachableCitiesFromAirport) {
    Dataset dataset;

    dataset.readFiles();

    auto fao = dataset.getAirport("FAO");
    auto cities = dataset.getReachableCitiesFromAirport(fao, 0);
    EXPECT_EQ(58, cities.size());
}

TEST(Issue25Test, GetReachableCountriesFromAirport) {
    Dataset dataset;

    dataset.readFiles();

    auto fao = dataset.getAirport("FAO");
    auto countries = dataset.getReachableCountriesFromAirport(fao, 0);
    EXPECT_EQ(14, countries.size());
}

TEST(Issue31Test, GetMaxTrips) {
    Dataset dataset;

    dataset.readFiles();

    int diameter = 0;
    auto pairs = dataset.getMaxTrips(diameter);
    EXPECT_EQ(12, diameter);
    EXPECT_EQ(8, pairs.size());
}
