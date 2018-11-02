#include "Operand.class.hpp"
#include <sstream>
#include <iostream>

/* STATIC VARIABLES ==========================================================*/
// int const		_registersIndex[5] = {
// 	0,
// 	sizeof( int8_t ),
// 	sizeof( int8_t ) + sizeof( int16_t ),
// 	sizeof( int8_t ) + sizeof( int16_t ) + sizeof( int32_t ),
// 	sizeof( int8_t ) + sizeof( int16_t ) + sizeof( int32_t ) + sizeof( float )
// };
//
// t_registers	_registers = 0;

/* CONSTRUCTORS ==============================================================*/

template <class T>
Operand<T>::Operand( T value, eOperandType type ):
_value( value ),
_type( type ) {
	std::stringstream ss;
	if ( type < FLOAT ) {
		ss << static_cast<int32_t>(this->_value);
	} else {
		ss << static_cast<double>(this->_value);
	}
	this->_str = ss.str();
	// std::cout << ss.str() << std::endl;
	// std::cout << this->str << std::endl;
}

template <class T>
Operand<T>::Operand( Operand const & src ):
_value( src.getValue() ),
_type( src.getType() ),
_str( src.toString() ) {
}

/* MEMBER OPERATORS OVERLOAD =================================================*/

template <class T>
Operand<T>				&Operand<T>::operator=( Operand const & rhs ) {
	this->_value = rhs.getValue();
	this->_type = rhs.getType();
	return *this;
}

template <class T>
IOperand const	*Operand<T>::operator+( IOperand const & rhs ) const {
	// eOperandType	type = this->getType() > rhs.getType() ? this->getType() : rhs.getType();
	// Operand<T>::_registers + Operand<T>::_registersIndex[ type ] = 1;
	// double			result = this->getValue() + rhs.getValue();
	// Operand<T>	*op = new Operand(   )
	return NULL;
}

template <class T>
IOperand const	*Operand<T>::operator-( IOperand const & rhs ) const {
	return NULL;
}

template <class T>
IOperand const	*Operand<T>::operator*( IOperand const & rhs ) const {
	return NULL;
}

template <class T>
IOperand const	*Operand<T>::operator/( IOperand const & rhs ) const {
	return NULL;
}

template <class T>
IOperand const	*Operand<T>::operator%( IOperand const & rhs ) const {
	return NULL;
}



/* DESTRUCTOR ================================================================*/

template <class T>
Operand<T>::~Operand( void ) {
	return ;
}

/* MEMBER FUNCTIONS ==========================================================*/

template <class T>
int							Operand<T>::getPrecision( void ) const {
	switch (this->_type) {
		case INT8:
			return 0;
		case INT16:
			return 0;
		case INT32:
			return 0;
		case FLOAT:
			return 7; // man float
		case DOUBLE:
			return 16; // man float
		default:
			return 0;
	}
}

template <class T>
eOperandType		Operand<T>::getType( void ) const {
	return this->_type;
}

template <class T>
T								Operand<T>::getValue( void ) const {
	return this->_value;
}
#include <iostream>
template <class T>
std::string const	&Operand<T>::toString( void ) const {
	return this->_str;
}

/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/

/* TEMPLATES =================================================================*/

template class Operand<int8_t>;
// template class Operand<int16_t>;
template class Operand<int32_t>;
// template class Operand<float>;
template class Operand<double>;
