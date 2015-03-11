#include "IRHelpers.h"
#include "grammar.h"
#include "IntermidRepresent.h"
#include "SubtreeWrapper.h"

namespace IRTranslate {

	class CConditionalWrapper : public ISubtreeWrapper {
		const IExpr* ToExp( ) const;
		const IStmt* ToStm( ) const;
	};

	class CAndWrapper : public CConditionalWrapper {
	public:
		const IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f );
	private:
		const IExpr* left;
		const IExpr* right;
	};

	class CLessWrapper : public CConditionalWrapper {
	public:
		const IStmt* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f );
	private:
		const IExpr* left;
		const IExpr* right;
	};
}