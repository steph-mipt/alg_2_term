#include <iostream>
#include <vector>


class solution {
private:
    std::vector<std::vector<int>> dp;
public:
    int ans = 0;

    solution( std::vector<int> &seq_1, std::vector<int> &seq_2 ) {
        int len_seq_1 = seq_1.size(), len_seq_2 = seq_2.size();

        dp = std::vector<std::vector<int>>(len_seq_1 + 1, std::vector<int>(len_seq_2 + 1, 0));

        for (int i = 0; i < len_seq_1; ++i) {
            for (int j = 0; j < len_seq_2; ++j) {
                if (seq_1[i] == seq_2[j]) {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                } else {
                    dp[i + 1][j + 1] = std::max(dp[i][j + 1], dp[i + 1][j]);
                }
            }
        }

        ans = dp[len_seq_1][len_seq_2];
    }
};

int main(void) {
    std::vector<int> X, Y;
    int n, m;

    std::cin >> n;
    X.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> X[i];
    }

    std::cin >> m;
    Y.resize(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> Y[i];
    }

    solution Sol(X, Y);
    std::cout << Sol.ans;

    return 0;
}