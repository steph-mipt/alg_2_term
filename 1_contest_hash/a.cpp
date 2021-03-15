#include <iostream>
#include <vector>
#include <list>
#include <string>
#define T_SIZE 100000


class hashTable{
private:
  std::vector<std::list<std::pair<std::string, int>>> table;

public:
  hashTable( void ) {
    table.resize(T_SIZE);
  }

  long long add( const int val, const std::string &str ) {
    long long h = hash(str);

    for (auto &i : table[h]) {
      if (i.first == in) {
        i.second += val;
    
        return i.second;
      }
    }
    table[h].push_front({str, val});
   
    return val;
  }

  long long hash( const std::string &str ) {
      long long
           ans = 0,
           x = 1,
           p = 31;

      for (char &i : str) {
          ans += (x * i);
          ans %= T_SIZE;
          x *= p;
          x %= T_SIZE;
      }

      return ans;
  }
};

int main( void ) {
    std::string in;
    int val;
    hashTable hash_table();

    while (std::cin >> in) {
        std::cin >> val;
        std::cout << hash_table.add(val, in);
    }

    return 0;
}

