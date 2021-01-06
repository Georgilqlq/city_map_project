#include "graph.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>

Graph::~Graph()
{
    delete_graph();
}

Graph::Graph(const std::string &file_name)
{
    load_from_file(file_name);
}

void Graph::add_vertex(const std::string &vertex_name)
{
    vertex_point.insert(vertex_name);
    vertices[vertex_name];
}

void Graph::add_edge(const std::string &from_vertex, const std::string &to_vertex, const unsigned int &value)
{
    vertex_point.insert(from_vertex);
    vertex_point.insert(to_vertex);
    vertices[from_vertex].insert(to_vertex);
    vertices[to_vertex];
    edge_weigh[std::make_pair(from_vertex, to_vertex)] = value;
}

bool Graph::is_it_reachable(const std::string &from_vertex, const std::string &to_vertex, const std::set<std::string> &closed_vertices)
{
    if (!has_vertex(from_vertex) || !has_vertex(to_vertex))
    {
        throw std::invalid_argument("Invalid vertices!");
    }

    if (from_vertex == to_vertex)
    {
        return true;
    }

    if (closed_vertices.count(to_vertex) == 1)
    {
        return false;
    }

    VisitedTable visited_vertices;
    create_closed_vertices(visited_vertices, closed_vertices);
    visited_vertices[from_vertex] = true;

    return dfs_search(from_vertex, to_vertex, visited_vertices);
}

std::map<std::vector<std::string>, unsigned int> Graph::find_three_shortest_paths(const std::string &from_vertex, const std::string &to_vertex, const std::set<std::string> &closed_vertices)
{
    if (!has_vertex(from_vertex) || !has_vertex(to_vertex))
    {
        throw std::invalid_argument("Invalid vertices!");
    }

    std::map<std::vector<std::string>, unsigned int> three_shortest_paths;
    if (is_it_reachable(from_vertex, to_vertex) == false)
    {
        return three_shortest_paths;
    }

    ListOfPaths paths;
    VisitedTable visited_vertices;
    std::vector<std::string> current_path;

    create_closed_vertices(visited_vertices, closed_vertices);

    find_all_paths(from_vertex, to_vertex, visited_vertices, paths, current_path);

    unsigned int min_weight;
    std::vector<std::string> min_path;
    for (size_t i = 0; i < 3 && !paths.empty(); i++)
    {
        min_weight = UINT_MAX;
        min_path.clear();

        find_min_path(paths, min_weight, min_path);

        three_shortest_paths[min_path] = min_weight;

        paths.remove(min_path);
    }
    return three_shortest_paths;
}
void Graph::find_all_paths(const std::string &from_vertex, const std::string &to_vertex, VisitedTable &visited_vertices, ListOfPaths &paths, std::vector<std::string> &current_path)
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
                find_all_paths(neighbour, to_vertex, visited_vertices, paths, current_path);
            }
        }
    }
    visited_vertices[from_vertex] = false;
    current_path.pop_back();
}

bool Graph::can_reach_all_vertices(const std::string &from_vertex)
{
    if (!has_vertex(from_vertex))
    {
        throw std::invalid_argument("Invalid vertex!");
    }

    for (auto vertex : vertices)
    {
        if (!is_it_reachable(from_vertex, vertex.first))
        {
            return false;
        }
    }

    return true;
}

std::map<std::string, std::set<std::string>> Graph::find_all_dead_ends()
{
    std::map<std::string, std::set<std::string>> dead_ends;
    for (auto vertex : vertices)
    {
        if (vertex.second.empty())
        {
            dead_ends[vertex.first] = print_all_dead_ends(vertex.first);
        }
    }

    return dead_ends;
}

bool Graph::mini_tour_and_return(const std::string &from_vertex)
{
    if (!has_vertex(from_vertex))
    {
        throw std::invalid_argument("Invalid vertex!");
    }

    VisitedTable visited_vertices;
    create_visited_vertices(visited_vertices);

    return dfs_search(from_vertex, from_vertex, visited_vertices);
}

std::vector<std::string> Graph::start_euler_tour(const std::string &starting_vertex)
{
    if (!has_vertex(starting_vertex))
    {
        throw std::invalid_argument("Invalid vertex!");
    }

    std::map<std::string, std::set<std::string>> vertices_copy = vertices;
    std::vector<std::string> path;
    find_euler_tour(starting_vertex, path, vertices_copy);

    return path;
}

bool Graph::has_vertex(const std::string &vertex_name)
{
    return vertex_point.count(vertex_name) == 1;
}

bool Graph::has_edge(const std::string &first_vertex, const std::string &second_vertex)
{
    return has_vertex(first_vertex) && vertices[first_vertex].count(second_vertex) == 1;
}

bool Graph::searching_through_neighbours(const std::string &current_vertex, VisitedTable &visited_vertices, std::stack<std::string> &path, const std::string &to_vertex)
{
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
    return false;
}

void Graph::create_visited_vertices(VisitedTable &visited_vertices)
{
    for (auto vertex : vertices)
    {
        visited_vertices[vertex.first] = false;
    }
}

void Graph::find_min_path(ListOfPaths &paths, unsigned int &min_weight, std::vector<std::string> &min_path)
{
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
}

std::set<std::string> Graph::print_all_dead_ends(const std::string &dead_end_vertex)
{
    std::set<std::string> dead_end_starts;
    for (auto search_vertices : vertices)
    {
        if (search_vertices.second.count(dead_end_vertex) == 1)
        {
            dead_end_starts.insert(search_vertices.first);
        }
    }

    return dead_end_starts;
}

void Graph::delete_graph()
{
    vertex_point.clear();
    vertices.clear();
    edge_weigh.clear();
}

std::set<std::string> Graph::get_neighbours(const std::string &current_vertex)
{
    if (!has_vertex(current_vertex))
    {
        throw std::invalid_argument("The vertex doesn't exist!");
    }

    return vertices[current_vertex];
}

void Graph::load_from_file(const std::string &file_name)
{
    std::ifstream graph_file(file_name);
    if (!graph_file.is_open())
    {
        throw std::invalid_argument("This file doesn't exist!");
    }

    std::string vertex_name, neighbour_name, line;
    int weight;
    while (std::getline(graph_file, line))
    {
        std::istringstream stream_line(line);
        stream_line >> vertex_name;
        add_vertex(vertex_name);
        while (stream_line >> neighbour_name >> weight)
        {
            if (weight < 0)
            {
                throw std::overflow_error("Cannot assign a negative weight!");
            }
            add_edge(vertex_name, neighbour_name, weight);
        }
    }
}

void Graph::create_closed_vertices(VisitedTable &visited_vertices, const std::set<std::string> &closed_vertices)
{
    for (auto vertex : vertices)
    {
        if (closed_vertices.count(vertex.first) == 1)
        {
            visited_vertices[vertex.first] = true;
        }
        else
        {
            visited_vertices[vertex.first] = false;
        }
    }
}

void Graph::visualise(std::ostream &out)
{
    out << "digraph visual{" << std::endl;

    for (auto vertex : vertices)
    {
        for (auto neighbour : vertex.second)
        {
            out << vertex.first << "->" << neighbour << "[weight=" << edge_weigh[std::make_pair(vertex.first, neighbour)] << "];" << std::endl;
        }
    }
    out << "}" << std::endl;
}

void Graph::find_euler_tour(const std::string &from_vertex, std::vector<std::string> &path, std::map<std::string, std::set<std::string>> &vertices_copy)
{
    while (vertices_copy[from_vertex].size() != 0)
    {
        std::string next_vertex = *vertices_copy[from_vertex].rbegin();
        vertices_copy[from_vertex].erase(next_vertex);
        find_euler_tour(next_vertex, path, vertices_copy);
    }
    path.push_back(from_vertex);
}

bool Graph::is_valid_path(std::vector<std::string> &path)
{
    for (std::vector<std::string>::reverse_iterator note = path.rbegin(); note != path.rend() - 1; ++note)
    {
        if (!has_edge(*note, *(note + 1)))
        {
            return false;
        }
    }
    return true;
}

bool Graph::dfs_search(const std::string &from_vertex, const std::string &end_vertex, VisitedTable &visited_vertices)
{
    std::stack<std::string> path;

    path.push(from_vertex);

    std::string current_vertex;
    while (!path.empty())
    {
        current_vertex = path.top();
        path.pop();

        if (searching_through_neighbours(current_vertex, visited_vertices, path, end_vertex))
        {
            return true;
        }
    }

    return false;
}
