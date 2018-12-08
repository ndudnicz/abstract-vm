#include "Cpu.class.hpp"

int		main(int ac, char const **av) {
	Cpu cpu;
	static_cast<void>( cpu.run(ac, av) );
	return 0;
}
