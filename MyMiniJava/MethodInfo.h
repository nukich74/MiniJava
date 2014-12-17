#pragma once
#include "VariableInfo.h"
#include <vector>

namespace SymbolsTable {

	class CMethodInfo {
	public:

		CMethodInfo( const std::string& _retType, const std::string& _name ) : type( _retType ), name( _name ) { }
		std::string GetReturnType() const { return type; }
		std::string GetName() const { return name; }

		const std::vector< CVariableInfo* >& GetArgumentList() const { return arguments; }
		const std::vector< CVariableInfo* >& GetLocalVariablesList( ) const { return localVariables; }

		void AddLocalVar( CVariableInfo* var ) { localVariables.push_back( var ); }
		void AddArgument( CVariableInfo* arg ) { arguments.push_back( arg ); }

		CVariableInfo* FindVarAmongArgs( const std::string& id );
		CVariableInfo* FindVarAmongLocals( const std::string& id );

		bool HaveLocalVar( const std::string& id ) {
			bool haveInLocal = std::find_if( localVariables.begin(), localVariables.end(), [&id]( const CVariableInfo* info ) 
				{ return info->GetName() == id; } ) != localVariables.end();
		}

		bool HaveInArgs( const std::string& id ) {
			bool haveInArgs = std::find_if( arguments.begin(), arguments.end(), [&id]( const CVariableInfo* info ) 
				{ return info->GetName() == id; } ) != arguments.end();
		}
	private:

		std::string type;
		std::string name;
		std::vector< CVariableInfo* > localVariables;
		std::vector< CVariableInfo* > arguments;
	};
}