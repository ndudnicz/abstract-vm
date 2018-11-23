#include "Operand.class.hpp"
#include <iostream>
#include <vector>
#include "Cpu.class.hpp"

int		main(int ac, char const **av) {
	Operand<int32_t> op("3", INT32);
	Operand<float> op2("200.222", FLOAT);
	Operand<float> opZero("0.0", FLOAT);
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
	static_cast<void>( cpu.run(ac, av) );
	// IOperand const *result = op + op2;
	// std::cout << (op + op2)->toString() << '\n';
	// std::cout << (op - op2)->toString() << '\n';
	// std::cout << (*(op + op2) * op)->toString() << '\n';
	// std::cout << (op2 / op)->toString() << '\n';
	// try {
	// 	std::cout << (op2 / opZero)->toString() << '\n';
	// } catch (Operand<float>::FloatingPoint &e) {
	// 	std::cout << e.what() << '\n';
	// }
	//
	// std::cout << (op2 % op)->toString() << '\n';
	// try {
	// 	std::cout << (op2 % opZero)->toString() << '\n';
	// } catch (Operand<float>::FloatingPoint &e) {
	// 	std::cout << e.what() << '\n';
	// }
	return 0;
}
