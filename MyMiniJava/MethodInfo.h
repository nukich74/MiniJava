#pragma once
#include "VariableInfo.h"
#include <vector>
#include <algorithm>

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

		CVariableInfo* FindVarAmongArgs( const std::string& id ) {
			auto iter = std::find_if( arguments.begin(), arguments.end(), [&id]( const CVariableInfo* info ) 
				{ return info->GetName() == id; } );
			return iter == arguments.end() ? 0 : *iter;
		}
		CVariableInfo* FindVarAmongLocals( const std::string& id ) {
			auto iter = std::find_if( localVariables.begin(), localVariables.end(), [&id]( const CVariableInfo* info ) 
				{ return info->GetName() == id; } );
			return iter == localVariables.end() ? 0 : *iter;
		}

		bool HaveLocalVar( const std::string& id ) {
			return FindVarAmongLocals( id ) != 0;
		}
		bool HaveInArgs( const std::string& id ) {
			return FindVarAmongArgs( id ) != 0;
		}
	private:

		std::string type;
		std::string name;
		std::vector< CVariableInfo* > localVariables;
		std::vector< CVariableInfo* > arguments;
	};
}