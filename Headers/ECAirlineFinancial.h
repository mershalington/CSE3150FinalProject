//
//  ECAirlineFinancial.h
//  
//
//  Created by Yufeng Wu on 5/16/23.
//

#ifndef ECAirlineFinancial_h
#define ECAirlineFinancial_h

#include "ECFlightItinerary.h"

// ****************************************************************************
// Airline finanical: budgetting, pricing and money bookkeeping

class ECAirlineOperation;
class ECFlightItinerary;

class ECAirlineFinancial 
{
public:
    ECAirlineFinancial();
    ~ECAirlineFinancial();

    // function to initialize pointers (Diagram on HuskyCT said Financial object needed pointer to Operation object. I don't use it anywhere yet, though...)
    void Init(ECAirlineOperation* op);

    // Function to price an itinerary
    double CalculatePrice(const ECFlightItinerary& itinerary);

private:
    ECAirlineOperation* pAirlineOp;
};

#endif
