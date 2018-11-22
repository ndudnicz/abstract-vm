#include <Cpu.class.hpp>
#include <sstream>
#include "regex_defines.hpp"
#include <limits>

/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
Cpu::Cpu( void ) {}

/* MEMBER OPERATORS OVERLOAD =================================================*/


/* DESTRUCTOR ================================================================*/
Cpu::~Cpu( void ) {}

/* MEMBER FUNCTIONS ==========================================================*/
int		Cpu::run( int ac, char const **av ) {
	// read file
	try {
		if (ac > 1) {
			(void)this->_getFile(av[1]);
		} else {
			(void)this->_getStdin();
		}
		(void)this->_generateStack();
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

int		Cpu::_generateStack( void ) {
	eOperandType												eop;
	std::string													value;

	try {
		(void)this->_validInput();
	} catch (...) {
		throw ;
	}
	return 0;
}

int		Cpu::_validInput( void ) {
	std::vector<std::string>::iterator	it = this->_input.begin();
	int																	line = 1;
	std::smatch													sm;

	for (; it < this->_input.end(); it++, line++) {
		try {
			std::cout << "*it: "<< *it << '\n'; // DEBUG
			(void)this->_regValidInstruction( line, *it, &sm );
			std::cout << "sm[1]:"<< sm[1].str() << '\n'; // DEBUG
			(void)this->_regValidSm( line, sm[1].str() );
		} catch (...) {
			throw ;
		}
	}
	return 0;
}

int		Cpu::_regValidInstruction(
	int const line,
	std::string const str,
	std::smatch *sm
) const {
	std::regex	regPush(REG_PUSH);
	std::regex	regPop(REG_POP);
	std::regex	regDump(REG_DUMP);
	std::regex	regAssert(REG_ASSERT);
	std::regex	regAdd(REG_ADD);
	std::regex	regSub(REG_SUB);
	std::regex	regMul(REG_MUL);
	std::regex	regDiv(REG_DIV);
	std::regex	regMod(REG_MOD);
	std::regex	regPrint(REG_PRINT);
	std::regex	regExit(REG_EXIT);
	std::regex	regComment(REG_COMMENT);

	if ( (std::regex_match( str, *sm, regPush) == true  ||
	std::regex_match( str, *sm, regAssert ) == true) && sm->size() == 2 ) {
		std::cout << "reg found : push or assert" << '\n'; // DEBUG
	} else if ( ( std::regex_match( str, *sm, regPop ) == true ||
	std::regex_match( str, *sm, regDump ) == true ||
	std::regex_match( str, *sm, regAdd ) == true ||
	std::regex_match( str, *sm, regSub ) == true ||
	std::regex_match( str, *sm, regMul ) == true ||
	std::regex_match( str, *sm, regDiv ) == true ||
	std::regex_match( str, *sm, regMod ) == true ||
	std::regex_match( str, *sm, regPrint ) == true ||
	std::regex_match( str, *sm, regExit ) == true ||
	std::regex_match( str, *sm, regComment ) == true ) && sm->size() == 1 ) {
		std::cout << "reg found : other" << '\n'; // DEBUG
		std::smatch ret;
		*sm = ret;
	} else {
		std::ostringstream	strs;
		strs << line;
		std::string					str1( EXCEP_UNKNOWN_INSTRUCTION );
		std::string					str2( strs.str() );
		throw Cpu::UnknownInstructionException( str1 + str2 );
	}
	return 0;
}

int		Cpu::_regValidSm(
	int const line,
	std::string sm1
) const {
	// std::cout << "valid sm ..." << '\n'; // DEBUG
	std::regex	regInt(REG_INT);
	std::regex	regFloat(REG_FLOAT);
	std::regex	regDouble(REG_DOUBLE);
	std::smatch	typeSm;

	std::cout << "_regValidSm: " << sm1 << '\n'; // DEBUG
	if ( std::regex_match( sm1, typeSm, regInt ) == true ) {
		int32_t zero = std::stoi(typeSm[2]);
		std::cout << "typeSm[2]:" << zero << '\n'; // DEBUG
		switch ( std::stoi(typeSm[1]) ) {
			case 8:
			if ( zero == 0 || typeSm[2].length() <= 4 ) {
				int32_t const value = std::stoi(typeSm[2]);
				if ( value >= std::numeric_limits<int8_t>::min() && value <= std::numeric_limits<int8_t>::max() ) {
					return 0;
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
			break;
			case 16:
			if ( zero == 0 || typeSm[2].length() <= 6 ) {
				int32_t const value = std::stoi(typeSm[2]);
				if ( value >= std::numeric_limits<int16_t>::min() && value <= std::numeric_limits<int16_t>::max() ) {
					return 0;
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
			break;
			case 32:
			if ( zero == 0 || typeSm[2].length() <= 11 ) {
				try {
					std::stoi(typeSm[2]);
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
			break;
		}
	} else if ( std::regex_match( sm1, typeSm, regFloat ) == true ) {
		for (int i = 0; i < typeSm.size(); i++) {
			std::cout << "typesm float: " << typeSm[i] << '\n'; // DEBUG
		}
	} else if ( std::regex_match( sm1, typeSm, regDouble ) == true ) {
		for (int i = 0; i < typeSm.size(); i++) {
			std::cout << "typesm double: " << typeSm[i] << '\n'; // DEBUG
		}
	} else {
		std::cout << "heeeeere" << '\n';
		std::ostringstream	strs;
		strs << line;
		std::string					str1( EXCEP_UNKNOWN_TYPE_OR_VALUE );
		std::string					str2( strs.str() );
		throw Cpu::UnknownTypeOrValueException( str1 + str2 );
	}
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
