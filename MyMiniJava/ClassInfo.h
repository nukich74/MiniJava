#pragma once
#include "VariableInfo.h"
#include "MethodInfo.h"
#include <algorithm>

namespace SymbolsTable {
	
	class CClassInfo {
	public:

		CClassInfo( const std::string& _name, const std::string& _extName ) : name( _name ), extendedName( _extName ) { } 
		void AddLocalVar( CVariableInfo* _var ) { localVars.push_back( _var ); }
		void AddMethod( CMethodInfo* _method ) { methods.push_back( _method ); }
		std::string GetName() { return name; }
		std::string GetExtendedName() { return extendedName; }
		const std::vector< CVariableInfo* >& GetLocals() { return localVars; }
		const std::vector< CMethodInfo* >& GetMethods() { return methods; }
		bool HaveVariable( const std::string& id ) {
			return std::find_if( localVars.begin(), localVars.end(), [&id]( const CVariableInfo* info ) 
				{ return info->GetName() == id; } ) != localVars.end();
		}

		bool HaveMethod( const std::string& id ) { 
			return std::find_if( methods.begin(), methods.end(), [&id]( const CVariableInfo* info ) 
				{ return info->GetName() == id; } ) != methods.end();
		}

	private:

		std::string name;
		std::string extendedName;
		std::vector< CVariableInfo* > localVars;
		std::vector< CMethodInfo* > methods;
	};
}