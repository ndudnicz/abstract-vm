#include <Cpu.class.hpp>
#include <sstream>
#include "regex_defines.hpp"
#include <limits>
#include "Operand.class.hpp"

/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
Cpu::Cpu( void ) {}

/* MEMBER OPERATORS OVERLOAD =================================================*/


/* DESTRUCTOR ================================================================*/
Cpu::~Cpu( void ) {}

/* MEMBER FUNCTIONS ==========================================================*/
eInstruction	Cpu::_getInstruction(
	std::string const str,
	std::smatch *sm
) {
	std::regex const	regPush(REG_PUSH);
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
		std::cout << e.what() << '\n';
	} catch (Cpu::DidntGetEndOfInputException &e) {
		std::cout << e.what() << '\n';
	} catch (Cpu::UnknownInstructionException &e) {
		std::cout << e.what() << '\n';
	} catch (Cpu::UnknownTypeOrValueException &e) {
		std::cout << e.what() << '\n';
	} catch (Cpu::InvalidValueException &e) {
		std::cout << e.what() << '\n';
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
	std::string													matchstr1("");
	std::string													matchstr2("");

	for (; it < this->_input.end(); it++, line++) {
		try {
			std::cout << "*it: "<< *it << '\n'; // DEBUG
			if ( this->_regValidInstruction( line, *it, &matchstr1, &matchstr2 ) == 0 ) {
				static_cast<void>(this->_regValidSm( line, matchstr2 ));
			}
		} catch (...) {
			throw ;
		}
	}
	return 0;
}

int		Cpu::_regValidInstruction(
	int const line,
	std::string const str,
	std::string *matchstr1,
	std::string *matchstr2
) {
	std::smatch smlocal;
	eInstruction const i = this->_getInstruction( str, &smlocal );
	*matchstr1 = smlocal[0];
	*matchstr2 = smlocal[1];

	if ( i <= EIASSERT ) {
		return 0;
	} else if ( i <= EICOMMENT ) {
		std::cout << "reg found : other" << '\n'; // DEBUG
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
		float const value = std::stof( typeSm[1] );

		if ( value == 0 || typeSm[1].length() <= ( IOperand::precisions[ FLOAT ] + 2 ) ) {
			try {
				std::stof( typeSm[1] );
			} catch ( const std::out_of_range& oor ) {
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

		/* DOUBLE ==================================================================*/
	} else if ( std::regex_match( sm1, typeSm, regDouble ) == true ) {
		double const value = std::stod( typeSm[1] );

		if ( value == 0 || typeSm[1].length() <= ( IOperand::precisions[ DOUBLE ] + 2 ) ) {
			try {
				std::stof( typeSm[1] );
			} catch ( const std::out_of_range& oor ) {
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

	} else {
		// std::cout << "heeeeere" << '\n'; // DEBUG
		std::ostringstream	strs;
		strs << line;
		std::string					str1( EXCEP_UNKNOWN_TYPE );
		std::string					str2( strs.str() );
		throw Cpu::UnknownTypeOrValueException( str1 + str2 );
	}
	return 0;
}

int		Cpu::_exec( void ) {
	std::vector<std::string>::iterator	it = this->_input.begin();
	std::smatch													sm;
	IOperand														*o;

	for (; it < this->_input.end(); it++) {
		try {
			switch ( this->_getInstruction( *it, &sm ) ) {
				case EIPUSH:
				std::cout << "exec: " << sm[1] << '\n';
				this->_push( sm[1] );
				break;
				case EIASSERT:
				this->_assert( sm[1] );
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
				this->_print();
				break;
				case EIINVALID:
				this->_print();
				break;
				case EIEXIT:
				return 0;
			}
		} catch (...) {
			throw ;
		}
	}
	return 0;
}

#include <stdio.h> // DEBUG
int Cpu::_push( std::string str ) {
	std::vector<IOperand*>::iterator	it;
	IOperand													*o;
	std::smatch												typeSm;
	std::regex	regInt(REG_INT);
	std::regex	regFloat(REG_FLOAT);
	std::regex	regDouble(REG_DOUBLE);

	it = this->_stack.begin();
	std::cout << "pushing: " << str << '\n';
	if ( std::regex_match( str, typeSm, regInt ) == true ) {
	std::cout << "pushing: " << typeSm[2] << '\n';

		switch ( std::stoi( typeSm[1] ) ) {
			/* INT8 ================================================================*/
			case 8:
			o = new Operand<int8_t>( typeSm[2], INT8 );
			break;
			/* INT16 ===============================================================*/
			case 16:
			o = new Operand<int16_t>( typeSm[2], INT16 );
			break;
			/* INT32 ===============================================================*/
			case 32:
			o = new Operand<int32_t>( typeSm[2], INT32 );
			break;
		}

		/* FLOAT ===================================================================*/
	} else if ( std::regex_match( str, typeSm, regFloat ) == true ) {
		o = new Operand<float>( typeSm[1], FLOAT );
		/* DOUBLE ==================================================================*/
	} else {
		o = new Operand<double>( typeSm[1], DOUBLE );
	}
	this->_stack.insert( it, o );

	printf("stack: %d\n", this->_stack.size());

	// if ( sm->size() > 1 ) {
	// 	switch ( std::stoi( (*sm)[1] ) ) {
	// 		case INT8:
	// 		case INT16:
	// 		o = new Operand<int16_t>( (*sm)[2], INT16 );
	// 		break;
	// 		case INT32:
	// 		o = new Operand<int32_t>( (*sm)[2], INT32 );
	// 		break;
	// 	}
	// } else {
	// 	if ( !(std::string( "float" )).compare( (*sm)[0] ) ) {
	// 		o = new Operand<float>( (*sm)[2], FLOAT );
	// 	} else {
	// 		o = new Operand<double>( (*sm)[2], DOUBLE );
	// 	}
	// }
	return 0;
}

int Cpu::_assert( std::string str ) {
	return 0;
}

int Cpu::_add( void ) {
	return 0;
}

int Cpu::_div( void ) {
	return 0;
}

int Cpu::_mod( void ) {
	return 0;
}
int Cpu::_mul( void ) {
	return 0;
}

int Cpu::_pop( void ) {
	return 0;
}

int Cpu::_sub( void ) {
	return 0;
}

int Cpu::_dump( void ) {
	return 0;
}

int Cpu::_print( void ) {
	return 0;
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
	return CONCAT("Exception : Didn't get end of input : ", END_OF_INPUT);
}

Cpu::CantOpenFileException::CantOpenFileException( const std::string& error_message ) :
runtime_error(error_message) {}

Cpu::UnknownInstructionException::UnknownInstructionException( const std::string& error_message ) :
runtime_error(error_message) {}

Cpu::UnknownTypeOrValueException::UnknownTypeOrValueException( const std::string& error_message ) :
runtime_error(error_message) {}

Cpu::InvalidValueException::InvalidValueException( const std::string& error_message ) :
runtime_error(error_message) {}
