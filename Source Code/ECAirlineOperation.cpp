//
//  ECAirlineOperation.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECAirlineOperation.h"
#include "ECFlightItinerary.h"
#include "ECAirlineFinancial.h"
#include "ECFlight.h"

#include <iostream>
#include <string>
using namespace std;

void ECAirlineOperation::Init(ECAirlineFinancial* fin) {
    pAirlineFin = fin;
}

void ECAirlineOperation::AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers) {
    // add flight to list
    listFlights.push_back(ECFlight(srcAirport, destAirport, tmDepart, maxPassengers));
}

ECFlight& ECAirlineOperation::GetFlight(int index) {
    return listFlights[index];
}

int ECAirlineOperation::GetNumFlights() {
    return listFlights.size();
}

void ECAirlineOperation::PostFlightSetup() {
    // blank for now
}
