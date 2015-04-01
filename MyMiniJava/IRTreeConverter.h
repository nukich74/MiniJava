// Pavel Borin

#include <list>
#include <StackFrame.h>
#include <vector>

namespace Converter {

class AsmVertex;
class CommonAsmVertex;
class MoveAsmVertex;
class LabelAsmVertex;

class IRTreeConverter {
public:	
	static std::vector< std::vector<AsmVertex> > ConvertAllFunctions( std::list<StackFrame::CFrame*> functions );

private:
	static std::vector<AsmVertex> convertFunction( StackFrame::CFrame* function );
};

}; // namespace Converter