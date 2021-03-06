#pragma once 
#include <string>

//http://www.ibm.com/developerworks/library/l-flexbison/
struct CCodeInfo {
	int firstLine;
	int firstColumn;
	int lastLine;
	int lastColumn;

	CCodeInfo() {}
	CCodeInfo( const int begLine, const int begPos, const int endLine, const int endPos ) : firstLine( begLine ),
		firstColumn( begPos ),
		lastLine( endLine ),
		lastColumn( endPos ) { }

	std::string ToString() const {
		return std::to_string( firstLine ) + ':' + std::to_string( firstColumn );
	}
};