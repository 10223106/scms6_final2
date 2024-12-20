#pragma once
#ifndef MENU_H
#define MENU_H  


#include "olcPixelGameEngine.h"
#include <vector>
#include <string>

using namespace std; 
struct MenuOption {
    string text;
    olc::vf2d position;
    olc::Pixel color;
};

class Menu {
public:
    void AddTitle(const std::string& text, const olc::vf2d& position, olc::Pixel color = olc::WHITE);    
    void AddOption(const std::string& text, const olc::vf2d& position, olc::Pixel color = olc::WHITE);
    void Draw(olc::PixelGameEngine* pge);
    void HandleInput(olc::PixelGameEngine* pge);
    int GetSelectedOption() const;

private:
    vector<MenuOption> titles; 
    vector<MenuOption> options;
    int selectedOption = 0;
};
#endif