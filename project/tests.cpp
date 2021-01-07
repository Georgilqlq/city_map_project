#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "graph.h"

TEST_CASE("testing creation of vertices and edges")
{
    Graph basic_map;

    basic_map.add_vertex("Sofia");
    basic_map.add_vertex("Varna");
    basic_map.add_vertex("Ruse");

    CHECK(basic_map.has_vertex("Sofia"));
    CHECK(basic_map.has_vertex("Ruse"));
    CHECK(!basic_map.has_vertex("Plovdiv"));

    basic_map.add_edge("Sofia", "Varna", 13);
    basic_map.add_edge("Varna", "Ruse", 13);

    CHECK(basic_map.is_it_reachable("Sofia", "Ruse"));
    CHECK(!basic_map.is_it_reachable("Ruse", "Sofia"));
    CHECK(!basic_map.can_reach_all_vertices("Varna"));
    CHECK(basic_map.can_reach_all_vertices("Sofia"));
}

TEST_CASE("finding path and dead ends + reading from file")
{
    Graph basic_map("test_input.txt");

    std::map<std::vector<std::string>, unsigned int> path_from_Two_to_One = basic_map.find_three_shortest_paths("Two", "One");
    std::vector<std::string> first_path{"Two", "Five", "One"};
    std::vector<std::string> second_path{"Two", "One"};

    CHECK(path_from_Two_to_One[first_path] == 70);
    CHECK(path_from_Two_to_One[second_path] == 41);

    std::map<std::string, std::set<std::string>> dead_ends = basic_map.find_all_dead_ends();

    CHECK(dead_ends.empty());

    basic_map.add_edge("Five", "Six", 32);
    dead_ends = basic_map.find_all_dead_ends();

    CHECK(!dead_ends.empty());
    CHECK(dead_ends["Six"].count("Five") == 1);
}

TEST_CASE("testing tours + neighbours")
{
    Graph basic_graph("test_input.txt");

    std::vector<std::string> path = basic_graph.start_euler_tour("Two");
    CHECK(basic_graph.is_valid_path(path));

    path = basic_graph.start_euler_tour("One");
    CHECK(!basic_graph.is_valid_path(path));

    CHECK(basic_graph.mini_tour_and_return("One"));
    CHECK(basic_graph.mini_tour_and_return("Two"));
    CHECK(basic_graph.mini_tour_and_return("Three"));

    std::set<std::string> ones_neighbours = basic_graph.get_neighbours("Zero");

    CHECK(ones_neighbours.count("Two") == 1);
    CHECK(ones_neighbours.count("Three") == 1);
    CHECK(ones_neighbours.count("Four") == 0);
}
