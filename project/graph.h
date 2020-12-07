#ifndef GRAPH_HH
#define GRAPH_HH
#include <set>
#include <map>
#include <string>

class Graph
{
private:
    std::map<std::string, std::set<std::string>> vertices;
    std::map<std::pair<std::string, std::string>, unsigned int> edge_weigh;

public:
    Graph(/* args */); ///todo()!
    ~Graph();          ///todo()!

    void add_vertex(const std::string &);
    void add_edge(const std::string &, const std::string &, const unsigned int &);
};

#endif
