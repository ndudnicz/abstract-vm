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

	Operand( T value, eOperandType type );
	Operand( Operand const & src );
	~Operand( void );

	IOperand &	operator=( IOperand const & rhs ) const;
	IOperand const	*operator+( IOperand const & rhs ) const;
	IOperand const	*operator-( IOperand const & rhs ) const;
	IOperand const	*operator*( IOperand const & rhs ) const;
	IOperand const	*operator/( IOperand const & rhs ) const;
	IOperand const	*operator%( IOperand const & rhs ) const;

	int								getPrecision( void ) const;
	eOperandType			getType( void ) const;
	std::string const	&toString( void ) const;
};

// #include "IOperand.hpp"
// #include "Factory.hpp"
// #include <iostream>
// #include <sstream>
// #include <iomanip>
// #include <string>
// #include <cmath>
//
// template <typename T>
// class eOperand : public IOperand
// {
// 	public:
// 		eOperand(T value);
// 		eOperand( void );
// 		~eOperand( void );
// 		IOperand const &operator=(eOperand const &rhs);
// 		eOperand(eOperand const &src);
//
// 		int 			getPrecision( void ) const;
// 		eOperandType 	getType( void ) const;
//
// 		IOperand const *operator + (IOperand const &rhs) const;
// 		IOperand const *operator - (IOperand const &rhs) const;
// 		IOperand const *operator * (IOperand const &rhs) const;
// 		IOperand const *operator / (IOperand const &rhs) const;
// 		IOperand const *operator % (IOperand const &rhs) const;
// 		bool 			operator == (IOperand const &rhs) const;
// 		bool 			operator > (IOperand const &rhs) const;
// 		bool 			operator < (IOperand const &rhs) const;
// 		bool 			operator >= (IOperand const &rhs) const;
// 		bool 			operator <= (IOperand const &rhs) const;
// 		bool 			operator != (IOperand const &rhs) const;
// 		std::string const &toString(void) const;
//
// 	private:
// 		T				_value;
// 		std::string		_str;
// };

#endif
