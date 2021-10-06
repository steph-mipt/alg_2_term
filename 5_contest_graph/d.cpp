#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

const long long INF = 10000000000000000;

struct Edge {
public:
    long long start, end, weight;

    Edge(const long long &start, const long long &end, const long long &weight) : end(end), weight(weight),
                                                                                  start(start) {
    }
};


class Graph {
private:
    long long num_vertices_;
    long long start;

    enum class Color {
        kWhite = 0,
        kGray = 1,
        kBlack = -1,
    };

    std::vector<long long> is_unreach;
    std::vector<Color> colors_;
    std::vector<long long> dist_;
    std::vector<std::vector<int>> adjancency_list_;
    std::vector<Edge> data_;

    void BFS(long long x) {
        std::queue<int> q;
        int current = -1;
        q.push(x);
        colors_[x] = Color::kWhite;

        while (!q.empty()) {
            current = q.front();
            q.pop();

            for (int vertex : adjancency_list_[current]) {
                if (colors_[vertex] == Color::kWhite) {
                    q.push(vertex);
                    colors_[vertex] = Color::kGray;
                    is_unreach[vertex] = -1;
                }
            }
        }
    }

public:

    Graph(long long num_vertices, long long main) : num_vertices_(num_vertices),
                                                    adjancency_list_(num_vertices) {
        colors_ = std::vector<Color>(num_vertices, Color::kWhite);

        is_unreach = std::vector<long long>(num_vertices, 0);
        dist_ = std::vector<long long>(num_vertices, INF);
        dist_[main - 1] = 0;
        start = main - 1;
    }

    void AddEdge(long long first, long long second, long long weight) {
        data_.push_back(Edge(first - 1, second - 1, weight));
        adjancency_list_[first - 1].push_back(second - 1);
    }

    void solve(void) {
        for (long long _ = 0; _ < num_vertices_ - 1; ++_) {
            for (auto &edge  : data_) {
                if (dist_[edge.end] > dist_[edge.start] + edge.weight and dist_[edge.start] != INF) {
                    dist_[edge.end] = dist_[edge.start] + edge.weight;
                }
            }
        }

        auto d = dist_;

        for (auto &edge  : data_) {
            if (dist_[edge.end] > dist_[edge.start] + edge.weight and dist_[edge.start] != INF) {
                dist_[edge.end] = dist_[edge.start] + edge.weight;
            }
        }


        for (long long i = 0; i < dist_.size(); ++i) {
            if (dist_[i] != d[i]) {
                BFS(i);
            }
        }

        for (long long i = 0; i < dist_.size(); ++i) {
            if (dist_[i] != d[i] or is_unreach[i] == -1) {
                std::cout << "-\n";
            } else if (dist_[i] != INF) {
                std::cout << dist_[i] << "\n";
            } else {
                std::cout << "*\n";
            }
        }
    }
};

int main() {
    long long n, m, s;
    std::cin >> n >> m >> s;

    Graph g(n, s);

    for (long long i = 0; i < m; ++i) {
        long long vertex1, vertex2, weight;

        std::cin >> vertex1 >> vertex2 >> weight;
        g.AddEdge(vertex1, vertex2, weight);
    }

    g.solve();

    return 0;
}

