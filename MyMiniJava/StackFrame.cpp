#include "StackFrame.h"
#include <IntermidRepresent.h>

namespace StackFrame {



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

const IExpr* CInFrame::GetExp( const CFrame* frame ) const
{
	//адресс по смещению
	return new IRTree::CMem( new IRTree::CBinop(
		IRTree::BinOp::BO_Plus, new IRTree::CTemp( frame->GetFramePointer() ),
		new IRTree::CMem( new IRTree::CBinop( IRTree::BinOp::BO_Mult, 
		new IRTree::CConst( address ), new IRTree::CConst( frame->WordSize() ) ) ) ) );
}

//StackFrame

}