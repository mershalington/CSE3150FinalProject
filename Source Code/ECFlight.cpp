//
//  ECFlight.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlight.h"
#include "ECAirport.h"

#include <iostream>
using namespace std;

ECFlight::ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn) : src(srcIn), dest(destIn), tmDepart(tmDepartIn), maxPassengers(maxPassengersIn), currPassengers(0) {
    // Use ECAirportInfo singleton to get distance between src and dest, use to calculate/set flight duration and time of arrival
    flightDistance = ECAirportInfo::Instance().GetDistanceBtw(src, dest);
    // assume speed of plane is constant 500 mi/hr
    flightDuration = static_cast<double>(flightDistance) / 500;
    // arrival time is just departure time plus flight duration
    tmArrive = tmDepart + flightDuration;
}

double ECFlight::GetDepartureTime() const {
    return tmDepart;
}

double ECFlight::GetArrivalTime() const {
    return tmArrive;
}
    
void ECFlight::SetMaxNumPassengers(int m) {
    maxPassengers = m;
}

std::string ECFlight::GetSource() const {
    return src;
}

std::string ECFlight::GetDest() const {
    return dest;
}

double ECFlight::GetFlightDuration() const {
    return flightDuration;
}

int ECFlight::GetFlightDistance() const {
    return flightDistance;
}