#include <iostream>
#include <string>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "app.hpp"
#include "add.hpp"

using namespace std;

void start_app()
{
    string input = "";
    sf::RenderWindow window(sf::VideoMode(540, 960), "To Do Lists", sf::Style::Close); //size:  (9  in  16)  * 60

    // Add a Background
    sf::Texture back_texture;
    if (!back_texture.loadFromFile("../assets/images/back.png"))
        cout << "Error On Loading BackGround Image" << endl;
    sf::Sprite back_sprite;
    back_sprite.setTexture(back_texture);
    // End Of Adding Background

    // Add ADD-Icon
    int add_icon_x = 420, add_icon_y = 835;
    sf::Texture add_texture;
    if (!add_texture.loadFromFile("../assets/icons/add.png"))
        cerr << "Error On Loading ADD-Icon" << endl;
    sf::Sprite add_sprite;
    add_sprite.setTexture(add_texture);
    add_sprite.setPosition(sf::Vector2f(add_icon_x, add_icon_y));
    // Add add-icon : Hovered
    sf::Texture add_texture_hovered;
    if (!add_texture_hovered.loadFromFile("../assets/icons/add-hover.png"))
        cerr << "Error On Loading Add-hover" << endl;
    sf::Sprite add_sprite_hovered;
    add_sprite_hovered.setTexture(add_texture_hovered);
    add_sprite_hovered.setPosition(sf::Vector2f(add_icon_x, add_icon_y));
    // Add add-icon : Click
    sf::Texture add_texture_clicked;
    if (!add_texture_clicked.loadFromFile("../assets/icons/add-click.png"))
        cerr << "Error On Loading ADD-clicl" << endl;
    sf::Sprite add_sprite_clicked;
    add_sprite_clicked.setTexture(add_texture_clicked);
    add_sprite_clicked.setPosition(sf::Vector2f(add_icon_x, add_icon_y));
    //End Of Adding ADD-Icon
    sf::Text te;
    sf::Font font;
    sf::Color color;
    font.loadFromFile("../assets/fonts/Poppins-Light.ttf");
    te.setFont(font);
    te.setFillColor(sf::Color::Black);
    te.setCharacterSize(22);
    te.setPosition(sf::Vector2f(30, 160));
    te.setString("123456789012345678901234567890");
    // Main Loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        { // Close Window    ?? TODO: SAY GOODBYE && style::none
            if (event.type == sf::Event::EventType::Closed)
            {
                window.close();
            }
            //  ADD-Button :  Mouse HOVER
            if (event.type == sf::Event::MouseMoved)
            {
                if (add_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                {
                    add_sprite.setTexture(add_texture_hovered);
                }
                else
                    add_sprite.setTexture(add_texture);
            } // End Mouse HOVER
            //  ADD-Button :  Mouse CLICK
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (add_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            window.draw(back_sprite);
                            window.draw(add_sprite_clicked);
                            window.display();
                        }
                        cout << "add" << endl;
                        add();
                    }
                }
            } // End Mouse CLICK
        }

        window.draw(back_sprite);
        window.draw(add_sprite);
        window.draw(te);
        window.display();
    }
}