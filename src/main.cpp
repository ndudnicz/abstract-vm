#include "Operand.hpp"
#include <iostream>

int		main(int ac, char **av) {
	Operand<int32_t> *op = new Operand<int32_t>(1, INT32);
	Operand<int8_t> *op2 = new Operand<int8_t>(1, INT8);
	Operand<double> *opdouble = new Operand<double>(1.0001, DOUBLE);
	std::cout << op->toString() << std::endl;
	std::cout << op2->toString() << std::endl;
	std::cout << opdouble->toString() << std::endl;
	return 0;
}
