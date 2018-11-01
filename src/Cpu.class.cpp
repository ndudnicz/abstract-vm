#include <Cpu.class.hpp>

/* STATIC VARIABLES ==========================================================*/


/* CONSTRUCTORS ==============================================================*/
Cpu::Cpu( void ) {}

/* MEMBER OPERATORS OVERLOAD =================================================*/


/* DESTRUCTOR ================================================================*/
Cpu::~Cpu( void ) {}

/* MEMBER FUNCTIONS ==========================================================*/
int		Cpu::run( int ac, char **av ) {
	if (ac > 1) {
		// read file
	} else {
		// read stdin
		try {
			this->getStdin();
		} catch (Cpu::DidntGetEndOfInputException &e) {
			std::cout << e.what() << '\n';
		}
	}
	return 0;
}

int		Cpu::getStdin( void ) {
	std::string	input;

	while ( 1 ) {
		std::getline( std::cin, input );
		if ( std::cin.eof() ) {
			throw Cpu::DidntGetEndOfInputException();
		} else if ( input.compare( END_OF_INPUT ) == 0 ) {
			goto end;
		} else {
			this->input.push_back( input );
		}
	}
	end:
		this->printInput();
		return 0;
}

// DEBUG
void Cpu::printInput( void ) {
	std::vector<std::string>::iterator		it = this->input.begin();
	for (; it < this->input.end(); it++) {
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
