#include "../include/GSS/Reader.hpp"
#include <cassert>
#include <cmath>

int main()
{
    //Testing for loadFromFile
    GSS::PropertyReader source = GSS::PropertyReader::loadFromFile("properties.gss");

    //Testing for getString
    assert(source.getString("MainToolbar::Button::background-color") == "#000000");
    assert(source.getString("MainToolbar::Button::color") == "#ffffff");

    //Testing for getInt
    assert(source.getInt("MainToolbar::Button::width") == 50);
    assert(source.getInt("MainToolbar::Button::height") == 20);

    //Testing for getDouble
    assert(source.getDouble("RPG::Hero::attack") == 38.0);
    assert(source.getDouble("RPG::Hero::life") == 42.5);
    assert(ceil(source.getDouble("RPG::Hero::life")) == 43.0);
}
