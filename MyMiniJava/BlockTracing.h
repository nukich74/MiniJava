#include "IntermidRepresent.h"
#include <map>
#include <vector>
#include <string>

namespace Canon {

	struct CBlock {
		std::vector<const IRTree::IStmt*> stms;
		std::string targetLabel;
		std::string rootLabel;
		bool isCJump;

		CBlock() : isCJump( false ), targetLabel( "emptyLabel" ), rootLabel("emptyRootLabel") {}
	};

	class Tracer {
	public:
		void doCJump();

	private:
		Temp::CLabel* doneLabel;
		std::map<std::string, int> labelMap;
		std::vector<CBlock> blockSequence;

		void findBlocks( const IRTree::CStmtList* list );
		void sortBlocks();
	};

}