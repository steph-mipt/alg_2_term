#include <vector>
#include <algorithm>
#include <iostream>

class Graph {
private:
    std::vector<std::vector<int>> adjancency_list_;
    std::vector<int> time_in_, time_out_;
    int num_vertices_;
    int time_ = 0;
    int root_;

public:
    Graph(int num_vertices) : num_vertices_(num_vertices), adjancency_list_(num_vertices) {
        time_in_.resize(num_vertices);
        time_out_.resize(num_vertices);
    }

    void AddEdge(int first, int second) {
        adjancency_list_[first - 1].push_back(second - 1);
        if (second != 0){
            adjancency_list_[second - 1].push_back(first - 1);
        } else {
            root_ = first - 1;
        }
    }

    void solve(void) {
        DFS(root_);
    }

    void DFS(int v, int p = -1) {
        time_in_[v] = time_++;
        for (auto vertex : adjancency_list_[v]) {
            if (vertex != p) {
                DFS(vertex, v);
            }
        }
        time_out_[v] = time_++;
    }

    bool isParent(int parent, int child) {
        return time_in_[parent - 1] < time_in_[child - 1] and time_out_[parent - 1] > time_out_[child - 1];
    }
};

int main(void) {
    int N, m;

    std::cin >> N;
    Graph g(N);
    for (int i = 1; i <= N; ++i) {
        int tmp;

        std::cin >> tmp;
        g.AddEdge(i, tmp);
    }
    std::cin >> m;
    g.solve();
    for (int i = 0; i < m; ++i) {
        int child, parent;

        std::cin >> parent >> child;
        std::cout << g.isParent(parent, child) << "\n";
    }

    return 0;
}
