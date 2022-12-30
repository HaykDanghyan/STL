#include <iostream>
#include "VectorBool.h"
int main()
{
    VectorBool ob(8 , 1);
    std::cout << ob << std::endl;
    ob.push_back(0);
    ob.push_back(1);
    ob.push_back(1);
    ob.push_back(0);
    ob.push_back(1);
    ob.pop_back();
    ob.replace(0 , 0);
    std::cout << ob << std::endl;
    ob.clear();
    if(ob.isEmpty())
    {
        std::cout << "VectorBool ob is empty!" << std::endl;
    }
}