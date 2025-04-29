#pragma once
// File: Demand.h
//
// Contains class definition for the Demand class on the power grid and
// represents a power demand point (e.g., city or village).
//
// Demand objects identify a location and a the amount of power (megawatts) 
// that the location requires.  
// 
// They track how much power is currently being supplied and the amount 
// needed to fully to meet their power requirements.  They can also 
// quickly report on the status of if their requiermends are satisfied.
// 
#include <string>
using namespace std;

class Demand {
protected:
    string      location;
    double      mwRetailPrice;      // Price this location pays for mwh
    double      totalPowerPrice;    // The price that the location owes
    double      totalPowerCost;     // The cost of this power from the plant
    double      powerRequired;
    double      powerAcquired;
    double      powerDeficit;
    string      status;

    // Private support functions
    void        calcPowerDeficit();  // Calculates the power deficit when required or acquired changes 

public:
    // Consructors & Destructors
    Demand(const string& location, double requiredCapacity, double mwRetailPrice);

    // Mutators
    void addPowerToLocation(double powerAmount, double sellPrice, double cost);


    // Accesors
    string getLocation() const;
    double getMwRetailPrice() const;
    double getTotalPowerPrice() const;
    double getTotalPowerCost() const;
    double getPowerRequired() const;
    double getPowerAcquired() const;
    double getPowerDeficit() const;
    string getStatus() const;

    // Print and debug
    void printAll() const;   // Prints information for debugging
};
