#include "animate.h"
#include "constants.h"
#include <iostream>
using namespace std;
#include "system.h"
#include <cstdlib>



animate::animate():sidebar(WORK_PANEL, SIDE_BAR)

{
    cout<<"animate CTOR: TOP"<<endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game of Life!");
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third argumnet to set style
    //of the window: resize, fullscreen etc.

    window.setFramerateLimit(40);   //speed of moving cell
    cout<<"Geme CTOR. preparing to load the font."<<endl;

    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf")){
        cout<<"animate() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    cout<<"animate instantiated successfully."<<endl;

    //Making menu options
    //Set the position by deviding screen height by number of options
    menu0.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu0.setPosition(sf::Vector2f(WORK_PANEL , SCREEN_HEIGHT/(MAX_SD+1)*1));

    menu1.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu1.setPosition(sf::Vector2f(WORK_PANEL , SCREEN_HEIGHT/(MAX_SD+1)*2));

    menu2.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu2.setPosition(sf::Vector2f(WORK_PANEL , SCREEN_HEIGHT/(MAX_SD+1)*3));

    menu3.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu3.setPosition(sf::Vector2f(WORK_PANEL , SCREEN_HEIGHT/(MAX_SD+1)*4));

    menu4.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu4.setPosition(sf::Vector2f(WORK_PANEL , SCREEN_HEIGHT/(MAX_SD+1)*5));

    menu5.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu5.setPosition(sf::Vector2f(WORK_PANEL , SCREEN_HEIGHT/(MAX_SD+1)*6));

    menu6.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu6.setPosition(sf::Vector2f(WORK_PANEL , SCREEN_HEIGHT/(MAX_SD+1)*7));

    menu7.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu7.setPosition(sf::Vector2f(WORK_PANEL , SCREEN_HEIGHT/(MAX_SD+1)*8));

    menu8.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu8.setPosition(sf::Vector2f(WORK_PANEL , SCREEN_HEIGHT/(MAX_SD+1)*9));

    menu9.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu9.setPosition(sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT/(MAX_SD+1)*10));

    menu10.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu10.setPosition(sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT/(MAX_SD+1)*11));

    menu11.setSize(sf::Vector2f(MENU_X,MENU_Y));
    menu11.setPosition(sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT/(MAX_SD+1)*12));


    //initializing variables
    drag = false;
    keep = false;
}

void animate::Draw(){
    /*
     * Function: Draw
     * arguments: nothing
     * returns: nothing
     * purpose: draw on the window
     */

    //Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);            //drawing window
    sidebar.draw(window);           //drawing sidebar
    window.draw(myTextLabel);       //drawing menu options

    if(drag == true || keep == true)
        window.draw(selected_rect); //drawing selected rectangle
}

void animate::update(){
    /*
     * Function: update
     * arguments: nothing
     * returns: nothing
     * purpose: make changes to the data for the next frame
     */

    system.Step(command,start_row_y,start_col_x,end_row_y,end_col_x);   //give parameters from processEvents()
}

void animate::render(){
    /*
     * Function: render
     * arguments: nothing
     * returns: nothing
     * purpose: make change on the window
     */

       window.clear();
       Draw();
       window.display();
}

void animate::processEvents(){
    /*
     * Function: processEvents
     * arguments: nothing
     * returns: nothing
     * purpose: make commands depending on the events
     */

   sf::Event event;
   float mouseX, mouseY;

   if(command == 17){   //for calling random function just one time
       command = 13;    //pause
   }

   while (window.pollEvent(event))//or waitEvent
       {
       // check the type of the event...
           switch (event.type)
           {
           // window closed
           case sf::Event::Closed:
               window.close();
               break;

           // key pressed
           case sf::Event::KeyPressed:

               switch(event.key.code){
               case sf::Keyboard::Enter:
                   //Enter key -> delete selected rectangle
                   drag = false;
                   keep = false;
                   selected_rect.setSize(sf::Vector2f(0,0));
                break;

               case sf::Keyboard::Escape:
                   //ESC -> close window
                  window.close();
                   break;
               }
               break;
            //mouse button pressed
           case sf::Event::MouseButtonPressed:{
               drag = true;
               mouseX = event.mouseButton.x;    //x coordiate of mouse button pressed
               mouseY = event.mouseButton.y;    //y coordiate of mouse button pressed

               //chech is it in the range
               drag = system.InRange(mouseX,mouseY);

               if(drag == true){
                   system.getArray(mouseX,mouseY,start_row_y,start_col_x);          //for getting a starting row,column
                   system.getCoordinates(start_row_y,start_col_x,x,y);           //get coordinates of starting point
                   selected_rect.setPosition(sf::Vector2f(x,y));                //set position at starting point
                   selected_rect.setSize(sf::Vector2f(1*CELLSIZE,1*CELLSIZE));  //set size to CELLSIZE
                   selected_rect.setFillColor(sf::Color::Transparent);          //set color to transparent so that see through
                   selected_rect.setOutlineThickness(1);                        //set thickness to 1
               }

               if(!DEBUG){
                   cout<<"start (row y,col x)"<<start_row_y<<" , "<<start_col_x<<endl;
                   cout<<"mouse button (x,y)"<<mouseX<<" , "<<mouseY<<endl;
               }
           }
               break;

            //mouse moved
           case sf::Event::MouseMoved:
                mouseX = event.mouseMove.x;     //x coordiate of mouse moved
                mouseY = event.mouseMove.y;     //y coordiate of mouse moved

                if(mouseX>SCREEN_HEIGHT || mouseX<0 || mouseY<0|| mouseY>SCREEN_HEIGHT)
                      drag=false;

                if(drag==true){
                    system.getArray(mouseX,mouseY,moving_row_y,moving_col_x);
                    system.getCoordinates(start_row_y,start_col_x,x,y);
                    selected_rect.setSize(sf::Vector2f(((moving_col_x-start_col_x)+1)*CELLSIZE, //x= length of row * CELLSIZE
                                                       (moving_row_y-start_row_y+1)*CELLSIZE)); //y= length of col * CELLSIZE
                    selected_rect.setPosition(sf::Vector2f(x,y));
                    selected_rect.setFillColor(sf::Color::Transparent);
                    selected_rect.setOutlineColor(sf::Color::White);
                    selected_rect.setOutlineThickness(1);
                }

                    if(!DEBUG){
                        cout<<"mouse move(x,y) "<<mouseX<<" , "<<mouseY<<endl;
                        cout<<"moving array(x,y) "<<moving_row_y<<" , "<<moving_col_x<<endl;
                    }
               break;
           //mouse button released
           case sf::Event::MouseButtonReleased:
               drag = false;
               keep = true;
               mouseX = event.mouseButton.x;
               mouseY = event.mouseButton.y;

               //chech is it in the range
               keep = system.InRange(mouseX,mouseY);

               system.getArray(mouseX,mouseY,end_row_y,end_col_x);
               system.getCoordinates(start_row_y,start_col_x,x,y);
               selected_rect.setPosition(sf::Vector2f(x,y));
               selected_rect.setSize(sf::Vector2f((end_col_x-start_col_x+1)*CELLSIZE,(end_row_y-start_row_y+1)*CELLSIZE));
               selected_rect.setFillColor(sf::Color::Transparent);
               selected_rect.setOutlineColor(sf::Color::Cyan);
               selected_rect.setOutlineThickness(1);

               if(!DEBUG){
                   cout<<"end (row,xol)"<<end_row_y<<" , "<<end_col_x<<endl;
                   cout<<"x,y : "<<x<<" , "<<y;
               }

               //make menu option rectangles
               //if get in the range
                if((sf::Mouse::getPosition(window).x > menu0.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu0.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu0.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu0.getPosition().y)+MENU_Y))
               {
                    command = 10;   //passing command
                }
                if((sf::Mouse::getPosition(window).x > menu1.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu1.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu1.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu1.getPosition().y)+MENU_Y))
               {
                    command = 11;
                }
                if((sf::Mouse::getPosition(window).x > menu2.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu2.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu2.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu2.getPosition().y)+MENU_Y))
               {
                    command = 12;
                }
                if((sf::Mouse::getPosition(window).x > menu3.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu3.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu3.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu3.getPosition().y)+MENU_Y))
               {
                    command = 13;
                }
                if((sf::Mouse::getPosition(window).x > menu4.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu4.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu4.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu4.getPosition().y)+MENU_Y))
               {
                    command = 14;
                }
                if((sf::Mouse::getPosition(window).x > menu5.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu5.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu5.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu5.getPosition().y)+MENU_Y))
               {
                    command = 15;
                }
                if((sf::Mouse::getPosition(window).x > menu6.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu6.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu6.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu6.getPosition().y)+MENU_Y))
               {
                    command = 16;
                }
                if((sf::Mouse::getPosition(window).x > menu7.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu7.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu7.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu7.getPosition().y)+MENU_Y))
               {
                    command = 17;
                }
                if((sf::Mouse::getPosition(window).x > menu8.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu8.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu8.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu8.getPosition().y)+MENU_Y))
               {
                    command = 18;
                }
                if((sf::Mouse::getPosition(window).x > menu9.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu9.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu9.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu9.getPosition().y)+MENU_Y))
               {
                    command = 19;
                }
                if((sf::Mouse::getPosition(window).x > menu10.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu10.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu10.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu10.getPosition().y)+MENU_Y))
               {
                    command = 20;
                }
                if((sf::Mouse::getPosition(window).x > menu11.getPosition().x) &&
                        (sf::Mouse::getPosition(window).x < (menu11.getPosition().x)+MENU_X) &&
                        (sf::Mouse::getPosition(window).y > menu11.getPosition().y) &&
                        (sf::Mouse::getPosition(window).y < (menu11.getPosition().y)+MENU_Y))
               {
                    command = 21;
                }


               break;

               default:
                   break;
           }
       }
}

void animate::run(){
    /*
     * Function: run
     * arguments: nothing
     * returns: nothing
     * purpose: get a command, give a command, draw
     */

   while (window.isOpen())
   {
       processEvents(); //get command
       update();        //call functions depending on command
       render();        //clear/draw/display

   }
   cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;

}

