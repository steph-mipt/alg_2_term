#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct Edge {
public:
    long long start, end, weight;

    Edge(const long long &start, const long long &end, const long long &weight) : start(start), end(end),
                                                                                  weight(weight) {
    }

    Edge() = default;
};


class Graph {
private:
    long long num_vertices_;
    enum class Color {
        kWhite = 0,
        kBlack = -1,
    };
    std::vector<Color> colors_;
    std::vector<std::vector<Edge>> edges_;
public:
    Graph(long long num_vertices) : num_vertices_(num_vertices) {
        edges_.resize(num_vertices);
        colors_.resize(num_vertices, Color::kWhite);
    }

    void AddEdge(long long first, long long second, long long weight) {
        edges_[first - 1].push_back(Edge(first - 1, second - 1, weight));
        edges_[second - 1].push_back(Edge(second - 1, first - 1, weight));
    }

    long long solve(void) {
        std::vector<Edge> min_edges(num_vertices_, Edge(0, 0, std::numeric_limits<long long>::max()));
        std::set<std::pair<long long, long long>> used;
        used.insert({0, 0});
        long long sum_weight = 0;

        for (long long i = 0; i < num_vertices_; i++) {
            long long v = used.begin()->second;
            used.erase(used.begin());
            colors_[v] = Color::kBlack;

            for (const Edge &e : edges_[v]) {
                long long end = e.end, weight = e.weight;

                if (weight < min_edges[end].weight && colors_[end] != Color::kBlack) {
                    used.erase({min_edges[end].weight, end});
                    min_edges[end] = Edge(v, end, weight);
                    used.insert({min_edges[end].weight, end});
                }
            }
        }
        for (const auto &e : min_edges) {
            if (e.weight != std::numeric_limits<long long>::max())
                sum_weight += e.weight;
        }

        return sum_weight;
    }
};

int main() {
    long long n, m;
    std::cin >> n >> m;


    Graph g(n);

    for (long long i = 0; i < m; ++i) {
        long long vertex1, vertex2, weight;

        std::cin >> vertex1 >> vertex2 >> weight;
        g.AddEdge(vertex1, vertex2, weight);
    }

    std::cout << g.solve();

    return 0;
}
