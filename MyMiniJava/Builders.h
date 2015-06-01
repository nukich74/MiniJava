#pragma once
#include "StackFrame.h"

namespace PrologEpilogBuilder {

	class IntermidInstructionBuilder {
	public:
		std::vector<std::string> AddProlog( const StackFrame::CFrame* frame );
		std::vector<std::string> AddEpilog( const StackFrame::CFrame* frame );
	};

}