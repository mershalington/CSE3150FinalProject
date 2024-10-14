//
//  ECAirlineTicketing.h
//  
//
//  Created by Yufeng Wu on 5/12/23.
//

#ifndef ECAirlineTicketing_h
#define ECAirlineTicketing_h

// ****************************************************************************
// Airline ticketing: search for flights, issue tickets, etc
#include "ECFlightItinerary.h"
#include "ECFlight.h"
#include "ECAirlineOperation.h"
class ECAirlineOperation;
class ECAirlineFinancial;

class ECAirlineTicketing 
{
public:
    ECAirlineTicketing();
    ~ECAirlineTicketing();

    // initialize pointers to Operation and Financial objects, which I do actually use here
    void Init(ECAirlineOperation* op, ECAirlineFinancial* fin);

    // search for all valid itineraries from src to dest
    void SearchForItineraries(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries); 

    // helper function which introduces an auxiliary itinerary aux which we use to build itineraries during search
    void SearchForItinerariesHelper(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries, ECFlightItinerary& aux, std::string currLocation);

    // check if 'newFlight' satisfies all requirements in order to be added to itinerary 'curr' to create a new valid itinerary (assuming the source of 'newFlight' is equal to our current location)
    bool ValidFlight(const ECFlightItinerary& curr, const ECFlight& newFlight);

private:
    ECAirlineOperation *pAirlineOp;
    ECAirlineFinancial *pAirlineFin;
};

#endif /* ECAirlineTicketing_h */
