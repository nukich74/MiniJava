#include "IRPrint.h"
#include "IntermidRepresent.h"

namespace IRTree {

	std::string IRTreePrinter::GetResult() const
	{
		return "";
	}

	void IRTreePrinter::Visit( const CLabel& p ) 
	{
	}
	
	void IRTreePrinter::Visit( const CBinop& p )
	{
	}

	void IRTreePrinter::Visit( const CCall& p )
	{
	}
	
	void IRTreePrinter::Visit( const CCJump& p )
	{
	}	

	void IRTreePrinter::Visit( const CConst& p ) 
	{
	}
	
	void IRTreePrinter::Visit( const CEseq& p )
	{
	}
	
	void IRTreePrinter::Visit( const CExp& p )
	{
	}
	
	void IRTreePrinter::Visit( const CExprList& p )
	{		
	}

	void IRTreePrinter::Visit( const CJump& p )
	{
	}

	void IRTreePrinter::Visit( const CStmtList& p )
	{	
	}

	void IRTreePrinter::Visit( const CName& p )
	{	
	}

	void IRTreePrinter::Visit( const CTemp& p )
	{	
	}

	void IRTreePrinter::Visit( const CMove& p )
	{	
	}

	void IRTreePrinter::Visit( const CMem& p )
	{	
	}

	void IRTreePrinter::Visit( const CSeq& p )
	{	
	}

	void IRTreePrinter::Visit( const Canon::CMoveCall& p )
	{	
	}

	void IRTreePrinter::Visit( const Canon::CExpCall& p )
	{	
	}

};