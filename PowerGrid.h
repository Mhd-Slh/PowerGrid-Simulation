#pragma once
// File: PowerGrid.h
//
// Contains class definition for the overall PowerGrid Object class
// 
// The PowerGrid class contains support, analysis, and modeling attribues 
// for the overall Grid
//

#include <vector>
#include <string>
#include <cctype>

#include "Plant.h"
#include "Demand.h"
#include "TransLine.h"
#include "LinkedList.h"

//
// Class PowerGrid
//
// This class is an aggregation of all the Plants, Demand Locations, and
// Transmission Lines if the power Grid.   The information for each instance
// of these is stored in a vector in this class.
// 
// The class has functions to read a data file, add an instance to the grid,
// and print the components in the grid.
// 
// The class also has support and action function(s) includeiing:
//  1) Run a balancing routine to distribute power from the plants to
//     the locations over the transmission lines and track enrgy loss.
// 
//  2) Print a report of the distribution and effciency.
// 
class PowerGrid {
protected:

    // Vectors containing instances of demands, and transmission lines
    // Custom Linked List containing plants
    LinkedList<Plant*>    plants; // Implemented LinkedList class used to store pointers of Plants
    vector<Demand>    demands;
    vector<TransLine> transLines;

public:
    // Functions to read, manage, and print power plants
    int readPlantData(const string& filename);
    void addPlantToGrid(Plant* plant);
    void printPlants() const;
    void adjustPlantsForConditions();   // Calls each plant to adjust for unique conditions

    // Functions to read, manage, and print power demand locations
    int readDemandData(const string& filename);
    void addDemand(const Demand& demand);
    void printDemands() const;

    // Functions to read, manage, and print the transmison lines
    int readTransLineData(const string& filename);
    void addTransLine(const TransLine& transLine);
    void printTransLines() const;

    // Functions to distribute power : in file DistPower.cpp
    void distributePower();                         // Distributes power to all demand locations
    void allocateToDemand(Demand& demand);          // Allocates power and line capacity to a demand location
    void generateUsageReport(string companyName);   // Generates a power report to the console

    void printGrid(string description); // Prints all the plants, demands, and lines
    int loadGrid(); // Loads all the plants, demands, and lines
    void shutdownGrid(); // Removes all the grid's information from the system
    void sortTransLines(); // Sorts all the Trans Lines by efficiency
};

