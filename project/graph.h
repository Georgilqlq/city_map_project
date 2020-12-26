#ifndef GRAPH_HH
#define GRAPH_HH
#include <set>
#include <map>
#include <string>
#include <stack>
#include <list>
#include <vector>

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
    Graph(const std::string &);
    ~Graph();

    void add_vertex(const std::string &);
    void add_edge(const std::string &, const std::string &, const unsigned int &);
    bool is_it_reachable(const std::string &, const std::string &, const std::set<std::string> & = std::set<std::string>());
    void find_all_paths(const std::string &, const std::string &, const std::set<std::string> & = std::set<std::string>());
    bool can_reach_all_vertices(const std::string &);
    void find_all_dead_ends();
    bool mini_tour_and_return(const std::string &);
    void start_euler_tour(const std::string &);
    bool has_vertex(const std::string &);
    void print_neighbours(const std::string &);
    void load_from_file(const std::string &);
    void visualise(std::ostream &);
    void euler_tour(const std::string &, std::vector<std::string> &, std::map<std::string, std::set<std::string>> &);

private:
    void find_all_paths_helper(const std::string &, const std::string &, VisitedTable &, ListOfPaths &, std::vector<std::string> &);
    bool has_edge(const std::string &, const std::string &); // might not need
    bool searching_through_neighbours(const std::string &, VisitedTable &, std::stack<std::string> &, const std::string &);
    void create_visited_vertices(VisitedTable &);
    void find_min_path(ListOfPaths &, unsigned int &, std::vector<std::string> &);
    void print_all_dead_ends(const std::string &);
    void delete_graph();
    void create_closed_vertices(VisitedTable &, const std::set<std::string> &);

    bool is_valid_path(std::vector<std::string> &);
    bool dfs_search(const std::string &, const std::string &, VisitedTable &);
};
#endif
