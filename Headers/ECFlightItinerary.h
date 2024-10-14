//
//  ECFlightItinerary.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECFlightItinerary_h
#define ECFlightItinerary_h

#include <vector>
#include <string>
#include "ECAirlineFinancial.h"

class ECFlight;
class ECAirlineFinancial;

// ****************************************************************************
// Flight itinerary: consisting segments of flights so to go from one airport to another airport

class ECFlightItinerary
{
public:
    // we need to pass a pointer to the Financial object for the GetPrice function to work
    ECFlightItinerary(ECAirlineFinancial* fin);
    
    // access/edit segments
    // Return the number of segments of the itinerary
    int GetNumSegments() const;
    
    // Return a segment
    ECFlight* GetSegment(int segIndex) const;
    
    // Adds the time of all segments, excluding layovers
    double GetFlightTime() const;
    
    // total duration of itinerary, including layovers
    double GetTimeAllSegments() const;
    
    // Get departure time
    double GetDepartTime() const;
    
    // Get arrival time
    double GetArrivalTime() const;
    
    // Price 
    double GetPrice() const;

    // function to tack a flight onto the end of an itinerary
    void AddFlightToItinerary(ECFlight* flight);

    // function to pop last flight from itinerary; we don't care about returning it
    void RemoveFlightFromItinerary();

    // dump an itinerary's contents
    void Dump() const;

    // return a string displaying the itinerary; for use in part 4
    std::string GetDisplayString();
    
    
private:
    // your code
    // list of flight pointers which point, in order, to the flight objects composing this itinerary
    // note the itinerary has no responsibility to, nor should it at all, call delete on these pointers. 
    std::vector<ECFlight*> itineraryFlights;
    ECAirlineFinancial* pAirlineFin;
};

#endif /* ECFlightItinerary_h */
