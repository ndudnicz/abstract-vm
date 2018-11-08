#include <Cpu.class.hpp>
#include <sstream>
#include "regex_defines.hpp"

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
	std::cmatch													cm;

	for (; it < this->_input.end(); it++, line++) {
		try {
			std::cout << *it << '\n';
			(void)this->_regValidInstruction( line, (*it).c_str(), &cm );
			(void)this->_regValidCm( cm );
		} catch (...) {
			throw ;
		}
	}
	return true;
}

int		Cpu::_regValidInstruction(
	int const line,
	char const *const str,
	std::cmatch *cm
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

	if ( (std::regex_match( str, *cm, regPush) == true  ||
	std::regex_match( str, *cm, regAssert ) == true) && cm->size() == 2 ) {
		std::cout << "reg found : push or assert" << '\n';
	} else if ( (std::regex_match( str, *cm, regPop ) == true ||
	std::regex_match( str, *cm, regDump ) == true ||
	std::regex_match( str, *cm, regAdd ) == true ||
	std::regex_match( str, *cm, regSub ) == true ||
	std::regex_match( str, *cm, regMul ) == true ||
	std::regex_match( str, *cm, regDiv ) == true ||
	std::regex_match( str, *cm, regMod ) == true ||
	std::regex_match( str, *cm, regPrint ) == true ||
	std::regex_match( str, *cm, regExit ) == true ||
	std::regex_match( str, *cm, regComment ) == true) && cm->size() == 1 ) {
		std::cout << "reg found : other" << '\n';
	} else {
		std::ostringstream	strs;
		strs << line;
		std::string					str1( EXCEP_UNKNOWN_INSTRUCTION );
		std::string					str2( strs.str() );
		throw Cpu::UnknownInstructionException( str1 + str2 );
	}
	return 0;
}

int		Cpu::_regValidCm( std::cmatch &cm ) const {
	std::cout << "valid cm ..." << '\n';

	return 0;
}

// DEBUG
void Cpu::_printInput( void ) { // DEBUG
	std::vector<std::string>::iterator		it = this->_input.begin();
	for (; it < this->_input.end(); it++) {
		std::cout << "DEBUG : " << *it << std::endl;
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
