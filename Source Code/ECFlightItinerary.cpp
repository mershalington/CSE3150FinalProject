//
//  ECFlightItinerary.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlightItinerary.h"
#include "ECFlight.h"
#include <iostream>
#include <sstream>
#include <string>
#include <set>
using namespace std;

ECFlightItinerary::ECFlightItinerary(ECAirlineFinancial* fin) : pAirlineFin(fin) {}

int ECFlightItinerary::GetNumSegments() const {
    return itineraryFlights.size();
}

ECFlight* ECFlightItinerary::GetSegment(int segIndex) const {
    return itineraryFlights[segIndex];
}

// sum of flight times (ie. not including layovers)
double ECFlightItinerary::GetFlightTime() const {
    double sum = 0;
    for (auto x : itineraryFlights) {
        sum += x->GetFlightDuration();
    }
    return sum;
}

// total duration of itinerary, including layovers
double ECFlightItinerary::GetTimeAllSegments() const {
    return GetArrivalTime() - GetDepartTime();
}

double ECFlightItinerary::GetDepartTime() const {
    // departure time of first flight
    return itineraryFlights[0]->GetDepartureTime();
}

double ECFlightItinerary::GetArrivalTime() const {
    // arrival time of final flight
    return itineraryFlights[GetNumSegments()-1]->GetArrivalTime();
}

double ECFlightItinerary::GetPrice() const {
    // call financial object's CalculatePrice method on this itinerary
    return pAirlineFin->CalculatePrice(*this);
}

void ECFlightItinerary::AddFlightToItinerary(ECFlight* flight) {
    itineraryFlights.push_back(flight);
}

void ECFlightItinerary::RemoveFlightFromItinerary() {
    itineraryFlights.pop_back();
}

void ECFlightItinerary::Dump() const {
    cout << "Price: $" << GetPrice() << "   --Number of segments: " << GetNumSegments() << "  flight time:" << GetFlightTime() << "  ";
    for(int i=0; i<GetNumSegments(); ++i)
    {
        cout << "[" << i+1 << "]:" << GetSegment(i)->GetSource() << " to " << GetSegment(i)->GetDest() << ": departing: " << GetSegment(i)->GetDepartureTime() << ", arriving: " << GetSegment(i)->GetArrivalTime()  << "    ";
    }
    cout << endl;
}

std::string ECFlightItinerary::GetDisplayString() {
    std::stringstream displayString;

    // write number of segments
    displayString << GetNumSegments() << " segments | ";

    // add segments
    for (auto x : itineraryFlights) {
        displayString << x->GetSource() << "->";
    }
    displayString << itineraryFlights[itineraryFlights.size()-1]->GetDest() << " | ";

    // add flight duration
    displayString << "Time in air: " << GetFlightTime() << " | ";

    // add flight price
    displayString << "Price: " << GetPrice();

    return displayString.str();
}
