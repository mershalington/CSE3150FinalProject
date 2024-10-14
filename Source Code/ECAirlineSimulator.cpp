//
//  ECAirlineSimulator.cpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//

#include "ECAirlineSimulator.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECAirport.h"
#include "ECFlight.h"

#include <iostream>
using namespace std;

ECAirlineSimulator::ECAirlineSimulator() {
    pAirlineOp = new ECAirlineOperation();
    pAirlineFin = new ECAirlineFinancial();
    pAirlineTicket = new ECAirlineTicketing();

    // call Init function to initialize each of these three objects with pointers they need
    Init();
}

ECAirlineSimulator::~ECAirlineSimulator() {
    delete pAirlineOp;
    delete pAirlineFin;
    delete pAirlineTicket;
}

void ECAirlineSimulator::AddAirport(const std::string &name, const std::string &code) {
    // use ECAirportInfo singleton
    ECAirportInfo::Instance().CreateAirport(name, code);
}

void ECAirlineSimulator::SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist) {
    // use ECAirportInfo singleton
    ECAirportInfo::Instance().SetDistanceBtw(srcAirport, destAirport, dist);
}
    
void ECAirlineSimulator::AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate) {
    // for now, we do nothing with the cost to operate the flight, as the flight constructor given
    // does not accept a cost to operate, nor is the cost of an itinerary based on this value (it is only based on distance of flight)
    pAirlineOp->AddFlight(srcAirport, destAirport, tmDepart, maxPassengers);
}

void ECAirlineSimulator::DoneFlightAdding() {
    // blank for now
}

void ECAirlineSimulator::SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries ) const {
    // for now, this function will simply populate listItineraries with all possible 'valid' itineraries. Later on,
    // it may be changed so that listItineraries is ordered according to some preference (see prefer functions below)
    pAirlineTicket->SearchForItineraries(src, dest, listItineraries);
}

void ECAirlineSimulator::Init() {
    // initialize each object with pointers to other objects
    
    // only pass pointers to each of the three objects based on what the lab slides
    // said. Can always add the others if needed later on...
    pAirlineOp->Init(pAirlineFin);
    pAirlineFin->Init(pAirlineOp);
    pAirlineTicket->Init(pAirlineOp, pAirlineFin);
}

void ECAirlineSimulator::PreferShortTime() {
    // blank for now
}

void ECAirlineSimulator::PreferEarlyArrival() {
    // blank for now
}

void ECAirlineSimulator::PreferLowPrice() {
    // blank for now
}

// these two were added for part 4 to retrieve airport codes
int ECAirlineSimulator::GetNumAirports() {
    return ECAirportInfo::Instance().GetNumAirports();
}

std::string ECAirlineSimulator::GetAirportCode(int index) {
    return ECAirportInfo::Instance().GetAirportCode(index);
}