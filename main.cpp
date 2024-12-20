#include <iostream>
#include "Menu.h" 
#include "CircuitSimulator.h" 
// Hide cmd
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
	/*CircuitGui gui;

	gui.Start();*/
	CircuitSimulator demo; 
	if (demo.Construct(256, 240, 4, 4)) {
		demo.Start();
	} 
	return 0;
}