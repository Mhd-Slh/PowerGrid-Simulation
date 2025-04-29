//
// File:  main.cpp
// 
// It instantiates a PowerGrid type called myGrid.  The grid reads data
// files containing configurations of Plants, Demand locations, 
// and transmission lines.  The plants, demands, and lines have varying
// levels of capacity, need, and efficiencies.
//
// The grid then calls a function to distribute the energy from the plants
// to the demand locations using the transmission lines.  All of the data
// is received in a sorted order and the distribution follows a simple
// algorithm.
//
// After the distribution, a well formatted report is produced showing
// various usage and efficiency characteristics of the power grid.
//

#include "GridDef.h"
#include "PowerGrid.h"
#include <iostream>
using namespace std;

//
// main():  Main function for Power Grid project
//
int main() {
    PowerGrid myGrid;
    int rc;

    // Load and print Power Grid information.
    rc = myGrid.loadGrid();

    if (rc)
    {
        cout << "Error loading Initial Grid: " << rc << endl;
        exit(rc);
    }

    // Sort lines in decreasing order of effciency
    myGrid.sortTransLines();

    myGrid.printGrid("Initial");

    // Have each plant adjust for the conditons of the plant (Sunlight, Rain, Temperature, ...)
    myGrid.adjustPlantsForConditions();
    cout << "\n\n\t\t\t--- Plant Current Condition Summary ---\n";
    myGrid.printPlants();


    // Distribute power from plants to all demand locations
    cout << "\n\t--- Allocating power to the demand locations ---\n";
    myGrid.distributePower();


    // Generate report on usage and efficiency
    cout << endl << endl;
    myGrid.generateUsageReport(GRID_NAME);


    // Print Final grid status
    myGrid.printGrid("Final");

    // Removes the grid's information from the system
    myGrid.shutdownGrid();

    return 0;
}
