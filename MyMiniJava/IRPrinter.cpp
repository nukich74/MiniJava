#include "IRPrint.h"
#include "IntermidRepresent.h"
#include <algorithm>

namespace IRTree {

	void IRGraph::Clear() {
		labels.clear();
		vertexSet.clear();
		edgeList.clear();
	}

	void IRTreePrinter::Clear() {
		vertexStat.clear();
		vertexId = 0;
		graph.Clear();
		lastName = "";
	}

	void IRGraph::AddEdge( const std::string& from, const std::string& to ) 
	{
		vertexSet.insert( from );
		vertexSet.insert( to );
		labels.push_back( "" );
		edgeList.push_back( std::make_pair( from, to ) );
	}

	void IRGraph::AddEdge( const std::string& from, const std::string& to, const std::string& text ) 
	{
		vertexSet.insert( from );
		vertexSet.insert( to );
		labels.push_back( text );
		edgeList.push_back( std::make_pair( from, to ) );
	}

	std::string IRGraph::ToString() const 
	{
		std::string result = "digraph G { ";
		for( int i = 0; i < edgeList.size(); i++ ) {
			result += edgeList[i].first + " -> " + edgeList[i].second +
				" [ label=\"" + labels[i] + "\" ];" + " \n";
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
		lastName = newVertex( "_" + p.label->ToString() );
	}

	std::string ToOperator( IRTree::BinOp arg ) {
		switch (arg)
		{
		case IRTree::BO_Plus:
			return "Plus";
			break;
		case IRTree::BO_Minus:
			return "Minus";
			break;
		case IRTree::BO_Mult:
			return "Mult";
			break;
		case IRTree::BO_Div:
			return "Div";
			break;
		case IRTree::BO_And:
			return "And";
			break;
		case IRTree::BO_Less:
			return "Less";
			break;
		default:
			assert( false );
			break;
		}
	}
	
	void IRTreePrinter::Visit( const CBinop& p )
	{
		std::string curName = newVertex( "Binop" + ToOperator( p.oper ) );
		if( p.left ) {
			p.left->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		if( p.right ) { 
			p.right->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		lastName = curName;
//		graph.AddEdge( curName, std::to_string( p.oper ) );
	}

	void IRTreePrinter::Visit( const CCall& p )
	{
		std::string curName = newVertex( "Call" );
		if( p.args ) {
			p.args->Accept( this );
			graph.AddEdge( curName, lastName, "1" );
		}

		if( p.func ) {
			p.func->Accept( this );
			graph.AddEdge( curName, lastName, "2" );
		}
		lastName = curName;
	}
	
	void IRTreePrinter::Visit( const CCJump& p )
	{
		std::string curName = newVertex( "CJump " );
		if( p.left ) {
			p.left->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		if( p.right ) {
			p.right->Accept( this );
			graph.AddEdge( curName, lastName );
		}
		graph.AddEdge( curName, "_" + p.ifFalse->ToString(), "false" );
		graph.AddEdge( curName, "_" + p.ifTrue->ToString(), "true" );
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
			graph.AddEdge( curName, lastName, "1" );
		}
		if( p.expr ) {
			p.expr->Accept( this );
			graph.AddEdge( curName, lastName, "2" );
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
		graph.AddEdge( lastName, "_" + p.label->label->ToString() );
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
		lastName = newVertex( "_Name_" + p.label->ToString() );
	}

	void IRTreePrinter::Visit( const CTemp& p )
	{	
		lastName = newVertex( "_" + p.temp->ToString() );
	}

	void IRTreePrinter::Visit( const CMove& p )
	{
		std::string curName = newVertex( "Move" );
		if( p.src ) {
			p.src->Accept( this );
			graph.AddEdge( curName, lastName, "src" );
		}
		if( p.dst ) {
			p.dst->Accept( this );
			graph.AddEdge( curName, lastName, "dst" );
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
			graph.AddEdge( curName, lastName, "1" );
		}
		if( p.right ) {
			p.right->Accept( this );
			graph.AddEdge( curName, lastName, "2" );
		}
		if( p.last ) {
			p.last->Accept( this );
			graph.AddEdge( curName, lastName, "3" );
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
		if( name[0] == '_' ) {
			return name;
		}
		auto iter = vertexStat.find( name );
		if( iter == vertexStat.end() ) {
			vertexStat[name] = 1;
		} else {
			vertexStat[name] += 1;		
		}
		return name + std::to_string( vertexStat[name] );
	}

};