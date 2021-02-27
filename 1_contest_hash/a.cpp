#include <iostream>
#include <vector>
#include <list>
#include <string>
#define T_SIZE 100000

long long hash( std::string &str ) {
    long long ans = 0, x = 1, p = 31;

    for (char i : str)
    {
        ans += (x * i);
        ans %= T_SIZE;
        x *= p;
        x %= T_SIZE;
    }

    return ans;
}

int main( void ) {
    std::vector<std::list<std::pair<std::string, int>>> A;
    std::string in;
    int val;
    bool f = false;

    A.resize(T_SIZE);

    while (std::cin >> in) {
        std::cin >> val;

        long long h = hash(in);

        for (auto &i : A[h])
        {
           if (i.first == in) {
               i.second += val;
               f = true;
               std::cout << i.second << "\n";
               break;
           }
        }
        if (!f) {
            A[h].push_front({in, val});
            std::cout << val << "\n";
        }
        f = false;
    }
    return 0;
}

