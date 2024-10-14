//
//  ECAirlineOperation.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//  About operation of an airline: especially flights management

#ifndef ECAirlineOperation_h
#define ECAirlineOperation_h
#include <vector>
#include "ECFlight.h"

// put your code about airline operation here...
class ECAirlineFinancial;

class ECAirlineOperation 
{
public:
    ECAirlineOperation() {}
    ~ECAirlineOperation() {}

    // function to initialize pointers (Diagram on HuskyCT said Operation object needed pointer to Financial object. I don't use it anywhere yet, though...)
    void Init(ECAirlineFinancial* fin);

    // add flight to list of flights
    void AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers);

    // used to retrieve flights from the array
    ECFlight& GetFlight(int index);

    // get number of flights
    int GetNumFlights();

    // blank for now
    void PostFlightSetup();

private:
    // NOTE: this list of flights are the only ECFlight objects created during execution. 
    // All uses of flights (such as storing a list of flights to compose an itinerary) will be done
    // by keeping pointers or references to the very ECFlight objects stored in this list
    std::vector<ECFlight> listFlights;
    ECAirlineFinancial* pAirlineFin;
};

#endif
