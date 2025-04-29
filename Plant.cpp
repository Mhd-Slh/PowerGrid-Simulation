// File: Plant.cpp
// 
// Contains the function definitions for the power Plant class and 
// all the derived plants that are derived from Plant

#include "GridDef.h"
#include "Plant.h"
#include <iostream>
#include <sstream>
#include <iomanip>

//******************************************************
//                  Plant Base Class               *****
//******************************************************
// 
// plantCount
// 
// Initializing plantCount to zero
int Plant::plantCount = 0;


//
//  Constructors and Destructors
//
// This constructor use the technique of using underscores to differentiate a paramater from a class variable.
Plant::Plant(const string& _name, const string& _type, int _sustain, double _capacity, double _cost, double _uptime) {
    name = _name;
    type = _type;
    sustainScore = _sustain;
    uptime = _uptime;
    maxCapacity = _capacity;        // Initally set all capacities to the same value
    curCapacity = _capacity;
    availCapacity = _capacity;
    costPerMW = _cost;

    plantCount++;
}

Plant::~Plant() // Destructor
{
    plantCount--;

    cout << "Destroying plant: " << name << ". Number of plants left: " << plantCount << ".\n";
}



//
// reduceCapacity() - reduces available capacity of a plant 
//
void Plant::reduceCapacity(double amount) {

    // Check for rounding discrenpency with floating point numbers
    if (fabs(amount - availCapacity) < 0.001) {
        // This request uses all available cpacity for the plant
        availCapacity = 0;
    }
    else {
        // Lower the avaiable capacity by the amount requested.
        assert(amount <= availCapacity);
        availCapacity -= amount;
    }
}


// Getters and Setters
string Plant::getName() const { return name; }
string Plant::getType() const { return type; }
int Plant::getSustainScore() const { return sustainScore; }
double Plant::getMaxCapacity() const { return maxCapacity; }
double Plant::getCurCapacity() const { return curCapacity; }
double Plant::getAvailCapacity() const { return availCapacity; }
double Plant::getCostPerMW() const { return costPerMW; }
double Plant::getUptimePercent() const { return uptime; }


// Display plant information
void Plant::printAll() {
    cout << name <<
        " $/MW: $" << costPerMW <<
        " Max: " << maxCapacity <<
        " Avail: " << availCapacity <<
        " Uptime%: " << uptime << "% ";
    cout << " " << getCurConditions() << endl;
}

//
// Default virtual plant condition function
//
string Plant::getCurConditions() {
    return "No plant condtions available.";
}

//
// Overloaded Comparison Operator
//
bool Plant::operator<(const Plant& other) const
{
    // Sort by sustainability descending
    return this->getSustainScore() > other.getSustainScore();
}




//******************************************************
//                  Solar Plant                    *****
//******************************************************
//
//  Constructors and Destructors
//
SolarFarm::SolarFarm(const string& name, int sustain, double capacity, double cost, double uptime, double count, double sunlight) :
    Plant(name, PT_SOLAR, sustain, capacity, cost, uptime), panelCount(count), sunlightHours(sunlight) {
}

//
// calcuateOutput():  Override to calculate output of the plant
// This adjust the available capacity of the plant based on the factors unique to this plant
//
double SolarFarm::calculateOutput() {

    // Calculate and set the current output of this plant
    double output = panelCount * (sunlightHours / 24) * uptime / 70000.0;
    curCapacity = output;
    availCapacity = output;
    return output;

}

string SolarFarm::getCurConditions() {
    stringstream oss;
    oss << "Panel Cnt: " << panelCount <<
        ", Sun Hrs: " << sunlightHours << " Hrs";
    return oss.str();
}


#if 0
// printAll():  Override to include specific plant type attributes
void SolarFarm::printAll() {

    // Print the base plant information, then the plant specific information
    Plant::printAll();
    cout << getCurConditions() << endl;
}
#endif


//******************************************************
//                 Wind Farm Plant                 *****
//******************************************************
//
//  Constructors and Destructors
//
WindFarm::WindFarm(const string& name, int sustain, double capacity, double cost, double uptime, int turbines, double windSpeed) :
    Plant(name, PT_WIND, sustain, capacity, cost, uptime), turbineCount(turbines), avgWindSpeed(windSpeed) {
}

// calcuateOutput():  Override to calculate output of the plant
double WindFarm::calculateOutput() {
    double output = turbineCount * 2 * avgWindSpeed * uptime / 1900.0;
    curCapacity = output;
    availCapacity = output;
    return  output;
}


//
// getCurCondtions():  Returns the current conditons at the plant
// 
string WindFarm::getCurConditions() {
    stringstream oss;
    oss << "Turbines Operational: " << turbineCount <<
        ", Wind Spd: " << avgWindSpeed;
    return oss.str();
}




//******************************************************
//                Fossil Fuel Plant                *****
//******************************************************
//
//  Constructors and Destructors
//
FossilPlant::FossilPlant(const string& name, int sustain, double capacity, double cost, double uptime, const string& fuel, double emissions) :
    Plant(name, PT_FOSSIL, sustain, capacity, cost, uptime), fuelType(fuel), emissionRate(emissions) {
}

double FossilPlant::calculateOutput() {
    double output;
    output = maxCapacity * uptime / 100.0;
    curCapacity = output;
    availCapacity = output;
    return output;
}

//
// getCurCondtions():  Returns the current conditons at the plant
// 
string FossilPlant::getCurConditions() {
    stringstream oss;
    oss << "Fuel Type: " << fuelType <<
        ", Co2 Rate: " << emissionRate;
    return oss.str();
}




//******************************************************
//               Hydro Electric Plant              *****
//******************************************************
//
//  Constructors and Destructors
//
HydroPlant::HydroPlant(const string& name, int sustain, double capacity, double cost, double uptime, double flowRate) :
    Plant(name, PT_HYDRO, sustain, capacity, cost, uptime), waterFlowRate(flowRate) {
}

double HydroPlant::calculateOutput() {
    double output;
    output = waterFlowRate * uptime / 3065500.0;
    curCapacity = output;
    availCapacity = output;
    return output;
}

//
// getCurCondtions():  Returns the current conditons at the plant
// 
string HydroPlant::getCurConditions() {
    stringstream oss;
    oss << std::fixed << std::setprecision(0) <<
        "Water Flow: " << waterFlowRate;
    return oss.str();
}



//******************************************************
//               Nuclear Power Plant               *****
//******************************************************
//
//  Constructors and Destructors
//
NuclearPlant::NuclearPlant(const string& name, int sustain, double capacity, double cost, double uptime) :
    Plant(name, PT_NUCLEAR, sustain, capacity, cost, uptime) {
}

double NuclearPlant::calculateOutput() {
    double output;
    output = maxCapacity * uptime / 100;
    curCapacity = output;
    availCapacity = output;
    return output;
}

//
// getCurCondtions():  Returns the current conditons at the plant
// 
string NuclearPlant::getCurConditions() {
    return "All nuclear systems nominal";
}


//******************************************************
//            Geothermal Power Plant               *****
//******************************************************
//
//  Constructors and Destructors
//
GeothermalPlant::GeothermalPlant(const string& name, int sustain, double capacity, double cost, double uptime) :
    Plant(name, PT_GEO_THERMAL, sustain, capacity, cost, uptime) {
}

double GeothermalPlant::calculateOutput() {
    double output;
    output = maxCapacity * uptime / 100;
    curCapacity = output;
    availCapacity = output;
    return output;
}

//
// getCurCondtions():  Returns the current conditons at the plant
// 
string GeothermalPlant::getCurConditions() {
    return "Geothermal conditions normal";
}


//******************************************************
//            Fusion Plant                         *****
//******************************************************
//
//  Constructors and Destructors
//
Fusion::Fusion(const string& name, int sustain, double capacity, double cost, double uptime, double flux) :
    Plant(name, PT_FUSION, sustain, capacity, cost, uptime), neutronFlux(flux) {
}

double Fusion::calculateOutput() {
    double output;
    output = maxCapacity * 0.6;
    curCapacity = output;
    availCapacity = output;
    return output;
}

//
// getCurCondtions():  Returns the current conditons at the plant
// 
string Fusion::getCurConditions()
{
    stringstream oss;
    oss << "Neutron Flux: " << neutronFlux << " (MW/sqMeter)";
    return oss.str();
}


//******************************************************
//            DiLithium Plant                      *****
//******************************************************
//
//  Constructors and Destructors
//
DiLithium::DiLithium(const string& name, int sustain, double capacity, double cost, double uptime, int purity, double stability) :
    Plant(name, PT_DILITHIUM, sustain, capacity, cost, uptime), crystalPurity(purity), fieldStability(stability) {
}

double DiLithium::calculateOutput() {
    double output;
    output = maxCapacity * 0.995;
    curCapacity = output;
    availCapacity = output;
    return output;
}

//
// getCurCondtions():  Returns the current conditons at the plant
// 
string DiLithium::getCurConditions()
{
    stringstream oss;
    oss << "Current Purity: " << crystalPurity <<
        ", Field Stability: " << fieldStability;
    return oss.str();
}
