//Borin Pavel
//StackFrame + вспомогательные классы

#pragma once
#include <string>
#include <list>
#include <vector>
#include "Temp.h"
#include "IntermidRepresent.h"
#include <map>
#include <unordered_map>


namespace StackFrame {

class CFrame;

//интерфейс для переменной из фрейма
class IAccess {
public:
	virtual ~IAccess() = 0 {};
	virtual const IRTree::IExpr* GetExp( const CFrame* frame ) const = 0;
};

//Соотв переменная в фрэйме
///НЕ понятно что этим хотели сказать
class CInFrame : public IAccess {
public:
	CInFrame( int _address ): address( _address ) {};

	const IRTree::IExpr* GetExp( const CFrame* frame ) const;

private:
	int address;
};

//в регистре, не исользуется???
class CInReg: public IAccess {
public:
	CInReg( int _address ): address( _address ) {};

	const IRTree::IExpr* GetExp( const CFrame* frame ) const {};
private:
	int address;
};


//С Этим классов явно не все в порядке
//The class Frame holds information about formal parameters and local variables allocated in this frame.
//To make a new frame for a function f with k formal parameters, call newFrame(f)
//Не делаем интрефейс, так как реализация строго на 1 машине
class CFrame {
public:
	CFrame( const std::string _name, IRTree::IStmt* _funcRoot ) : name( _name ),
		wordSize(4), funcRoot(_funcRoot),
		framePointer( new Temp::CTemp( _name + "_FP" ) ),
		stackPointer( new Temp::CTemp( _name + "_SP" ) ),
		returnValue( new Temp::CTemp( _name + "_RV" ) )
		{};

	int WordSize() const { return wordSize; };
	
	const Temp::CTemp* GetReturnValuePointer() const { return returnValue; };
	const Temp::CTemp* GetStackPointer() const { return stackPointer; };
	const Temp::CTemp* GetFramePointer() const { return framePointer; };

	const IAccess* GetFormal( const std::string& name ) const;
	const IAccess* GetLocal( const std::string& name ) const;
	void AddFormal( const std::string& temp, const IAccess* accs ) { formals[temp] = accs; };
	void AddLocal( const std::string& temp, const IAccess* accs ) { locals[temp] = accs; };

	const IAccess* GetAccess( const std::string& name ) const;

	const IRTree::IStmt* funcRoot;
	int wordSize;
	const std::string name;

private:
	std::map<const std::string, const IAccess* > formals;
	std::map<const std::string, const IAccess* > locals;
	const Temp::CTemp* returnValue;
	const Temp::CTemp* stackPointer;
	const Temp::CTemp* framePointer;
};

}