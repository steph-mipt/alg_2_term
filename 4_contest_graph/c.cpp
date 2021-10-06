#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>

class Graph {
private:
    std::vector<std::vector<int>> adjancency_list_;
    int num_vertices_;
    /// 0 - white, 1 - gray, (-1) - black
    enum class Colors {
      kWhite = 0,
      kGray = 1,
      kBlack = -1,
    };

    std::vector<int> colors_;
    std::stack<int> way;

    bool DFS(int v) {
        colors_[v] = Colors.kGray;
        for (auto vertex : adjancency_list_[v]) {
            if (colors_[vertex] == Colors.kGray) {
                way.emplace(v);
                way.emplace(vertex);
                return true;
            } else if (colors_[vertex] == Colors.kBlack) {
                continue;
            } else {
                way.emplace(v);
                if (DFS(vertex))
                    return true;
                way.pop();
            }
        }
        colors_[v] = Colors.kBlack;
        return false;
    }

public:
    Graph(int num_vertices) : num_vertices_(num_vertices), adjancency_list_(num_vertices) {
        colors_ = std::vector<int>(num_vertices, 0);
    }

    void AddEdge(int first, int second) {
        adjancency_list_[first - 1].push_back(second - 1);
    }

    void solve(void) {
        for (int i = 0; i < num_vertices_; ++i) {
            if (colors_[i] == Colors.kWite) {
                if (DFS(i)) {
                    std::cout << "YES\n";

                    std::vector<int> tmp;
                    int x = way.top();
                    way.pop();
                    tmp.reserve(way.size());
                    while (way.top() != x) {
                        tmp.push_back(way.top());
                        way.pop();
                    }
                    tmp.push_back(x);
                    std::reverse(tmp.begin(), tmp.end());
                    for (auto vertex : tmp) {
                        std::cout << vertex + 1 << " ";
                    }
                    return;
                }
            }
        }
        std::cout << "NO";
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
