#include "IntermidRepresent.h"

namespace Canon {

class Tracer {
public:
	void Rebuild( const IRTree::IStmt* stmt );
private:
	bool isStart( const IRTree::IStmt* stmt ) {
		return ( dynamic_cast<const IRTree::CLabel*>( stmt ) != 0 );
	}
	bool isLeaf( const IRTree::IStmt* stmt ) {
		return ( ( dynamic_cast<const IRTree::CJump*>( stmt ) != 0 ) || 
			( dynamic_cast<const IRTree::CCJump*>( stmt ) != 0 ) );
	}
	IRTree::CStmtList list;
};

}