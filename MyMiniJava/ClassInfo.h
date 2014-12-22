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
		std::string GetName() const { return name; }
		std::string GetExtendedName() const { return extendedName; }
		const std::vector< CVariableInfo* >& GetLocals() const { return localVars; }
		const std::vector< CMethodInfo* >& GetMethods() const { return methods; }
		
		CVariableInfo* FindVariable( const std::string& id ) const {
			auto iter = std::find_if( localVars.begin(), localVars.end(), [&id]( const CVariableInfo* info ) 
				{ return info->GetName() == id; } );
			return iter == localVars.end() ? 0 : *iter;
		}

		CMethodInfo* FindMethod( const std::string& id ) const {
			auto iter = std::find_if( methods.begin(), methods.end(), [&id]( const CMethodInfo* info ) 
				{ return info->GetName() == id; } );
			return iter == methods.end() ? 0 : *iter; 
		}

		bool HaveVariable( const std::string& id ) const {
			return ( FindVariable( id ) != 0 );
		}

		bool HaveMethod( const std::string& id ) const { 
			return ( FindMethod( id ) != 0 );
		}
	private:

		std::string name;
		std::string extendedName;
		std::vector< CVariableInfo* > localVars;
		std::vector< CMethodInfo* > methods;
	};
}