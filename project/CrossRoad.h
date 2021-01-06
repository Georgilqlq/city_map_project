#ifndef CROSSROAD_HH
#define CROSSROAD_HH
#include <string>
#include <set>

///This is the class containing the closed location and the current location
class CrossRoad
{
private:
    std::string current_location;
    std::set<std::string> closed_locations;

public:
    const std::string get_location() const;
    const std::set<std::string> get_closed_locations();
    void change_location(const std::string &);
    void open_location(const std::string &);
    void close_location(const std::string &);
    void clear();
};

#endif
