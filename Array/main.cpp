#include <iostream>
#include <algorithm>
#include <numeric>
#include "array.hpp"

int main() {
    ds::array<int, 5> arr = {1, 2, 3, 4, 5};
    ds::array<int, 5> arr2 = {5, 4, 3, 2, 1};
    auto max = std::max_element(arr.begin(), arr.end());
    std::cout << *max << std::endl;
    std::for_each(arr.begin(), arr.end(), [](int n){std::cout << n << std::endl;});
    arr2.swap(arr);
    std::cout << arr2 << std::endl;
    return EXIT_SUCCESS;
}