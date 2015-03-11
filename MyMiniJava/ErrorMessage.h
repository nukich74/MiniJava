#pragma once 
#include "CodeInfo.h"
#include <exception>
#include <string>

class CSemanticError {
public:
	CSemanticError::CSemanticError() {}
	CSemanticError::CSemanticError( const std::string& msg, const CCodeInfo& _place ) : message( msg ), place( _place ) { }
	std::string What() {
		return "Error at " + place.ToString() + ": " + message;
	}
protected:
	CCodeInfo place;
	std::string message;
};


class CNameRedefinition : public CSemanticError {
public:
	CNameRedefinition::CNameRedefinition( const std::string& name, const CCodeInfo& place ) : CSemanticError( "", place )
	{
		message = "Name " + name + "was already defined";
	}
};

class CIncompatibleTypes : public CSemanticError {
public:
	CIncompatibleTypes::CIncompatibleTypes( const std::string& type1, const std::string& type2, const CCodeInfo& place ) : CSemanticError( "", place ) 
	{
		message = "Incompatible types " + type1 + " " + type2;
	}
};

class CUnexpectedType : public CSemanticError {
public:
	CUnexpectedType::CUnexpectedType( const std::string& have, const std::string& need, const CCodeInfo& place ) : CSemanticError( "", place ) 
	{
		message = "Unexpected type " + have + " instead of " + need;
	}
};

class CNoSuchVariable : public CSemanticError {
public:
	CNoSuchVariable::CNoSuchVariable( const std::string& name, const CCodeInfo& place ) : CSemanticError( "", place )
	{
		message = "Undefined variable <" + name + ">";
	}
};

class CNoSuchType : public CSemanticError {
public:
	CNoSuchType::CNoSuchType( const std::string& name, const CCodeInfo& place ) : CSemanticError( "", place )
	{
		message = "Undefined type at <" + name + ">";
	}
};

class CNoSuchMethod : public CSemanticError {
public:
	CNoSuchMethod::CNoSuchMethod( const std::string& name, const CCodeInfo& place ) : CSemanticError( "", place )
	{
		message = "Undefined method at <" + name + ">";
	}
};


class CCyclicInheritance : public CSemanticError {
public:
	CCyclicInheritance::CCyclicInheritance( const std::string& name, const CCodeInfo& place ) : CSemanticError( "", place ) 
	{
		message = name + " has cyclic inheritance";
	}
};
