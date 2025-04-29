// File: DistPower.cpp
// 
// Contains the functions for Power Distribution functions of the PowerGrid class
// 
// The functions implement the algorithms for analyzing demand, capacity, 
// grid topology, efficiency, and environmental impact to satisfy power
// demands.

#include "PowerGrid.h"
using namespace std;

//
// distributePower(): Distributes power to all demand locations
//
// This routine simply loops through each demand location, checks if
// has outstanding power requiemennts and calls the allocateToDemand 
// function to allocate power to it.
//
void PowerGrid::distributePower() {

    // Process the demand for each location
    for (auto& demand : demands) {

        // Check if this location has outstanding demand and allocate power to it
        if (demand.getPowerDeficit() > 0) {
            // cout << demand.getLocation() << " requesting " << demand.getPowerRequired() << "MW" << endl;
            allocateToDemand(demand);
        }
    }
}


//
// Allocates power and line capacity to a demand location
//
void PowerGrid::allocateToDemand(Demand& demand) {

    // Check every line to see if it has capacity left to supply power for the demand location
    for (auto& line : transLines) {

        // Move to the next transmission line if this trans line does not have any capacity remaining
        if (line.getAvailCapacity() <= 0.0)   continue;

        // Stop checking if the full demand has been met
        if (demand.getPowerDeficit() == 0) break;

        // Search the plants to see which plants have power to provide
        for (auto plant : plants) {

            // Stop checking other plants if the full demand is met
            if (demand.getPowerDeficit() == 0) break;

            // Check if this plant has power avaialble to meet this demand
            double rawPlantPowerAvail = plant->getAvailCapacity();
            if (rawPlantPowerAvail > 0) {

                // Scale the power that will be provided and that provided from this plant (based on line efficiency)
                double  lineEfficiency;         // The effciency percentage of the line - causes reduction to plant
                double  maxScaledPowerAvail;    // The max power scaled to the power lost in transmission
                double  powerSuppliedToLocation;  // The amount of power supplied to the Demand location
                double  rawPowerFromPlant;      // The amount of power drawn from plant for this demand 

                lineEfficiency = line.getEfficiency();
                maxScaledPowerAvail = rawPlantPowerAvail * lineEfficiency;
                powerSuppliedToLocation = min(demand.getPowerDeficit(), min(maxScaledPowerAvail, line.getAvailCapacity()));  // Changed in A3


                // Scale the power and remove the capacity from the plant and the transmission line
                rawPowerFromPlant = powerSuppliedToLocation / lineEfficiency;
                plant->reduceCapacity(rawPowerFromPlant);
                line.allocateLineCapacity(powerSuppliedToLocation);    // Changed in A3


                // Determine the cost (from the plant) and the selling price for the power
                double costOfPower = rawPowerFromPlant * plant->getCostPerMW();
                double sellPriceOfPower = powerSuppliedToLocation * demand.getMwRetailPrice();


                // Add the capacity to the demand location with the cost of the power
                demand.addPowerToLocation(powerSuppliedToLocation, sellPriceOfPower, costOfPower);

                // Print the allocation
                cout << "Allocating: "
                    << std::fixed << std::setprecision(2) << std::setw(6) << powerSuppliedToLocation
                    << " for " << std::setw(10) << std::left << demand.getLocation()
                    << " Using: " << std::setprecision(2) << std::setw(6) << rawPowerFromPlant
                    << " From " << std::setw(12) << std::left << plant->getName()
                    << " On " << line.getLineID()
                    << ", Sell: $" << std::setprecision(2) << std::setw(11) << sellPriceOfPower
                    << " Cost: $" << std::setprecision(2) << std::setw(11) << costOfPower
                    << endl;
            }

            // Check if Line capacity has been reached and we need to move to the next line.
            if (line.getAvailCapacity() <= 0.5)
                break;

        } // for Plants

    } // for TransLine
}



//
// generateUsageReport(): Print the final simulation report
//
void PowerGrid::generateUsageReport(string companyName) {
    double totalDemandRequested = 0;
    double totalDemandSupplied = 0;
    double totalCost = 0;
    double totalPrice = 0;
    double curCost, curPrice, curProfit;   // Cost, Sell, and Profit of the current demand location

    // Print Headings
    cout << "\t\t\t\t" << companyName << endl;
    cout << "\t\t\t\t Grid Simulation Report" << endl;
    cout << "Location   | Required(MW) | Supplied(MW) |     Status    |  Sell Price |  Power Cost |   Profit   |" << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;

    // Loop through Demands and print status of each demand location
    for (auto& demand : demands) {

        // Get cost, selling price and profit for this demand location
        curCost = demand.getTotalPowerCost();
        curPrice = demand.getTotalPowerPrice();
        curProfit = curPrice - curCost;


        // Print out the demand inforamtion
        cout << std::setw(10) << std::left << demand.getLocation() << " | "
            << std::setprecision(2) << std::setw(12) << std::right << demand.getPowerRequired() << " | "
            << std::setprecision(2) << std::setw(12) << std::right << demand.getPowerAcquired() << " | "
            << std::setw(13) << std::left << demand.getStatus() << " | "
            << std::setprecision(2) << std::setw(11) << std::right << curPrice << " | "
            << std::setprecision(2) << std::setw(11) << std::right << curCost << " |"
            << std::setprecision(2) << std::setw(11) << std::right << curProfit << " |"
            << endl;

        // Adjust the running totals 
        totalCost += curCost;
        totalPrice += curPrice;

        // Collect the total requested and supplied Demand
        totalDemandRequested += demand.getPowerRequired();
        totalDemandSupplied += demand.getPowerAcquired();
    }

    // Loop through the plants and total how much capacity was used.
    double totalPlantUsage = 0;
    for (auto plant : plants) {
        double plantUsage = plant->getMaxCapacity() - plant->getAvailCapacity();
        totalPlantUsage += plantUsage;
    }

    cout << endl << endl << "Overall Grid Performance:" << endl;
    cout << "    Total Demand Request:  " << totalDemandRequested << " MW" << endl;
    cout << "    Total Demand supplied: " << totalDemandSupplied << " MW" << endl;
    cout << "    Percent of demand met: " << ((totalDemandSupplied / totalDemandRequested) * 100) << "%" << endl;
    cout << endl;
    cout << "    Plant Capacity used:   " << totalPlantUsage << " MW" << endl;
    cout << "    Efficiency percentage: " << (totalDemandSupplied / totalPlantUsage) << endl << endl;
    cout << "    Total Revenue (Price): " << totalPrice << endl;
    cout << "    Total cost of Power:   " << totalCost << endl;
    cout << "             Total Profit: " << totalPrice - totalCost << endl;

}