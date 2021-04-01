#include <iostream>
#include <vector>
#include <list>
#include <string>


class hashTable{
private:
  std::vector<std::list<std::pair<std::string, int>>> table;
  int size_;

public:
  hashTable( int size = 1000000 ) : size_(size) {
    table.resize(size);
  }

  long long add( const int val, const std::string &str ) {
    long long h = hash(str);

    for (auto &element : table[h]) {
      if (element.first == in) {
        element.second += val;
    
        return element.second;
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

      for (char &ch : str) {
          ans += (x * ch);
          ans %= size;
          x *= p;
          x %= size;
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

