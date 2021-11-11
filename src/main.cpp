/* Author: Jieun Lee
 * Program: Final Project
 * Purpose: play a game of life
 * Note: Rules of the Game:
 *       A live cell with two or three live neighbors will remain alive
 *       A live cell with fewer than two live neighbors will die
 *       A live cell with more than three live enighmors will die
 *       A dead cell with exactly three live enighbors will become a live cell.
 */

#include <iostream>
#include "animate.h"


using namespace std;

int main()
{

    animate game;
    game.run();
    cout<<endl<<endl<<"------ MAIN EXITING --------------------------"<<endl;
    return 0;
}

