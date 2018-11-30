#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP

# include "IOperand.hpp"
# include <stdexcept>

# define MAX(A, B) (A > B ? A : B)

template <typename T>
class Operand: public IOperand {

private:

	Operand( void );

	eOperandType	_type;
	std::string		_str;

protected:

public:

	Operand( std::string const & str, eOperandType type );
	Operand( Operand const & src );
	~Operand( void );

	Operand		&operator=( Operand const & rhs );
	IOperand const	*operator+( IOperand const & rhs ) const;
	IOperand const	*operator-( IOperand const & rhs ) const;
	IOperand const	*operator*( IOperand const & rhs ) const;
	IOperand const	*operator/( IOperand const & rhs ) const;
	IOperand const	*operator%( IOperand const & rhs ) const;

	int								getPrecision( void ) const;
	eOperandType			getType( void ) const;
	std::string const	&toString( void ) const;

};

#endif
