#include "Operand.class.hpp"
#include <sstream>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "OperandFactory.class.hpp"

/* STATIC VARIABLES ==========================================================*/
double const	IOperand::precisions[5] = {3, 5, 10, 39 + 7, 309 + 16};


/* CONSTRUCTORS ==============================================================*/

template <class T>
Operand<T>::Operand( std::string const & str, eOperandType type ):
_type( type ),
_str( str ) {
}

template <class T>
Operand<T>::Operand( Operand const & src ):
_type( src.getType() ),
_str( src.toString() ) {
}

/* MEMBER OPERATORS OVERLOAD =================================================*/

template <class T>Operand<T> &
Operand<T>::operator=( Operand const & rhs ) {
	this->_type = rhs.getType();
	this->_str = rhs.toString();
	return *this;
}

template <class T> IOperand const*
Operand<T>::operator+( IOperand const & rhs ) const {
	double							result = std::stod( this->toString() ) + std::stod( rhs.toString() );
	eOperandType const	type = MAX( this->getType(), rhs.getType() );
	std::ostringstream	strs;
	result = type > INT32 ? result : floor( result );

	strs << std::setprecision( Operand<T>::precisions[ type ] ) << result;
	return OperandFactory::createop( strs.str(), type );
}

template <class T> IOperand const*
Operand<T>::operator-( IOperand const & rhs ) const {
	double							result = std::stod( this->toString() ) - std::stod( rhs.toString() );
	eOperandType const	type = MAX( this->getType(), rhs.getType() );
	std::ostringstream	strs;
	result = type > INT32 ? result : floor( result );

	strs << std::setprecision( Operand<T>::precisions[ type ] ) << result;
	return OperandFactory::createop( strs.str(), type );
}

template <class T> IOperand const*
Operand<T>::operator*( IOperand const & rhs ) const {
	double							result = std::stod( this->toString() ) * std::stod( rhs.toString() );
	eOperandType const	type = MAX( this->getType(), rhs.getType() );
	std::ostringstream	strs;
	result = type > INT32 ? result : floor( result );

	strs << std::setprecision( Operand<T>::precisions[ type ] ) << result;
	return OperandFactory::createop( strs.str(), type );;
}

template <class T> IOperand const*
Operand<T>::operator/( IOperand const & rhs ) const {
	double							result = std::stod( this->toString() ) / std::stod( rhs.toString() );
	eOperandType	type = MAX( this->getType(), rhs.getType() );
	std::ostringstream	strs;
	result = type > INT32 ? result : floor( result );

	strs << std::setprecision( Operand<T>::precisions[ type ] ) << result;
	return OperandFactory::createop( strs.str(), type );;
}

template <class T> IOperand const*
Operand<T>::operator%( IOperand const & rhs ) const {
	double							result = std::fmod( std::stod( this->toString() ), std::stod( rhs.toString() ) );
	eOperandType const	type = MAX( this->getType(), rhs.getType() );
	std::ostringstream	strs;
	result = type > INT32 ? result : floor( result );

	strs << std::setprecision( Operand<T>::precisions[ type ] ) << result;
	return OperandFactory::createop( strs.str(), type );
}



/* DESTRUCTOR ================================================================*/

template <class T>
Operand<T>::~Operand( void ) {
	return ;
}

/* MEMBER FUNCTIONS ==========================================================*/

template <class T> int
Operand<T>::getPrecision( void ) const {
	return Operand<T>::precisions[ this->_type ];
}

template <class T> eOperandType
Operand<T>::getType( void ) const {
	return this->_type;
}

template <class T> std::string const &
Operand<T>::toString( void ) const {
	return this->_str;
}

/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/

/* TEMPLATES =================================================================*/

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
