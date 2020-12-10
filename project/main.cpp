#include "graph.h"
#include <iostream>

int main()
{
    Graph test_graph;
    test_graph.add_vertex("1");
    test_graph.add_vertex("2");
    test_graph.add_vertex("3");
    test_graph.add_vertex("4");

    test_graph.add_edge("1", "2", 1);
    test_graph.add_edge("1", "3", 2);
    test_graph.add_edge("1", "4", 3);
    test_graph.add_edge("3", "1", 4);
    test_graph.add_edge("3", "2", 5);
    test_graph.add_edge("2", "4", 6);
    test_graph.add_edge("4", "3", 10);

    std::cout << test_graph.is_it_reachable("3", "4") << std::endl;
    test_graph.find_all_paths("3", "4");
    std::cout << test_graph.can_reach_all_vertices("4") << std::endl;
    test_graph.find_all_dead_ends();

    std::set<std::string> close_test;
    close_test.insert("1");
    test_graph.find_all_paths("3", "4", close_test);
    std::cout << test_graph.mini_tour_and_return("2");
}
