#include <fstream>
#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <optional>

template<typename T>
class HashTable {
public:
    int size = 0;
    std::vector<std::list<std::pair<T, T>>> table;

    HashTable( int size = 100000 ) {
        this->size = SIZE;
        this->table.resize(this->size);
    }

    ~HashTable( void ) = default;

    bool put( const T &x, const T &y ) {
        long long h = hash(x);
        bool f = false;

        for (auto &i : table[h]) {
            if (i.first == x) {
                i.second = y;
                return true;
            }
        }
        table[h].push_front({x, y});
        return false;
    }

    bool pop( const T &x ) {
        long long h = hash(x);

        for (auto &i : table[h]) {
            if (i.first == x) {
                table[h].remove(i);
                return true;
            }
        }
        return false;
    }

    std::optional<T> get( const T &x ) {
        long long h = hash(x);
        bool f = false;

        for (auto &i : table[h]) {
            if (i.first == x) {
                return i.second;
            }
        }
        return {};
    }
private:
    long long hash( T &x ) {
        long long ans = 0, mul = 1, prime = 3284243;

        for (char i : x) {
            ans += (mul * i);
            ans %= this->size;
            mul *= prime;
            mul %= this->size;
        }

        return ans;
    }
};


int main( void ) {
    std::string in, arg1, arg2;
    std::ofstream outfile;
    std::ifstream infile;
    HashTable<std::string> A;

    outfile.open("map.out");
    infile.open("map.in");

    while (infile >> in) {
        switch (in[0]) {
            case 'p':
                infile >> arg1 >> arg2;
                A.put(arg1, arg2);
                break;
            case 'd':
                infile >> arg1;
                A.pop(arg1);
                break;
            case 'g':
                infile >> arg1;
                auto tmp = A.get(arg1);
                if (tmp == "") {
                    outfile << "none\n";
                } else {
                    outfile << tmp << "\n";
                }
                break;
        }
    }
    outfile.close();
    infile.close();
    return 0;
}
