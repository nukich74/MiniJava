#include "IntermidRepresent.h"
#include <map>
#include <vector>
#include <string>

namespace Canon {

	struct CBlock {
		std::vector<const IRTree::IStmt*> stms;
		std::string rootLabel;
		bool isInverted; //нужно ли инвертировать условие, при сборке.
		bool isNoConditions; //нужно ли делать левую метку и т.д.
		CBlock() : isNoConditions( false ), isInverted( false ), rootLabel("emptyRootLabel") {}
	};

	class Tracer {
	public:
		Tracer();
		IRTree::CStmtList* Transform( const IRTree::CStmtList* list );
	private:
		Temp::CLabel* doneLabel;
		std::map<const Temp::CLabel*, int> labelMap;
		std::vector<CBlock> blockSequence;
		std::vector<int> resultVector;

		void findBlocks( const IRTree::CStmtList* list );
		void sortBlocks();
		void dfs( int blockId, std::vector<int>& used );
	};

}