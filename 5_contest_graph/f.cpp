#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

struct Edge {
public:
    long long end, weight;

    Edge(const long long &end, const long long &weight) : end(end), weight(weight) {
    }
};


class Graph {
private:
    long long num_vertices_;
    long long start;
    long long end;

    std::vector<long long> dist_;
    std::vector<std::vector<int>> adjancency_list_;
    std::vector<std::vector<Edge>> edges_;
public:
    Graph(long long num_vertices, long long main, long long end) : num_vertices_(num_vertices),
                                                                   adjancency_list_(num_vertices), end(end - 1) {
        edges_.resize(num_vertices);
        dist_ = std::vector<long long>(num_vertices, std::numeric_limits<long long>::max());
        dist_[main - 1] = 0;
        start = main - 1;
    }

    void AddEdge(long long first, long long second, long long weight) {
        edges_[first - 1].push_back(Edge(second - 1, weight));
        edges_[second - 1].push_back(Edge(first - 1, weight));
        adjancency_list_[first - 1].push_back(second - 1);
        adjancency_list_[second - 1].push_back(first - 1);
    }

    void solve(void) {
        std::set<std::pair<long long, long long>> set;

        set.insert({dist_[start], start});
        while (!set.empty()) {
            auto cur = set.begin()->second;

            set.erase(set.begin());
            for (int i = 0; i < adjancency_list_[cur].size(); ++i) {
                auto &a = adjancency_list_[cur];
                if (dist_[a[i]] > dist_[cur] + edges_[cur][i].weight) {
                    dist_[a[i]] = dist_[cur] + edges_[cur][i].weight;
                    set.insert({dist_[a[i]], a[i]});
                }
            }
        }

        if (dist_[end] == std::numeric_limits<long long>::max()) {
            std::cout << -1;
        } else {
            std::cout << dist_[end] << " ";
        }

    }
};

int main() {
    long long n, m, s, t;
    std::cin >> n >> m;
    std::cin >> s >> t;


    Graph g(n, s, t);

    for (long long i = 0; i < m; ++i) {
        long long vertex1, vertex2, weight;

        std::cin >> vertex1 >> vertex2 >> weight;
        g.AddEdge(vertex1, vertex2, weight);
    }

    g.solve();

    return 0;
}

