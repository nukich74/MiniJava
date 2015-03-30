#include "IRPrint.h"
#include "IntermidRepresent.h"

namespace IRTree {

	void IRGraph::AddEdge( const std::string& from, const std::string& to ) 
	{
		edgeList.push_back( std::make_pair( from, to ) );
	}

	std::string IRGraph::ToString() const 
	{
		std::string result = "digraph G { ";
		for( const auto& e : edgeList ) {
			result += e.first + " -> " + e.second + " ";
		}
		return result + "}";
	}

	std::string IRTreePrinter::GetResult() const
	{
		return graph.ToString();
	}

	void IRTreePrinter::Visit( const CLabel& p ) 
	{
		lastName = "CLabel";
	}
	
	void IRTreePrinter::Visit( const CBinop& p )
	{
		if( p.left ) {
			p.left->Accept( this );
		}
		if( p.right ) { 
			p.right->Accept( this );
		}
	}

	void IRTreePrinter::Visit( const CCall& p )
	{
		if( p.args ) {
			p.args->Accept( this );
		}
		if( p.func ) {
			p.func->Accept( this );
		}
	}
	
	void IRTreePrinter::Visit( const CCJump& p )
	{
		if( p.left ) {
			p.left->Accept( this );
		}
		if( p.right ) {
			p.right->Accept( this );
		}
	}	

	void IRTreePrinter::Visit( const CConst& p ) 
	{
		lastName = "Const_" + std::to_string( p.value );
	}
	
	void IRTreePrinter::Visit( const CEseq& p )
	{
		if( p.stm ) {
			p.stm->Accept( this );
		}
		if( p.expr ) {
			p.expr->Accept( this );
		}
	}
	
	void IRTreePrinter::Visit( const CExp& p )
	{
		if( p.exp ) {
			p.exp->Accept( this );
		}
	}
	
	void IRTreePrinter::Visit( const CExprList& p )
	{		
		if( p.GetCurrent() ) {
			p.GetCurrent()->Accept( this );
		}
		if( p.GetNextExprs() ) {
			p.GetNextExprs()->Accept( this );
		}
	}

	void IRTreePrinter::Visit( const CJump& p )
	{
		lastName = "CJump";
	}

	void IRTreePrinter::Visit( const CStmtList& p )
	{	
		if( p.GetCurrent() ) {
			p.GetCurrent()->Accept( this );
		}
		if( p.GetNextStmts() ) {
			p.GetNextStmts()->Accept( this );
		}
	}

	void IRTreePrinter::Visit( const CName& p )
	{	
		lastName = "CName_" + p.label->ToString();
	}

	void IRTreePrinter::Visit( const CTemp& p )
	{	
		lastName = "CTemp";
	}

	void IRTreePrinter::Visit( const CMove& p )
	{
		if( p.src ) {
			p.src->Accept( this );
		}
		if( p.dst ) {
			p.dst->Accept( this );
		}
	}

	void IRTreePrinter::Visit( const CMem& p )
	{	
		if( p.expr ) {
			p.expr->Accept( this );
		}
	}

	void IRTreePrinter::Visit( const CSeq& p )
	{	
		if( p.left ) {
			p.left->Accept( this );
		}
		if( p.right ) {
			p.right->Accept( this );
		}
		if( p.last ) {
			p.last->Accept( this );
		}
	}

	void IRTreePrinter::Visit( const Canon::CMoveCall& p )
	{	
		//TODO
		assert( false );
	}

	void IRTreePrinter::Visit( const Canon::CExpCall& p )
	{	
		//TODO
		assert( false );
	}

};