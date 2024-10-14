//
//  ECAirport.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECAirport.h"

void ECAirportInfo::CreateAirport(const std::string &name, const std::string &code) {
    airportVector.push_back(new ECAirport(name, code));
}

ECAirport& ECAirportInfo::GetAirport(const std::string &code) {
    for (auto x : airportVector) {
        if (code == x->GetCode()) {
            return *x;
        }
    }
    throw std::string("No airport by that name");
}

void ECAirportInfo::SetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code, int dist) {
    // use iterators to determine if airport with ap1Code already has an entry in map
    // if airport already has an entry, simply append pair to its vector
    // if airport has no entry yet, create one with empty vector, then append pair
    auto airportIter = distances.find(ap1Code);
    if (airportIter != distances.end()) {
        // entry already exists
        (airportIter->second).push_back(std::make_pair(ap2Code,dist));
    } else {
        // entry does not exist
        distances[ap1Code] = std::vector<std::pair<std::string, int>>();
        distances[ap1Code].push_back(std::make_pair(ap2Code, dist));
    }

    // repeat for ap2 -> ap1
    auto airportIter2 = distances.find(ap2Code);
    if (airportIter2 != distances.end()) {
        // entry already exists
        (airportIter2->second).push_back(std::make_pair(ap1Code,dist));
    } else {
        // entry does not exist
        distances[ap2Code] = std::vector<std::pair<std::string, int>>();
        distances[ap2Code].push_back(std::make_pair(ap1Code, dist));
    }
}

int ECAirportInfo::GetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code) {
    for (auto x : distances[ap1Code]) {
        if (x.first == ap2Code) {
            return x.second;
        }
    }
    throw std::string("No distance exists between airports yet");
}

ECAirportInfo::~ECAirportInfo() {
    for (auto x : airportVector) {
        delete x;
    }
}

// these two were added later to help with part 4
int ECAirportInfo::GetNumAirports() {
    return airportVector.size();
}

std::string ECAirportInfo::GetAirportCode(int index) {
    return airportVector[index]->GetCode();
}