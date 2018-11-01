#ifndef STACK_CLASS_HPP
# define STACK_CLASS_HPP

# include <vector>
# include "IOperand.hpp"

class Stack {

private:
	Stack( Stack const & src );
	Stack &	operator=( Stack const & rhs );

	std::vector<IOperand*>	stack;

protected:

public:
	Stack( void );
	~Stack( void );

};

#endif
