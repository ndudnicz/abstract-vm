#include "OperandFactory.class.hpp"
#include "Operand.class.hpp"

/* STATIC VARIABLES ==========================================================*/
IOperand const* OperandFactory::createop( std::string const &str, eOperandType type ) {
	switch (type) {
		case INT8:
		return OperandFactory::createInt8( str, type );
		break;
		case INT16:
		return OperandFactory::createInt16( str, type );
		break;
		case INT32:
		return OperandFactory::createInt32( str, type );
		break;
		case FLOAT:
		return OperandFactory::createFloat( str, type );
		break;
		case DOUBLE:
		return OperandFactory::createDouble( str, type );
		break;
	}
}

IOperand const* OperandFactory::createInt8( std::string const &str, eOperandType type ) {
	return new Operand<int8_t>( str, type );
}

IOperand const* OperandFactory::createInt16( std::string const &str, eOperandType type ) {
	return new Operand<int16_t>( str, type );
}

IOperand const* OperandFactory::createInt32( std::string const &str, eOperandType type ) {
	return new Operand<int32_t>( str, type );
}

IOperand const* OperandFactory::createFloat( std::string const &str, eOperandType type ) {
	return new Operand<float>( str, type );

}

IOperand const* OperandFactory::createDouble( std::string const &str, eOperandType type ) {
	return new Operand<double>( str, type );
}

/* CONSTRUCTORS ==============================================================*/

/* MEMBER OPERATORS OVERLOAD =================================================*/


/* DESTRUCTOR ================================================================*/

/* MEMBER FUNCTIONS ==========================================================*/


/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/
