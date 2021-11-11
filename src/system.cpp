#include "system.h"
#include "random.h"
#include "animate.h"
#include <iostream>
#include "../../!Include/gameoflife/gameoflife.h"
#include <constants.h>

System::System()
{
    //initializing
    clear(intBox);
    pause = false;
    x = 0;
    y = 0;

}

void System::Step(int command, int start_row_y, int start_col_x, int end_row_y, int end_col_x){
    /*
     * Function: Step
     * arguments: command, start_row_y_y, start_col, end_row_y, end_col_x
     * returns: nothing
     * purpose: get a command and call several functions
     */
    pause=true;

    if(command == 10){                      //menu0 - Blinker
        blinker_initialization(intBox);
    }
    if (command == 11){                     //menu1 - Glider
        glider_initialization(intBox);
    }
    if(command == 12){                      //menu2 - Play
        pause = false;
    }
    if(command == 13){                      //menu3 - Pause
        pause = true;
    }
    if(command ==14){                       //menu4 - Clear
        clear(intBox);
    }
    if(command == 15){                      //menu5 - Save
        write(save_pattern,intBox);
    }
    if(command == 16){                       //menu6 - Load
        read_file(save_pattern,intBox);
    }
    if(command == 17){                       //menu7 - Random
        random(intBox);
    }

    if(start_row_y >= 0 && start_col_x >= 0 && end_col_x < MAX && end_row_y < MAX ){

        if(command == 18){                   //menu8 - Save pattern
            write_newbox(usersPattern,intBox,start_row_y,start_col_x,end_row_y,end_col_x);
        }

        if(command == 19){                   //menu9 - load pattern
            read_file_newBox(usersPattern,intBox,start_row_y,start_col_x,end_row_y,end_col_x);
        }
        if(command == 20){                   //menu10 - kill
            intBox[start_row_y][start_col_x]=0;
        }
        if(command == 21){                   //menu9 - bring to life
            intBox[start_row_y][start_col_x]=1;
        }

    }

    if (!pause){        //if command 10, keep calling step function
        step(intBox);
    }

}


void System::Draw(sf::RenderWindow& window){
    /*
     * Function: Draw
     * arguments: window
     * returns: nothing
     * purpose: draw on the window
     */

    window.clear();
    drawCells(window,cells,intBox);

}
void System::drawCells(sf::RenderWindow& window,sf::RectangleShape cells, int intBox[][MAX]){
    /*
     * Function: drawCells
     * arguments: window, cells, intBox
     * returns: nothing
     * purpose: draw cells on the window
     */


    int x;
    int y;

    for(int row=0; row<MAX; row++){
        for(int col=0; col<MAX; col++){

            cells.setSize(sf::Vector2f(CELLSIZE,CELLSIZE));
            getCoordinates(row,col,x,y);
            cells.setPosition(sf::Vector2f(x,y));                //set position at starting point
            cells.setOutlineColor(sf::Color(150, 50, 250));
            cells.setOutlineThickness(0.8);

            if(intBox[row][col]==1){                            //alive cell
                cells.setFillColor(sf::Color::Yellow);          //set color as yellow
                cells.setOutlineColor(sf::Color(150, 50, 250));
            }
            else                                                //dead cell
                cells.setFillColor(sf::Color::Black);           //set color as black

            window.draw(cells);
        }
    }
}



void System::getCoordinates(int row, int col, int& x, int& y){
    /*
     * Function: getCoordinates
     * arguments: row, col, x , y
     * returns: nothing
     * purpose: get row and col, give coordinates x,y
     */

    x=0;
    y=0;

    //set size depending on CELLSIZE
    x=col*CELLSIZE;
    y=row*CELLSIZE;

}

void System::getArray(int x, int y, int& row, int& col){
    /*
     * Function: getCoordinates
     * arguments: row, col, x , y
     * returns: nothing
     * purpose: get coordinates x,y and give row and col
     */

    row=0;
    col=0;

    col = x/CELLSIZE;
    row = y/CELLSIZE;

}
bool System::InRange(int mouseX, int mouseY){
    /*
     * Function: InRange
     * arguments: mouseX, mouseY
     * returns: true or false
     * purpose: if they are in the range return true,
     *          otherwise false
     */


    //if its in the range
    if(mouseX>SCREEN_HEIGHT-1 || mouseX<0 || mouseY<0|| mouseY>SCREEN_HEIGHT-1)
        return false;
    else
        return true;

}



