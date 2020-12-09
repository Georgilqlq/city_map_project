#include "graph.h"
#include <iostream>
#include <limits>

void Graph::add_vertex(const std::string &vertex_name)
{
    vertices[vertex_name];
}

void Graph::add_edge(const std::string &from_vertex, const std::string &to_vertex, const unsigned int &value)
{
    // vertices[from_vertex] = to_vertex; //ask nikola in discord
    // edge_weigh[std::make_pair(from_vertex, to_vertex)].insert(value); //??
    vertices[from_vertex].insert(to_vertex);
    edge_weigh[std::make_pair(from_vertex, to_vertex)] = value;
}

bool Graph::is_it_reachable(const std::string &from_vertex, const std::string &to_vertex)
{
    if (from_vertex == to_vertex)
    {
        return true;
    }

    std::map<std::string, bool> visited_vertices;
    std::stack<std::string> path;

    for (auto vertex : vertices)
    {
        visited_vertices[vertex.first] = false;
    }

    visited_vertices[from_vertex] = true;
    path.push(from_vertex);

    std::string current_vertex;
    while (!path.empty())
    {
        current_vertex = path.top();
        path.pop();

        for (auto neighbour : vertices[current_vertex])
        {
            if (neighbour == to_vertex)
            {
                return true;
            }

            if (visited_vertices[neighbour] == false)
            {
                visited_vertices[neighbour] = true;
                path.push(neighbour);
            }
        }
    }

    return false;
}

void Graph::find_all_paths(const std::string &from_vertex, const std::string &to_vertex)
{
    if (is_it_reachable(from_vertex, to_vertex) == false)
    {
        return;
    }

    std::list<std::vector<std::string>> paths;
    std::map<std::string, bool> visited_vertices;
    std::vector<std::string> current_path;

    for (auto vertex : vertices)
    {
        visited_vertices[vertex.first] = false;
    }

    find_all_paths_helper(from_vertex, to_vertex, visited_vertices, paths, current_path);

    for (size_t i = 0; i < 3 && !paths.empty(); i++)
    {
        unsigned int min_weight = UINT_MAX;
        std::vector<std::string> min_path;
        for (auto vector : paths)
        {
            unsigned int total_weight = 0;
            std::vector<std::string>::const_iterator end = vector.cend() - 1;
            for (std::vector<std::string>::const_iterator element = vector.cbegin(); element != end; ++element)
            {
                total_weight = total_weight + edge_weigh[std::make_pair(*element, *(element + 1))];
            }

            if (total_weight < min_weight)
            {
                min_weight = total_weight;
                min_path = vector;
            }
        }

        for (auto element : min_path)
        {
            std::cout << element << " ";
        }
        std::cout << min_weight << std::endl;
        paths.remove(min_path);
    }
}

void Graph::find_all_paths_helper(const std::string &from_vertex, const std::string &to_vertex, std::map<std::string, bool> &visited_vertices, std::list<std::vector<std::string>> &paths, std::vector<std::string> &current_path)
{
    visited_vertices[from_vertex] = true;
    current_path.push_back(from_vertex);

    if (from_vertex == to_vertex)
    {
        paths.push_back(current_path);
    }
    else
    {
        for (auto neighbour : vertices[from_vertex])
        {
            if (visited_vertices[neighbour] == false)
            {
                find_all_paths_helper(neighbour, to_vertex, visited_vertices, paths, current_path);
            }
        }
    }

    visited_vertices[from_vertex] = false;
    current_path.pop_back();
}

bool Graph::can_reach_all_vertices(const std::string &from_vertex)
{
    for (auto vertex : vertices)
    {
        if (!is_it_reachable(from_vertex, vertex.first))
        {
            return false;
        }
    }

    return true;
}

void Graph::find_all_dead_ends()
{
    for (auto vertex : vertices)
    {
        if (vertex.second.empty())
        {
            for (auto search_vertices : vertices)
            {
                if (search_vertices.second.count(vertex.first) == 1)
                {
                    std::cout << search_vertices.first << " - " << vertex.first << std::endl;
                }
            }
        }
    }
}
