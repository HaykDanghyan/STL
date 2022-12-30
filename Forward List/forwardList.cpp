#include "forward.h"

int main() {	
	forward_list<int> f1 {4, 5, 2, 3, 6, 1};
	f1.sort();
	for (const auto& elem : f1) {
		std::cout << elem << "   ";
	}
	std::cout << std::endl;
	forward_list<double> f2(3, 3.14);
	for (auto it = f2.begin(); it != f2.end(); ++it){
		std::cout << *it << "  ";
	}
	std::cout << std::endl;
	f1.clear();
	std::cout << std::boolalpha << f1.empty() << std::endl;
	return 0;
}
