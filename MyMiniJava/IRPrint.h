#pragma once
#include <utility>
#include <vector>
#include <string>

namespace Canon {
	class CMoveCall;
	class CExpCall;
}

namespace IRTree {

class CLabel;
class CBinop;
class CCall;
class CCJump;
class CConst;
class CEseq;
class CExp;
class CExprList;
class CJump;
class CStmtList;
class CName;
class CTemp;
class CMove;
class CSeq;
class CMem;

class IRGraph {
public:
	std::string ToString();
private:
	std::vector< std::pair< std::string, std::string > > edgeList;
};

class IRTreePrinter {
public:
	std::string GetResult() const;
	void Visit( const CLabel& p );
	void Visit( const CBinop& p );
	void Visit( const CCall& p );
	void Visit( const CCJump& p );
	void Visit( const CConst& p );
	void Visit( const CEseq& p );
	void Visit( const CExp& p );
	void Visit( const CExprList& p );
	void Visit( const CJump& p );
	void Visit( const CStmtList& p );
	void Visit( const CName& p );
	void Visit( const CTemp& p );
	void Visit( const CMove& p );
	void Visit( const CMem& p );
	void Visit( const CSeq& p );
	void Visit( const Canon::CMoveCall& p );
	void Visit( const Canon::CExpCall& p );
private:
	std::string result;
};

}