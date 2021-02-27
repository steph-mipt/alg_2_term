#include <fstream>
#include <vector>
#include <iostream>
#include <list>
#include <string>

template<typename T, int SIZE>
class HashTable {
public:
    int size = 0;
    std::vector<std::list<std::pair<T, T>>> table;

    HashTable( void ) {
        this->size = SIZE;
        this->table.resize(this->size);
    }

    ~HashTable( void ) = default;

    bool put( T &x, T &y ) {
        long long h = hash(x);
        bool f = false;

        for (auto &i : table[h])
        {
            if (i.first == x) {
                i.second = y;
                return true;
            }
        }
        table[h].push_front({x, y});
        return false;
    }

    bool pop( T &x ) {
        long long h = hash(x);

        for (auto &i : table[h])
        {
            if (i.first == x) {
                table[h].remove(i);
                return true;
            }
        }
        return false;
    }

    T get( T &x ) {
        long long h = hash(x);
        bool f = false;

        for (auto &i : table[h])
        {
            if (i.first == x) {
                return i.second;
            }
        }
        return "";
    }
private:
    long long hash( T &x ) {
        long long ans = 0, X = 1, p = 3284243;

        for (char i : x)
        {
            ans += (X * i);
            ans %= this->size;
            X *= p;
            X %= this->size;
        }

        return ans;
    }
};


int main( void ) {
    std::string in, arg1, arg2;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);

    HashTable<std::string, 100000> A;

    while (std::cin >> in) {
        switch (in[0]) {
            case 'p':
                std::cin >> arg1 >> arg2;
                A.put(arg1, arg2);
                break;
            case 'd':
                std::cin >> arg1;
                A.pop(arg1);
                break;
            case 'g':
                std::cin >> arg1;
                auto tmp = A.get(arg1);
                if (tmp == "") {
                    std::cout << "none\n";
                } else {
                    std::cout << tmp << "\n";
                }
                break;
        }
    }
    return 0;
}
