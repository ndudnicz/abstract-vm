#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"

template <typename T>
class Operand: public IOperand {

private:

	Operand( void );

	T							_value;
	eOperandType	_type;

protected:

public:

	std::string	str;

	Operand( T value, eOperandType type );
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
	T									getValue( void ) const;
	std::string const	&toString( void ) const;
};

#endif
