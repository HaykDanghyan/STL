#include <iostream>
#include "stack.h"

int main() {
    stack<int> st {1, 2, 3, 4, 5};
    st.pop();
    st.push(124);
    std::cout << st << std::endl;
}