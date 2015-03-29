// Борин Павел
// интерфейс визитора для дерева промежуточного представления

#include <IntermidRepresent.h>

namespace IRTree
{

class IIRVisitor {

public:
	virtual ~IIRVisitor() {};

	virtual void Visit( const CConst& p ) = 0;
	virtual void Visit( const CName& p ) = 0;
	virtual void Visit( const CTemp& p ) = 0;
	virtual void Visit( const CBinop& p ) = 0;

	virtual void Visit( const CMem& p ) = 0;
	virtual void Visit( const CCall& p ) = 0;

	virtual void Visit( const CEseq& p ) = 0;
	virtual void Visit( const CMove& p ) = 0;
	virtual void Visit( const CExp& p ) = 0;
	virtual void Visit( const CJump& p ) = 0;
	virtual void Visit( const CCJump& p ) = 0;
	virtual void Visit( const CSeq& p ) = 0;
	virtual void Visit( const CLabel& p ) = 0;

	virtual void Visit( const CExprList& p ) = 0;
	virtual void Visit( const CStmtList& p ) = 0;

};

};