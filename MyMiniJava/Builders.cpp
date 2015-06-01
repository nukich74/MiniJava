#pragma once
#include "Builders.h"
#include "AssemblerInstr.h"
#include "StackFrame.h"

namespace PrologEpilogBuilder {

	using namespace Assembler;

	std::vector<std::string> IntermidInstructionBuilder::AddProlog(const StackFrame::CFrame* frame ) 
	{
		//запомнили, где сейчас
		std::vector<std::string> prologIList;
		prologIList.push_back( "; prolog begin" );
		prologIList.push_back( frame->name + ":" );
		prologIList.push_back("push EBP");
		//указываем на старое место
		prologIList.push_back( "mov EBP, ESP" );
		int espShift = frame->WordSize() * frame->GetLocalCount();
		prologIList.push_back( "sub esp, " + std::to_string( espShift ) );
		//сохранили
		for( const auto& regName : frame->GetRegisters() ) {
			prologIList.push_back( "push " + regName );
		}
		prologIList.push_back( "; prolog end" );
		return prologIList;
	}

	std::vector<std::string> IntermidInstructionBuilder::AddEpilog( const StackFrame::CFrame* frame )
	{
		std::vector<std::string> epilogIList;
		std::vector<const std::string> regs( frame->GetRegisters() );
		std::reverse( regs.begin(), regs.end() );
		epilogIList.push_back( "; epilog begin" );
		int espShift = frame->WordSize() * frame->GetLocalCount();
		for( const auto& item : regs ) {
			epilogIList.push_back( "pop " + item );
		}
		epilogIList.push_back( "add ESP, " + std::to_string( espShift ) );
		epilogIList.push_back( "pop EBP" );
		epilogIList.push_back( "ret" );
		epilogIList.push_back( "; epilog end" );
		return epilogIList;
	}
}