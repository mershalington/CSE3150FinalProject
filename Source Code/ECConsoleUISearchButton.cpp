#include "ECConsoleUISearchButton.h"

ECConsoleUISearchButton::ECConsoleUISearchButton(int xUL, int yUL, int xLR, int yLR, const std::string& textButton) : ECConsoleUIButton(xUL, yUL, xLR, yLR, textButton) {}

void ECConsoleUISearchButton::setSrcBox(ECConsoleUIListBox* box) {
    srcBox = box;
}

void ECConsoleUISearchButton::setDestBox(ECConsoleUIListBox* box) {
    destBox = box;
}

void ECConsoleUISearchButton::setItineraryBox(ECConsoleUIListBox* box) {
    itineraryBox = box;
}

void ECConsoleUISearchButton::setAirline(ECAirlineSimulator* sim) {
    AirlineSim = sim;
}
    
void ECConsoleUISearchButton::HdlKeyEnter() {
    // clear the output list box
    itineraryBox->clearListBox();

    // grab src and dest from input list boxes
    std::string src = srcBox->GetChosenString();
    std::string dest = destBox->GetChosenString();

    // if src and dest are the same, there will be no valid itineraries,
    // so it's ok to leave the output list box empty
    if (src == dest) return;

    // vector to populate with valid itineraries
    std::vector<ECFlightItinerary> validItineraries;

    // do the search
    AirlineSim->SearchForFlights(src, dest, validItineraries);

    // populate output list box
    for (auto x : validItineraries) {
        itineraryBox->AddChoice(x.GetDisplayString());
    }
}
