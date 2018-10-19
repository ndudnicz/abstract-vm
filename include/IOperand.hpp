#include <string>

class IOperand {

private:

protected:

public:
	IOperand( void );
	IOperand( IOperand const & src );

	IOperand &	operator=( IOperand const & rhs );

	virtual int				getPrecision( void ) const = 0;
	virtual eOperandType	getType( void ) const = 0;

	virtual IOperand const*	operator+( IOperand const & rhs ) const = 0;
	virtual IOperand const*	operator-( IOperand const & rhs ) const = 0;
	virtual IOperand const*	operator*( IOperand const & rhs ) const = 0;
	virtual IOperand const*	operator/( IOperand const & rhs ) const = 0;
	virtual IOperand const*	operator%( IOperand const & rhs ) const = 0;

	virtual std::string const & toString( void ) const = 0;

	virtual ~IOperand( void ) = 0;

};
