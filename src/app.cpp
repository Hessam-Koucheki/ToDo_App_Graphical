#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "app.hpp"

using namespace std;

void start_app()
{
    string input = "";
    sf::RenderWindow window(sf::VideoMode(540, 960), "To Do Lists", sf::Style::Close); //size:  (9  in  16)  * 60
    
    // Add a Background
    sf::Texture back_texture;
    if ( !back_texture.loadFromFile("../assets/images/back.png") )
        cout << "Error On Loading BackGround Image" << endl;
    sf::Sprite back_sprite;
    back_sprite.setTexture(back_texture);
    // End Of Adding Background
    
    // Add an ADD-Icon
    sf::Texture add_texture;
    if( !add_texture.loadFromFile("../assets/icons/AddIcon.png"))
        cerr << "Error On Loading ADD-Icon" << endl;    
    sf::Sprite add_sprite;
    add_sprite.setTexture(add_texture);
    add_sprite.setPosition(sf::Vector2f(376.f, 790.f));
    // no-shaodw & clicked
    sf::Texture add_texture_clicked;
    if( !add_texture_clicked.loadFromFile("../assets/icons/AddIcon-noshadow.png"))
        cerr << "Error On Loading ADD-Icon-noshadow" << endl;    
    sf::Sprite add_sprite_clicked;
    add_sprite_clicked.setTexture(add_texture_clicked);
    add_sprite_clicked.setPosition(sf::Vector2f(376.f, 790.f));

    //End Of Adding ADD-Icon

    // Main Loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::EventType::Closed){
                window.close();
            }
            if (event.type == sf::Event::EventType::TextEntered){
                input += static_cast<char>(event.text.unicode);
                cout << input << endl;
            }

            window.draw(back_sprite);
            window.draw(add_sprite);
            window.display();
        }
    }
}