#include "PowerGrid.h"

void PowerGrid::printGrid(string description)
{
    // Display Plant information.
    cout << "\n\t\t\t\t--- " << description << " Plant Capacity Summary-- - \n";
    printPlants();

    // Display Demand information.
    cout << "\n\n\t--- " << description << " Demand Summary ---\n";
    printDemands();

    // Display Transmission Line information.
    cout << "\n\n\t--- " << description << " Transmission Line Summary ---\n";
    printTransLines();
}

int PowerGrid::loadGrid()
{
    int rc;

    // Read Plant information
    rc = readPlantData(PLANTS_FILE);
    if (rc) { return 1; }

    // Read Demand information.
    rc = readDemandData(DEMANDS_FILE);
    if (rc) { return 1; }

    // Read Transmission Line information.
    rc = readTransLineData(TRANSLINES_FILE);
    if (rc) { return 1; }

    return 0;
}

void PowerGrid::shutdownGrid()
{
    // Clearing the vector of demands
    for (Demand a : demands)
    {
        demands.pop_back();
    }

    // Clearing the vector of lines
    for (TransLine b : transLines)
    {
        transLines.pop_back();
    }

    // Clearing the LinkedList of plants
    plants.emptyList();

}