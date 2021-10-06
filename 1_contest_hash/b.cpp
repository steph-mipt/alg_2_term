#include <fstream>
#include <vector>
#include <iostream>
#include <list>
#include <string>

template<typename T>
class HashTable {
public:
    int size = 0;
    std::vector<std::list<std::pair<T, T>>> table;

    HashTable( int size = 1000000 ) {
        this->size = SIZE;
        this->table.resize(this->size);
    }

    ~HashTable( void ) = default;

    std::pair<T, T> & put( const T &x, const T &y ) {
        long long h = hash(x);
        bool f = false;

        for (auto &element : table[h]) {
            if (element.first == x) {
                element.second = y;
                return element;
            }
        }
        table[h].push_front({x, y});
        return table[h].front();
    }

    bool pop( const T &x ) {
        long long h = hash(x);

        for (auto &element : table[h]) {
            if (element.first == x) {
                table[h].remove(element);
                return true;
            }
        }
        return false;
    }

    T get( const T &x ) {
        long long h = hash(x);
        bool f = false;

        for (auto &element : table[h]) {
            if (element.first == x) {
                return element.second;
            }
        }
        return 0;
    }
private:
    long long hash( const T &x ) {
        long long constant1 = 37, constant2 = 191, p = 3284243;

        return (constant1 + constant2 * x) % p % this->size;
    }
public:
    int swap( const T x, const T y ) {
        long long hx = hash(x), hy = hash(y);
        std::pair<T, T> *tmp1, *tmp2;
        bool f = false;

        for (auto &element : table[hx]) {
            if (element.first == x) {
                tmp1 = &element;
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
    HashTable<long long> A;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> ind1 >> ind2;
        std::cout << A.swap(ind1, ind2) << "\n";
    }

    return 0;
}
