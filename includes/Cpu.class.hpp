#ifndef CPU_CLASS_HPP
# define CPU_CLASS_HPP

# include "IOperand.hpp"
// # include "Stack.class.hpp"
# include <vector>
# include <iostream>
# include <stdexcept>
# include <fstream>
# include <regex>

# define END_OF_INPUT	";;"

# define EXCEP_CANT_OPEN_FILE					"Exception : Can't open file : "
# define EXCEP_UNKNOWN_INSTRUCTION		"Exception : Unknown instruction line : "
# define EXCEP_UNKNOWN_TYPE						"Exception : Unknown type line : "
# define EXCEP_INVALID_VALUE					"Exception : Invalid value line : "

# define _CONCAT(A, B) A # B
# define EVALUATOR(A, B) _CONCAT(A, B)
# define CONCAT(A, B) EVALUATOR(A, B)

class Cpu {

private:
	Cpu( Cpu const & src );
	Cpu &	operator=( Cpu const & rhs );

	std::vector<std::string>	_input;
	std::vector<IOperand*>		_stack;

	int		_getStdin( void );
	int		_getFile( char const *const filename );
	int		_generateStack( void );
	int		_validInput( void );
	int		_regValidInstruction(
		int const line,
		std::string const str,
		std::smatch *sm
	) const;
	int		_regValidSm(
		int const line,
		std::string sm1
	) const;

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

	/* UNKNOWN INSTRUCTION EXCEPTION ===========================================*/
	class UnknownInstructionException : public std::runtime_error {
	public:
		UnknownInstructionException(const std::string& error_message);
	};

	/* UNKNOWN TYPE OR VALUE EXCEPTION =========================================*/
	class UnknownTypeOrValueException : public std::runtime_error {
	public:
		UnknownTypeOrValueException(const std::string& error_message);
	};

	/* INVALID VALUE EXCEPTION =================================================*/
	class InvalidValueException : public std::runtime_error {
	public:
		InvalidValueException(const std::string& error_message);
	};

};

#endif
