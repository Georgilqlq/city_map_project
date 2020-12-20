#include "city_map.h"
#include <iostream>
#include <sstream>
#include <fstream>

void clear_screen()
{
    std::cout << std::string(3, '\n');
}

void City_map::load(const std::string &file_name)
{
    try
    {
        current_location.clear();
        closed_locations.clear();
        map.load_from_file(file_name);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void City_map::location()
{
    if (current_location.empty())
    {
        std::cout << "You haven't set the current location yet." << std::endl;
    }
    else
    {
        std::cout << "Current location is: " << current_location << std::endl;
    }
}

void City_map::change(const std::string &new_location)
{
    if (map.has_vertex(new_location))
    {
        current_location = new_location;
        std::cout << "Location changed to: " << current_location << std::endl;
    }
    else
    {
        std::cout << "Invalid location!" << std::endl;
    }
}

void City_map::neighbours()
{
    try
    {
        map.print_neighbours(current_location);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void City_map::move(const std::string &new_location)
{
    try
    {
        if (map.is_it_reachable(current_location, new_location, closed_locations))
        {
            map.find_all_paths(current_location, new_location, closed_locations);
            change(new_location);
        }
        else
        {
            std::cout << new_location << " can't be reached from " << current_location << "." << std::endl;
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void City_map::close(const std::string &closed_location)
{
    if (map.has_vertex(closed_location))
    {
        closed_locations.insert(closed_location);
        std::cout << "[ " << closed_location << " ] has been closed." << std::endl;
    }
    else
    {
        std::cout << closed_location << " doen't exist on the map." << std::endl;
    }
}

void City_map::open(const std::string &opened_location)
{
    closed_locations.erase(opened_location);
}

void City_map::closed()
{
    std::cout << "[ ";
    for (auto location : closed_locations)
    {
        std::cout << location << " ";
    }
    std::cout << "]" << std::endl;
}

void City_map::tour()
{
    try
    {
        map.start_euler_tour(current_location);
        map.load_from_file("input.txt");
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void City_map::user_interface()
{
    std::string input, command, value;
    menu();
    do
    {
        clear_screen();
        std::cin.clear();
        std::cout << ">";
        std::getline(std::cin, input);
        std::cout << "-----------" << std::endl;
        if (input == "location")
        {
            location();
        }
        else if (input == "neighbours")
        {
            neighbours();
        }
        else if (input == "closed")
        {
            closed();
        }
        else if (input == "tour")
        {
            tour();
        }
        else if (input == "image")
        {
            image();
        }
        else if (input == "dead ends")
        {
            dead_ends();
        }
        else if (input == "mini tour")
        {

            mini_tour();
        }
        else if (input == "reach all")
        {
            reach_all();
        }
        else if (input.find("@") != std::string::npos)
        {
            try
            {
                extract_words(input, command, value);
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        if (command == "change")
        {
            change(value);
        }
        else if (command == "move")
        {
            move(value);
        }
        else if (command == "close")
        {
            close(value);
        }
        else if (command == "open")
        {
            open(value);
        }

        command.clear();
        value.clear();

    } while (input != "exit" && input != "quit");
}

void City_map::extract_words(std::string &input, std::string &command, std::string &value)
{
    std::stringstream input_stream(input);
    std::string item;
    input_stream >> command >> item >> value;
    if (item != "@")
    {
        throw std::invalid_argument("'@' Needs to be placed after the command!");
    }
}

void City_map::image()
{
    std::ofstream output("Graph.dot");
    map.visualise(output);
    std::cout << "Open the Graph.dot file." << std::endl;
}

void City_map::dead_ends()
{
    map.find_all_dead_ends();
}

void City_map::mini_tour()
{
    try
    {

        if (map.mini_tour_and_return(current_location))
        {
            std::cout << "Yes you will be able to return after a mini tour of the city." << std::endl;
        }
        else
        {
            std::cout << "No you won't be able to return after a mini tour of the city." << std::endl;
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void City_map::reach_all()
{
    try
    {

        if (map.can_reach_all_vertices(current_location))
        {
            std::cout << "You can reach all intersections from here." << std::endl;
        }
        else
        {
            std::cout << "You can't reach all intersections from here." << std::endl;
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void City_map::menu()
{
    std::cout << "Welcome to the City Map Menu" << std::endl
              << "The functions that are currently available are: " << std::endl
              << std::endl
              << "load @ <file name> - to load a map from a file" << std::endl
              << "location - tells you the current location" << std::endl
              << "change @ <new location> - chane your current location to the new location" << std::endl
              << "neighbours - display all the neighbouring crossroads" << std::endl
              << "move @ <new location> - move to a new location displaying the shortest paths" << std::endl
              << "close @ <location> - close off a crossroad" << std::endl
              << "open @ <location> - open a closed crossroad" << std::endl
              << "closed - display all the closed crossroads" << std::endl
              << "tour - display the Euler tour if one is possible" << std::endl
              << "image - display the map in the Graph.dot file" << std::endl
              << "dead ends - display all dead ends" << std::endl
              << "mini tour - see if you can return to your current location after a mini tour" << std::endl
              << "reach all - see if you can reach all crossroads from your current location" << std::endl;
}
