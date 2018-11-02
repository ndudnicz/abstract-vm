#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP

# include "IOperand.hpp"

// typedef struct	s_registers {
// 	int8_t	_int8;
// 	int16_t	_int16;
// 	int32_t	_int32;
// 	float		_float;
// 	double	_double;
// }								t_registers;

template <typename T>
class Operand: public IOperand {

private:

	Operand( void );

	T							_value;
	eOperandType	_type;
	std::string		_str;
	// static t_registers	_registers;
	// static int const		_registersIndex[5]; = {
	// 	sizeof( int8_t ),
	// 	sizeof( int16_t ),
	// 	sizeof( int32_t ),
	// 	sizeof( float ),
	// 	sizeof( double )
	// }

protected:

public:


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
