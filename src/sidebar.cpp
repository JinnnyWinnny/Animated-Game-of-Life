#include <sidebar.h>
#include <constants.h>

Sidebar::Sidebar(float left, float width){

    cout<<"Sidebar CTOR: TOP"<<endl;
    items.reserve(50);

    //set up the sidebar rectangle:
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout<<"Sidebar CTOR: about to load font."<<endl;

    //Load the font from a file in memory
    if (!font.loadFromFile("Roboto-Thin.ttf")){
        cout<<"Sidebar() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }

    cout<<"Sidebar CTOR: loaded font."<<endl;
    cout<<"Sidebar CTOR: Text object initialized."<<endl;

    //set up menu options
    sb_text[0] = sf::Text("BLINKER", font);
    sb_text[1] = sf::Text("GLIDER", font);
    sb_text[2] = sf::Text("PLAY", font);
    sb_text[3] = sf::Text("STOP", font);
    sb_text[4] = sf::Text("CLEAR", font);
    sb_text[5] = sf::Text("SAVE SCREEN", font);
    sb_text[6] = sf::Text("LOAD SCREEN", font);
    sb_text[7] = sf::Text("RANDOM", font);
    sb_text[8] = sf::Text("SAVE PATTERN", font);
    sb_text[9] = sf::Text("LOAD PATTERN", font);
    sb_text[10] = sf::Text("KILL", font);
    sb_text[11] = sf::Text("BRING TO LIFE", font);


    for(int i=0; i<=MAX_SD; i++){
        sb_text[i].setFont(font);
        sb_text[i].setCharacterSize(30);
        sb_text[i].setStyle(sf::Text::Bold);
        sb_text[i].setFillColor(sf::Color::Cyan);
        sb_text[i].setPosition(sf::Vector2f(WORK_PANEL, SCREEN_HEIGHT/(MAX_SD+1)*(i+1)));
    }
}

void Sidebar::draw(sf::RenderWindow& window){
    /*
     * Function: draw
     * arguments: window
     * returns: nothing
     * purpose: draw menu options on the window
     */


    window.draw(rect);
    //drawing menu options
    for(int i=0; i<MAX_SD; i++){
        window.draw(sb_text[i]);

    }

}

