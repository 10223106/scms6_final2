#pragma once
#ifndef CIRCUITSIMULATOR_H
#define CIRCUITSIMULATOR_H

#include "olcPixelGameEngine.h"
#include "Menu.h"
#include "Resistor.h"
#include "VoltageDivider.h" 
#include "SeriesCircuit.h"
#include "ParallelCircuit.h"
#include <vector>
#include <string>
#include <iomanip>  // For std::setprecision
#include <stdexcept>  // For exception handling
enum class AppState {
    MENU,
    CREDIT, 
    SIMULATION,
    VOLTAGE_DIVIDER,
    SERIES_PARALLEL,

};

class CircuitSimulator : public olc::PixelGameEngine {
public:
    CircuitSimulator();

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

private:
    AppState currentState;
    Menu menu;
    //FOR VOLTAGE DIVIDER
    std::string resistor1Input, resistor2Input, VoltageInput;  // Variables to store the user input for resistors
    double resistor1Value, resistor2Value, VinValue, VoutValue, totalResistance ;  // Variables to store the parsed resistor values 

    //FOR SERIES PARALLEL 
    //int choiceInput;
    std::string choiceInput, voltageInput, resistorCountInput; 
    //static std::vector<Resistor*> resistors; 
    //Handle Input
    bool HandleNumericInput(const std::string& prompt, std::string& input, float y); 
    //void HandleResistorInput(std::string& input, double& value, const std::string& prompt, AppState nextState);
    int convertToInt(const std::string& input); 
    double convertToDouble(const std::string& input); 
    //bool HandleNumericInput(const std::string& label, std::string& input, bool& isComplete, float x, float y); 
    void AddText(float x, float y, const std::string& text, olc::Pixel color = olc::WHITE); 

    // State methods for each AppState
    void InitializeMenuState();
    //void InitializeSimulationState();
    void InitializeVoltageDividerState();
    void InitializeSeriesParallelState(); 
    void InitializeCreditState();

    bool HandleMenuState(); 
    //void HandleSimulationState();
    void HandleVoltageDividerState();
    void HandleSeriesParallelState();
    void HandleCreditState();

    //pointer
    VoltageDivider* voltageDivider = nullptr; //stupid pointer
    //std::unique_ptr<VoltageDivider> voltageDivider = nullptr; //smart pointer 
};

#endif // CIRCUITSIMULATOR_H