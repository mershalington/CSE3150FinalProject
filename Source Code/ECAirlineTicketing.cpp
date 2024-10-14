//
//  ECAirlineTicketing.cpp
//  
//
//  Created by Yufeng Wu on 5/12/23.
//

#include "ECAirlineTicketing.h"




ECAirlineTicketing::ECAirlineTicketing() {}

ECAirlineTicketing::~ECAirlineTicketing() {}

void ECAirlineTicketing::Init(ECAirlineOperation* op, ECAirlineFinancial* fin) {
    pAirlineOp = op;
    pAirlineFin = fin;
}

void ECAirlineTicketing::SearchForItineraries(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries) {
    // create temporary auixilary itinerary (starting out empty) for use in building the itineraries
    ECFlightItinerary aux(pAirlineFin);
    std::string currLocation(src);

    // call helper
    SearchForItinerariesHelper(src, dest, listItineraries, aux, currLocation);
}

void ECAirlineTicketing::SearchForItinerariesHelper(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries, ECFlightItinerary& aux, std::string currLocation) {
    // base case: itinerary has reached dest, and a copy must be added to listItineraries
    // if ((aux.GetNumSegments() != 0) && (aux.GetSegment(aux.GetNumSegments()-1)->GetDest() == dest)) {
    if (currLocation == dest) {
        listItineraries.push_back(aux);
        return;
    }

    // brute force path search (loop through all flights and choose valid ones to traverse)
    for (int i = 0; i < pAirlineOp->GetNumFlights(); i++) {
        ECFlight& candidate = pAirlineOp->GetFlight(i);
        // add flight if source of flight matches current location, and is valid
        if (currLocation == candidate.GetSource() && ValidFlight(aux, candidate)) {
            aux.AddFlightToItinerary(&candidate);
            SearchForItinerariesHelper(src, dest, listItineraries, aux, candidate.GetDest());
            aux.RemoveFlightFromItinerary();
        }
    }
}

bool ECAirlineTicketing::ValidFlight(const ECFlightItinerary& curr, const ECFlight& newFlight) {
    // if curr is empty, then simply return true (since newFlight will be the first flight in the itinerary)
    if (curr.GetNumSegments() == 0) return true;

    // return false if newFlight's departure time is earlier than the arrival time of curr's last flight
    if (newFlight.GetDepartureTime() < curr.GetSegment(curr.GetNumSegments()-1)->GetArrivalTime()) return false;

    // return false if adding newFlight to curr would create a loop (ie. dest of newFlight is the same as of the flights' sources in curr)
    for (int i = 0; i < curr.GetNumSegments(); i++) {
        if (newFlight.GetDest() == curr.GetSegment(i)->GetSource()) return false;
    }

    // else, flight is valid
    return true;
}
