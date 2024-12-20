#pragma once
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>
#include "Component.h"

class Circuit {
protected:
	vector<Component*> components;         //dynamic allocation
public:
	Circuit();
	virtual~Circuit();

	// Adds a component to the circuit (caller uses 'new' before passing)
	void addComponent(Component* component);

	virtual double calculateOutputVoltage(double inputVoltage) const = 0;      //abstract for specialized cirtcuits
	virtual double calculateTotalResistance() const = 0;
};
#endif // !CIRCUIT_H