#include <gtest/gtest.h>
#include <algorithm>
#include "Dataset.h"

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
    EXPECT_EQ(americanAirlines.lock()->getName(),"American Airlines");
    EXPECT_EQ(americanAirlines.lock()->getCountry().lock()->getName(),"United States");
    EXPECT_EQ(americanAirlines.lock()->getCallsign(),"AMERICAN");
    AirlineRef airEuropa = dataset.getAirline("AEA");
    EXPECT_EQ(airEuropa.lock()->getName(),"Air Europa");
    EXPECT_EQ(airEuropa.lock()->getCountry().lock()->getName(),"Spain");
    EXPECT_EQ(airEuropa.lock()->getCallsign(),"EUROPA");
    AirlineRef airCaraibes = dataset.getAirline("FWI");
    EXPECT_EQ(airCaraibes.lock()->getName(),"Air Caraibes");
    EXPECT_EQ(airCaraibes.lock()->getCountry().lock()->getName(),"France");
    EXPECT_EQ(airCaraibes.lock()->getCallsign(),"FRENCH WEST");

    int total = 0;
    for (auto &v: dataset.getNetwork().getVertexSet())
        total += (int)v->getAdj().size();
    EXPECT_EQ(63832, total);

    AirportRef JFKAirport = dataset.getAirport("JFK");
    vector<Flight> flights = JFKAirport.lock()->getAdj();
    auto specific_flight = find_if(flights.begin(), flights.end(), [](const Flight& f) { return f.getDest().lock()->getInfo().getCode() == "FRA" && f.getInfo().getAirline().lock()->getCode() == "ETH"; });
    EXPECT_NE(specific_flight, flights.end());

    AirportRef SCKAirport = dataset.getAirport("SCK");
    EXPECT_TRUE(SCKAirport.lock());
    EXPECT_EQ(1, SCKAirport.lock()->getAdj().size());
    EXPECT_EQ("AAY", SCKAirport.lock()->getAdj()[0].getInfo().getAirline().lock()->getCode());
    EXPECT_EQ("LAS", SCKAirport.lock()->getAdj()[0].getDest().lock()->getInfo().getCode());
    EXPECT_EQ(1, SCKAirport.lock()->getIndegree());
}
