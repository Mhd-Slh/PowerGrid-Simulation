// File: PowerGrid.cpp
// 
// Contains the function code for the overal PowerGrid class
// 
// This class contains the plants, demands, and lines of the grid and
// this file contains member functions for reading, inserting, and 
// printing the key components of the grid.

#include "GridDef.h"
#include "PowerGrid.h"
#include <iostream>
#include <cctype>
using namespace std;


//********************************************************
//*****        Functions for Power Plants            *****
//********************************************************

//
//  readPlantData():   Reads the information about each plant from the data
//                  file and adds them to the grid
//
int PowerGrid::readPlantData(const string& plantFilename) {

    // Variables used to read demand info from file
    string name, type, headerLine;
    int sustain;
    double capacity;
    double  costPerMW, uptime;

    // Open data file for reading
    ifstream isPlant(plantFilename);
    if (!isPlant) {
        cerr << "Error: Unable to open file " << plantFilename << endl;
        return 1;
    }

    // The first two lines of the file is a header line, read them but don't do anything
    getline(isPlant, headerLine);
    getline(isPlant, headerLine);

    // Read the tcommon information for the first plant
    isPlant >> name >> type >> sustain >> costPerMW >> capacity >> uptime;


    // Process all records in the file 
    while (!isPlant.eof() && !isPlant.fail()) {

        // Read the rest of the data depending on the type of the plant and add theplant to the grid
        if (type == PT_SOLAR) {
            double panelCount, sunlightHours;
            isPlant >> panelCount >> sunlightHours;
            SolarFarm* pSolar = new SolarFarm(name, sustain, capacity, costPerMW, uptime, panelCount, sunlightHours);
            addPlantToGrid(pSolar);
        }

        else if (type == PT_WIND) {
            int turbineCnt;
            double windSpeed;
            isPlant >> turbineCnt >> windSpeed;
            WindFarm* pWind = new WindFarm(name, sustain, capacity, costPerMW, uptime, turbineCnt, windSpeed);
            addPlantToGrid(pWind);
        }

        else if (type == PT_FOSSIL) {
            string fuelType;
            double emissionsRate;
            isPlant >> fuelType >> emissionsRate;
            FossilPlant* pFossil = new FossilPlant(name, sustain, capacity, costPerMW, uptime, fuelType, emissionsRate);
            addPlantToGrid(pFossil);
        }

        else if (type == PT_HYDRO) {
            double waterFlowRate;
            isPlant >> waterFlowRate;
            HydroPlant* pHydro = new HydroPlant(name, sustain, capacity, costPerMW, uptime, waterFlowRate);
            addPlantToGrid(pHydro);
        }

        else if (type == PT_NUCLEAR) {
            NuclearPlant* pNuclear = new NuclearPlant(name, sustain, capacity, costPerMW, uptime);
            addPlantToGrid(pNuclear);
        }

        else if (type == PT_GEO_THERMAL) {
            GeothermalPlant* pGeo = new GeothermalPlant(name, sustain, capacity, costPerMW, uptime);
            addPlantToGrid(pGeo);
        }

        else if (type == PT_FUSION) {
            double neutronFlux;
            isPlant >> neutronFlux;
            Fusion* pFus = new Fusion(name, sustain, capacity, costPerMW, uptime, neutronFlux);
            addPlantToGrid(pFus);
        }

        else if (type == PT_DILITHIUM) {
            int crystalPurity;
            double fieldStability;
            isPlant >> crystalPurity >> fieldStability;
            DiLithium* pDi = new DiLithium(name, sustain, capacity, costPerMW, uptime, crystalPurity, fieldStability);
            addPlantToGrid(pDi);
        }

        else {
            cerr << "\nUnkown plant type found: " << type << endl;
            assert(0);
        }

        // Read the common information of the next record
        isPlant >> name >> type >> sustain >> costPerMW >> capacity >> uptime;
    }

    isPlant.close();

    return 0;
}


//
// addPlant()
//
void PowerGrid::addPlantToGrid(Plant* plant) {
    plants.insert(plant);
}


//
// adjustPlantsforConditons():  Adjust the available cpacity of each plant by
//                      calling each plants virtual function calculateOutput.
//
void PowerGrid::adjustPlantsForConditions() {
    // In assignment 2 and beyond, the plant vector contains pointers to a
    // plant object, not a plant object.   When we itereate, the iteration variable
    // is a pointer so need to use the -> notation instead of the . notation.

    // Loop and call the calculateOutputfor each plant.
    for (const auto& plant : plants) {
        plant->calculateOutput();
    }
}



//
// printPlants()
//
void PowerGrid::printPlants() const {
    int     totalSustain = 0;
    double  totalMaxCap = 0;
    double  totalCurCap = 0;
    double  totalAvailCap = 0;
    double  totalUptime = 0;
    double  totalMWCost = 0;
    int     plantCount = 0;

    // Print column headings
    cout << "  Plant         Type     Sustain    Max Cap      Cur Cap     Avail Cap     %UpTime   Cost/MwH     Current Operating Conditions\n";
    cout << "---------     -------    -------    -------     ---------    ----------    -------   --------  ==================================  \n";
    
    // Loop, print, and total information for each Plant and collect totals.
    for (const auto& plant : plants) {
        cout <<
            setw(14) << left << plant->getName() <<
            setw(10) << left << plant->getType() <<
            setw(6) << right << plant->getSustainScore() <<
            std::fixed << std::setprecision(2) << right <<
            setw(11) << right << plant->getMaxCapacity() << "mw" <<
            setw(12) << right << plant->getCurCapacity() << "mw" <<
            setw(12) << right << plant->getAvailCapacity() << "mw" <<
            setw(11) << right << plant->getUptimePercent() <<
            setw(11) << right << plant->getCostPerMW() << "  ";
    
        // Print the current conditions at the plant
        cout << plant->getCurConditions() << endl;
    
        // Accumulate totals
        totalSustain += plant->getSustainScore();
        totalMaxCap += plant->getMaxCapacity();
        totalCurCap += plant->getCurCapacity();
        totalAvailCap += plant->getAvailCapacity();
        totalUptime += plant->getUptimePercent();
        totalMWCost += plant->getCostPerMW();
        plantCount++;
    }

    // Print Totals
    cout << "                         =======    =======     =========    ==========     ======   ========\n";
    cout <<
        setw(24) << left << "Total:" <<
        std::fixed << std::setprecision(2) << right <<
        setw(7) << right << ((double)totalSustain / plantCount) <<
        setw(10) << right << totalMaxCap << "mw" <<
        setw(12) << right << totalCurCap << "mw" <<
        setw(12) << right << totalAvailCap << "mw" <<
        setw(11) << right << (totalUptime / plantCount) <<
        setw(11) << right << (totalMWCost / plantCount) << endl;

}


//********************************************************
//*****       Functions for Demand Locations         *****
//********************************************************

//
//  readDemandData():   Reads the information about each demand from the data
//                  file and adds them to the grid
//
int PowerGrid::readDemandData(const string& demandFilename) {

    // Variables used to read demand info from file
    string  location;
    double  requiredCapacity;
    double  price;
    string  status;
    string  headerLine;

    // Open data file for reading
    ifstream isDemand(demandFilename);
    if (!isDemand) {
        cerr << "Error: Unable to open file " << demandFilename << endl;
        return 1;
    }

    // Skip the two header lines
    getline(isDemand, headerLine);
    getline(isDemand, headerLine);

    // Read the first demand record
    isDemand >> location >> requiredCapacity >> price;

    // Process all reords in the file 
    while (!isDemand.eof() && !isDemand.fail()) {

        // Declare a Demand variable and add it to the grid 
        Demand newDemand(location, requiredCapacity, price);
        addDemand(newDemand);
        // newDemand.printAll();   // Display information to screen before adding 

        // Read next record
        isDemand >> location >> requiredCapacity >> price;
    }

    isDemand.close();

    return 0;
}


//
// addDemand()
//
void PowerGrid::addDemand(const Demand& demand) {
    demands.push_back(demand);
}


//
// printDemands()
//
void PowerGrid::printDemands() const {
    double  totalRequired = 0;
    double  totalSupplied = 0;

    // Print column headings
    cout << " Location      Demand     Supplied     Status\n";
    cout << "----------    --------    --------    --------\n";

    // Loop, print, and total all information for each demand.
    for (const auto& demand : demands) {
        cout <<
            setw(14) << left << demand.getLocation() <<
            std::fixed << std::setprecision(1) <<
            setw(8) << right << demand.getPowerRequired() <<
            setw(12) << right << demand.getPowerAcquired() <<
            setw(12) << right << demand.getStatus() << endl;

        totalRequired += demand.getPowerRequired();
        demand.getPowerAcquired();
    }

    // Print totals
    cout << "              ========    ========\n";
    cout <<
        setw(14) << left << "Total:" <<
        std::fixed << std::setprecision(1) <<
        setw(8) << std::right << totalRequired <<
        setw(12) << std::right << totalSupplied << endl;

}



//********************************************************
//*****      Functions for Transmission Lnes         *****
//********************************************************

// Matching the binary file structure
struct TransLineFileRecord
{
    char lineName[20];
    double lineCapacity;
    double lineEfficiency;
};

const streamoff RECORD_COUNT_POS = 128;
const streamoff FIRST_RECORD_POS = 1024;
const streamoff RECORD_SPACING = 512;

//
//  readTransLineData():   Reads the information about each transLine 
//              from the data file and adds them to the grid
//
int PowerGrid::readTransLineData(const string& transLineFilename) {

    // Open data file for reading
    ifstream isTransLine(transLineFilename, ios::binary);
    if (!isTransLine) {
        cerr << "Error: Unable to open file " << transLineFilename << endl;
        return 1;
    }

    // Seek to the record count position and read number of records
    isTransLine.seekg(RECORD_COUNT_POS);
    int numRecords = 0;
    isTransLine.read(reinterpret_cast<char*>(&numRecords), sizeof(numRecords));

    // Read each transmission line record
    for (int i = 0; i < numRecords; ++i)
    {
        TransLineFileRecord record;

        // Seek to the correct position for this record
        streamoff recordPos = FIRST_RECORD_POS + (i * RECORD_SPACING);
        isTransLine.seekg(recordPos);
        isTransLine.read(reinterpret_cast<char*>(&record), sizeof(record));

        // Create and add the transmission line
        TransLine newTransLine(record.lineName, record.lineCapacity, record.lineEfficiency);
        addTransLine(newTransLine);
    }

    isTransLine.close();

    return 0;
}


//
// addTransLine()
//
void PowerGrid::addTransLine(const TransLine& transLine) {
    transLines.push_back(transLine);
}


//
// printTransLines()
//
void PowerGrid::printTransLines() const {
    double  totalMaxCap = 0;
    double  totalAvailCap = 0;
    double  totalEff = 0;
    int     lineCount = 0;

    // Print column headings
    cout << "    Line ID       Capacity      Avail    Efficiency\n";
    cout << "---------------   --------    --------   ----------\n";

    // Loop, print, and total information for each transLine.
    for (const auto& transLine : transLines) {
        cout <<
            setw(18) << left << transLine.getLineID() <<
            std::fixed << std::setprecision(2) <<
            setw(8) << right << transLine.getMaxCapacity() <<
            setw(12) << right << transLine.getAvailCapacity() <<
            setw(12) << right << transLine.getEfficiency() << endl;

        totalMaxCap += transLine.getMaxCapacity();
        totalAvailCap += transLine.getAvailCapacity();
        totalEff += transLine.getEfficiency();
        lineCount++;
    }

    // Print totals
    cout << "                   ========     =======   =========\n";
    cout <<
        setw(18) << left << "Total/Avg" <<
        setw(8) << right << totalMaxCap <<
        setw(12) << right << totalAvailCap <<
        setw(12) << std::fixed << std::setprecision(2) <<
        right << (totalEff / lineCount) << endl << endl;

}

int compareTransLines(const void* a, const void* b)
{
    const TransLine* T1 = static_cast<const TransLine*>(a);
    const TransLine* T2 = static_cast<const TransLine*>(b);
    return (int)(100 * T2->getEfficiency()) - (int)(100 * T1->getEfficiency());
}


void PowerGrid::sortTransLines()
{
    qsort(&transLines[0], size(transLines), sizeof(TransLine), compareTransLines);
}
