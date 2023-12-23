/**
 * @file
 * Header file for class Airport.
 */

#ifndef FEUP_AED2_AIRPORT_H
#define FEUP_AED2_AIRPORT_H


#include <string>
#include "City.h"
#include "Graph.h"
#include "Flight.h"


class City;
typedef std::weak_ptr<City> CityRef;
class FlightInfo;

class AirportInfo {
  public:
    AirportInfo(std::string code, std::string name, CityRef city, double latitude, double longitude);

    const std::string &getCode() const;
    const std::string &getName() const;
    const CityRef &getCity() const;
    double getLatitude() const;
    double getLongitude() const;

  private:
    std::string code_;
    std::string name_;
    CityRef city_;
    double latitude_;
    double longitude_;
};


struct AirportInfoHash {
    int operator() (const AirportInfo& airport) const;
    bool operator() (const AirportInfo& airport1, const AirportInfo& airport2) const;
};


typedef Vertex<AirportInfo, FlightInfo> Airport;
typedef VertexRef<AirportInfo, FlightInfo> AirportRef;


#endif //FEUP_AED2_AIRPORT_H
