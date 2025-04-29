// File: Demand.cpp
// 
// Contains the function definitions for the power grid Demand class
//
#include "Demand.h"
#include <iostream>
#include <iomanip>


//
//  Constructors and Destructors
//
Demand::Demand(const string& name, double powerRequired, double mwRetailPrice)
    : location(name), powerRequired(powerRequired), mwRetailPrice(mwRetailPrice) {
    powerAcquired = 0;
    powerDeficit = powerRequired;
    totalPowerPrice = 0;
    totalPowerCost = 0;
    status = "Not Met";
}


//
//  calcPowerDeficit() - Calculates the power deficit after a change in supply or demand
// 
void Demand::calcPowerDeficit() {

    // Determine the deficit of power and then set to zero if very small
    powerDeficit = powerRequired - powerAcquired;
    if (fabs(powerDeficit) < 0.01)
        powerDeficit = 0;
}


//
// addPowerToLocation() 
//      Adds power capacity to the demand location
//      It adjusts both the retail price and power cost for the demand.
//
void Demand::addPowerToLocation(double amount, double sellPrice, double powerCost) {

    // Add the amount pf power acquired and calculate if the remaing power deficit for the location
    powerAcquired += amount;
    calcPowerDeficit();

    // Add the Retail price of this power to amount the location owes
    totalPowerPrice += sellPrice;

    // Add the cost of the power from the plant to total for the location
    totalPowerCost += powerCost;

    // Update the demand status
    if (powerDeficit == 0)
        status = "Met";
    else if (powerAcquired > 0)
        status = "Partially Met";
    else
        status = "Not Met";
}


//
// Setters and Getters
//
string Demand::getLocation() const { return location; }
double Demand::getMwRetailPrice() const { return mwRetailPrice; }
double Demand::getTotalPowerPrice() const { return totalPowerPrice; }
double Demand::getTotalPowerCost() const { return totalPowerCost; }
double Demand::getPowerRequired() const { return powerRequired; }
double Demand::getPowerAcquired() const { return powerAcquired; }
double Demand::getPowerDeficit() const { return powerDeficit; }
string Demand::getStatus() const { return status; }

// Debug and Print functions
void Demand::printAll() const {
    cout << this <<
        " Demand for: " << setw(12) << left << location <<
        " Req: " << setw(8) << right << powerRequired <<
        " Acq: " << setw(8) << right << powerAcquired <<
        " Def: " << setw(8) << right << powerDeficit <<
        setw(12) << right << status << endl;
}

