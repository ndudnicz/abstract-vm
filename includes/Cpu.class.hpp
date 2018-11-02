#ifndef CPU_CLASS_HPP
# define CPU_CLASS_HPP

# include "IOperand.hpp"
# include "Stack.class.hpp"
# include <vector>
# include <iostream>
# include <stdexcept>
# include <fstream>

# define END_OF_INPUT	";;"

# define _CONCAT(A, B) A # B
# define EVALUATOR(A, B) _CONCAT(A, B)
# define CONCAT(A, B) EVALUATOR(A, B)

class Cpu {

private:
	Cpu( Cpu const & src );
	Cpu &	operator=( Cpu const & rhs );

	std::vector<std::string>	_input;
	std::vector<Stack*>				_stack;

	int	_getStdin( void );
	int	_getFile( char const *const filename );

	void	_printInput( void );// DEBUG

protected:

public:
	Cpu( void );
	~Cpu( void );

	int		run( int ac, char const **av );

	/* DIDN'T GET END_OF_INPUT STRING EXCEPTION ================================*/
	class DidntGetEndOfInputException : public std::exception {

	public:
		DidntGetEndOfInputException( void ) throw();
		~DidntGetEndOfInputException( void ) throw();
		virtual const char *what( void ) const throw();

	};

	/* CANT OPEN FILE EXCEPTION ================================================*/
	class CantOpenFileException : public std::runtime_error {

	public:
		CantOpenFileException(const std::string& error_message);

	};

};

#endif
