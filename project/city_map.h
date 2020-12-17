#include "graph.h"
#include <string>

class City_map
{
private:
    Graph map;
    std::string current_location;
    std::set<std::string> closed_locations;

public:
    void load(const std::string &);
    void location();
    void change(const std::string &);
    void neighbours();
    void move(const std::string &);
    void close(const std::string &);
    void open(const std::string &);
    void closed();
    void tour();
};
