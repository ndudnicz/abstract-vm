#include "Operand.class.hpp"
#include <iostream>
#include <vector>
#include "Cpu.class.hpp"

int		main(int ac, char **av) {
	// Operand<int32_t> *op = new Operand<int32_t>(1, INT32);
	// Operand<int8_t> *op2 = new Operand<int8_t>(1, INT8);
	// Operand<double> *opdouble = new Operand<double>(1.0001, DOUBLE);
	//
	// IOperand *p = op;
	// // std::vector<IOperand*> v;
	// // std::vector<IOperand*> it;
	// // v.insert(it, op);
	// // v.insert(it, op2);
	//
	// std::cout << op->toString() << std::endl;
	// std::cout << op2->toString() << std::endl;
	// std::cout << opdouble->toString() << std::endl;
	Cpu cpu;
	(void)cpu.run(ac, av);
	return 0;
}
