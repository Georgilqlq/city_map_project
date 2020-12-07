#include <graph.h>

void Graph::add_vertex(const std::string &vertex_name)
{
    vertices[vertex_name];
}

void Graph::add_edge(const std::string &from_vertex, const std::string &to_vertex, const unsigned int &value)
{
    // vertices[from_vertex] = to_vertex; //ask nikola in discord
    vertices[from_vertex].insert(to_vertex);
    edge_weigh[std::make_pair(from_vertex, to_vertex)] = value;
    // edge_weigh[std::make_pair(from_vertex, to_vertex)].insert(value); //??
}
