#include "../include/GSS/Reader.hpp"
#include <cassert>
#include <cmath>

int main()
{
    GSS::PropertySheet source = GSS::PropertySheet::loadFromFile("properties.gss");
    assert(source.getString("MainToolbar::DropdownMenu::Button::background-color") == "#ffffff");
    assert(source.getInt("MainToolbar::Button::width") == 50);
    assert(source.getInt("MainToolbar::Button::height") == 20);

    //Testing for getDouble
    GSS::PropertySheet rpgData = GSS::PropertySheet::loadFromFile("properties.gss");
    double life = rpgData.getDouble("RPG::Hero::life");
    double attack = rpgData.getDouble("RPG::Hero::attack");
    std::cout << life << std::endl;       // Outputs 42,5.
    std::cout << ceil(life) << std::endl; // Outputs 43,0.

    return 0;
}
