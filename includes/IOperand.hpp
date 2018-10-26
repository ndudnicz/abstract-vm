#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <string>

enum eOperandType
{
	INT8 = 0,
	INT16,
	INT32,
	FLOAT,
	DOUBLE
};

class IOperand {

private:

protected:

public:
	virtual int				getPrecision( void ) const = 0;
	virtual eOperandType	getType( void ) const = 0;

	virtual IOperand &	operator=( IOperand const & rhs ) const = 0;
	virtual IOperand const*	operator+( IOperand const & rhs ) const = 0;
	virtual IOperand const*	operator-( IOperand const & rhs ) const = 0;
	virtual IOperand const*	operator*( IOperand const & rhs ) const = 0;
	virtual IOperand const*	operator/( IOperand const & rhs ) const = 0;
	virtual IOperand const*	operator%( IOperand const & rhs ) const = 0;

	virtual std::string const & toString( void ) const = 0;

	virtual ~IOperand( void ) {};

};

#endif
