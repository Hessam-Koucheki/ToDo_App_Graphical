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
    std::string input = "", tmp = ""; 

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
            // Handle ASCII characters only Except Enter:13 & Backsapce:8 
            if (event.text.unicode <= 128 && event.text.unicode != 8 && event.text.unicode != 13){
                input += event.text.unicode;
                text.setString(input);
                cout << "got input!" << endl;
            } 
            // Handling Enter
            if ( event.text.unicode == 13 ) 
                cout << "enter!!" << endl;
            // Handling Backsapce
            if ( event.text.unicode == 8 ){
                cout << "Backspaceeee" << endl;
                // input.erase(input.end());
                text.setString(tmp);
                input = tmp;
                cout << "Backspace" << endl;
            }
        } // TODO : Add Star Icon to favourite 
    }


    sf::Font font;
    sf::Color color;
    font.loadFromFile("../assets/fonts/Poppins-Regular.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(22);
    text.setPosition(sf::Vector2f(80, 160));
    box.clear();
    box.draw(back_sprite);
    tmp = input.substr(0, input.length() - 1);// Keeping Last input for usage in backsapce
    box.draw(text);
    box.display();
  }
}