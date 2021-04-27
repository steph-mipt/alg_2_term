#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <set>

class Graph {
private:
    std::vector<std::vector<int>> adjancency_list_;
    int num_vertices_;
    std::vector<int> time_in_;
    std::vector<int> up_;
    int time_ = 0;
    /// 0 - white, 1 - gray, (-1) - black
    enum class Colors {
      kWhite = 0,
      kGray = 1,
      kBlack = -1,
    };

    std::vector<int> colors_;
    std::set<int> articula_points_;

    void DFS(int v, int p = -1) {
        int children = 0;

        colors_[v] = Colors.kGray;
        up_[v] = time_in_[v] = time_++;
        for (auto vertex : adjancency_list_[v]) {
            if (vertex != p) {
                if (colors_[vertex] == Colors.kGray) {
                    up_[v] = std::min(up_[v], time_in_[vertex]);
                    continue;
                } else if (colors_[vertex] == Colors.kBlack) {
                    continue;
                } else {
                    DFS(vertex, v);
                    up_[v] = std::min(up_[v], up_[vertex]);
                    if (up_[vertex] >= time_in_[v] && p != -1) {
                        articula_points_.insert(v);
                    }
                    ++children;
                }
            }
        }
        colors_[v] = Colors.kBlack;
        if (p == -1 && children > 1) {
            articula_points_.insert(v);
        }
    }

public:
    Graph(int num_vertices) : num_vertices_(num_vertices), adjancency_list_(num_vertices) {
        colors_ = std::vector<int>(num_vertices, Colors.kWhite);
        time_in_ = std::vector<int>(num_vertices, 0);
        up_ = std::vector<int>(num_vertices, 0);
    }

    void AddEdge(int first, int second) {
        adjancency_list_[first - 1].push_back(second - 1);
        adjancency_list_[second - 1].push_back(first - 1);
    }

    void solve(void) {
        DFS(0);

        std::cout << articula_points_.size() << "\n";
        for (auto i : articula_points_) {
            std::cout << i + 1 << " ";
        }
    }
};

int main(void) {
    int N, M;

    std::cin >> N >> M;

    Graph g(N);
    for (int i = 1; i <= M; ++i) {
        int v1, v2;

        std::cin >> v1 >> v2;
        g.AddEdge(v1, v2);
    }

    g.solve();


    return 0;
}
