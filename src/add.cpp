#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "add.hpp"
using std::cout;
using std::endl;

void add()
{
    sf::RenderWindow box(sf::VideoMode(1000, 300), "Type Something", sf::Style::Close);
    // Add a Background
    sf::Texture back_texture;
    if (!back_texture.loadFromFile("../assets/images/add_text.png"))
        std::cout << "Error On Loading BackGround Image" << std::endl;
    sf::Sprite back_sprite;
    back_sprite.setTexture(back_texture);
    // End Of Adding Background
    // Add Star Icon
    sf::Texture star_texture, star_texture_hovered, star_texture_hovered_true;
    if (!star_texture.loadFromFile("../assets/icons/star-off.png"))
        std::cout << "Error On Loading Star Icon" << std::endl;
    if (!star_texture_hovered.loadFromFile("../assets/icons/star-hover.png"))
        std::cout << "Error On Loading Star-hover Icon" << std::endl;
    if (!star_texture_hovered_true.loadFromFile("../assets/icons/star-hover-true.png"))
        std::cout << "Error On Loading Star-hover-true Icon" << std::endl;
    sf::Sprite star_sprite;
    star_sprite.setTexture(star_texture);
    bool is_favourite = false;
    // End of Adding Star Icon

    std::string input = "", tmp = "";
    sf::Text text;

    // Main Loop
    while (box.isOpen())
    {
        box.requestFocus();
        sf::Event event;
        std::string str;
        while (box.pollEvent(event))
        {
            if (event.type == sf::Event::EventType::Closed)
                box.close();
            if (event.type == sf::Event::TextEntered)
            { // Handle ASCII characters only Except Enter:13 & Backsapce:8
                if (event.text.unicode <= 128 && event.text.unicode != 8 && event.text.unicode != 13)
                {
                    input += event.text.unicode;
                    text.setString(input);
                    cout << "got input!" << endl;
                }
                // Handling Enter
                if (event.text.unicode == 13)
                {
                    cout << "enter!!" << endl;
                }
                // Handling Backsapce
                if (event.text.unicode == 8)
                {
                    text.setString(tmp);
                    input = tmp;
                    // cout << "Backspace" << endl;
                }
            }
            // Star Icon : HOVER
            if (event.type == sf::Event::MouseMoved)
            {   // Hover But not already favourite
                if (star_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))
                    && is_favourite == false)
                {
                    star_sprite.setTexture(star_texture_hovered);
                }
                // Hover But already is favourite
                else if (star_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))
                    && is_favourite == true)
                {
                    star_sprite.setTexture(star_texture_hovered_true);
                }
                // Not Hovered
                else 
                    star_sprite.setTexture(star_texture);
            }
            // Star icon : Click
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {   // Make Favourite
                    if (star_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))
                        && is_favourite == false)
                    {
                        star_texture.loadFromFile("../assets/icons/star-on.png");
                        is_favourite = true;
                        cout << "Favourite!!" << endl;
                    }
                    // Delete Favourite
                    else if (star_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))
                        && is_favourite == true)
                    {
                        star_texture.loadFromFile("../assets/icons/star-off.png");
                        is_favourite = false;
                        cout << "UnFavourite!!" << endl;
                    }
                }
            }
        }
        // Prepairing Text
        sf::Font font;
        sf::Color color;
        font.loadFromFile("../assets/fonts/Poppins-Regular.ttf");
        text.setFont(font);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(22);
        text.setPosition(sf::Vector2f(80, 160));
        tmp = input.substr(0, input.length() - 1); // Keeping Last input for usage in backsapce
        // End of Prepairing Text
        // Prepairing Star Icon
        star_sprite.setPosition(885, 140);
        // End of Prepairing Star Icon

        box.clear();
        box.draw(back_sprite);
        box.draw(star_sprite);
        box.draw(text);
        box.display();
    }
}