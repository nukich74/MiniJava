#pragma once
#include <utility>
#include <vector>
#include <string>
#include <set>
#include <map>

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
	std::string ToString() const;
	void AddEdge( const std::string& from, const std::string& to );
	void AddEdge( const std::string& from, const std::string& to, const std::string& text );
	void Clear();
private:
	std::set< std::string > vertexSet;
	std::vector< std::pair< std::string, std::string > > edgeList;
	std::vector< std::string > labels;
};

class IRTreePrinter {
public:
	IRTreePrinter() : vertexId(0) {}
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
	void Clear();
private:
	IRGraph graph;
	std::string lastName;
	int vertexId;
	std::map<std::string, int > vertexStat;
	std::string newVertex( const std::string& name ); 
};

}