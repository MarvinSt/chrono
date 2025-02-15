// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Radu Serban
// =============================================================================
//
// Simple powertrain model for the UAZBUS vehicle.
// - based on torque-speed engine maps
// - both power and torque limited
// - no torque converter
// - simple gear-shifting model (in automatic mode)
//
// =============================================================================

#include "chrono_models/vehicle/unimog/U401_SimpleMapPowertrain.h"

namespace chrono {
namespace vehicle {
namespace unimog {

const double rpm2rads = CH_C_PI / 30;

U401_SimpleMapPowertrain::U401_SimpleMapPowertrain(const std::string& name) : ChSimpleMapPowertrain(name) {}

double U401_SimpleMapPowertrain::GetMaxEngineSpeed() {
    return 3200 * rpm2rads;
}

void U401_SimpleMapPowertrain::SetEngineTorqueMaps(ChFunction_Recorder& map0, ChFunction_Recorder& mapF) {
    map0.AddPoint(rpm2rads * -10000.0, 0.0);
    map0.AddPoint(rpm2rads * 1000.0, 0.0);
    map0.AddPoint(rpm2rads * 1.5002376354371584e+03, -3.0);
    map0.AddPoint(rpm2rads * 1.9805319424140143e+03, -3.0);
    map0.AddPoint(rpm2rads * 2.3483645267445136e+03, -3.0);
    map0.AddPoint(rpm2rads * 2.7370849651969356e+03, -4.0);
    map0.AddPoint(rpm2rads * 3.1899218510296519e+03, -4.0);
    map0.AddPoint(rpm2rads * 3.6847450081517964e+03, -5.0);
    map0.AddPoint(rpm2rads * 3.9080471179935125e+03, -100.0);

    // Mercedes OM363 18.5 kW
    mapF.AddPoint(rpm2rads * -10000.0, 44.83);
    mapF.AddPoint(rpm2rads * 757.63, 44.83);
    mapF.AddPoint(rpm2rads * 980.32, 50.77);
    mapF.AddPoint(rpm2rads * 1188.75, 56.59);
    mapF.AddPoint(rpm2rads * 1502.43, 58.46);
    mapF.AddPoint(rpm2rads * 1801.97, 59.44);
    mapF.AddPoint(rpm2rads * 2101.56, 60.04);
    mapF.AddPoint(rpm2rads * 2253.80, 59.89);
    mapF.AddPoint(rpm2rads * 2577.31, 59.60);
    mapF.AddPoint(rpm2rads * 2800.98, 58.94);
    mapF.AddPoint(rpm2rads * 3000.87, 58.29);
    mapF.AddPoint(rpm2rads * 3100.00, -50);
    mapF.AddPoint(rpm2rads * 3200.00, -100);
}

void U401_SimpleMapPowertrain::SetGearRatios(std::vector<double>& fwd, double& rev) {
    rev = -1.0 / 14.286;

    fwd.push_back(1.0 / 14.286);
    fwd.push_back(1.0 / 8.333);
    fwd.push_back(1.0 / 4.545);
    fwd.push_back(1.0 / 2.500);
    fwd.push_back(1.0 / 1.563);
    fwd.push_back(1.0);
}

void U401_SimpleMapPowertrain::SetShiftPoints(std::vector<std::pair<double, double>>& shift_bands) {
    shift_bands.push_back(std::pair<double, double>(1200 * rpm2rads, 2800 * rpm2rads));
    shift_bands.push_back(std::pair<double, double>(1200 * rpm2rads, 2800 * rpm2rads));
    shift_bands.push_back(std::pair<double, double>(1200 * rpm2rads, 2800 * rpm2rads));
    shift_bands.push_back(std::pair<double, double>(1200 * rpm2rads, 2800 * rpm2rads));
    shift_bands.push_back(std::pair<double, double>(1200 * rpm2rads, 2800 * rpm2rads));
    shift_bands.push_back(std::pair<double, double>(1200 * rpm2rads, 2800 * rpm2rads));
}

}  // namespace unimog
}  // end namespace vehicle
}  // end namespace chrono
