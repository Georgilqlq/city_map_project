#include "city_map.h"
#include <iostream>

void City_map::load(const std::string &file_name)
{
    try
    {
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
    map.print_neighbours(current_location);
}

void City_map::move(const std::string &new_location)
{
    try
    {
        if (map.is_it_reachable(current_location, new_location))
        {
            map.find_all_paths(current_location, new_location, closed_locations);
            change(new_location);
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void City_map::close(const std::string &closed_location)
{
    closed_locations.insert(closed_location);
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
    std::cout << " ]" << std::endl;
}

void City_map::tour()
{
    try
    {
        map.start_euler_tour(current_location);
        
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }
}
