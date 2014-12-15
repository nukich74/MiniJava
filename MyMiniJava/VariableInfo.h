#pragma once
#include <string>

namespace SymbolsTable {
	//надо ли делать переход в enum?
	enum VariableTypes {
		VT_INT,
		VT_ARRAY,
		VT_USER,
		VT_BOOL,
		VT_STR
	};

	class CVariableInfo {
	public:

		CVariableInfo( const std::string& _type, const std::string& _name, bool _isUserDefined ) 
			: type( _type ), name( _name ), definedByUser( _isUserDefined ) { }

		void SetType( const std::string& _type ) { type = _type; }
		void SetName( const std::string& _name ) { name = _name; }
		std::string GetType() const { return type; }
		std::string GetName() const { return name; }
		bool isUserDefined() const { return definedByUser; }

	private:

		//VariableTypes type;
		bool definedByUser;
		std::string type;
		std::string name;

	};
}