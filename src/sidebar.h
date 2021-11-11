#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <constants.h>
using namespace std;


class Sidebar
{
public:
    Sidebar(float left, float width);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    sf::Font font;                      //used to draw text
    sf::Text sb_text[MAX_SD+1];         //used to draw strings on the window object
};

#endif // SIDEBAR_H
