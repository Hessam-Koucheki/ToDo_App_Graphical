#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "add.hpp"
#include "task.hpp"
#include "write_file.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

void add(vector<Task> &vec, string st)
{
    sf::RenderWindow box(sf::VideoMode(1000, 300), "Type Something", sf::Style::None);

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
    string input = st, tmp = st;
    sf::Text text;
    text.setString(st);
    Task task;
    bool is_favourite = false;
    string what_edited = st;

    // Main Loop
    while (box.isOpen())
    {
        box.requestFocus();
        sf::Event event;
        std::string str;
        while (box.pollEvent(event))
        {
            // Hanlding Entering Text
            if (event.type == sf::Event::TextEntered)
            {                                    // Handle ASCII characters only Except Enter:13 & Backsapce:8
                if (event.text.unicode <= 128    // Be an ascii char
                    && event.text.unicode != 8   // Backspace
                    && event.text.unicode != 13  // Enter
                    && event.text.unicode != 59) // semicolon :: used in file handling
                {
                    input += event.text.unicode;
                    text.setString(input);
                    cout << "got input! : " << input << " -> " << input.length() << endl;
                }
                // Handling Enter
                if (event.text.unicode == 13 && input.length() != 0)
                {
                    // search for the current task and replace it
                    for (size_t i = 0; i < vec.size(); i++)
                    {
                        if (what_edited == vec[i].get_task())
                        {
                            task.set_task(input);
                            task.set_favourite(is_favourite);
                            task.set_state(false);
                            vec.erase(vec.begin() + i);
                            vec.insert(vec.begin() + i, task);
                            cout << "Submited!! Edited" << endl;
                            box.close();
                            return;
                        }
                    }
                    task.set_task(input);
                    task.set_favourite(is_favourite);
                    task.set_state(false);
                    vec.push_back(task);
                    cout << "enter!!" << endl;
                    box.close();
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
            { // Hover But not already favourite
                if (star_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)) && is_favourite == false)
                {
                    star_sprite.setTexture(star_texture_hovered);
                }
                // Hover But already is favourite
                else if (star_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)) && is_favourite == true)
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
                { // Make Favourite
                    if (star_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && is_favourite == false)
                    {
                        star_texture.loadFromFile("../assets/icons/star-on.png");
                        is_favourite = true;
                        cout << "Favourite!!" << endl;
                    }
                    // Delete Favourite
                    else if (star_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && is_favourite == true)
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
                    if (submit_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && input.length() != 0)
                    {
                        // search for the current task and replace it
                        for (size_t i = 0; i < vec.size(); i++)
                        {
                            if (what_edited == vec[i].get_task())
                            {
                                task.set_task(input);
                                task.set_favourite(is_favourite);
                                task.set_state(false);
                                vec.erase(vec.begin() + i);
                                vec.insert(vec.begin() + i, task);
                                cout << "Submited!! Edited" << endl;
                                box.close();
                                return;
                            }
                        }
                        /*
                        task.set_task(input);
                        task.set_favourite(is_favourite);
                        task.set_state(false);
                        // vec.erase(vec.begin() + found);
                        // vec.insert(vec.begin() + found, task);
                        vec.push_back(task);
                        cout << "Submited!!" << endl;
                        box.close();*/
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
                        cout << "Task : " << input << endl;
                        write_file(vec);
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