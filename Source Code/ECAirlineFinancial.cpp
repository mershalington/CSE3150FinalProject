//
//  ECAirlineFinancial.cpp
//  
//
//  Created by Yufeng Wu on 5/16/23.
//

#include "ECAirlineFinancial.h"
#include "ECAirlineOperation.h"
#include "ECFlightItinerary.h"

#include <string>
#include <iostream>
using namespace std;

ECAirlineFinancial::ECAirlineFinancial() {}

ECAirlineFinancial::~ECAirlineFinancial() {}

void ECAirlineFinancial::Init(ECAirlineOperation* op) {
    pAirlineOp = op;
}

double ECAirlineFinancial::CalculatePrice(const ECFlightItinerary& itinerary) {
    double price = 0;
    for (int i = 0; i < itinerary.GetNumSegments(); i++) {
        price += ((itinerary.GetSegment(i)->GetFlightDuration()) * 120);
    }
    return price;
}
