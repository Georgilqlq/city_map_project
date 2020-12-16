#include "graph.h"
#include <iostream>
// #include <Windows.h>

int main()
{
    // SetConsoleCP(866);
    // SetConsoleOutputCP(866);

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

    std::cout << test_graph.is_it_reachable("2", "1") << std::endl;
    test_graph.find_all_paths("3", "4");
    std::cout << test_graph.can_reach_all_vertices("4") << std::endl;
    test_graph.find_all_dead_ends();

    std::set<std::string> close_test;
    close_test.insert("1");
    test_graph.find_all_paths("3", "4", close_test);
    std::cout << test_graph.mini_tour_and_return("2") << std::endl;

    Graph second_test;
    second_test.add_vertex("1");
    second_test.add_vertex("2");
    second_test.add_vertex("3");
    second_test.add_vertex("4");
    second_test.add_vertex("5");

    second_test.add_edge("2", "4", 2);
    second_test.add_edge("2", "3", 2);

    second_test.add_edge("1", "2", 4);
    second_test.add_edge("3 ", "1", 5);
    second_test.add_edge("4", "5", 6);
    second_test.add_edge("5", "2", 6);

    second_test.start_euler_tour("1");

    Graph third_test("input.txt");
    third_test.find_all_paths("Попа", "BSFS");
    std::wcout << "ПопаAAAаааадавaddwa";
}
