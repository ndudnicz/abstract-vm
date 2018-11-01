#ifndef CPU_CLASS_HPP
# define CPU_CLASS_HPP

# include "IOperand.hpp"
# include "Stack.class.hpp"
# include <vector>
# include <iostream>
# include <stdexcept>

# define END_OF_INPUT	";;"

# define _CONCAT(A, B) A # B
# define EVALUATOR(A, B) _CONCAT(A, B)
# define CONCAT(A, B) EVALUATOR(A, B)

class Cpu {

private:
	Cpu( Cpu const & src );
	Cpu &	operator=( Cpu const & rhs );

	std::vector<std::string>	input;
	std::vector<Stack*>				stack;

	int	getStdin( void );

	// DEBUG
	void	printInput( void );

protected:

public:
	Cpu( void );
	~Cpu( void );

	int		run( int ac, char **av );

	/* DIDN'T GET END_OF_INPUT STRING EXCEPTION ================================*/
	class DidntGetEndOfInputException : std::exception {

	public:
		DidntGetEndOfInputException( void ) throw();
		~DidntGetEndOfInputException( void ) throw();
		virtual const char *what( void ) const throw();

	};

};

#endif
