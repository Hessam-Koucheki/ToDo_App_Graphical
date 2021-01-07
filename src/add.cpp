#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "add.hpp"
using std::cout;
using std::endl;
using std::string;
void add()
{
    sf::RenderWindow box(sf::VideoMode(1000, 300), "Type Something", sf::Style::Close);
    // Add a Background
    sf::Texture back_texture;
    if (!back_texture.loadFromFile("../assets/images/add_text.png"))
        cout << "Error On Loading BackGround Image" << endl;
    sf::Sprite back_sprite;
    back_sprite.setTexture(back_texture);
    // End Of Adding Background
    // Add Star Icon
    sf::Texture star_texture, star_texture_hovered, star_texture_hovered_true;
    if (!star_texture.loadFromFile("../assets/icons/star-off.png"))
        cout << "Error On Loading Star Icon" << endl;
    if (!star_texture_hovered.loadFromFile("../assets/icons/star-hover.png"))
        cout << "Error On Loading Star-hover Icon" << endl;
    if (!star_texture_hovered_true.loadFromFile("../assets/icons/star-hover-true.png"))
        cout << "Error On Loading Star-hover-true Icon" << endl;
    sf::Sprite star_sprite;
    star_sprite.setTexture(star_texture);
    bool is_favourite = false;
    // End of Adding Star Icon
    // Add Submit Button
    sf::Texture submit_texture, submit_texture_hovered;
    if (!submit_texture.loadFromFile("../assets/icons/submit.png"))
        cout << "Error On Loading submit Icon" << endl;
    if (!submit_texture_hovered.loadFromFile("../assets/icons/submit-hover.png"))
        cout << "Error On Loading submit-hover Icon" << endl;
    sf::Sprite submit_sprite;
    submit_sprite.setTexture(submit_texture);
    // End of Adding Submit Button
    // Add Cancel Button
    sf::Texture cancel_texture, cancel_texture_hovered;
    if (!cancel_texture.loadFromFile("../assets/icons/cancel.png"))
        cout << "Error On Loading cancel Icon" << endl;
    if (!cancel_texture_hovered.loadFromFile("../assets/icons/cancel-hover.png"))
        cout << "Error On Loading cancel-hover Icon" << endl;
    sf::Sprite cancel_sprite;
    cancel_sprite.setTexture(cancel_texture);
    // End of Adding cancel Button
    string input = "", tmp = "";
    sf::Text text;

    // Main Loop
    while (box.isOpen())
    {
        box.requestFocus();
        sf::Event event;
        std::string str;
        while (box.pollEvent(event))
        {   // Proccess Close
            if (event.type == sf::Event::EventType::Closed)
                box.close();
            // Hanlding Entering Text
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
            } // End Of Text Handling 
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
            } // End Star Icon : HOVER

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
            } // End Star icon : Click


            // Submit Icon : HOVER
            if (event.type == sf::Event::MouseMoved)
            {
                if (submit_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                {
                    submit_sprite.setTexture(submit_texture_hovered);
                }
                // Not Hovered
                else 
                    submit_sprite.setTexture(submit_texture);
            } // End Submit : Hover
            // Submit icon : Click
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (submit_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        cout << "Submited!!" << endl;
                        // SAVE
                        box.close();
                    }
                }
            } // End Submit : Click

            // Cancel Icon : HOVER
            if (event.type == sf::Event::MouseMoved)
            {
                if (cancel_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                {
                    cancel_sprite.setTexture(cancel_texture_hovered);
                }
                // Not Hovered
                else 
                    cancel_sprite.setTexture(cancel_texture);
            } // End cancel : Hover
            // cancel icon : Click
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (cancel_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        cout << "cancel!!" << endl;
                        // SAVE
                        box.close();
                    }
                }
            } // End cancel : Click

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
        star_sprite.setPosition(635, 195);
        // End of Prepairing Star Icon
        // Prepairing submit Icon
        submit_sprite.setPosition(500, 200);
        // End of Prepairing submit Icon
        // Prepairing cancel Icon
        cancel_sprite.setPosition(350, 200);
        // End of Prepairing cancel Icon

        box.clear();
        box.draw(back_sprite);
        box.draw(star_sprite);
        box.draw(submit_sprite);
        box.draw(cancel_sprite);
        box.draw(text);
        box.display();
    }
}