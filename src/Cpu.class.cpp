#include <Cpu.class.hpp>

/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
Cpu::Cpu( void ) {}

/* MEMBER OPERATORS OVERLOAD =================================================*/


/* DESTRUCTOR ================================================================*/
Cpu::~Cpu( void ) {}

/* MEMBER FUNCTIONS ==========================================================*/
int		Cpu::run( int ac, char const **av ) {
	if (ac > 1) {
		// read file
		try {
			(void)this->_getFile(av[1]);
		} catch ( Cpu::CantOpenFileException &e ) {
			std::cout << e.what() << '\n';
		}
	} else {
		// read stdin
		try {
			(void)this->_getStdin();
		} catch (Cpu::DidntGetEndOfInputException &e) {
			std::cout << e.what() << '\n';
		}
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
			this->_printInput(); // DEBUG
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
		std::cout << "read file" << '\n';
	} else {
		std::string	str1( "Exception : Can't open file : " );
		std::string	str2( filename );
		throw Cpu::CantOpenFileException( str1 + str2 );
	}
	return 0;
}

// DEBUG
void Cpu::_printInput( void ) { // DEBUG
	std::vector<std::string>::iterator		it = this->_input.begin();
	for (; it < this->_input.end(); it++) {
		std::cout << *it << std::endl;
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
