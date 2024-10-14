//
//  ECFlight.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECFlight_h
#define ECFlight_h

#include <string>


// ****************************************************************************
// Flight: service between two airports at a specific time;

class ECFlight 
{
public:
    // flight constructor: may potentially add attribute to keep track of operating cost since this is passed to AddFlight function in sim class
    ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn);

    virtual ~ECFlight() {}
    
    // Get departure time
    double GetDepartureTime() const;
    
    // Get arrival time
    double GetArrivalTime() const;
    
    // Set max passenger for this flight
    void SetMaxNumPassengers(int m);
    
    // Get src airport code
    std::string GetSource() const;
    
    // Get destination code
    std::string GetDest() const;

    // more to add...   

    // Get flight duration
    double GetFlightDuration() const;

    // Get flight distance
    int GetFlightDistance() const;

    // WHAT ELSE TO ADD???


private:
    // your code
    std::string src;
    std::string dest;
    double tmDepart;
    double tmArrive;
    double flightDuration;
    // tracking flight distance isn't necessary, since we could always just consult the singleton for the distance
    // between src and dest. However, I figured having the information locally could not hurt
    int flightDistance;
    int maxPassengers;
    int currPassengers;
};

#endif /* ECFlight_h */
