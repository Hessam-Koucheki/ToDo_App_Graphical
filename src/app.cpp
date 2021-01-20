#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "read_file.hpp"
#include "app.hpp"
#include "add.hpp"
#include "task.hpp"
#include "write_file.hpp"
#include "move_done_to_end.hpp"

#define TASKS_CAPACITY 36
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
    // Add Full Icon
    sf::Texture full_texture;
    if (!full_texture.loadFromFile("../assets/icons/full.png"))
        cout << "Error On Loading full Icon" << endl;
    sf::Sprite full_sprite;
    // End of Adding delete Button
    // Add all-done button
    sf::Texture all_done_texture, all_done_hover_texture;
    if (!all_done_texture.loadFromFile("../assets/icons/all-done.png"))
        cout << "Error On Loading all_done_texture button" << endl;
    if (!all_done_hover_texture.loadFromFile("../assets/icons/all-done-hover.png"))
        cout << "Error On Loading all_done_hover_texture button" << endl;
    sf::Sprite all_done_sprite;
    all_done_sprite.setTexture(all_done_texture);
    all_done_sprite.setPosition(50 + 240, 840);
    // End of Adding all-done button
    // Add all-undone button
    sf::Texture all_undone_texture, all_undone_hover_texture;
    if (!all_undone_texture.loadFromFile("../assets/icons/all-undone.png"))
        cout << "Error On Loading all_undone_texture button" << endl;
    if (!all_undone_hover_texture.loadFromFile("../assets/icons/all-undone-hover.png"))
        cout << "Error On Loading all_undone_hover_texture button" << endl;
    sf::Sprite all_undone_sprite;
    all_undone_sprite.setTexture(all_undone_texture);
    all_undone_sprite.setPosition(50 + 240, 840 + 60);
    // End of Adding all-done button
    // Add all-fav button
    sf::Texture all_fav_texture, all_fav_hover_texture;
    if (!all_fav_texture.loadFromFile("../assets/icons/all-fav.png"))
        cout << "Error On Loading all_fav_texture button" << endl;
    if (!all_fav_hover_texture.loadFromFile("../assets/icons/all-fav-hover.png"))
        cout << "Error On Loading all_fav_hover_texture button" << endl;
    sf::Sprite all_fav_sprite;
    all_fav_sprite.setTexture(all_fav_texture);
    all_fav_sprite.setPosition(50, 840);
    // End of Adding all-fav button
    // Add all-unfav button
    sf::Texture all_unfav_texture, all_unfav_hover_texture;
    if (!all_unfav_texture.loadFromFile("../assets/icons/all-unfav.png"))
        cout << "Error On Loading all_unfav_texture button" << endl;
    if (!all_unfav_hover_texture.loadFromFile("../assets/icons/all-unfav-hover.png"))
        cout << "Error On Loading all_unfav_hover_texture button" << endl;
    sf::Sprite all_unfav_sprite;
    all_unfav_sprite.setTexture(all_unfav_texture);
    all_unfav_sprite.setTexture(all_unfav_texture);
    all_unfav_sprite.setPosition(50, 840 + 60);
    // End of Adding all-unfav button
    // Add all-del button
    sf::Texture all_del_texture, all_del_hover_texture;
    if (!all_del_texture.loadFromFile("../assets/icons/del-all.png"))
        cout << "Error On Loading del-all-texture button" << endl;
    if (!all_del_hover_texture.loadFromFile("../assets/icons/del-all-hover.png"))
        cout << "Error On Loading del_all_hover_texture button" << endl;
    sf::Sprite all_del_sprite;
    all_del_sprite.setTexture(all_del_texture);
    all_del_sprite.setPosition(50 + 240 + 240, 840 + 60);
    // End of Adding all-unfav button
    // Add done Icon
    sf::Texture done_false_texture, done_true_texture, done_hover_texture;
    if (!done_false_texture.loadFromFile("../assets/icons/done-false.png"))
        cout << "Error On Loading done-false Icon" << endl;
    if (!done_true_texture.loadFromFile("../assets/icons/done-true.png"))
        cout << "Error On Loading done-true Icon" << endl;
    if (!done_hover_texture.loadFromFile("../assets/icons/done-hover.png"))
        cout << "Error On Loading done-hover Icon" << endl;
    sf::Sprite done_sprite[TASKS_CAPACITY];
    // End of Adding done Button
    // Adding Some Sounds But they Didn't Work...
    /*
    sf::SoundBuffer submit_cancel_edit_buffer ;
    if (!submit_cancel_edit_buffer.loadFromFile("../assets/sounds/fav.wav"))
        cout << "Error On Loading submit_cancel_edit sound!!!!" << endl;
    sf::Sound submit_cancel_edit;
    submit_cancel_edit.setBuffer(submit_cancel_edit_buffer);
    submit_cancel_edit.play();
    */

    // vector to save read contents from file
    vector<Task> my_vec;
    // to display in sfml
    sf::Text task_array[TASKS_CAPACITY];
    sf::Font font;
    sf::Color color;
    font.loadFromFile("../assets/fonts/Poppins-Light.ttf");
    read_file(my_vec);
    size_t mouse_pos = -1;
    bool something_changed = true;
    ///////////////////////////////////////////////////////////////////
    //////////////////////////Optimization/////////////////////////////
    ///////////////////////////////////////////////////////////////////
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

    // Main Loop
    while (window.isOpen())
    {
        read_file(my_vec);
        move_done_to_end(my_vec);
        // Display Tasks
        if (something_changed == true) // Optimizations
        {
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
            something_changed = false;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close Window
            if (event.type == sf::Event::EventType::Closed)
            {
                write_file(my_vec);
                window.close();
            }
            //  Mouse Moved
            if (event.type == sf::Event::MouseMoved)
            {
                // Check as Done - Icon : Hover
                if (done_sprite[mouse_pos].getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                {
                    done_sprite[mouse_pos].setTexture(done_hover_texture);
                }
                // End  Check as Done - Icon : Hover
                // Done All - Hover
                if (all_done_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                    all_done_sprite.setTexture(all_done_hover_texture);
                else
                    all_done_sprite.setTexture(all_done_texture);
                // End Done All : Hover
                // unDone All - Hover
                if (all_undone_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                    all_undone_sprite.setTexture(all_undone_hover_texture);
                else
                    all_undone_sprite.setTexture(all_undone_texture);
                // End unDone All : Hover
                // fav All - Hover
                if (all_fav_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                    all_fav_sprite.setTexture(all_fav_hover_texture);
                else
                    all_fav_sprite.setTexture(all_fav_texture);
                // End fav All : Hover
                // unfav All - Hover
                if (all_unfav_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                    all_unfav_sprite.setTexture(all_unfav_hover_texture);
                else
                    all_unfav_sprite.setTexture(all_unfav_texture);
                // End unfav All : Hover
                // del All - Hover
                if (all_del_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                    all_del_sprite.setTexture(all_del_hover_texture);
                else
                    all_del_sprite.setTexture(all_del_texture);
                // End del All : Hover
                // Add Icon - Hover
                if (add_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
                    add_sprite.setTexture(add_texture_hovered);
                else
                    add_sprite.setTexture(add_texture);
                // End Add Icon : Hover
                // Edit Icon & Delete Icon

                for (size_t i = 0; i < my_vec.size(); i++)
                {
                    if (task_array[i].getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)) && my_vec.size() > 0)
                    {
                        // Column 1
                        if (i % 2 == 0)
                        {
                            edit_sprite[i].setTexture(edit_texture);
                            edit_sprite[i].setPosition(sf::Vector2f(750 + 35, 218 + (17 * i)));
                            mouse_pos = i;
                            delete_sprite[i].setTexture(delete_texture);
                            delete_sprite[i].setPosition(sf::Vector2f(758, 219 + (17 * i)));
                            task_array[i].setStyle(sf::Text::Bold);
                        }
                        else // Column 2
                        {
                            edit_sprite[i].setTexture(edit_texture);
                            edit_sprite[i].setPosition(sf::Vector2f(740 + 35 + 807, 218 + (17 * (i - 1))));
                            mouse_pos = i;
                            delete_sprite[i].setTexture(delete_texture);
                            delete_sprite[i].setPosition(sf::Vector2f(748 + 807, 219 + (17 * (i - 1))));
                            task_array[i].setStyle(sf::Text::Bold);
                        }
                    }
                    else
                    {
                        task_array[i].setStyle(sf::Text::Regular);
                    }
                    // End Edit Icon & Delete Icon
                }
            } // End Mouse Moved
            // Mouse CLICK
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Buttons
                    // click on Delete-ALL button
                    if (all_del_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        while (!my_vec.empty())
                        {
                            my_vec.pop_back();
                        }
                        write_file(my_vec);
                        cout << "Delete All " << endl;
                    } // end click on Delete All button
                    // click on all-done button
                    if (all_done_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        for (auto &it : my_vec)
                        {
                            it.set_state(true);
                        }
                        write_file(my_vec);
                        cout << "All Done " << endl;
                    } // end click on all-done button
                    // click on all-undone button
                    if (all_undone_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        for (auto &it : my_vec)
                        {
                            it.set_state(false);
                        }
                        write_file(my_vec);
                        cout << "All unDone " << endl;
                    } // end click on all-undone button
                    // click on all-fav button
                    if (all_fav_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        for (auto &it : my_vec)
                        {
                            it.set_favourite(true);
                        }
                        write_file(my_vec);
                        cout << "All fav " << endl;
                    } // end click on all-fav button
                    // click on all-unfav button
                    if (all_unfav_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        for (auto &it : my_vec)
                        {
                            it.set_favourite(false);
                        }
                        write_file(my_vec);
                        cout << "All unfav " << endl;
                    } // end click on all-unfav button
                    // Click On Add Icon
                    if (add_sprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        window.draw(add_sprite_clicked);
                        if (my_vec.size() < TASKS_CAPACITY)
                        {
                            add(my_vec);
                            cout << "Adding a New Task" << endl;
                        }
                    } // End Click on Add Icon
                    // click on Edit Icon
                    if (edit_sprite[mouse_pos].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        add(my_vec, my_vec[mouse_pos].get_task());
                        write_file(my_vec);
                        cout << "EDIT ICON" << endl;
                    } // end click on Edit Icon
                    // click on Delete Icon
                    if (delete_sprite[mouse_pos].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        // add(my_vec, my_vec[mouse_pos].get_task());
                        my_vec.erase(my_vec.begin() + mouse_pos);
                        write_file(my_vec);
                        cout << "Delete ICON" << endl;
                    } // end click on Edit Icon
                    // End Buttons
                    // click on favorite Icon ---> Make it un-Favorite
                    if (favorite_sprite[mouse_pos].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                    {
                        if (my_vec[mouse_pos].get_favourite() == true)
                        {
                            favorite_sprite[mouse_pos].setTexture(favorite_no_texture);
                            my_vec[mouse_pos].set_favourite(false);
                            write_file(my_vec);
                            cout << "Unfavorite ICON" << endl;
                        }
                        else
                        {
                            favorite_sprite[mouse_pos].setTexture(favorite_texture);
                            my_vec[mouse_pos].set_favourite(true);
                            write_file(my_vec);
                            cout << "favorite ICON  " << my_vec[mouse_pos].get_task() << endl;
                        } // end click on favorite Icon
                    }     // end click on favorite Icon
                    else  // click on favorite-no Icon ---> Make it Favorite
                    {
                        // click on done Icon ---> Make it un-done
                        if (done_sprite[mouse_pos].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                        {
                            if (my_vec[mouse_pos].get_state() == true)
                            {
                                task_array[mouse_pos].setStyle(sf::Text::Regular);
                                done_sprite[mouse_pos].setTexture(done_false_texture);
                                my_vec[mouse_pos].set_state(false);
                                write_file(my_vec);
                                cout << "Un-Done ICON" << endl;
                            }
                            // click on Done Icon ---> Make it Done
                            else
                            {
                                done_sprite[mouse_pos].setTexture(done_true_texture);
                                my_vec[mouse_pos].set_state(true);
                                Task tmp = my_vec[mouse_pos];
                                my_vec.erase(my_vec.begin() + mouse_pos);
                                my_vec.push_back(tmp);
                                write_file(my_vec);
                                cout << "Done ICON  " << my_vec[mouse_pos].get_task() << endl;
                            } // end click on Done Icon
                        }     // end click on done Icon
                    }
                }
            } // End Mouse CLICK
        }
        ////////////////////////////////////////////////////////////////////////////////
        // Display Contents
        window.draw(back_sprite);
        window.draw(add_sprite);
        // Show Tasks
        for (size_t i = 0; i < my_vec.size(); i++)
        {
            // Column 1
            if (i % 2 == 0)
            {
                // Done Icon
                if (my_vec[i].get_state() == true)
                {
                    task_array[i].setStyle(sf::Text::StrikeThrough);
                    done_sprite[i].setTexture(done_true_texture);
                    done_sprite[i].setPosition(sf::Vector2f(720, 219 + (17 * i)));
                }
                else if (my_vec[i].get_state() == false && i != mouse_pos)
                {
                    done_sprite[i].setTexture(done_false_texture);
                    done_sprite[i].setPosition(sf::Vector2f(720, 219 + (17 * i)));
                } // End Done Icon
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
                window.draw(done_sprite[i]);
            }
            // Column 2
            else
            {
                // Done Icon
                if (my_vec[i].get_state() == true)
                {
                    task_array[i].setStyle(sf::Text::StrikeThrough);
                    done_sprite[i].setTexture(done_true_texture);
                    done_sprite[i].setPosition(sf::Vector2f(710 + 807, 219 + (17 * (i - 1))));
                }
                else if (my_vec[i].get_state() == false && i != mouse_pos)
                {

                    done_sprite[i].setTexture(done_false_texture);
                    done_sprite[i].setPosition(sf::Vector2f(710 + 807, 219 + (17 * (i - 1))));
                } // End Done Icon
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
                window.draw(done_sprite[i]);
            }
            // displays all tasks
            window.draw(task_array[i]);
        }
        // display edit and delete icons
        if (my_vec.size() == TASKS_CAPACITY)
        {
            full_sprite.setTexture(full_texture);
            full_sprite.setPosition(window_x - 135, window_y - 135);
            window.draw(full_sprite);
        }
        if (my_vec.size() != 0)
        {
            window.draw(edit_sprite[mouse_pos]);
            window.draw(delete_sprite[mouse_pos]);
        }
        // MAKE ALL FAVORITE AND ALL NOT_FAVOURITE
        window.draw(all_fav_sprite);
        window.draw(all_unfav_sprite);
        // MAKE ALL DONE AND ALL NOT_DONE
        window.draw(all_done_sprite);
        window.draw(all_undone_sprite);
        // DELETE ALL
        window.draw(all_del_sprite);
        window.display();
    }
}

//  TODO : Move Comlpeted Task at the end even when a new task is added