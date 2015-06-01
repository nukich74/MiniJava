#include "StackFrame.h"
#include <IntermidRepresent.h>

namespace StackFrame {

CFrame::CFrame( const std::string _name, IRTree::IStmt* _funcRoot ) : name( _name ),
	wordSize( 4 ), funcRoot( _funcRoot ),
	framePointer( new Temp::CTemp( "EBP" ) ),
	stackPointer( new Temp::CTemp( "ESP" ) ),
	returnValue( new Temp::CTemp( _name + "_RV" ) ),
	eax( new Temp::CTemp( "EAX" ) ),
	edx( new Temp::CTemp( "EDX" ) )
{
	registers.emplace_back( "EAX" );
	registers.emplace_back( "EBX" );
	registers.emplace_back( "ECX" );
	registers.emplace_back( "EDX" );
	registers.emplace_back( "ESI" );
	registers.emplace_back( "EDI" );
	// registers.emplace_back( "ESP" );
	// registers.emplace_back( "EBP" );
}

const IAccess* CFrame::GetFormal( const std::string& name ) const 
{
	/*auto iter = formals->GetElement( name );
	if( iter != formals->GetEnd() ) {
		return iter->second;
	}*/
	auto iter = formals.find( name );
	if( iter != formals.end() ) {
		return iter->second;
	}
	return 0;
}

const IAccess* CFrame::GetLocal( const std::string& name ) const 
{ 
	//auto iter = locals->GetElement( name );
	//if( iter != locals->GetEnd() ) {
	//	return iter->second;
	//}
	//return 0;
	auto iter = locals.find( name );
	if( iter != locals.end() ) {
		return iter->second;
	}
	return 0;
}

const IAccess* CFrame::GetAccess( const std::string& name ) const 
{
	const IAccess* res = GetLocal( name );
	if( res != 0 ) {
		return res;
	}
	return GetFormal( name );
}

const IRTree::IExpr* CInFrame::GetExp( const CFrame* frame ) const
{
	IRTree::BinOp oper = IRTree::BinOp::BO_Minus;
	//адресс по смещению
	if( address < 0 ) {
		oper = IRTree::BinOp::BO_Minus;
	} else {
		oper = IRTree::BinOp::BO_Plus;
	}
	return new IRTree::CMem( new IRTree::CBinop(
		oper, new IRTree::CTemp( frame->GetFramePointer() ),
		new IRTree::CMem( new IRTree::CBinop( IRTree::BinOp::BO_Mult, 
		new IRTree::CConst( address ), new IRTree::CConst( frame->WordSize() ) ) ) ) );
}

//StackFrame

}