#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "add.hpp"
using std::cout;
using std::endl;
void add(){
    sf::RenderWindow box(sf::VideoMode(1000, 300), "Type Something", sf::Style::Close);
    // Add a Background
    sf::Texture back_texture;
    if ( !back_texture.loadFromFile("../assets/images/add_text.png") )
        std::cout << "Error On Loading BackGround Image" << std::endl;
    sf::Sprite back_sprite;
    back_sprite.setTexture(back_texture);
    // End Of Adding Background
    std::string input = ""; 

    sf::Text text;
    text.setString("Hello");
// Main Loop
  while( box.isOpen() ){
    box.requestFocus();
    sf::Event event;
    std::string str;
    while (box.pollEvent(event)){
        if (event.type == sf::Event::EventType::Closed)
                box.close();
        if (event.type == sf::Event::TextEntered){
            // Handle ASCII characters only
            if (event.text.unicode <= 128){
                input += event.text.unicode;
                text.setString(input);
                cout << "got input!" << endl;
                if ( event.text.unicode == 13 ) cout << "enter!!" << endl;
            } if ( event.text.unicode == 10 ){
                box.draw(text);
                cout << "Inputing finished" << endl;
            }
        } // TODO : Getting and Drawing Text into the box
    

      
        // if (event.type == sf::Event::TextEntered){
        // }

    }
    sf::Font font;
    font.loadFromFile("../assets/fonts/Poppins-Regular.ttf");
    text.setFont(font);
    // text.setColor(sf::Color::Red);
    sf::Color color;
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(22);
    text.setPosition(sf::Vector2f(80, 160));
    box.clear();
    box.draw(back_sprite);
    box.draw(text);
    box.display();
  }
}