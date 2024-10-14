#ifndef ECConsoleUISearchButton_h
#define ECConsoleUISearchButton_h

// Basic headers
#include <string>
#include <vector>

// UI headers
#include "ECConsoleUIItem.h"
#include "ECConsoleUIButton.h"
#include "ECConsoleUIListBox.h"

// Back-end headers
#include "ECFlightItinerary.h"
#include "ECAirlineSimulator.h"

// A button subclass which controls the search functionality.
// Has pointers to two input list boxes (src and dest).
// Has pointer to one output list box (list of valid itineraries).
// Has pointer to an ECAirlineSimulator, to which it delegates the search.
// When enter is pressed, this button will grab src and dest from input list boxes,
// run search, and populate output list box with results.

class ECConsoleUISearchButton : public ECConsoleUIButton
{
public:
    ECConsoleUISearchButton(int xUL, int yUL, int xLR, int yLR, const std::string& textButton);

    // set pointer to src list box
    void setSrcBox(ECConsoleUIListBox* box);

    // set pointer to dest list box
    void setDestBox(ECConsoleUIListBox* box);

    // set pointer to itinerary list box
    void setItineraryBox(ECConsoleUIListBox* box);

    // set pointer to Airline Simulator object
    void setAirline(ECAirlineSimulator* sim);
    
    // handle IO/search functionality described above
    void HdlKeyEnter();

private:
    ECConsoleUIListBox* srcBox;
    ECConsoleUIListBox* destBox;
    ECConsoleUIListBox* itineraryBox;
    ECAirlineSimulator* AirlineSim;
};

#endif
