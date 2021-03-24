#include "../include/GSS/Reader.hpp"
#include <cassert>

int main()
{
    GSS::PropertySheet source = GSS::PropertySheet::loadFromFile("properties.gss");
    assert(source.getString("MainToolbar::DropdownMenu::Button::background-color") == "#ffffff");
    assert(source.getInt("MainToolbar::Button::width") == 50);
    assert(source.getInt("MainToolbar::Button::height") == 20);
    return 0;
}
