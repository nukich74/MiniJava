//Borin Pavel

#pragma once

#include <IIRTreeVisitor.h>

namespace IRTree {

class IRTreeToAssambler : public IIRVisitor {

public:
	virtual void Visit( const CConst& p );
	virtual void Visit( const CName& p );
	virtual void Visit( const CTemp& p );
	virtual void Visit( const CBinop& p );

	virtual void Visit( const CMem& p );
	virtual void Visit( const CCall& p );

	virtual void Visit( const CEseq& p );
	virtual void Visit( const CMove& p );
	virtual void Visit( const CExp& p );
	virtual void Visit( const CJump& p );
	virtual void Visit( const CCJump& p );
	virtual void Visit( const CSeq& p );
	virtual void Visit( const CLabel& p );

	virtual void Visit( const CExprList& p );
	virtual void Visit( const CStmtList& p );

};

}; // IRTree