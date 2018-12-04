#ifndef OPERANDFACTORY_CLASS_HPP
# define OPERANDFACTORY_CLASS_HPP

# include "IOperand.hpp"

class OperandFactory: public IOperand {

private:
	OperandFactory( void );
	~OperandFactory( void );

	static IOperand const* createInt8( std::string const &str, eOperandType type );
	static IOperand const* createInt16( std::string const &str, eOperandType type );
	static IOperand const* createInt32( std::string const &str, eOperandType type );
	static IOperand const* createFloat( std::string const &str, eOperandType type );
	static IOperand const* createDouble( std::string const &str, eOperandType type );

protected:

public:
	static IOperand const* createop( std::string const &str, eOperandType type );

};

#endif
