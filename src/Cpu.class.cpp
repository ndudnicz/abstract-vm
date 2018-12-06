#include <Cpu.class.hpp>
#include <sstream>
#include "regex_defines.hpp"
#include <limits>
#include "Operand.class.hpp"
#include <iomanip>
#include "OperandFactory.class.hpp"

/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
Cpu::Cpu( void ) {}

/* MEMBER OPERATORS OVERLOAD =================================================*/


/* DESTRUCTOR ================================================================*/
Cpu::~Cpu( void ) {}

/* MEMBER FUNCTIONS ==========================================================*/
eInstruction	Cpu::_getInstruction(
	std::string const str,
	std::smatch *sm,
	std::string **s
) {
	std::regex 	regPush(REG_PUSH);
	std::regex const	regPop(REG_POP);
	std::regex const	regDump(REG_DUMP);
	std::regex const	regAssert(REG_ASSERT);
	std::regex const	regAdd(REG_ADD);
	std::regex const	regSub(REG_SUB);
	std::regex const	regMul(REG_MUL);
	std::regex const	regDiv(REG_DIV);
	std::regex const	regMod(REG_MOD);
	std::regex const	regPrint(REG_PRINT);
	std::regex const	regExit(REG_EXIT);
	std::regex const	regComment(REG_COMMENT);

	if ( std::regex_match( str, *sm, regPush ) == true ) {
		std::cout << "ddd: "<< (*sm)[1] << '\n';
		*s = new std::string( (*sm)[1] );
		std::cout << "push" << '\n'; // DEBUG
		return EIPUSH;
	} else if ( std::regex_match( str, *sm, regAssert ) == true ) {
		std::cout << "assert" << '\n'; // DEBUG
		return EIASSERT;
	} else if ( std::regex_match( str, *sm, regPop ) == true ) {
		std::cout << "pop" << '\n'; // DEBUG
		return EIPOP;
	} else if ( std::regex_match( str, *sm, regDump ) == true ) {
		std::cout << "dump" << '\n'; // DEBUG
		return EIDUMP;
	} else if ( std::regex_match( str, *sm, regAdd ) == true ) {
		std::cout << "add" << '\n'; // DEBUG
		return EIADD;
	} else if ( std::regex_match( str, *sm, regSub ) == true ) {
		std::cout << "sub" << '\n'; // DEBUG
		return EISUB;
	} else if ( std::regex_match( str, *sm, regMul ) == true ) {
		std::cout << "mul" << '\n'; // DEBUG
		return EIMUL;
	} else if ( std::regex_match( str, *sm, regDiv ) == true ) {
		std::cout << "div" << '\n'; // DEBUG
		return EIDIV;
	} else if ( std::regex_match( str, *sm, regMod ) == true ) {
		std::cout << "mod" << '\n'; // DEBUG
		return EIMOD;
	} else if ( std::regex_match( str, *sm, regPrint ) == true ) {
		std::cout << "print" << '\n'; // DEBUG
		return EIPRINT;
	} else if ( std::regex_match( str, *sm, regExit ) == true ) {
		std::cout << "exit" << '\n'; // DEBUG
		return EIEXIT;
	} else if ( std::regex_match( str, *sm, regComment ) == true ) {
		std::cout << "comment" << '\n'; // DEBUG
		return EICOMMENT;
	} else {
		std::cout << "invalid" << '\n'; // DEBUG
		return EIINVALID;
	}
}

int		Cpu::run( int ac, char const **av ) {
	// read file
	try {
		if (ac > 1) {
			static_cast<void>(this->_getFile(av[1]));
		} else {
			static_cast<void>(this->_getStdin());
		}
		static_cast<void>(this->_validInput());
		static_cast<void>(this->_exec());
	} catch ( Cpu::CantOpenFileException &e ) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::DidntGetEndOfInputException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::UnknownInstructionException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::UnknownTypeException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::InvalidValueException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::AssertFailedException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::PopEmptyStackException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::NotEnoughElementsInStackException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::OperationOverflowException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::OperationUnderflowException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::PrintWrongTypeException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::FloatingPointException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::OverflowException &e) {
		std::cout << e.what() << std::endl;
	} catch (Cpu::UnderflowException &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}

int		Cpu::_getStdin( void ) {
	std::string	input;

	while ( 1 ) {
		std::getline( std::cin, input );
		if ( std::cin.eof() ) {
			throw Cpu::DidntGetEndOfInputException();
		} else if ( input.compare( END_OF_INPUT ) == 0 ) {
			// this->_printInput(); // DEBUG
			return 0;
		} else {
			this->_input.push_back( input );
		}
	}
}

int		Cpu::_getFile( char const *const filename ) {
	std::string		line;
	std::ifstream	file( filename );

	if ( file.good() ) {
		while ( std::getline( file, line ) ) {
			this->_input.push_back( line );
		}
		file.close();
		// this->_printInput(); // DEBUG
	} else {
		std::string	str1( EXCEP_CANT_OPEN_FILE );
		std::string	str2( filename );
		throw Cpu::CantOpenFileException( str1 + str2 );
	}
	return 0;
}

int		Cpu::_validInput( void ) {
	std::vector<std::string>::iterator	it = this->_input.begin();
	int																	line = 1;
	std::string													*matchstr2 = NULL;

	for (; it < this->_input.end(); it++, line++) {
		if ( (*it).length() > 0 ) {
			try {
				std::cout << "*it: "<< *it << '\n'; // DEBUG
				if ( this->_regValidInstruction( line, *it, &matchstr2 ) == 0 ) {
					static_cast<void>(this->_regValidSm( line, *matchstr2 ));
					if ( matchstr2 ) {
						delete matchstr2;
					}
				}
			} catch (...) {
				throw ;
			}
		}
	}
	return 0;
}
int		Cpu::_regValidInstruction(
	int const line,
	std::string const str,
	std::string **matchstr2
) {
	std::smatch smlocal;
	eInstruction const i = this->_getInstruction( str, &smlocal, matchstr2 );
	std::cout << "matchstr2: " << **matchstr2 << '\n';

	if ( i <= EIASSERT ) {
		return 0;
	} else if ( i <= EICOMMENT ) {
		// std::cout << "reg found : other" << '\n'; // DEBUG
		return 1;
	} else {
		std::ostringstream	strs;
		strs << line;
		std::string					str1( EXCEP_UNKNOWN_INSTRUCTION );
		std::string					str2( strs.str() );
		throw Cpu::UnknownInstructionException( str1 + str2 );
	}
}

int		Cpu::_regValidSm(
	int const line,
	std::string &sm1
) const {
	std::regex	regInt(REG_INT);
	std::regex	regFloat(REG_FLOAT);
	std::regex	regDouble(REG_DOUBLE);
	std::smatch	typeSm;

	std::cout << "_regValidSm: " << sm1 << '\n'; // DEBUG

	/* INT ===================================================================*/
	if ( std::regex_match( sm1, typeSm, regInt ) == true ) {

		switch ( std::stoi( typeSm[1] ) ) {

			/* INT8 ================================================================*/
			case 8:
			try {
				int32_t const value = std::stoi( typeSm[2] );

				if ( value == 0 || typeSm[2].length() <= 4 ) {
					if ( value >= std::numeric_limits<int8_t>::min() && value <= std::numeric_limits<int8_t>::max() ) {
						break;
					} else {
						std::ostringstream	strs;
						strs << line;
						std::string					str1( EXCEP_INVALID_VALUE );
						std::string					str2( strs.str() );
						throw Cpu::InvalidValueException( str1 + str2 );
					}
				} else {
					std::ostringstream	strs;
					strs << line;
					std::string					str1( EXCEP_INVALID_VALUE );
					std::string					str2( strs.str() );
					throw Cpu::InvalidValueException( str1 + str2 );
				}
			} catch ( const std::out_of_range& oor ) {
				std::ostringstream	strs;
				strs << line;
				std::string					str1( EXCEP_INVALID_VALUE );
				std::string					str2( strs.str() );
				throw Cpu::InvalidValueException( str1 + str2 );
			}

			/* INT16 ===============================================================*/
			case 16:
			try {
				int32_t const value = std::stoi( typeSm[2] );

				if ( value == 0 || typeSm[2].length() <= 6 ) {
					if ( value >= std::numeric_limits<int16_t>::min() && value <= std::numeric_limits<int16_t>::max() ) {
						break;
					} else {
						std::ostringstream	strs;
						strs << line;
						std::string					str1( EXCEP_INVALID_VALUE );
						std::string					str2( strs.str() );
						throw Cpu::InvalidValueException( str1 + str2 );
					}
					break;
				} else {
					std::ostringstream	strs;
					strs << line;
					std::string					str1( EXCEP_INVALID_VALUE );
					std::string					str2( strs.str() );
					throw Cpu::InvalidValueException( str1 + str2 );
				}
			} catch ( const std::out_of_range& oor ) {
				std::ostringstream	strs;
				strs << line;
				std::string					str1( EXCEP_INVALID_VALUE );
				std::string					str2( strs.str() );
				throw Cpu::InvalidValueException( str1 + str2 );
			}

			/* INT32 ===============================================================*/
			case 32:
			try {
				int32_t const value = std::stoi( typeSm[2] );
				if ( value == 0 || typeSm[2].length() <= 11 ) {
					break;
				} else {
					std::ostringstream	strs;
					strs << line;
					std::string					str1( EXCEP_INVALID_VALUE );
					std::string					str2( strs.str() );
					throw Cpu::InvalidValueException( str1 + str2 );
				}
			} catch ( const std::out_of_range& oor ) {
				std::ostringstream	strs;
				strs << line;
				std::string					str1( EXCEP_INVALID_VALUE );
				std::string					str2( strs.str() );
				throw Cpu::InvalidValueException( str1 + str2 );
			}
		}

		/* FLOAT ===================================================================*/
	} else if ( std::regex_match( sm1, typeSm, regFloat ) == true ) {

		try {
			float const value = std::stof( typeSm[1] );
			if ( value == 0 || typeSm[1].length() /*<= ( IOperand::precisions[ FLOAT ] + 2 ) */) {
				return 0;
			} else {
				std::ostringstream	strs;
				strs << line;
				std::string					str1( EXCEP_INVALID_VALUE );
				std::string					str2( strs.str() );
				throw Cpu::InvalidValueException( str1 + str2 );
			}

		} catch ( const std::out_of_range& oor ) {
			std::ostringstream	strs;
			strs << line;
			std::string					str1( EXCEP_INVALID_VALUE );
			std::string					str2( strs.str() );
			throw Cpu::InvalidValueException( str1 + str2 );
		}

		/* DOUBLE ==================================================================*/
	} else if ( std::regex_match( sm1, typeSm, regDouble ) == true ) {

		try {
			double const value = std::stod( typeSm[1] );
			if ( value == 0 || typeSm[1].length() /*<= ( IOperand::precisions[ DOUBLE ] + 2 ) */) {
				return 0;
			} else {
				std::ostringstream	strs;
				strs << line;
				std::string					str1( EXCEP_INVALID_VALUE );
				std::string					str2( strs.str() );
				throw Cpu::InvalidValueException( str1 + str2 );
			}

		} catch ( const std::out_of_range& oor ) {
			std::ostringstream	strs;
			strs << line;
			std::string					str1( EXCEP_INVALID_VALUE );
			std::string					str2( strs.str() );
				std::cout << "yo" << '\n';
			throw Cpu::InvalidValueException( str1 + str2 );
		}

	} else {
		std::cout << "heeeeere" << '\n'; // DEBUG
		std::cout << typeSm[0] << '\n';
		std::ostringstream	strs;
		strs << line;
		std::string					str1( EXCEP_UNKNOWN_TYPE );
		std::string					str2( strs.str() );
		throw Cpu::UnknownTypeException( str1 + str2 );
	}
	return 0;
}

int		Cpu::_exec( void ) {
	std::vector<std::string>::iterator	it = this->_input.begin();
	std::smatch													sm;
	IOperand														*o;
	std::string													*s = NULL;

	for (; it < this->_input.end(); it++) {
		if ( (*it).length() > 0 ) {
			try {
				switch ( this->_getInstruction( *it, &sm, &s ) ) {
					case EIPUSH:
					std::cout << "exec: " << *s << '\n'; // DEBUG
					this->_push( *s );
					break;
					case EIASSERT:
					this->_assert( *s );
					break;
					case EIPOP:
					this->_pop();
					break;
					case EIDUMP:
					this->_dump();
					break;
					case EIADD:
					this->_add();
					break;
					case EISUB:
					this->_sub();
					break;
					case EIMUL:
					this->_mul();
					break;
					case EIDIV:
					this->_div();
					break;
					case EIMOD:
					this->_mod();
					break;
					case EIPRINT:
					this->_print();
					break;
					case EICOMMENT:
					break;
					case EIINVALID:
					break;
					case EIEXIT:
					return 0;
				}
			} catch (...) {
				throw ;
			}
		}
	}
	if ( s ) {
		delete s;
	}
	return 0;
}

	/* INSTRUCTIONS ============================================================*/

int	Cpu::_push( std::string str ) {
	std::vector<IOperand*>::iterator	it;
	IOperand													*o;
	std::smatch												typeSm;
	std::regex	regInt(REG_INT);
	std::regex	regFloat(REG_FLOAT);
	std::regex	regDouble(REG_DOUBLE);

	it = this->_stack.begin();
	if ( std::regex_match( str, typeSm, regInt ) == true ) {

		switch ( std::stoi( typeSm[1] ) ) {
			/* INT8 ================================================================*/
			case 8:
			o = const_cast<IOperand*>(OperandFactory::createop( typeSm[2], INT8 ));
			break;
			/* INT16 ===============================================================*/
			case 16:
			o = const_cast<IOperand*>(OperandFactory::createop( typeSm[2], INT16 ));
			break;
			/* INT32 ===============================================================*/
			case 32:
			o = const_cast<IOperand*>(OperandFactory::createop( typeSm[2], INT32 ));
			break;
		}

		/* FLOAT =================================================================*/
	} else if ( std::regex_match( str, typeSm, regFloat ) == true ) {
		o = const_cast<IOperand*>(OperandFactory::createop( typeSm[1], FLOAT ));
		/* DOUBLE ================================================================*/
	} else if ( std::regex_match( str, typeSm, regDouble ) == true ) {
		o = const_cast<IOperand*>(OperandFactory::createop( typeSm[1], DOUBLE ));
	}
	this->_stack.insert( it, o );
	return 0;
}

int	Cpu::_assert( std::string str ) {
	std::vector<IOperand*>::iterator	it;
	std::smatch												typeSm;
	std::regex	regInt(REG_INT);
	std::regex	regFloat(REG_FLOAT);
	std::regex	regDouble(REG_DOUBLE);

	it = this->_stack.begin();
	// std::cout << "asserting: " << str << '\n'; // DEBUG
	if ( std::regex_match( str, typeSm, regInt ) == true ) {
		// std::cout << "asserting: " << typeSm[2] << '\n'; // DEBUG
		if ( std::stod( (*it)->toString() ) != std::stod( typeSm[2] ) ) {
			throw Cpu::AssertFailedException();
		}
		/* FLOAT ===================================================================*/
	} else if ( std::regex_match( str, typeSm, regFloat ) == true ) {
		if ( std::stod( (*it)->toString() ) != std::stod( typeSm[1] ) ) {
			throw Cpu::AssertFailedException();
		}
		/* DOUBLE ==================================================================*/
	} else if ( std::regex_match( str, typeSm, regDouble ) == true ) {
		if ( std::stod( (*it)->toString() ) != std::stod( typeSm[1] ) ) {
			throw Cpu::AssertFailedException();
		}
	}
	return 0;
}

int	Cpu::_add( void ) {
	if ( this->_stack.size() > 1 ) {
		std::vector<IOperand*>::iterator	it = this->_stack.begin();
		IOperand													*v1 = *it;
		IOperand													*v2 = *(it + 1);
		int 															overflow;
		this->_add_overflow( v1, v2, MAX( v1->getType(), v2->getType() ), &overflow );

		std::cout << overflow << '\n';
		if ( overflow > 0 ) {
			throw Cpu::OverflowException();
		} else if ( overflow < 0 ) {
			throw Cpu::UnderflowException();
		} else {
			IOperand* result = const_cast<IOperand*>(*v2 + *v1);
			this->_stack.erase( this->_stack.begin() );
			this->_stack.erase( this->_stack.begin() );
			delete v1;
			delete v2;
			it = this->_stack.begin();
			// std::cout << "tosting: "<< result->toString() << '\n'; // DEBUG
			// std::cout << "type: "<<result->getType() << '\n'; // DEBUG
			this->_stack.insert( it, result );
			return 0;
		}
	} else {
		throw Cpu::NotEnoughElementsInStackException();
	}
}

int	Cpu::_div( void ) {
	if ( this->_stack.size() > 1 ) {
		std::vector<IOperand*>::iterator	it = this->_stack.begin();
		IOperand													*v1 = *it;
		IOperand													*v2 = *(it + 1);

		// std::cout << "div: " << v2->toString() << "/" << v1->toString() << '\n'; // DEBUG
		if ( std::stod( (*it)->toString() ) != static_cast<double>(0) ) {
			// TODO OP HERE
			IOperand* result = const_cast<IOperand*>(*v2 / *v1);
			this->_stack.erase( this->_stack.begin() );
			this->_stack.erase( this->_stack.begin() );
			delete v1;
			delete v2;
			it = this->_stack.begin();
			// std::cout << result->toString() << '\n'; // DEBUG
			// std::cout << result->getType() << '\n'; // DEBUG
			this->_stack.insert( it, result );
			return 0;
		} else {
			throw Cpu::FloatingPointException();
		}
	} else {
		throw Cpu::NotEnoughElementsInStackException();
	}
}

int	Cpu::_mod( void ) {
	if ( this->_stack.size() > 1 ) {
		std::vector<IOperand*>::iterator	it = this->_stack.begin();
		IOperand													*v1 = *it;
		IOperand													*v2 = *(it + 1);
		// std::cout << "div: " << v2->toString() << "%" << v1->toString() << '\n'; // DEBUG

		if ( std::stod( (*it)->toString() ) != static_cast<double>(0) ) {
			std::vector<IOperand*>::iterator	it = this->_stack.begin();

			IOperand* result = const_cast<IOperand*>(*v2 % *v1);
			this->_stack.erase( this->_stack.begin() );
			this->_stack.erase( this->_stack.begin() );
			delete v1;
			delete v2;
			it = this->_stack.begin();
			// std::cout << result->toString() << '\n'; // DEBUG
			// std::cout << result->getType() << '\n'; // DEBUG
			this->_stack.insert( it, result );
			return 0;
			return 0;
		} else {
			throw Cpu::FloatingPointException();
		}
	} else {
		throw Cpu::NotEnoughElementsInStackException();
	}
}

int	Cpu::_mul( void ) {
	if ( this->_stack.size() > 1 ) {
		std::vector<IOperand*>::iterator	it = this->_stack.begin();
		IOperand													*v1 = *it;
		IOperand													*v2 = *(it + 1);

		IOperand* result = const_cast<IOperand*>(*v2 * *v1);
		this->_stack.erase( this->_stack.begin() );
		this->_stack.erase( this->_stack.begin() );
		delete v1;
		delete v2;
		it = this->_stack.begin();
		// std::cout << result->toString() << '\n'; // DEBUG
		// std::cout << result->getType() << '\n'; // DEBUG
		this->_stack.insert( it, result );
		return 0;
	} else {
		throw Cpu::NotEnoughElementsInStackException();
	}
}

int	Cpu::_sub( void ) {
	if ( this->_stack.size() > 1 ) {
		std::vector<IOperand*>::iterator	it = this->_stack.begin();
		IOperand													*v1 = *it;
		IOperand													*v2 = *(it + 1);
		int 															overflow;
		this->_sub_overflow( v1, v2, MAX( v1->getType(), v2->getType() ), &overflow );

		std::cout << overflow << '\n';
		if ( overflow > 0 ) {
			throw Cpu::OverflowException();
		} else if ( overflow < 0 ) {
			throw Cpu::UnderflowException();
		} else {
			IOperand* result = const_cast<IOperand*>(*v2 - *v1);
			this->_stack.erase( this->_stack.begin() );
			this->_stack.erase( this->_stack.begin() );
			delete v1;
			delete v2;
			it = this->_stack.begin();
			// std::cout << result->toString() << '\n'; // DEBUG
			// std::cout << result->getType() << '\n'; // DEBUG
			this->_stack.insert( it, result );
			return 0;
		}
	} else {
		throw Cpu::NotEnoughElementsInStackException();
	}
}

int	Cpu::_pop( void ) {
	if ( this->_stack.size() > 0 ) {
		this->_stack.erase(this->_stack.begin());
		return 0;
	} else {
		throw Cpu::PopEmptyStackException();
	}
}


int	Cpu::_dump( void ) {
	std::vector<IOperand*>::iterator	it = this->_stack.begin();
// std::cout << "coucou" << '\n';
	for (; it != this->_stack.end(); it++) {
		std::ostringstream	strs;
		if ( (*it)->getType() < FLOAT ) {
			strs << std::stoi( (*it)->toString() );
		} else if ( (*it)->getType() < DOUBLE ) {
			strs << std::setprecision( (*it)->getPrecision() ) << std::stof( (*it)->toString() );
		} else {
			strs << std::setprecision( (*it)->getPrecision() ) << std::stod( (*it)->toString() );
		}
		std::cout << strs.str() << std::endl;
	}
	return 0;
}

int	Cpu::_print( void ) {
	if ( this->_stack.size() > 0 ) {
		std::vector<IOperand*>::iterator		it = this->_stack.begin();
		if ( (*it)->getType() == INT8 ) {
			char const c = static_cast<char>( std::stoi( (*it)->toString() ) );
			std::cout << c << std::endl;
		} else {
			throw Cpu::PrintWrongTypeException();
		}
	}
	return 0;
}
	/* OVERFLOW CHECK ==========================================================*/
#include <stdio.h> // DEBUG
int	Cpu::_add_overflow( IOperand *v1, IOperand *v2, eOperandType type, int *overflow ) const {
	*overflow = 0;
	if ( type < FLOAT ) {
		int32_t	_v1 = std::stoi( v1->toString() );
		int32_t	_v2 = std::stoi( v2->toString() );

		switch ( type ) {
			case INT8:
			int8_t	r8;
			*overflow = (__builtin_add_overflow( _v1, _v2, &r8 ) && (_v1 > 0 || _v2 > 0)) ? (__builtin_add_overflow( _v1, _v2, &r8 ) && (_v1 > 0 || _v2 > 0)) : -(__builtin_add_overflow( _v1, _v2, &r8 ) && (_v1 < 0 || _v2 < 0));
			return 0;
			case INT16:
			int16_t	r16;
			*overflow = (__builtin_add_overflow( _v1, _v2, &r16 ) && (_v1 > 0 || _v2 > 0)) ? (__builtin_add_overflow( _v1, _v2, &r16 ) && (_v1 > 0 || _v2 > 0)) : -(__builtin_add_overflow( _v1, _v2, &r16 ) && (_v1 < 0 || _v2 < 0));
			return 0;
			case INT32:
			int32_t	r32;
			*overflow = (__builtin_add_overflow( _v1, _v2, &r32 ) && (_v1 > 0 || _v2 > 0)) ? (__builtin_add_overflow( _v1, _v2, &r32 ) && (_v1 > 0 || _v2 > 0)) : -(__builtin_add_overflow( _v1, _v2, &r32 ) && (_v1 < 0 || _v2 < 0));
			return 0;
			default:
			return 0;
		}
	} else if ( type < DOUBLE ) {
		float	_v1 = std::stof( v1->toString() );
		float	_v2 = std::stof( v2->toString() );
		float	_floatMaxHalf = std::numeric_limits<float>::max() / 2.0f;
		float	_floatMinHalf = std::numeric_limits<float>::min() / 2.0f;

		*overflow = (_v1 > _floatMaxHalf && _v2 > _floatMaxHalf) ? (_v1 > _floatMaxHalf && _v2 > _floatMaxHalf) : -(_v1 < _floatMinHalf && _v2 < _floatMinHalf);
		return 0;
		// return (_v1 > _floatMaxHalf && _v2 > _floatMaxHalf) ||
						;
	} else {
		double	_v1 = std::stod( v1->toString() );
		double	_v2 = std::stod( v2->toString() );
		double	_doubleMaxHalf = std::numeric_limits<double>::max() / 2.0f;
		double	_doubleMinHalf = std::numeric_limits<double>::min() / 2.0f;

		*overflow = (_v1 > _doubleMaxHalf && _v2 > _doubleMaxHalf) ? (_v1 > _doubleMaxHalf && _v2 > _doubleMaxHalf) : -(_v1 < _doubleMinHalf && _v2 < _doubleMinHalf);
		return 0;
	}
}

int	Cpu::_sub_overflow( IOperand *v1, IOperand *v2, eOperandType type, int *overflow ) const {
	if ( type < FLOAT ) {
		int32_t	_v1 = std::stoi( v1->toString() );
		int32_t	_v2 = std::stoi( v2->toString() );

		switch ( type ) {
			case INT8:
			int8_t	r8;
			*overflow = (__builtin_sub_overflow( _v2, _v1, &r8 ) && (_v1 > 0 || _v2 < 0)) ? (__builtin_sub_overflow( _v2, _v1, &r8 ) && (_v1 > 0 || _v2 < 0)) : -(__builtin_sub_overflow( _v2, _v1, &r8 ) && (_v1 < 0 || _v2 > 0));
			return 0;
			case INT16:
			int16_t	r16;
			*overflow = (__builtin_sub_overflow( _v2, _v1, &r16 ) && (_v1 > 0 || _v2 < 0)) ? (__builtin_sub_overflow( _v2, _v1, &r16 ) && (_v1 > 0 || _v2 < 0)) : -(__builtin_sub_overflow( _v2, _v1, &r16 ) && (_v1 < 0 || _v2 > 0));
			return 0;
			case INT32:
			int32_t	r32;
			*overflow = (__builtin_sub_overflow( _v2, _v1, &r32 ) && (_v1 > 0 || _v2 < 0)) ? (__builtin_sub_overflow( _v2, _v1, &r32 ) && (_v1 > 0 || _v2 < 0)) : -(__builtin_sub_overflow( _v2, _v1, &r32 ) && (_v1 < 0 || _v2 > 0));
			return 0;
			default:
			return 0;
		}
	} else if ( type < DOUBLE ) {
		float	_v1 = std::stof( v1->toString() );
		float	_v2 = std::stof( v2->toString() );
		float	_floatMaxHalf = std::numeric_limits<float>::max() / 2.0f;
		float	_floatMinHalf = std::numeric_limits<float>::min() / 2.0f;

		return (_v1 > _floatMaxHalf && _v2 > _floatMaxHalf) ||
						-(_v1 < _floatMinHalf && _v2 < _floatMinHalf);
	} else {
		double	_v1 = std::stod( v1->toString() );
		double	_v2 = std::stod( v2->toString() );
		double	_doubleMaxHalf = std::numeric_limits<double>::max() / 2.0f;
		double	_doubleMinHalf = std::numeric_limits<double>::min() / 2.0f;

		return (_v1 > _doubleMaxHalf && _v2 > _doubleMaxHalf) ||
						-(_v1 < _doubleMinHalf && _v2 < _doubleMinHalf);
	}
}

int	Cpu::_mul_overflow( IOperand *v1, IOperand *v2, eOperandType type ) const {
	if ( type < FLOAT ) {
		int32_t	_v1 = std::stoi( v1->toString() );
		int32_t	_v2 = std::stoi( v2->toString() );

		switch ( type ) {
			case INT8:
			int8_t	r8;
			return __builtin_mul_overflow( _v1, _v2, &r8 );
			case INT16:
			int16_t	r16;
			return __builtin_add_overflow( _v1, _v2, &r16 );
			case INT32:
			int32_t	r32;
			return __builtin_add_overflow( _v1, _v2, &r32 );
			default:
			return 0;
		}
	} else if ( type < DOUBLE ) {
		float	_v1 = std::stof( v1->toString() );
		float	_v2 = std::stof( v2->toString() );
		float	_floatMaxHalf = std::numeric_limits<float>::max() / 2.0f;
		float	_floatMinHalf = std::numeric_limits<float>::min() / 2.0f;

		return (_v1 > _floatMaxHalf && _v2 > _floatMaxHalf) ||
						-(_v1 < _floatMinHalf && _v2 < _floatMinHalf);
	} else {
		double	_v1 = std::stod( v1->toString() );
		double	_v2 = std::stod( v2->toString() );
		double	_doubleMaxHalf = std::numeric_limits<double>::max() / 2.0f;
		double	_doubleMinHalf = std::numeric_limits<double>::min() / 2.0f;

		return (_v1 > _doubleMaxHalf && _v2 > _doubleMaxHalf) ||
						-(_v1 < _doubleMinHalf && _v2 < _doubleMinHalf);
	}
}

// DEBUG
void Cpu::_printInput( void ) { // DEBUG
	std::vector<std::string>::iterator		it = this->_input.begin();
	for (; it < this->_input.end(); it++) {
		std::cout << "DEBUG : " << *it << std::endl; // DEBUG
	}
}
// DEBUG

/* NON MEMBER FUNCTIONS ======================================================*/


/* OPERATOR ==================================================================*/

/* EXCEPTIONS ================================================================*/
Cpu::DidntGetEndOfInputException::DidntGetEndOfInputException( void ) throw() {}
Cpu::DidntGetEndOfInputException::~DidntGetEndOfInputException( void ) throw() {}
const char * Cpu::DidntGetEndOfInputException::what( void ) const throw() {
	return CONCAT("Error : Didn't get end of input : ", END_OF_INPUT);
}

Cpu::CantOpenFileException::CantOpenFileException( const std::string& error_message ) :
runtime_error(error_message) {}

Cpu::UnknownInstructionException::UnknownInstructionException( const std::string& error_message ) :
runtime_error(error_message) {}

Cpu::UnknownTypeException::UnknownTypeException( const std::string& error_message ) :
runtime_error(error_message) {}

Cpu::InvalidValueException::InvalidValueException( const std::string& error_message ) :
runtime_error(error_message) {}

Cpu::AssertFailedException::AssertFailedException( void ) throw() {}
Cpu::AssertFailedException::~AssertFailedException( void ) throw() {}
const char * Cpu::AssertFailedException::what( void ) const throw() {
	return "Error : assertion is not true.";
}

Cpu::PopEmptyStackException::PopEmptyStackException( void ) throw() {}
Cpu::PopEmptyStackException::~PopEmptyStackException( void ) throw() {}
const char * Cpu::PopEmptyStackException::what( void ) const throw() {
	return "Error : can't pop empty stack.";
}

Cpu::NotEnoughElementsInStackException::NotEnoughElementsInStackException( void ) throw() {}
Cpu::NotEnoughElementsInStackException::~NotEnoughElementsInStackException( void ) throw() {}
const char * Cpu::NotEnoughElementsInStackException::what( void ) const throw() {
	return "Error : not enough elements in stack.";
}

Cpu::OperationOverflowException::OperationOverflowException( void ) throw() {}
Cpu::OperationOverflowException::~OperationOverflowException( void ) throw() {}
const char * Cpu::OperationOverflowException::what( void ) const throw() {
	return "Error : operation overflow.";
}

Cpu::OperationUnderflowException::OperationUnderflowException( void ) throw() {}
Cpu::OperationUnderflowException::~OperationUnderflowException( void ) throw() {}
const char * Cpu::OperationUnderflowException::what( void ) const throw() {
	return "Error : operation underflow.";
}

Cpu::PrintWrongTypeException::PrintWrongTypeException( void ) throw() {}
Cpu::PrintWrongTypeException::~PrintWrongTypeException( void ) throw() {}
const char * Cpu::PrintWrongTypeException::what( void ) const throw() {
	return "Error : trying to print wrong type (must be int8).";
}

Cpu::FloatingPointException::FloatingPointException( void ) throw() {}
Cpu::FloatingPointException::~FloatingPointException( void ) throw() {}
const char * Cpu::FloatingPointException::what( void ) const throw() {
	return "Error : Floating point exception.";
}

Cpu::OverflowException::OverflowException( void ) throw() {}
Cpu::OverflowException::~OverflowException( void ) throw() {}
const char * Cpu::OverflowException::what( void ) const throw() {
	return "Error : Overflow exception.";
}

Cpu::UnderflowException::UnderflowException( void ) throw() {}
Cpu::UnderflowException::~UnderflowException( void ) throw() {}
const char * Cpu::UnderflowException::what( void ) const throw() {
	return "Error : Underflow exception.";
}
