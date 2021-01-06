#include "graph.h"
#include "CrossRoad.h"
#include <string>

///User interface class. Input/Output in the console.
class City_map
{
private:
    Graph map;
    CrossRoad locations;

public:
    void load();
    void location();
    void change(const std::string &);
    void neighbours();
    void move(const std::string &);
    void close(const std::string &);
    void open(const std::string &);
    void closed();
    void tour();
    void user_interface();
    void image();
    void dead_ends();
    void mini_tour();
    void reach_all();

private:
    ///Extracts the command and the value from the input
    void extract_words(std::string &, std::string &, std::string &);
    void menu();
    void initial_location();
};
