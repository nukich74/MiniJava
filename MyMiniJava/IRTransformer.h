#pragma once
#include "IntermidRepresent.h"

namespace Canon {

	class CMoveCall : public IRTree::IStmt {
	public:
		CMoveCall( const IRTree::CTemp* _dst, const IRTree::CCall* _src ) : dst( _dst ), src( _src ) {}
		const IRTree::CExprList* Kids() const;
		const IRTree::IStmt* Build( const IRTree::CExprList* kids ) const;
		virtual void Accept( IRTree::IRTreePrinter* p ) const { p->Visit( *this ); }
	private:
		const IRTree::CTemp* dst;
		const IRTree::CCall* src;
	};   

	class CExpCall : public IRTree::IStmt {
	public:
		CExpCall( const IRTree::CCall* _call ) : call( _call ) {}
		const IRTree::CExprList* Kids() const;
		const IRTree::IStmt* Build( const IRTree::CExprList* kids ) const;
		virtual void Accept( IRTree::IRTreePrinter* p ) const { p->Visit( *this ); }
	private:
		const IRTree::CCall* call;
	};   

	struct CStmExpList {
		CStmExpList( const IRTree::IStmt* _stm, const IRTree::CExprList* _exprs ) : stm( _stm ), exprs( _exprs ) {}
		const IRTree::IStmt* stm;
		const IRTree::CExprList* exprs;
	};

	class CCanon {
	public:
		bool IsNop( const IRTree::IStmt* a );

		const IRTree::IStmt* SimplifySeq( const IRTree::IStmt* a, const IRTree::IStmt* b );

		bool Commute( const IRTree::IStmt* a, const IRTree::IExpr* b );

		const IRTree::IStmt* DoStm( const IRTree::CSeq* s );

		const IRTree::IStmt* DoStm( const IRTree::CMove* s ); 

		const IRTree::IStmt* DoStm( const IRTree::CExp* s );

		const IRTree::IStmt* DoStm( const IRTree::IStmt* s );

		const IRTree::IStmt* ReorderStm( const IRTree::IStmt* s );

		const IRTree::CEseq* DoExp( const IRTree::CEseq* e );

		const IRTree::CEseq* DoExp( const IRTree::IExpr* e );

		const IRTree::CEseq* ReorderExp( const IRTree::IExpr* e );

		const CStmExpList* Reorder( const IRTree::CExprList* exps );
	   
		const IRTree::CStmtList* Linear( const IRTree::CSeq* s, const IRTree::CStmtList* l );

		const IRTree::CStmtList* Linear( const IRTree::IStmt* s, const IRTree::CStmtList* l );

		const IRTree::CStmtList* Linearize( const IRTree::IStmt* s );

	private:
		static CStmExpList* nopNull;
	};

}