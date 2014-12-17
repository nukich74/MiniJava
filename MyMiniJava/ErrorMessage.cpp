#pragma once

#include "ErrorMessage.h"
#include <sstream>

const char* CTypeException::what() const throw() {
	std::stringstream ss;
	ss << message;
	if( havePosition ) {
		ss << " at " << errorPosition.firstLine << ':' << errorPosition.firstColumn;
	}
	return ss.str().c_str();
}
