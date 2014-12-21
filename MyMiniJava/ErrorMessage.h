#pragma once 
#include "CodeInfo.h"
#include <exception>
#include <string>

class CSemanticError {
public:
	CSemanticError::CSemanticError() {}
	CSemanticError::CSemanticError( const std::string& msg ) : message( msg ) { }
	std::string What() {
		return "Error: " + message;
	}
protected:
	std::string message;
};


class CNameRedefinition : public CSemanticError {
public:
	CNameRedefinition::CNameRedefinition( const std::string& name, const CCodeInfo& place ) 
	{
		message = "Name at position " + place.ToString() + ' ' + name + "was already defined";
	}
};

class CIncompatibleTypes : public CSemanticError {
public:
	CIncompatibleTypes::CIncompatibleTypes( const std::string& type1, const std::string& type2, const CCodeInfo& place1, 
		const CCodeInfo& place2 ) 
	{
		message = "Incompatible types " + type1 + " " + type2 + " at " + place1.ToString() + " and " + place2.ToString();
	}
};

class CNoSuchVariable : public CSemanticError {
public:
	CNoSuchVariable::CNoSuchVariable( const std::string& name, const CCodeInfo& place )
	{
		message = "Undefined variable <" + name + "> at" + place.ToString();
	}
};

class CNoSuchType : public CSemanticError {
public:
	CNoSuchType::CNoSuchType( const std::string& name, const CCodeInfo& place )
	{
		message = "Undefined type at <" + name + "> at" + place.ToString();
	}
};

class CCyclicInheritance : public CSemanticError {
public:
	CCyclicInheritance::CCyclicInheritance( const std::string& name, const CCodeInfo& place ) 
	{
		message = "Name at position " + place.ToString() + ' ' + name + " has cyclic inheritance";
	}
};
