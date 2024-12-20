#include "CircuitSimulator.h"

CircuitSimulator::CircuitSimulator() {
    sAppName = "Simple Circuit Managing System";
}

bool CircuitSimulator::OnUserCreate() {
    currentState = AppState::MENU;
    InitializeMenuState();
    return true;
}

bool CircuitSimulator::OnUserUpdate(float fElapsedTime) {
    Clear(olc::BLACK);

    switch (currentState) {
    case AppState::MENU:
        if (!HandleMenuState()) {  // If HandleMenuState() returns false, exit the app
            return false;  // Exit the app
        }
        break;
        if (GetKey(olc::Key::ENTER).bPressed) {
            switch (menu.GetSelectedOption()) {
            case 0:
                currentState = AppState::CREDIT;
                break;
            case 1:
                currentState = AppState::SIMULATION;
                break;
            case 2:
                currentState = AppState::VOLTAGE_DIVIDER;
                break;
            case 3:
                currentState = AppState::SERIES_PARALLEL;
                break;
            case 4: //exit
                return false;
            }
        }
        break;
    case AppState::CREDIT:
        HandleCreditState();
        break;
    case AppState::SIMULATION:
        AddText(5, 10, "This feature is not ready", olc::WHITE);
        AddText(5, 50, "Press ESC to go back to menu", olc::DARK_BLUE);
        if (GetKey(olc::Key::ESCAPE).bPressed) {
            currentState = AppState::MENU;
        }
        break;

    case AppState::VOLTAGE_DIVIDER:
        HandleVoltageDividerState();
        break;

    case AppState::SERIES_PARALLEL:
        //AddText(5, 10, "Testing entering right state", olc::WHITE);
        HandleSeriesParallelState(); 
        break;
    }

    return true;
}

//MENU=========
void CircuitSimulator::InitializeMenuState() {
    menu.AddOption("Welcome to SCMS", { 5, 10 });

    menu.AddOption("1. Circuit Simulation", { 20, 30 });
    menu.AddOption("2. Voltage Divider", { 20, 50 });
    menu.AddOption("3. Series/Parallel Resistor", { 20, 70 });
    menu.AddOption("4. Exit", { 20, 90 });
}

bool CircuitSimulator::HandleMenuState() {
    menu.HandleInput(this);
    menu.Draw(this);

    if (GetKey(olc::Key::ENTER).bPressed) {
        switch (menu.GetSelectedOption()) {
        case 0: currentState = AppState::CREDIT; break;
        case 1: currentState = AppState::SIMULATION; break;
        case 2: currentState = AppState::VOLTAGE_DIVIDER; break;
        case 3: currentState = AppState::SERIES_PARALLEL; break;
        case 4: return false;  // Exit the app
        }
    }
    return true;
}
//CREDIT======
void CircuitSimulator::InitializeCreditState() {
    // Add CREDIT 
    AddText(5, 10, "Simple Circuit Managing System", olc::WHITE);
    AddText(20, 30, "OOP Project - ECE2023", olc::WHITE);
    AddText(20, 50, "Dang Minh Truc - 10223106", olc::WHITE);
    AddText(20, 70, "Tran Dinh Hoang Quan - 10223098", olc::WHITE);
    AddText(20, 90, "Le Nguyen Minh Thi - 17115", olc::WHITE);
    AddText(5, 110, "Press ESC to go back to menu", olc::DARK_BLUE); 
}
void CircuitSimulator::HandleCreditState() {
    InitializeCreditState();
    if (GetKey(olc::Key::ESCAPE).bPressed) {
        currentState = AppState::MENU;
    }
}
//VOLTAGE DIVIDER =====
void CircuitSimulator::InitializeVoltageDividerState() {
    //AddText(10, 50, "2 Testing entering right state", olc::WHITE);
    AddText(10, 10, "Voltage Divider State Initialized", olc::WHITE);
    
}
 
void CircuitSimulator::HandleVoltageDividerState() {
    //InitializeVoltageDividerState();
    static bool isInitialized = false;
    static bool isInputComplete1 = false; //add R1
    static bool isInputComplete2 = false; //add R2
    static bool isInputComplete3 = false; //add Vin

    static bool screenNeedsRefresh = true; // Flag to determine if screen needs refreshing

    static bool resultsDisplayed = false; // Ensure results are displayed only once 
    static std::vector<std::string> displayedLines; // Store all displayed lines 
    // Initialize once when entering the state
    if (!isInitialized) {
      
        resistor1Input.clear(); //reset input
        resistor2Input.clear(); 
        VoltageInput.clear(); 
        isInitialized = true; 
        isInputComplete1 = isInputComplete2 = isInputComplete3 = false; 
        screenNeedsRefresh = true;  // Mark that we need to clear the screen 
        resultsDisplayed = false; 
        displayedLines.clear(); 
        return;
    } 
    if (screenNeedsRefresh) {
        Clear(olc::BLACK);  // Clear screen only when necessary
        screenNeedsRefresh = false; // Reset the flag after clearing
    } 

    float y = 10; // Initial vertical position for text
    // Render all previous lines
    for (const auto& line : displayedLines) {
        AddText(10, y, line, olc::WHITE);
        y += 10; // Move to the next line
    } 

    // Handle Resistor 1 Input
    if (!isInputComplete1) {
        if (HandleNumericInput("Resistor 1 Value (Ohms):", resistor1Input, y)) {
            isInputComplete1 = true;
            displayedLines.push_back("Resistor 1 Value (Ohms): " + resistor1Input); // Add to history
        }
        return;
    }

    // Handle Resistor 2 Input
    if (!isInputComplete2) {
        if (HandleNumericInput("Resistor 2 Value (Ohms):", resistor2Input,y)) { 
            isInputComplete2 = true;
            displayedLines.push_back("Resistor 2 Value (Ohms): " + resistor2Input); // Add to history
        }
        return;
    }

    // Handle Voltage Input
    if (!isInputComplete3) {
        if (HandleNumericInput("Input Voltage (Volts):", VoltageInput,y)) { 
            isInputComplete3 = true;
            displayedLines.push_back("Input Voltage (Volts): " + VoltageInput); // Add to history 
        }
        return;
    }
    // Mark results as displayed to prevent duplication
    if (isInputComplete1 && isInputComplete2 && isInputComplete3 && !resultsDisplayed) { 
        resultsDisplayed = true;
        //VOLTAGE DIVIDER CALCULATION
        resistor1Value = convertToDouble(resistor1Input); // Convert to double
        resistor2Value = convertToDouble(resistor2Input);
        VinValue = convertToDouble(VoltageInput);

        Resistor* resistor1 = new Resistor("R1",resistor1Value);
        Resistor* resistor2 = new Resistor("R2",resistor2Value); 

        VoltageDivider voltageDivider;

        voltageDivider.addComponent(resistor1);
        voltageDivider.addComponent(resistor2);

        VoutValue = voltageDivider.calculateOutputVoltage(VinValue);
        totalResistance = voltageDivider.calculateTotalResistance();

        // Display results - display only once
        displayedLines.push_back("Output Voltage: " + std::to_string(VoutValue) + " V");
        displayedLines.push_back("Total Resistance: " + std::to_string(totalResistance) + " Ohms");
        displayedLines.push_back("Press ESC to go back to menu");

        screenNeedsRefresh = true;  // Mark screen for refresh after calculation 
    }
    
        if (GetKey(olc::Key::ESCAPE).bPressed) {             
            currentState = AppState::MENU;
            isInitialized = false;  // Reset initialization
        }
        //return;
}
//SERIES PARALLEL RESISTOR CIRCUIT
void CircuitSimulator::InitializeSeriesParallelState() {

}
void CircuitSimulator::HandleSeriesParallelState() {
    static bool isInitialized = false;
    static bool isChoiceComplete = false; // To check if user has chosen series or parallel
    static bool isVoltageInputComplete = false; // To check if voltage input is complete
    static bool isResistorCountComplete = false; // To check if number of resistors is complete
    static bool isInputComplete = false; // To check if input for resistors is complete
    static bool resultsDisplayed = false;

    static bool screenNeedsRefresh = true; // Flag to determine if screen needs refreshing 
   
    //for series
    static SeriesCircuit sc; //for series circuit 
    static double inputVoltage = 0.0;
    static int numResistors = 0;
    static int indexResistors = 0;
    static int indexResistors2 = 0;//for print voltage drop
    static int indexResistors3 = 0; //for print power 
    static std::vector<Resistor*> resistors; // Vector to hold resistors
    static std::string resistorInput;
    static vector<double> voltageDrops;
    static vector<double> powerDissipation;
    static std::vector<std::string> displayedLines; // Store all displayed lines 
    //for parallel
    static ParallelCircuit pc; //for parallel circuit 
    static double inputVoltageP = 0.0; 
    static int numResistorsP = 0;  
    static int indexResistorsP = 0;  
    static int indexResistors2P = 0; //for print voltage drop 
    static int indexResistors3P = 0;  //for print power  
    static std::vector<Resistor*> resistorsP;  // Vector to hold resistors 
    static std::string resistorInputP;  
    static vector<double> voltageDropsP; 
    static vector<double> powerDissipationP; 
    static std::vector<std::string> displayedLinesP; // Store all displayed lines 
    
    if (!isInitialized) {
        // Initialize everything for the first time
        isInitialized = true;
        isChoiceComplete = false;
        isVoltageInputComplete = false;
        isResistorCountComplete = false;
        isInputComplete = false;
        screenNeedsRefresh = true;  // Mark that we need to clear the screen  
        resultsDisplayed = false;
        displayedLines.clear();
        return;
    }
    if (screenNeedsRefresh) {
        Clear(olc::BLACK);  // Clear screen only when necessary
        screenNeedsRefresh = false; // Reset the flag after clearing
    }
    float y = 10; // Initial vertical position for text

    // Render all previous lines
    for (const auto& line : displayedLines) {
        AddText(10, y, line, olc::WHITE);
        y += 10; // Move to the next line
    }
    
    // Ask user for series or parallel choice
    if (!isChoiceComplete) {
        AddText(10, y, "Choose the configuration:", olc::WHITE);
        y += 10;
        AddText(10, y, "1. Series", olc::WHITE);
        y += 10;
        AddText(10, y, "2. Parallel", olc::WHITE);
        y += 10;

        if (HandleNumericInput("Enter choice (1 or 2):", choiceInput, y)) {
            isChoiceComplete = true;
            if (choiceInput == "1") {
                displayedLines.push_back("Chosen Configuration: Series");
            }
            else {
                displayedLines.push_back("Chosen Configuration: Parallel");
            }
            return; // Wait until input is complete
        }
        return; // Wait for user input
    }
    // Ask for Input Voltage
    if (!isVoltageInputComplete) {
        if (HandleNumericInput("Enter the input voltage (V):", voltageInput, y)) {
            inputVoltage = convertToDouble(voltageInput);
            inputVoltageP = convertToDouble(voltageInput); 
            isVoltageInputComplete = true;
            displayedLines.push_back("Input Voltage: " + voltageInput + " V");
            return; // Wait until input is complete
        }
        return; // Wait for user input
    }
    // Ask for Number of Resistors
    if (!isResistorCountComplete) {
        if (HandleNumericInput("Enter the number of resistors(<15):", resistorCountInput, y)) {
            // Convert to integer after receiving valid input
            numResistors = convertToInt(resistorCountInput); // Convert string input to integer
            numResistorsP = convertToInt(resistorCountInput); // Convert string input to integer
            //displayedLines.push_back("Input Voltage: " + voltageInput + " V");
            // Check for valid number of resistors (e.g., limit to <15)
            if (numResistors <= 0 || numResistors > 15) {
                displayedLines.push_back("Invalid number of resistors. Please enter a number between 1 and 15.");
                return; // Wait for user input again if invalid
            }
            isResistorCountComplete = true;
            displayedLines.push_back("Number of Resistors: " + resistorCountInput); // Add to displayed lines
            return; // Wait until input is complete
        }
        return; // Wait for user input
    }
    float yP = y;
    for (const auto& line : displayedLinesP) {
        AddText(10, yP, line, olc::WHITE);
        yP += 10; // Move to the next line
    }
    //AddText(10, y + 10, "Choice input =  " + choiceInput + "bool isInputComplete = " + std::to_string(isInputComplete), olc::WHITE);
    //AddText(10, y + 20, "numResitors = " + std::to_string(numResistors), olc::WHITE); 
     
    if (choiceInput == "1" && !isInputComplete && numResistors != indexResistors) {
        //for (int i = 0; i < numResistors; ++i) { 
        //while (true) {
        //std::string resistorInput;
        
        std::string label = "Enter resistance for R";
        label.append(std::to_string(indexResistors + 1));
        label.append(" (Ohms):");
        if (HandleNumericInput(label, resistorInput, y)) {
            try {
                double resistanceValue = convertToDouble(resistorInput);
                if (resistanceValue < 0) {
                    displayedLines.push_back("Invalid resistor value.");
                    //continue;
                }
                //Resistor* newResistor = new Resistor(resistanceValue);
                //resistors.push_back(newResistor);
                sc.addComponent(new Resistor("R" + to_string(++indexResistors), resistanceValue));  
                displayedLines.push_back("R" + std::to_string(indexResistors) + ": " + resistorInput + " Ohms");
                y += 10;
                resistorInput.clear();
                //break;
            }
            catch (...) {
                displayedLines.push_back("Invalid input.");

            }
        }
        
        y += 10;
    //}
    }
    else if (choiceInput == "1" && !isInputComplete && numResistors == indexResistors)
    {
        isInputComplete = true;
        //calculate series circuit
        double totalResistance = sc.calculateTotalResistance();
        displayedLines.push_back("Total Resistance: " + std::to_string(totalResistance) +" Ohms"); 
        y += 10;
        //calculate voltage drops and power  dissipation 
       voltageDrops = sc.calculateVoltageDrops(inputVoltage);
       powerDissipation = sc.calculatePowerDissipation(inputVoltage);
       voltageDrops.resize(numResistors);
       powerDissipation.resize(numResistors); 
       displayedLines.push_back("Voltage Drops per resistor:");
        y += 10; 
        
        

    } else if (choiceInput == "1" && numResistors != indexResistors2) {
        //cout << "R" << i + 1 << ": " << voltageDrops[i] << " V\n"; 
        if (indexResistors2 < voltageDrops.size()) {
            displayedLines.push_back("R" + std::to_string(indexResistors2 + 1) + ": " + std::to_string(voltageDrops[indexResistors2]) + " Volt");
        }
        y += 10;
        indexResistors2++;
        if (numResistors == indexResistors2) {
            displayedLines.push_back("Power Dissipation per resistor:");
            y += 10;
        }
    }
    else if (choiceInput == "1" &&  numResistors != indexResistors3) {
        //cout << "R" << i + 1 << ": " << powerDissipation[i] << " W\n";
        if (indexResistors3 < powerDissipation.size()) {
            displayedLines.push_back("R" + std::to_string(indexResistors3 + 1) + ": " + std::to_string(powerDissipation[indexResistors3]) + " Watt");
        }
        y += 10;
        indexResistors3++;
        if (numResistors == indexResistors3) {
            displayedLines.push_back("Press ESC to Escape");
            //y += 10;
        }
        
    }//PARALLEL CIRCUIT
    else if (choiceInput == "2" && !isInputComplete && numResistorsP!= indexResistorsP ) {

        std::string labelP = "Enter resistance for R";
        labelP.append(std::to_string(indexResistorsP + 1));
        labelP.append(" (Ohms):");
        if (HandleNumericInput(labelP, resistorInputP, yP)) {
            try {
                double resistanceValueP = convertToDouble(resistorInputP); 
                if (resistanceValueP < 0) { 
                    displayedLinesP.push_back("Invalid resistor value."); 
                    //continue;
                }
                
                pc.addComponent(new Resistor("R" + to_string(++indexResistorsP), resistanceValueP));  
                displayedLinesP.push_back("R" + std::to_string(indexResistorsP) + ": " + resistorInputP + " Ohms"); 
                yP += 10; 
                resistorInputP.clear();
                //break;
            }
            catch (...) {
                displayedLinesP.push_back("Invalid input."); 

            }
        }

        yP += 10;
        //}
    }
    else if (choiceInput == "2" && !isInputComplete && numResistorsP == indexResistorsP)
    {
        isInputComplete = true;
        //calculate series circuit
        double totalResistanceP = pc.calculateTotalResistance(); 
        displayedLinesP.push_back("Total Resistance: " + std::to_string(totalResistanceP) + " Ohms"); 
        yP += 10;
        //calculate voltage drops and power  dissipation 
        voltageDropsP = pc.calculateVoltageDrops(inputVoltageP); 
        powerDissipationP = pc.calculatePowerDissipation(inputVoltageP); 
        voltageDropsP.resize(numResistorsP); 
        powerDissipationP.resize(numResistorsP); 
        displayedLinesP.push_back("Voltage Drops per resistor:");  
        yP += 10;

    }
    else if (numResistorsP != indexResistors2P) {
        //cout << "R" << i + 1 << ": " << voltageDrops[i] << " V\n"; 
        if (indexResistors2P < voltageDropsP.size()) {
            displayedLinesP.push_back("R" + std::to_string(indexResistors2P + 1) + ": " + std::to_string(voltageDropsP[indexResistors2P]) + " Volt");
        }  
        yP += 10;
        indexResistors2P++; 
        if (numResistorsP == indexResistors2P) {   
            displayedLinesP.push_back("Power Dissipation per resistor:");
            yP += 10;
        }
    }
    else if (numResistorsP != indexResistors3P) {  
        //cout << "R" << i + 1 << ": " << powerDissipation[i] << " W\n";
        if (indexResistors3P < powerDissipationP.size()) {
            displayedLinesP.push_back("R" + std::to_string(indexResistors3P + 1) + ": " + std::to_string(powerDissipationP[indexResistors3P]) + " Watt");
        }
        yP += 10;
        indexResistors3P++;
        if (numResistorsP == indexResistors3P) { 
            displayedLinesP.push_back("Press ESC to Escape");
            //y += 10;
        }
    }
     
    if (GetKey(olc::Key::ESCAPE).bPressed) { 
        currentState = AppState::MENU;
        //isInitialized = false;  // Reset initialization 

    }
    //return;
}
//CONVERTO STRING TO INT=======
int CircuitSimulator::convertToInt(const std::string& input) {
    try {
        return std::stoi(input);  // Convert to integer
    }
    catch (const std::invalid_argument& e) {
        // Handle invalid argument
        return 0;  // Return 0 in case of invalid input
    }
    catch (const std::out_of_range& e) {
        // Handle out of range exception
        return 0;  // Return 0 in case of out-of-range input
    }
}
//CONVERT STRING TO DOUBLE======
double CircuitSimulator::convertToDouble(const std::string& input) {
    try {
        return std::stod(input);  // Convert to double
    }
    catch (const std::invalid_argument& e) {
        // Handle invalid argument
        return 0.0;  // Return 0.0 in case of invalid input
    }
    catch (const std::out_of_range& e) {
        // Handle out of range exception
        return 0.0;  // Return 0.0 in case of out-of-range input
    }
}
//HANDLE INPUT METHOD=======
bool CircuitSimulator::HandleNumericInput(const std::string& prompt, std::string& input, float y) {
    AddText(10.0f, y, prompt + " " + input, olc::WHITE); // Position prompt dynamically

    if (GetKey(olc::Key::BACK).bPressed && !input.empty()) {
        input.pop_back(); // Remove the last character if BACKSPACE is pressed
    }

    if (GetKey(olc::Key::K0).bPressed || GetKey(olc::Key::NP0).bPressed) 
        input += '0';
    if (GetKey(olc::Key::K1).bPressed || GetKey(olc::Key::NP1).bPressed) 
        input += '1';
    if (GetKey(olc::Key::K2).bPressed || GetKey(olc::Key::NP2).bPressed) 
        input += '2';
    if (GetKey(olc::Key::K3).bPressed || GetKey(olc::Key::NP3).bPressed) 
        input += '3';
    if (GetKey(olc::Key::K4).bPressed || GetKey(olc::Key::NP4).bPressed) 
        input += '4';
    if (GetKey(olc::Key::K5).bPressed || GetKey(olc::Key::NP5).bPressed) 
        input += '5';
    if (GetKey(olc::Key::K6).bPressed || GetKey(olc::Key::NP6).bPressed) 
        input += '6';
    if (GetKey(olc::Key::K7).bPressed || GetKey(olc::Key::NP7).bPressed) 
        input += '7';
    if (GetKey(olc::Key::K8).bPressed || GetKey(olc::Key::NP8).bPressed) 
        input += '8';
    if (GetKey(olc::Key::K9).bPressed || GetKey(olc::Key::NP9).bPressed) 
        input += '9';

    if (GetKey(olc::Key::PERIOD).bPressed && input.find('.') == std::string::npos) {
        input += '.';
    }

    if (GetKey(olc::Key::ENTER).bPressed && !input.empty()) {
        return true; // Input is complete
    }

    return false; // Continue handling input
} 
//FOR LAYOUT ==========
void CircuitSimulator::AddText(float x, float y, const std::string& text, olc::Pixel color) {
    float scale = 0.6f; // Adjust this value to make text smaller
    DrawStringDecal({ x, y }, text, color, { scale, scale }); // Scale text by 0.5 
}
