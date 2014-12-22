//Stolbov Igor

#pragma once

#include<IntermidRepresent.h>
#include<grammar.h>
#include <IRPrint.h>
#include <memory>

namespace IRTree {

	class CExpList {
	public:
		CExpList( const IExpr* const _head, const CExpList* const _tail ) :
			head( _head ), tail( _tail )
		{}

		void Print( CPrinter& printer ) const
		{
			printer.Print( this );
		}

		std::shared_ptr<const IExpr> head;
		std::shared_ptr<const CExpList> tail;
	};

	class CStmList {
		CStmList( const IStmt* const _head, const CStmList* const _tail ) :
		head( _head ), tail( _tail )
		{}

		std::shared_ptr<const IStmt> head;
		std::shared_ptr<const CStmList> tail;
	};

} // namespace IRTree 