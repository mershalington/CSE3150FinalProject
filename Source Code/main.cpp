// basic headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// UI headers
#include "ECTextViewImp.h"
#include "ECConsoleUIView.h"
#include "ECConsoleUITextLabel.h"
#include "ECConsoleUIButton.h"
#include "ECConsoleUIListBox.h"
#include "ECConsoleUISearchButton.h"

// Airport back-end headers
#include "ECAirport.h"
#include "ECFlightItinerary.h"
#include "ECAirlineSimulator.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"

using namespace std;

// extract information from input file and use it to initialize our airline simulator
void setUpAirline(ECAirlineSimulator& AirlineSim, char* filename) {
    std::string line;
    std::string throwAway;
    std::string srcAirportCode;
    std::string destAirportCode;
    std::string airportName;
    std::string distance;
    std::string departTime;
    std::string maxPassengers;
    std::string costToOperate;
    ifstream configFile(filename);

    while (getline(configFile, line)) {
        if (line[0] == '#') continue;

        // create stream out of line so we can extract tokens
        stringstream lineStream(line);

        if (line[0] == '1') {
            getline(lineStream, throwAway, ' ');
            getline(lineStream, srcAirportCode, ' ');
            getline(lineStream, airportName);
            cout << srcAirportCode << " " << airportName << endl;
            AirlineSim.AddAirport(airportName, srcAirportCode);
        }

        if (line[0] == '2') {
            getline(lineStream, throwAway, ' ');
            getline(lineStream, srcAirportCode, ' ');
            getline(lineStream, destAirportCode, ' ');
            getline(lineStream, distance);
            cout << srcAirportCode << " " << destAirportCode << " " << distance << endl;
            AirlineSim.SetDistBtwAirports(srcAirportCode, destAirportCode, std::stoi(distance));
        }

        if (line[0] == '3') {
            getline(lineStream, throwAway, ' ');
            getline(lineStream, srcAirportCode, ' ');
            getline(lineStream, destAirportCode, ' ');
            getline(lineStream, departTime, ' ');
            getline(lineStream, maxPassengers, ' ');
            getline(lineStream, costToOperate);
            cout << srcAirportCode << " " << destAirportCode << " " << departTime << " " << maxPassengers << " " << costToOperate << endl;;
            AirlineSim.AddFlight(srcAirportCode, destAirportCode, std::stod(departTime), std::stoi(maxPassengers), std::stod(costToOperate));
        }
    }

    configFile.close();
}

void populateView(ECConsoleUIView& UIview, ECAirlineSimulator& AirlineSim) {
    // create all the text labels
    ECConsoleUITextLabel *title = new ECConsoleUITextLabel(10, 1, "Flowers Airlines Flight Reservation System");
    title->SetHighlight(true);
    UIview.AddUIItem(title);

    ECConsoleUITextLabel *src = new ECConsoleUITextLabel(10, 3, "Origination:");
    UIview.AddUIItem(src);

    ECConsoleUITextLabel *dest = new ECConsoleUITextLabel(30, 3, "Destination:");
    UIview.AddUIItem(dest);

    ECConsoleUITextLabel *flights = new ECConsoleUITextLabel(10, 11, "Flights:");
    UIview.AddUIItem(flights);

    // create all list boxes
    ECConsoleUIListBox *srcBox = new ECConsoleUIListBox(10, 5, 20, 7);
    for (int i = 0; i < AirlineSim.GetNumAirports(); i++) {
        srcBox->AddChoice(AirlineSim.GetAirportCode(i));
    }
    UIview.AddUIItem(srcBox);

    ECConsoleUIListBox *destBox = new ECConsoleUIListBox(30, 5, 40, 7);
    for (int i = 0; i < AirlineSim.GetNumAirports(); i++) {
        destBox->AddChoice(AirlineSim.GetAirportCode(i));
    }
    UIview.AddUIItem(destBox);

    // flights list box starts empty, only populated after hitting enter on button
    ECConsoleUIListBox *flightsBox = new ECConsoleUIListBox(10, 13, UIview.GetColNumInView()-1, 15);
    // I don't add the flights list box to the view until after adding the button,
    // so that the order in which we move between items (via crtl-A) feels more natural

    // create the Search button, link with the list boxes it needs + the airline simulator object
    ECConsoleUISearchButton *button = new ECConsoleUISearchButton(10, 9, 35, 9, "Search for Flights");
    button->setSrcBox(srcBox);
    button->setDestBox(destBox);
    button->setItineraryBox(flightsBox);
    button->setAirline(&AirlineSim);
    UIview.AddUIItem(button);

    UIview.AddUIItem(flightsBox);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        throw std::string("Usage: ./executable input_file.txt");
    }

    // Create Airline Simulator interface
    ECAirlineSimulator AirlineSim;

    // Initialize airline simulator using data in text file given on command line; see above
    setUpAirline(AirlineSim, argv[1]);

    // Create UI window
    ECTextViewImp UIwnd;

    // add status bar
    UIwnd.AddStatusRow("Search for Flights!", "CSE 3150 Project", true);

    // Create UI view
    ECConsoleUIView UIview(&UIwnd);

    // Populate view with UI items
    populateView(UIview, AirlineSim);

    // Display view
    UIview.Refresh();

    // Show window
    try {
        UIwnd.Show();
    }
    catch (std::string ex) {
        std::cout << "Exception: " << ex << std::endl;
    }

    return 0;
}
