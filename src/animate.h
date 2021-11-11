

#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "system.h"
#include "sidebar.h"
class animate{
public:
    animate();  //constructor

    void run();
    void processEvents();
    void update();
    void render();
    void Draw();


private:
    sf::RenderWindow window;
    System system;                      //container for all the animated objects
    sf::Font font;                      //font to draw on main screen
    sf::Text myTextLabel;               //text to draw on main screen
    Sidebar sidebar;                    //rectangular message sidebar

    //options in the menu
    sf::RectangleShape menu;
    sf::RectangleShape menu0;
    sf::RectangleShape menu1;
    sf::RectangleShape menu2;
    sf::RectangleShape menu3;
    sf::RectangleShape menu4;
    sf::RectangleShape menu5;
    sf::RectangleShape menu6;
    sf::RectangleShape menu7;
    sf::RectangleShape menu8;
    sf::RectangleShape menu9;
    sf::RectangleShape menu10;
    sf::RectangleShape menu11;
    sf::RectangleShape selected_rect;   //selected rectangle (dragged)

    int command;                          //command to send to system
    bool drag;                            //draw rectangle if drag is true
    bool keep;                            //draw rectangle if keep is true
    int start_row_y;                      //row of mouse pressed point
    int start_col_x;                      //column of mouse released point
    int end_row_y;                        //row of mouse pressed point
    int end_col_x;                        //column of mouse released point
    int moving_row_y;                     //row of mouse moving point
    int moving_col_x;                     //column of mouse moiving point
    int x;                                //coordinate x
    int y;                                //coordinate y
};


#endif // GAME_H
