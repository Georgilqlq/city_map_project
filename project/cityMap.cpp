#include "cityMap.h"
#include <iostream>
#include <sstream>
#include <fstream>

void clear_screen()
{
    std::cout << std::string(3, '\n');
}

void CityMap::load()
{
    std::string input;
    do
    {
        clear_screen();
        std::cin.clear();
        std::cout << "Enter the input txt file." << std::endl;
        std::cout << ">";
        std::getline(std::cin, input);
        std::cout << "-----------" << std::endl;

        try
        {
            locations.clear();
            map.load_from_file(input);
            std::cout << "File loaded successfully." << std::endl;
            file_name = input;
            break;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what() << std::endl;
        }
        catch (const std::overflow_error &e)
        {
            std::cerr << e.what() << std::endl;
            exit(1);
        }
    } while (true);
}

void CityMap::location()
{
    if (locations.get_location().empty())
    {
        std::cout << "You haven't set the current location yet." << std::endl;
    }
    else
    {
        std::cout << "Current location is: " << locations.get_location() << std::endl;
    }
}

void CityMap::change(const std::string &new_location)
{
    if (map.has_vertex(new_location))
    {
        locations.change_location(new_location);
        std::cout << "Location changed to: " << locations.get_location() << std::endl;
    }
    else
    {
        std::cout << "Invalid location!" << std::endl;
    }
}

void CityMap::initial_location()
{
    std::string input;
    do
    {
        clear_screen();
        std::cout << "Enter the starting location" << std::endl;
        std::cin.clear();
        std::cout << ">";
        std::getline(std::cin, input);
        std::cout << "-----------" << std::endl;

        if (map.has_vertex(input))
        {
            locations.change_location(input);
            std::cout << "Location changed to: " << locations.get_location() << std::endl;
            break;
        }
        else
        {
            std::cout << "Invalid location! Please try again!" << std::endl;
        }
    } while (true);
}

void CityMap::neighbours()
{
    try
    {
        std::set<std::string> vertex_for_print = map.get_neighbours(locations.get_location());
        std::cout << "[ ";
        for (auto neighbour : vertex_for_print)
        {
            std::cout << neighbour << " ";
        }
        std::cout << "]" << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void CityMap::move(const std::string &new_location)
{
    try
    {
        if (map.is_it_reachable(locations.get_location(), new_location, locations.get_closed_locations()))
        {
            std::map<std::vector<std::string>, unsigned int> three_shortest_paths = map.find_three_shortest_paths(locations.get_location(), new_location, locations.get_closed_locations());

            for (auto path : three_shortest_paths)
            {
                for (auto visited_vertex : path.first)
                {
                    std::cout << " -> " << visited_vertex;
                }
                std::cout << ": " << path.second << std::endl;
            }
            change(new_location);
        }
        else
        {
            std::cout << new_location << " can't be reached from " << locations.get_location() << "." << std::endl;
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void CityMap::close(const std::string &closed_location)
{
    if (map.has_vertex(closed_location))
    {
        locations.close_location(closed_location);
        std::cout << "[ " << closed_location << " ] has been closed." << std::endl;
    }
    else
    {
        std::cout << closed_location << " doen't exist on the map." << std::endl;
    }
}

void CityMap::open(const std::string &opened_location)
{
    locations.open_location(opened_location);
}

void CityMap::closed()
{
    std::cout << "[ ";
    for (auto location : locations.get_closed_locations())
    {
        std::cout << location << " ";
    }
    std::cout << "]" << std::endl;
}

void CityMap::tour()
{
    try
    {
        std::vector<std::string> path = map.start_euler_tour(locations.get_location());
        if (map.is_valid_path(path))
        {
            std::cout << "[ ";
            for (std::vector<std::string>::reverse_iterator note = path.rbegin(); note != path.rend() - 1; ++note)
            {
                std::cout << *note << " -> ";
            }
            std::cout << path[0] << " ]" << std::endl;
        }
        else
        {
            std::cout << "You cannot make a full tour of the city from here: " << locations.get_location() << std::endl;
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void CityMap::user_interface()
{
    load();
    initial_location();
    std::string input, command, value;
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
        else if (input == "reload")
        {
            reload();
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

void CityMap::extract_words(std::string &input, std::string &command, std::string &value)
{
    std::stringstream input_stream(input);
    std::string item;
    input_stream >> command >> item >> value;
    if (item != "@")
    {
        throw std::invalid_argument("'@' Needs to be placed after the command!");
    }
}

void CityMap::image()
{
    std::ofstream output("Graph.dot");
    map.visualise(output);
    std::cout << "Open the Graph.dot file." << std::endl;
}

void CityMap::dead_ends()
{
    std::map<std::string, std::set<std::string>> dead_ends = map.find_all_dead_ends();

    for (auto end_street : dead_ends)
    {
        for (auto begin_street : end_street.second)
        {
            std::cout << "[ " << begin_street << " - " << end_street.first << " ]" << std::endl;
        }
    }
}

void CityMap::mini_tour()
{
    try
    {

        if (map.mini_tour_and_return(locations.get_location()))
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

void CityMap::reach_all()
{
    try
    {

        if (map.can_reach_all_vertices(locations.get_location()))
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

void CityMap::menu1()
{
    std::cout << "Welcome to the City Map Menu 1/2" << std::endl
              << "The functions that are currently available are: " << std::endl
              << std::endl
              << "location - tells you the current location" << std::endl
              << "neighbours - display all the neighbouring crossroads" << std::endl
              << "closed - display all the closed crossroads" << std::endl
              << "tour - display the Euler tour if one is possible" << std::endl
              << "image - display the map in the Graph.dot file" << std::endl
              << "dead ends - display all dead ends" << std::endl
              << "mini tour - see if you can return to your current location after a mini tour" << std::endl
              << "reach all - see if you can reach all crossroads from your current location" << std::endl
              << "reload - reloads the city map from the initial file" << std::endl;
}

void CityMap::menu2()
{
    std::cout << "Welcome to the City Map Menu 2/2" << std::endl
              << "The functions that are currently available are: " << std::endl
              << std::endl
              << "load @ <file name> - to load a map from a file" << std::endl
              << "change @ <new location> - chane your current location to the new location" << std::endl
              << "move @ <new location> - move to a new location displaying the shortest paths" << std::endl
              << "close @ <location> - close off a crossroad" << std::endl
              << "open @ <location> - open a closed crossroad" << std::endl;
}

void CityMap::startup()
{
    std::string input;
    std::cout << "Welcome to the city map program! Please type one of the following: " << std::endl;
    std::cout << "--i   to start the program " << std::endl;
    std::cout << "--h1  for the menu without parameters" << std::endl;
    std::cout << "--h2  for the menu with parameters" << std::endl;
    std::cout << "exit  to quit the program" << std::endl;
    do
    {
        clear_screen();
        std::cin.clear();
        std::cout << ">";
        std::getline(std::cin, input);
        std::cout << "-----------" << std::endl;

        if (input == "--i")
        {
            user_interface();
            break;
        }
        else if (input == "--h1")
        {
            menu1();
        }
        else if (input == "--h2")
        {
            menu2();
        }
        else if (input == "exit")
        {
            break;
        }
        else
        {
            std::cout << "Invalid command! Please try again!" << std::endl;
        }
    } while (true);
}

void CityMap::reload()
{
    try
    {
        locations.clear();
        map.load_from_file(file_name);
        std::cout << "File loaded successfully." << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::overflow_error &e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
