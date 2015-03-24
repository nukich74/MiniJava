#include "IntermidRepresent.h"
#include <map>
#include <vector>

namespace Canon {

class Splitter {
public:
	
};

class Tracer {
public:
	void Rebuild( const IRTree::CStmtList& stmt );
private:
	std::vector< std::pair< IRTree::CLabel, IRTree::CStmtList > > blockTable;
};

}