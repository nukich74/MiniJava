#include "IRPrint.h"
#include "IntermidRepresent.h"
#include <algorithm>

namespace IRTree {

	void IRGraph::AddEdge( const std::string& from, const std::string& to ) 
	{
		vertexSet.insert( from );
		vertexSet.insert( to );
		edgeList.push_back( std::make_pair( from, to ) );
	}

	std::string IRGraph::ToString() const 
	{
		std::string result = "digraph G { ";
		for( const auto& e : edgeList ) {
			result += e.first + " -> " + e.second + " \n";
		}
		result += "}";
		std::replace( result.begin(), result.end(), '.', '_' );
		return result;
	}

	std::string IRTreePrinter::GetResult() const
	{
		return graph.ToString();
	}

	void IRTreePrinter::Visit( const CLabel& p ) 
	{
		lastName = newVertex( "CLabel" );
	}
	
	void IRTreePrinter::Visit( const CBinop& p )
	{
		std::string curName = newVertex( "Binop" );
		if( p.left ) {
			p.left->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		if( p.right ) { 
			p.right->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		lastName = curName;
		graph.AddEdge( curName, std::to_string( p.oper ) );
	}

	void IRTreePrinter::Visit( const CCall& p )
	{
		std::string curName = newVertex( "Call" );
		if( p.args ) {
			p.args->Accept( this );
			graph.AddEdge( curName, lastName );
		}

		if( p.func ) {
			p.func->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		lastName = curName;
	}
	
	void IRTreePrinter::Visit( const CCJump& p )
	{
		std::string curName = newVertex( "CJump" );
		if( p.left ) {
			p.left->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		if( p.right ) {
			p.right->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		lastName = curName;
	}	

	void IRTreePrinter::Visit( const CConst& p ) 
	{
		lastName = "Const_" + std::to_string( p.value );
	}
	
	void IRTreePrinter::Visit( const CEseq& p )
	{
		std::string curName = newVertex( "Eseq" );
		if( p.stm ) {
			p.stm->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		if( p.expr ) {
			p.expr->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		lastName = curName;
	}
	
	void IRTreePrinter::Visit( const CExp& p )
	{
		std::string curName = newVertex( "Exp" );
		if( p.exp ) {
			p.exp->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		lastName = curName;
	}
	
	void IRTreePrinter::Visit( const CExprList& p )
	{		
		std::string curName = newVertex( "ExpList" );
		if( p.GetCurrent() ) {
			p.GetCurrent()->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		if( p.GetNextExprs() ) {
			p.GetNextExprs()->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		lastName = curName;
	}

	void IRTreePrinter::Visit( const CJump& p )
	{
		lastName = newVertex( "Jump" );
	}

	void IRTreePrinter::Visit( const CStmtList& p )
	{	
		std::string curName = newVertex( "StmtList" );
		if( p.GetCurrent() ) {
			p.GetCurrent()->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		if( p.GetNextStmts() ) {
			p.GetNextStmts()->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		lastName = curName;
	}

	void IRTreePrinter::Visit( const CName& p )
	{	
		lastName = newVertex( "Name_" + p.label->ToString() );
	}

	void IRTreePrinter::Visit( const CTemp& p )
	{	
		lastName = newVertex( "Temp" );
	}

	void IRTreePrinter::Visit( const CMove& p )
	{
		std::string curName = newVertex( "Move" );
		if( p.src ) {
			p.src->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		if( p.dst ) {
			p.dst->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		lastName = curName;
	}

	void IRTreePrinter::Visit( const CMem& p )
	{	
		std::string curName = newVertex( "Mem" );
		if( p.expr ) {
			p.expr->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		lastName = curName;
	}

	void IRTreePrinter::Visit( const CSeq& p )
	{	
		std::string curName = newVertex( "Seq" );
		if( p.left ) {
			p.left->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		if( p.right ) {
			p.right->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		if( p.last ) {
			p.last->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		lastName = curName;
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

	std::string IRTreePrinter::newVertex( const std::string& name ) 
	{
		return name + std::to_string( ++this->vertexId );
	}

};