#include "CrossRoad.h"

const std::string CrossRoad::get_location() const
{
    return current_location;
}
const std::set<std::string> CrossRoad::get_closed_locations() const
{
    return closed_locations;
}
void CrossRoad::change_location(const std::string &new_location)
{
    current_location = new_location;
}
void CrossRoad::open_location(const std::string &opened_location)
{
    closed_locations.erase(opened_location);
}
void CrossRoad::close_location(const std::string &closed_location)
{
    closed_locations.insert(closed_location);
}
void CrossRoad::clear()
{
    current_location.clear();
    closed_locations.clear();
}
