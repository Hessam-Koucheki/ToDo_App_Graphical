#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "read_file.hpp"
#include "app.hpp"
#include "add.hpp"
#include "task.hpp"
#include "write_file.hpp"

#define TASKS_CAPACITY 44
#define add_icon_x 1492
#define add_icon_y 835
#define window_x 1614
#define window_y 960
#define character_size 24

using namespace std;

void start_app()
{
    string input = "";
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "To Do Lists", sf::Style::Close); //size:  (9  in  16)  * 60

    // Add a Background
    sf::Texture back_texture;
    if (!back_texture.loadFromFile("../assets/images/back.png"))
        cout << "Error On Loading BackGround Image" << endl;
    sf::Sprite back_sprite;
    back_sprite.setTexture(back_texture);
    // End Of Adding Background

    // Add ADD-Icon
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
    // Add favorite.png
    sf::Texture favorite_texture;
    if (!favorite_texture.loadFromFile("../assets/icons/favorite.png"))
        cerr << "Error On Loading favorite Icon" << endl;
    sf::Sprite favorite_sprite[TASKS_CAPACITY];
    // Add favorite_no.png
    sf::Texture favorite_no_texture;
    if (!favorite_no_texture.loadFromFile("../assets/icons/favorite-no.png"))
        cerr << "Error On Loading favorite_no Icon" << endl;
    // Add edit.png
    sf::Texture edit_texture;
    if (!edit_texture.loadFromFile("../assets/icons/edit.png"))
        cerr << "Error On Loading edit Icon" << endl;
    sf::Sprite edit_sprite[TASKS_CAPACITY];
    // Add delete Button
    sf::Texture delete_texture, delete_texture_hovered;
    if (!delete_texture.loadFromFile("../assets/icons/delete.png"))
        cout << "Error On Loading delete Icon" << endl;
    if (!delete_texture_hovered.loadFromFile("../assets/icons/delete-hover.png"))
        cout << "Error On Loading delete-hover Icon" << endl;
    sf::Sprite delete_sprite[TASKS_CAPACITY];
    // End of Adding delete Button

    // vector to save read contents from file
    vector<Task> my_vec;
    // to display in sfml
    sf::Text task_array[TASKS_CAPACITY];
    sf::Font font;
    sf::Color color;
    font.loadFromFile("../assets/fonts/Poppins-Light.ttf");
    read_file(my_vec);
    size_t mouse_pos;
    // Main Loop
    while (window.isOpen())
    {
        read_file(my_vec);
        // Display Tasks
        for (size_t i = 0; i < my_vec.size(); i++)
        {
            if (i % 2 == 0)
            {
                task_array[i].setFont(font);
                task_array[i].setFillColor(sf::Color::Black);
                task_array[i].setCharacterSize(character_size);
                task_array[i].setPosition(sf::Vector2f(50, 215 + (17 * i)));
                task_array[i].setString(my_vec[i].get_task());
            }
            else
            {
                task_array[i].setFont(font);
                task_array[i].setFillColor(sf::Color::Black);
                task_array[i].setCharacterSize(character_size);
                task_array[i].setPosition(sf::Vector2f(50 + 807, 215 + (17 * (i - 1))));
                task_array[i].setString(my_vec[i].get_task());
            }
        }
        sf::Event event;
        while (window.pollEvent(event))
        { // Close Window    ?? TODO: SAY GOODBYE && style::none
            if (event.type == sf::Event::EventType::Closed)
            {
                write_file(my_vec);
                window.close();
            }
            //  Mouse Moved
            if (event.type == sf::Event::MouseMoved)
            {
                // Add Icon - Hover
                if (add_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                {
                    add_sprite.setTexture(add_texture_hovered);
                }
                else
                    add_sprite.setTexture(add_texture);
                // End Add Icon : Hover
                // Edit Icon & Delete Icon
                for (size_t i = 0; i < my_vec.size(); i++)
                {
                    if (task_array[i].getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)) && my_vec.size() > 0)
                    {
                        if (i % 2 == 0)
                        {
                            edit_sprite[i].setTexture(edit_texture);
                            edit_sprite[i].setPosition(sf::Vector2f(750 + 35, 218 + (17 * i)));
                            mouse_pos = i;
                            delete_sprite[i].setTexture(delete_texture);
                            delete_sprite[i].setPosition(sf::Vector2f(750, 219 + (17 * i)));
                        }
                        else
                        {
                            edit_sprite[i].setTexture(edit_texture);
                            edit_sprite[i].setPosition(sf::Vector2f(740 + 35 + 807, 218 + (17 * (i - 1))));
                            mouse_pos = i;
                            delete_sprite[i].setTexture(delete_texture);
                            delete_sprite[i].setPosition(sf::Vector2f(740 + 807, 219 + (17 * (i - 1))));
                        }
                    }
                } // End Edit Icon & Delete Icon
            }     // End Mouse Moved
            //  ADD-Button :  Mouse CLICK
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Click On Add Icon
                    if (add_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            window.draw(back_sprite);
                            window.draw(add_sprite_clicked);
                            window.display();
                        }
                        if (my_vec.size() < TASKS_CAPACITY)
                        {
                            add(my_vec);
                            cout << "add" << endl;
                        }
                    } // End Click on Add Icon
                    // click on Edit Icon
                    if (edit_sprite[mouse_pos].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            add(my_vec, my_vec[mouse_pos].get_task());
                            write_file(my_vec);
                            cout << "EDIT ICON" << endl;
                        }
                    } // end click on Edit Icon
                    // click on Delete Icon
                    if (delete_sprite[mouse_pos].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            // add(my_vec, my_vec[mouse_pos].get_task());
                            my_vec.erase(my_vec.begin() + mouse_pos);
                            write_file(my_vec);
                            cout << "Delete ICON" << endl;
                        }
                    } // end click on Edit Icon
                    // click on favorite Icon ---> Make it un-Favorite
                    if (favorite_sprite[mouse_pos].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && my_vec[mouse_pos].get_favourite() == true)
                    {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            favorite_sprite[mouse_pos].setTexture(favorite_no_texture);
                            my_vec[mouse_pos].set_favourite(false);
                            write_file(my_vec);
                            cout << "Unfavorite ICON" << endl;
                        }
                    } // end click on favorite Icon
                    // click on favorite-no Icon ---> Make it Favorite
                    else
                    {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            favorite_sprite[mouse_pos].setTexture(favorite_texture);
                            my_vec[mouse_pos].set_favourite(true);
                            write_file(my_vec);
                            cout << "favorite ICON" << endl;
                        }
                    } // end click on favorite Icon
                }
            } // End Mouse CLICK
        }
        window.draw(back_sprite);
        window.draw(add_sprite);
        // Show Favourite Icon
        for (size_t i = 0; i < my_vec.size(); i++)
        {
            // Column 1
            if (i % 2 == 0)
            {
                // Favorite
                if (my_vec[i].get_favourite() == true)
                {
                    favorite_sprite[i].setTexture(favorite_texture);
                    favorite_sprite[i].setPosition(sf::Vector2f(20, 218 + (17 * i)));
                }
                else // no Favorite
                {
                    favorite_sprite[i].setTexture(favorite_no_texture);
                    favorite_sprite[i].setPosition(sf::Vector2f(20, 218 + (17 * i)));
                }
                window.draw(favorite_sprite[i]);
            }
            // Column 2
            else
            {
                // Favorite
                if (my_vec[i].get_favourite() == true)
                {
                    favorite_sprite[i].setTexture(favorite_texture);
                    favorite_sprite[i].setPosition(sf::Vector2f(20 + 807, 218 + (17 * (i - 1))));
                }
                else // no favorite
                {
                    favorite_sprite[i].setTexture(favorite_no_texture);
                    favorite_sprite[i].setPosition(sf::Vector2f(20 + 807, 218 + (17 * (i - 1))));
                }
                window.draw(favorite_sprite[i]);
            }
            // displays all tasks
            window.draw(task_array[i]);
        }
        // display edit and delete icons
        if (my_vec.size() != 0)
        {
            window.draw(edit_sprite[mouse_pos]);
            window.draw(delete_sprite[mouse_pos]);
        }
        window.display();
    }
}