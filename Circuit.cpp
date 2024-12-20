#include "Circuit.h"

Circuit::Circuit() {}

Circuit::~Circuit() {
	for (Component* component : components) {
		delete component;
	}
	components.clear();
}

void Circuit::addComponent(Component* component) {
	components.push_back(component);
}
