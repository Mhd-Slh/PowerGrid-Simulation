// File: TransLine.cpp
// 
// Contains the function definitions for the power grid Transmission Line class
//
// The transmission lines connect the power plants to the demand locations.
//		Each line has a name, a capacity, and an efficiency.
// 
// The capacity is maximum amount of power that can travel on the line. 
// 
// See TransLine.h for the descriptio of the TransLine and Connection classes 
// and there use.
// 
//
#include "GridDef.h"
#include "TransLine.h"
#include <iostream>
#include <iomanip>


//
//  Constructors and Destructors
//
// Constructor()  
TransLine::TransLine(const string& lineID, const double maxCapacity, const double efficiency)
    : lineID(lineID), maxCapacity(maxCapacity), availCapacity(maxCapacity), efficiency(efficiency) {
}

// Destructor() 
TransLine::~TransLine() { /* cout << "TransLine destructor: " << lineID << endl; */ }


//
// Setters and Getters
//
string TransLine::getLineID() const { return lineID; }
double TransLine::getAvailCapacity() const { return availCapacity; }
double TransLine::getMaxCapacity() const { return maxCapacity; }
double TransLine::getEfficiency() const { return efficiency; }



// Debug and Print functions

// PrintLineStatus():  Prints the high Level information for a line
void TransLine::printLineStatus() const {
    cout << this <<
        "  Line ID: " << setw(8) << left << lineID <<
        std::fixed << std::setprecision(2) <<
        "  Eff:" << setw(4) << right << efficiency << "%" <<
        "  MaxCap:" << setw(8) << right << maxCapacity <<
        "  AvialCap:" << setw(8) << right << availCapacity << endl;
}

// PrintAllStatus() : Prints the line informaton and the connection info
void TransLine::printAll() const {
    // Print the high level status
    printLineStatus();
}


//  Mutators
//

//
//  allocateLineCapacity();   Allocates capacity for a line to track that
//                           capacity cannot be exceeded on a line
//
void TransLine::allocateLineCapacity(double power) {

    // Reduce the amount avaiable and check for near zero condition
    availCapacity -= power;
    if (availCapacity < 0.001)
        availCapacity = 0.0;
}
