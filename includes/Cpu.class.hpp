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

enum eInstruction {
	EIPUSH = 0,
	EIASSERT,
	EIPOP,
	EIDUMP,
	EIADD,
	EISUB,
	EIMUL,
	EIDIV,
	EIMOD,
	EIPRINT,
	EIEXIT,
	EICOMMENT,
	EIINVALID
};

class Cpu {

private:
	Cpu( Cpu const & src );
	Cpu &	operator=( Cpu const & rhs );

	std::vector<std::string>	_input;
	std::vector<IOperand *>		_stack;

	eInstruction		_getInstruction(
		std::string const str,
		std::smatch *sm,
		std::string **s
	);
	int							_getStdin( void );
	int							_getFile( char const *const filename );
	int							_generateStack( void );
	int							_validInput( void );
	int							_regValidInstruction(
		int const line,
		std::string const str,
		std::string **matchstr2
	);
	int							_regValidSm(
		int const line,
		std::string &sm1
	) const;
	int							_exec( void );

	/* INSTRUCTIONS ============================================================*/
	int		_push( std::string str );
	int		_assert( std::string str );
	int		_pop( void );
	int		_dump( void );
	int		_add( void );
	int		_sub( void );
	int		_mul( void );
	int		_div( void );
	int		_mod( void );
	int		_print( void );

	/* OVERFLOW CHECK ==========================================================*/
	int	_add_overflow( IOperand *v1, IOperand *v2, eOperandType type, int *overflow ) const;
	int	_sub_overflow( IOperand *v1, IOperand *v2, eOperandType type, int *overflow ) const;
	int	_mul_overflow( IOperand *v1, IOperand *v2, eOperandType type, int *overflow ) const;
	int	_div_overflow( IOperand *v1, IOperand *v2, eOperandType type, int *overflow ) const;

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
	class UnknownTypeException : public std::runtime_error {
	public:
		UnknownTypeException(const std::string& error_message);
	};

	/* INVALID VALUE EXCEPTION =================================================*/
	class InvalidValueException : public std::runtime_error {
	public:
		InvalidValueException(const std::string& error_message);
	};

	/* ASSERT FAILED EXCEPTION =================================================*/
	class AssertFailedException : public std::exception {
	public:
		AssertFailedException( void ) throw();
		~AssertFailedException( void ) throw();
		virtual const char *what( void ) const throw();
	};

	/* POP EMPTY STACK EXCEPTION ===============================================*/
	class PopEmptyStackException : public std::exception {
	public:
		PopEmptyStackException( void ) throw();
		~PopEmptyStackException( void ) throw();
		virtual const char *what( void ) const throw();
	};

	/* NOT ENOUGHT ELEMENT IN STACK EXCEPTION ==================================*/
	class NotEnoughElementsInStackException : public std::exception {
	public:
		NotEnoughElementsInStackException( void ) throw();
		~NotEnoughElementsInStackException( void ) throw();
		virtual const char *what( void ) const throw();
	};

	/* OPERATION OVERFLOW EXCEPTION ============================================*/
	class OperationOverflowException : public std::exception {
	public:
		OperationOverflowException( void ) throw();
		~OperationOverflowException( void ) throw();
		virtual const char *what( void ) const throw();
	};

	/* OPERATION UNDERFLOW EXCEPTION ===========================================*/
	class OperationUnderflowException : public std::exception {
	public:
		OperationUnderflowException( void ) throw();
		~OperationUnderflowException( void ) throw();
		virtual const char *what( void ) const throw();
	};

	/* OPERATION UNDERFLOW EXCEPTION ===========================================*/
	class PrintWrongTypeException : public std::exception {
	public:
		PrintWrongTypeException( void ) throw();
		~PrintWrongTypeException( void ) throw();
		virtual const char *what( void ) const throw();
	};

	/* DIVISION BY 0 EXCEPTION =================================================*/
	class FloatingPointException : public std::exception {
	public:
		FloatingPointException( void ) throw();
		~FloatingPointException( void ) throw();
		virtual const char *what( void ) const throw();
	};

	/* OVERFLOW EXCEPTION ======================================================*/
	class OverflowException : public std::exception {
	public:
		OverflowException( void ) throw();
		~OverflowException( void ) throw();
		virtual const char *what( void ) const throw();
	};

	/* UNDERFLOW EXCEPTION =====================================================*/
	class UnderflowException : public std::exception {
	public:
		UnderflowException( void ) throw();
		~UnderflowException( void ) throw();
		virtual const char *what( void ) const throw();
	};

};

#endif
