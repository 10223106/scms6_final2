#include "Menu.h"

void Menu::AddOption(const std::string& text, const olc::vf2d& position, olc::Pixel color) {
    options.push_back({ text, position, color });
}

void Menu::Draw(olc::PixelGameEngine* pge) {
    for (size_t i = 0; i < options.size(); i++) {
        olc::Pixel drawColor = (i == selectedOption) ? olc::YELLOW : options[i].color;
        pge->DrawStringDecal(options[i].position, options[i].text, drawColor);
    }
}

void Menu::HandleInput(olc::PixelGameEngine* pge) {
    if (pge->GetKey(olc::Key::UP).bPressed) {
        selectedOption = (selectedOption - 1 + options.size()) % options.size();
    }
    if (pge->GetKey(olc::Key::DOWN).bPressed) {
        selectedOption = (selectedOption + 1) % options.size();
    }
}

int Menu::GetSelectedOption() const {
    return selectedOption;
}
