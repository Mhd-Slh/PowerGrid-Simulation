#pragma once
//
// File:  GridDef.h
//
// This file contains the constants and sizing parameters for the PowerGrid 
#include <string>
using namespace std;


// Name of company that owns the power grid
const string GRID_NAME = "Energy Grid";

// Filenames and/or Location Constants
const string PLANTS_FILE = "Plants.txt";
const string DEMANDS_FILE = "Demands.txt";
const string TRANSLINES_FILE = "TransLines.dat";
const string REPORT_FILE = "PowerGrid_Report.txt";

// Plant information - used to determine plant type and read plant data file
const string PT_SOLAR = "Solar";
const string PT_WIND = "Wind";
const string PT_HYDRO = "Hydro";
const string PT_FOSSIL = "Fossil";
const string PT_NUCLEAR = "Nuclear";
const string PT_GEO_THERMAL = "GeoTherm";
const string PT_FUSION = "Fusion";
const string PT_DILITHIUM = "Dilithium";


// Constansts used by Transmission line
const int	MAX_LINE_CONNECTIONS = 4;


