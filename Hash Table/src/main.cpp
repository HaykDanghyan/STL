#include "hash.h"

int main() {
    hash_table<char, int> ht {{'a', 97}, {'b', 98}};
    ht.insert(std::make_pair('c', 99));
    ht.insert(std::make_pair('d', 100));
    ht.insert(std::make_pair('e', 101));
    ht.insert(std::make_pair('f', 102));
    ht.insert(std::make_pair('g', 103));
    ht.insert(std::make_pair('a', 1000));
    ht.insert(std::make_pair('a', 999));
    ht.insert(std::make_pair('a', 754));
    std::cout << ht << std::endl;
}
