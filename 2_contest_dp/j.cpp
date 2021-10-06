#include <iostream>
#include <vector>

int main( void ) {
    int sum, n;
    std::cin >> sum >> n;
    std::vector<bool> items(sum + 1, false);

    items[0] = true;

    for (int i = 0; i < n; ++i){
        int weight;

        std::cin >> weight;
        for (int j = sum - weight; j >= 0; --j){
            if (items[j]) {
                items[j + weight] = true;
            }
        }
    }

    for (int i = sum; i > 0; i--){
        if (items[i] != 0){
            std::cout << i;
            return 0;
        }
    }
    
    std::cout << 0;
    return 0;
}
