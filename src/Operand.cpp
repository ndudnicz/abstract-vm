#include "Operand.hpp"

/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
template <class T> Operand<T>::Operand( void ) {
	return ;
}

template <class T> Operand<T>::Operand( T value, eOperandType type ):
_value( value ),
_type( type ) {
	return ;
}

template <class T> Operand<T>::Operand( Operand const & src ) {
	return ;
}

/* MEMBER OPERATORS OVERLOAD =================================================*/

template <class T> IOperand &Operand<T>::operator=( IOperand const & rhs ) const {
}

template <class T> IOperand const *Operand<T>::operator+( IOperand const & rhs ) const {
}

template <class T> IOperand const *Operand<T>::operator-( IOperand const & rhs ) const {
}

template <class T> IOperand const *Operand<T>::operator*( IOperand const & rhs ) const {
}

template <class T> IOperand const *Operand<T>::operator/( IOperand const & rhs ) const {
}

template <class T> IOperand const *Operand<T>::operator%( IOperand const & rhs ) const {
}



/* DESTRUCTOR ================================================================*/

template <class T> Operand<T>::~Operand( void ) {
	return ;
}

/* MEMBER FUNCTIONS ==========================================================*/

template <class T> int				Operand<T>::getPrecision( void ) const {
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

template <class T> eOperandType	Operand<T>::getType( void ) const {
	return this->_type;
}

template <class T> std::string const	&Operand<T>::toString( void ) const {

}

/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/
