//Borin Pavel
//StackFrame + ��������������� ������

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

//��������� ��� ���������� �� ������
class IAccess {
public:
	virtual ~IAccess() = 0 {};
	virtual const IRTree::IExpr* GetExp( const CFrame* frame ) const = 0;
};

//����� ���������� � ������
///�� ������� ��� ���� ������ �������
class CInFrame : public IAccess {
public:
	CInFrame( int _address ): address( _address ) {};

	const IRTree::IExpr* GetExp( const CFrame* frame ) const;

private:
	int address;
};

//� ��������, �� �����������???
class CInReg: public IAccess {
public:
	CInReg( int _address ): address( _address ) {};

	const IRTree::IExpr* GetExp( const CFrame* frame ) const {};
private:
	int address;
};


//� ���� ������� ���� �� ��� � �������
//The class Frame holds information about formal parameters and local variables allocated in this frame.
//To make a new frame for a function f with k formal parameters, call newFrame(f)
//�� ������ ���������, ��� ��� ���������� ������ �� 1 ������
class CFrame {
public:
	CFrame( const std::string _name, IRTree::IStmt* _funcRoot );

	int WordSize() const { return wordSize; };
	
	const Temp::CTemp* GetReturnValuePointer() const { return returnValue; };
	const Temp::CTemp* GetStackPointer() const { return stackPointer; };
	const Temp::CTemp* GetFramePointer() const { return framePointer; };

	const IAccess* GetFormal( const std::string& name ) const;
	const IAccess* GetLocal( const std::string& name ) const;
	void AddFormal( const std::string& temp, const IAccess* accs ) { formals[temp] = accs; };
	void AddLocal( const std::string& temp, const IAccess* accs ) { locals[temp] = accs; };
	int GetLocalCount() const { return locals.size(); }

	const IAccess* GetAccess( const std::string& name ) const;
	const std::vector<const std::string>& GetRegisters() const { return registers; }
	const Temp::CTemp* GetEax() const { return eax; }
	const Temp::CTemp* GetEdx() const { return edx; }

	const IRTree::IStmt* funcRoot;
	int wordSize;
	const std::string name;

private:
	std::map<const std::string, const IAccess* > formals;
	std::map<const std::string, const IAccess* > locals;
	std::vector<const std::string> registers;
	const Temp::CTemp* returnValue;
	const Temp::CTemp* stackPointer;
	const Temp::CTemp* framePointer;
	const Temp::CTemp* eax;
	const Temp::CTemp* edx;
};

}