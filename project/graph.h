#ifndef GRAPH_HH
#define GRAPH_HH
#include <set>
#include <map>
#include <string>
#include <stack>
#include <list>
#include <vector>

///This is the graph class.
///
///This is a weighted graph using an adjacency list.
class Graph
{
private:
    using VertexPair = std::pair<std::string, std::string>;
    using VisitedTable = std::map<std::string, bool>;
    using ListOfPaths = std::list<std::vector<std::string>>;

    std::set<std::string> vertex_point;
    std::map<std::string, std::set<std::string>> vertices;
    std::map<VertexPair, unsigned int> edge_weigh;

public:
    Graph() = default;
    ///Constructor for generating the graph after reading the input from a file.
    ///@see load_from_file(const std::string &)
    Graph(const std::string &);
    ~Graph();

    void add_vertex(const std::string &);
    void add_edge(const std::string &, const std::string &, const unsigned int &);
    void load_from_file(const std::string &);
    ///Writes the data from the graph in a .dot file so it can be visualized.
    void visualise(std::ostream &);

    ///Checks if it is possible to reach a vertex from another vertex. Some vertices may be closed.
    ///@param from_vertex is the starting vertex
    ///@param to_vertex is the destination vertex
    ///@param closed_vertices some vertices may be "closed". If there is no argument given we assume that no vertices are closed.
    bool is_it_reachable(const std::string &, const std::string &, const std::set<std::string> & = std::set<std::string>());
    ///Checks if it's possible to reach all vertices from a given vertex.
    bool can_reach_all_vertices(const std::string &);
    ///Checks if it's possible to make a small tour and return back to the starting vertex.
    bool mini_tour_and_return(const std::string &);
    bool has_vertex(const std::string &);
    ///Checks if a given path of vertices is valid
    bool is_valid_path(std::vector<std::string> &);

    ///Finds the three shortest paths in the graph from vertex to vertex. Some vertices may be closed.
    ///@param from_vertex is the starting vertex
    ///@param to_vertex is the destination vertex
    ///@param closed_vertices some vertices may be "closed". If there is no argument given we assume that no vertices are closed.
    ///@return the three shortest paths and their weight.
    ///@see find_all_paths(const std::string &, const std::string &, VisitedTable &, ListOfPaths &, std::vector<std::string> &)
    std::map<std::vector<std::string>, unsigned int> find_three_shortest_paths(const std::string &, const std::string &, const std::set<std::string> & = std::set<std::string>());
    ///Finds all streets that lead to a dead end.
    ///@return the vertices that have no neighbours and the vertices that lead there.
    std::map<std::string, std::set<std::string>> find_all_dead_ends();
    ///Finds the euler path from a vertex.
    ///@return the euler path.
    ///@note the path might not always be correct because an euler tour might not be possible from the given vertex. The path must be checked if it's valid.
    ///@see is_valid_path(std::vector<std::string> &)
    std::vector<std::string> start_euler_tour(const std::string &);
    ///@return the vertex's neighbours.
    std::set<std::string> get_neighbours(const std::string &);

private:
    ///@param from_vertex the starting vertex
    ///@param path where the euler path is stored. Needs to be checked if correct.
    ///@param vertices_copy because this is a destructive function.
    void find_euler_tour(const std::string &, std::vector<std::string> &, std::map<std::string, std::set<std::string>> &);
    ///@param from_vertex the starting vertex
    ///@param to_vertex the destination
    ///@param visited_vertices a table of previously visited vertices
    ///@param paths list of all the paths possible
    ///@param current_path the path the funcion is currenlty going through. It will be added to the paths after ending the recursion.
    void find_all_paths(const std::string &, const std::string &, VisitedTable &, ListOfPaths &, std::vector<std::string> &);
    ///Creates a table of previously visited vertices. None of them are currenly visited.
    void create_visited_vertices(VisitedTable &);
    ///Finds the shortest path out of @param paths (the list of all possible paths)
    /// and sets @param min_weight (the path's weight) @param min_path the path itself.
    void find_min_path(ListOfPaths &, unsigned int &, std::vector<std::string> &);
    void delete_graph();
    ///Creates the table of previously visited vertices. If some vertices are closed they will be counted as "visited".
    void create_closed_vertices(VisitedTable &, const std::set<std::string> &);

    bool has_edge(const std::string &, const std::string &);
    ///Searches through the neighbours of a vertex to see if it's reachable.
    bool searching_through_neighbours(const std::string &, VisitedTable &, std::stack<std::string> &, const std::string &);
    ///Searches through the graph if it's possible to reach one vertex from another.
    bool dfs_search(const std::string &, const std::string &, VisitedTable &);

    std::set<std::string> print_all_dead_ends(const std::string &);
};
#endif
