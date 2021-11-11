#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <constants.h>




using namespace std;
class System
{
public:
    System();
    void drawCells(sf::RenderWindow& window,sf::RectangleShape cells, int intBox[][MAX]);
    void Draw(sf::RenderWindow& widnow);
    void Step(int command, int TLx, int start_col_x, int BRx, int BRy);
    void getCoordinates(int row, int col, int &x, int &y);
    void getArray(int x, int y, int &row, int &col);
    bool InRange(int mouseX, int mouseY);

private:
    sf::RectangleShape cells;   //rectangles = cells to be draw
    int intBox[MAX][MAX];       //2d array will be used for drawing cells
    char save_pattern[MAX_FN] = "pattern.txt";        //file name
    char usersPattern[MAX_FN] = "users_pattern.txt";  //file name
    bool pause;                 //if true, pause the moving cells
    int x;                      //x coordinate
    int y;                      //y coordinate

};

#endif // SYSTEM_H
