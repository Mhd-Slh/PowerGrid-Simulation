#pragma once
// File: Plant.h
//
// Contains class definition for the power Plant class and the subclasses
// of the Plant class.
//
// Plants generate the electricity and supply it to demand location 
// using transmission lines.
//
// Plants have varying characteriscs such as Fuel Type, Capacity, Age, 
// cost to produce electricty, hours of operation, and environmental 
// impact.
//
// Plants understand their total capacity and track how much power
// has already been committed and the amount available to provide.
// 
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
using namespace std;

//******************************************************
//                      Plant                      *****
//            Base class for all plants            *****
//******************************************************
//
// Plant:  Base class for all plants
//
class Plant {
private:
    static int plantCount; // Indicates the number of plants

protected:
    string  name;
    string  type;
    int     sustainScore;       // Sustainability score of this plant
    double  maxCapacity;        // The absolute maximum capacity of the plant
    double  curCapacity;        // The current capacity of the plant based weather, rain,..
    double  availCapacity;      // The capacity that is avaiable for demand locations. (not already allocated)
    double  costPerMW;          // Average cost to produce including capital costs
    double  uptime;             // Percentage of time the plant is operational

public:
    // Consructors & Destructors
    Plant(const string& name, const string& type, int sustain, double maxCapacity, double cost, double uptime);
    virtual ~Plant();                 // Virtual destructor

    // Mutators
    void reduceCapacity(double amount);         // Reduce the available capacity for the plant when it is allocated to a location
    virtual double calculateOutput() = 0;       // Pure virtual function for calculating output today
    virtual string getCurConditions();          // Virtual functions to get current conditons at plant


    // Accessors
    string getName() const;
    string getType() const;
    int getSustainScore() const;
    double getMaxCapacity() const;
    double getCurCapacity() const;
    double getAvailCapacity() const;
    double getCostPerMW() const;
    double getUptimePercent() const;

    // Print and debug 
    virtual void printAll();          // Prints all the information for the plant

    //Overloaded Comparison operator
    virtual bool operator<(const Plant& other) const;

};



//******************************************************
//                  Solar Plant                    *****
//******************************************************
//
class SolarFarm : public Plant {
private:
    double panelCount;       // Total number of solar panels (assuming 500w panels)
    double sunlightHours;    // Average daily sunlight hours

public:
    // Constructors and Destructors
    SolarFarm(const string& name, int sustain, double capacity, double cost, double uptime, double count, double sunlight);

    double calculateOutput() override;          // Calculate output for this plant
    virtual string getCurConditions() override; // Get current conditons at plant
    //    void printAll()  override;                  // printAll to include plant specific attributes
};


//******************************************************
//                 Wind Farm Plant                 *****
//    Plant using a set of windmills (turbines)    *****
//******************************************************
class WindFarm : public Plant {
private:
    int     turbineCount;   // Number of turbines
    double  avgWindSpeed;   // Average wind speed in miles/hrs

public:
    // Constructors and Destructors
    WindFarm(const string& name, int sustain, double capacity, double cost, double uptime, int turbines, double windSpeed);

    double calculateOutput() override;          // Calculate output for this plant
    virtual string getCurConditions() override; // Get current conditons at plant
};


//******************************************************
//                 Fossil Fuel Plant               *****
//       Plant using any type of fossil fuel       *****
//******************************************************
class FossilPlant : public Plant {
    string      fuelType;           // Type of fuel (coal, naturalgas, ...)
    double      emissionRate;      // Emmisions per megawatt

public:
    // Constructors and Destructors
    FossilPlant(const string& name, int sustain, double capacity, double cost, double uptime, const string& fuel, double emissions);

    double calculateOutput() override;          // Calculate output for this plant
    virtual string getCurConditions() override; // Get current conditons at plant
};


//******************************************************
//                Hydro Electric Plant             *****
//******************************************************
class HydroPlant : public Plant {
    double waterFlowRate;

public:
    // Constructors and Destructors
    HydroPlant(const string& name, int sustain, double capacity, double cost, double uptime, double flowRate);

    double calculateOutput() override;          // Calculate output for this plant
    virtual string getCurConditions() override; // Get current conditons at plant
};


//******************************************************
//              Nuclear Electric Plant             *****
//******************************************************
class NuclearPlant : public Plant {
    // No plant specific varaibles - at this time :-)

public:
    // Constructors and Destructors
    NuclearPlant(const string& name, int sustain, double capacity, double cost, double uptime);

    double calculateOutput() override;          // Calculate output for this plant
    virtual string getCurConditions() override; // Get current conditons at plant
};


//******************************************************
//             Geothermal Electric Plant           *****
//******************************************************
class GeothermalPlant : public Plant {
    // No plant specific varaibles - at this time :-)

public:
    // Constructors and Destructors
    GeothermalPlant(const string& name, int sustain, double capacity, double cost, double uptime);

    double calculateOutput() override;          // Calculate output for this plant
    virtual string getCurConditions() override; // Get current conditons at plant
};


//******************************************************
//             Fusion Plant                        *****
//******************************************************
class Fusion : public Plant
{
private:
    double neutronFlux;  // Neutron Flux : Measures the radiation damage and shielding requirements. (MW / m^2)

public:
    // Constructors and Destructors
    Fusion(const string& name, int sustain, double capacity, double cost, double uptime, double flux);

    double calculateOutput() override;          // Calculate output for this plant
    virtual string getCurConditions() override; // Get current conditons at plant
};


//******************************************************
//             DiLithium Plant                     *****
//******************************************************
class DiLithium : public Plant {
    int crystalPurity; // Crystal Purity : Higher purity yielding more stable and efficient power generation. (0 - 100 %)
    double fieldStability; // Subspace Field Stability : Represents how well the reactor interacts with subspace for energy amplification and warp field support

public:
    // Constructors and Destructors
    DiLithium(const string& name, int sustain, double capacity, double cost, double uptime, int purity, double stability);

    double calculateOutput() override;          // Calculate output for this plant
    virtual string getCurConditions() override; // Get current conditons at plant
};

