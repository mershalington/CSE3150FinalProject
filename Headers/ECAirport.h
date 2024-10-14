//
//  ECAirport.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECAirport_h
#define ECAirport_h

#include <string>
#include <set>
#include <map>
#include <vector>


// ****************************************************************************
// Airport: start/end point of a flight

class ECAirport 
{
public:
    // by default, airport is operating (except in default constructor)
    ECAirport() : operating(false) {}
    ECAirport(const std::string &nameAP, const std::string &codeIATA) : nameAP(nameAP), codeIATA(codeIATA), operating(true) {}
    ECAirport(const ECAirport &rhs) : nameAP(rhs.nameAP), codeIATA(rhs.codeIATA), operating(rhs.operating) {}
    
    // Get the name of the airport
    std::string GetName() const {
        return nameAP;
    }
    
    // Get IATA code
    std::string GetCode() const {
        return codeIATA;
    }
    
    // Operating status: is it operating normally?
    bool IsOperating() {
        return operating;
    }
    
    // Set operating status
    void SetOperating(bool f) {
        operating = f;
    }

    // no need for destructor since nothing is dynamically allocated
    
private:
    // your code
    std::string nameAP;
    std::string codeIATA;
    bool operating;
};

// ****************************************************************************
// Airport info: access airport information
// Use singleton pattern

class ECAirportInfo
{
public:
    
    // Create a new airport in the system
    void CreateAirport(const std::string &name, const std::string &code);
    
    // Get airport by code
    // Throw exception (std::string) if there is no airport with the code
    ECAirport &GetAirport(const std::string &code);
    
    // Set distance (in miles) between airports
    void SetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code, int dist);

    // Get distance between two airports
    int GetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code);
    
    // more to add...

    // get single instance
    static ECAirportInfo& Instance() {
        static ECAirportInfo inst;
        return inst;
    }

    // destructor: deallocate airports
    ~ECAirportInfo();

    // added these two below to aid in part 4
    int GetNumAirports();

    std::string GetAirportCode(int index);
    
private:
   // your code 

   // private constructor since its a singleton
   ECAirportInfo() {}

   // vector to hold airports, where airports are dynamically allocated and must be deleted at end
   std::vector<ECAirport*> airportVector;

   // map each airport to a vector containing (airport, distance) pairs, where distance
   // is the distance between the two airports. Adding one distance between two airports
   // therefore requires adding two entries - one from A to B and one from B to A
   std::map<std::string, std::vector<std::pair<std::string, int>>> distances;
};


#endif /* ECAirport_h */
