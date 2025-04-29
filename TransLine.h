#pragma once
// File: TransLine.h
//
// Contains class definition for the Transmission Lines that connect 
// the plants to demand locations.  The power plants give are connected
// to the grid and place the power on the grid. The transmission lines 
// modeled connect the demand locations to the grid
// 
// Each line has a lineID, a total capacity, and a total capacity. 
//
// The Capacity of a line is maximum amount of power that can travel on the 
// line. The sum of all power going to all locations cannot exceed the 
// capacity of the Line.
// 
// Each line will track the power being used on a conection.  It use a member varibales
// and finctions within the Connection for this. 

#include "GridDef.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


//
// TransLine {}
// 
// Class to represent the transmission lines of the grid and the demand
// locations that a line can reach.
//
class TransLine {
protected:
    string      lineID;
    double      maxCapacity;
    double      availCapacity;
    double      efficiency;

public:
    // Constructors & Destructors
    TransLine(const string& lineID, const double efficiency, const double maxCapacity);
    ~TransLine();

    // Mutators
    void allocateLineCapacity(double power);

    // Accessors
    string getLineID() const;
    double getMaxCapacity() const;
    double getAvailCapacity() const;
    double getEfficiency() const;

    // Print and debug routines
    void printLineStatus() const;
    void printAll() const;

};


