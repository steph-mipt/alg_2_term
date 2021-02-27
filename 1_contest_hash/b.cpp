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

    std::pair<T, T> & put( T &x, T &y ) {
        long long h = hash(x);
        bool f = false;

        for (auto &i : table[h])
        {
            if (i.first == x) {
                i.second = y;
                return i;
            }
        }
        table[h].push_front({x, y});
        return table[h].front();
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
        return 0;
    }
private:
    long long hash( T &x ) {
        long long A = 37, B = 191, p = 3284243;

        return (A + B * x) % p % this->size;
    }
public:
    int swap( T x, T y ) {
        long long hx = hash(x), hy = hash(y);
        std::pair<T, T> *tmp1, *tmp2;
        bool f = false;

        for (auto &i : table[hx]) {
            if (i.first == x) {
                tmp1 = &i;
                f = true;
                break;
            }
        }
        if (!f) {
            tmp1 = &this->put(x, x);
        }
        f = false;
        for (auto &i : table[hy]) {
            if (i.first == y) {
                tmp2 = &i;
                f = true;
                break;
            }
        }
        if (!f) {
            tmp2 = &this->put(y, y);
        }

        std::swap(tmp1->second, tmp2->second);
        return abs(tmp1->second - tmp2->second);
    }
};

int main( void ) {
    std::string in, arg1, arg2;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, ind1, ind2;
    HashTable<long long, 100000> A;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> ind1 >> ind2;
        std::cout << A.swap(ind1, ind2) << "\n";
    }

    return 0;
}
