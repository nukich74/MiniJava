// Borin Pavel
// AsmCodeGeneration

#pragma once

#include <list>
#include <string.h>
#include <Temp.h>
#include <StackFrame.h>

namespace Assembler {

class AsmInstr { 
public:
	AsmInstr( const Temp::CTempList* _used, const Temp::CTempList* _defs, const Temp::CLabelList* _jumps ) :
		used(_used), defines(_defs), jumps(_jumps) {};

	const Temp::CTempList* UsedVars() const { return used; };
	const Temp::CTempList* Defines() const { return defines; };
	const Temp::CLabelList* Jumps() const { return jumps; };

	// подстановка, нужно обдумать
	void FormatInstr();

private:
	std::string asmCommand;
	const Temp::CTempList* used;
	const Temp::CTempList* defines;
	const Temp::CLabelList* jumps;
}; 

class AsmTreeMaker {
public:
	AsmTreeMaker( const StackFrame::CFrame* _stackFrame ) : stackFrame(_stackFrame), isInitialized(false) {};
	
	// функция интерпретиирования промежуточного представления функции
	void InitializeTree() const;
	bool IsInitialized() const { return isInitialized; };

	const std::list<const AsmInstr*> GetAsmInstr() const { return func; };
	const StackFrame::CFrame* GetFrame() const { return stackFrame; };

private:
	mutable std::list<const AsmInstr*> func;
	bool isInitialized;
	const StackFrame::CFrame* stackFrame;
};


};