//Stolbov Igor
#pragma once
#include "Temp.h"
#include "IntermidRepresent.h"
#include "grammar.h"

namespace IRTranslate {
	class ISubtreeWrapper {
	public:
		const virtual IExpr* ToExp( ) const = 0;
		const virtual IStmt* ToStm( ) const = 0;
		const virtual IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const = 0;
	};


};