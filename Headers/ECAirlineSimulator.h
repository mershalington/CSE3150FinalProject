//
//  ECAirlineSimulator.hpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//  Simulate airline activities: booking, flights, etc

#ifndef ECAirlineSimulator_h
#define ECAirlineSimulator_h

#include <string>
#include <set>
#include <vector>

class ECAirlineOperation;
class ECAirlineTicketing;
class ECAirlineFinancial;
class ECFlightItinerary;

//****************************************************************************
// Airline simulator

class ECAirlineSimulator
{
public:
    ECAirlineSimulator();
    virtual ~ECAirlineSimulator();
    
    // *****************************************************
    // Configuration
    
    // Adding airport with name and IATA code
    void AddAirport(const std::string &name, const std::string &code);
    
    // Setup distaince between airport; note distance is symmetric: the distance from dest to src is the same as from src to dest
    void SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist);
    
    // Adding flights: src airport, dest airport, depart time, max number of passenger, operating cost
    void AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate);
    
    // Called to indicate no more flights to add
    void DoneFlightAdding();

    // Preference functions that weren't added yet
    void PreferShortTime();

    void PreferEarlyArrival();
    
    void PreferLowPrice();
    

    // *****************************************************
    // Flight search
    
    // Search for flights; return all flights in listItineraries that go from src to dest
    void SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries) const;
    
    // Access airlines
    // First one commented out for some unknown reason
    ECAirlineFinancial* GetAirlineFin() { return pAirlineFin; }
    ECAirlineOperation* GetAirlineOp() { return pAirlineOp; }
    ECAirlineTicketing* GetAirlineTicketing() { return pAirlineTicket; }

    // these two were added for part 4 to retrieve airport codes
    int GetNumAirports();

    std::string GetAirportCode(int index);
    
    
private:
    // initialize
    void Init();
    
    // key data member
    ECAirlineOperation *pAirlineOp;
    ECAirlineFinancial *pAirlineFin;
    ECAirlineTicketing *pAirlineTicket;
};


#endif /* ECAirlineSimulator_h */
