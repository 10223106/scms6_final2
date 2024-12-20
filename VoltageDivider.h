#pragma once
#ifndef  VOLTAGEDIVIDER_H
#define VOLTAGEDIVIDER_H 


#include "Circuit.h"
#include "Resistor.h"
#include <stdexcept>   //for runtime_error

using namespace std;

class VoltageDivider : public Circuit {
public:
	VoltageDivider();
	double calculateOutputVoltage(double inputVoltage) const override;
	double calculateTotalResistance() const override;
};
#endif // ! VOLTAGEDIVIDER_H 