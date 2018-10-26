#include <iostream>
#include "Operand.hpp"

int		main(int ac, char **av) {
	Operand<int8_t> *op = new Operand<int8_t>(1, INT8);
	std::cout << "coucou" << std::endl;
	return 0;
}
