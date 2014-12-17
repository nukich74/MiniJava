#pragma once 
#include "CodeInfo.h"
#include <exception>
#include <string>

class CTypeException : public std::exception {
public:
	CTypeException::CTypeException( const std::string& msg ) : message( msg ), havePosition( false ) { }

	CTypeException::CTypeException( const std::string& msg, const CCodeInfo& info ) : message( msg ), errorPosition( info ), 
		havePosition( true ) { }

	virtual const char* CTypeException::what() const throw();


private:
	bool havePosition;
	CCodeInfo errorPosition;
	std::string message;
};

	const char* CTypeException::what() const throw() {
		return "1";
	}
