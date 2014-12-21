//Borin Pavel
//StackFrame + вспомогательные классы

#pragma once
#include <string>
#include <list>
#include <vector>
#include "Temp.h"
#include "grammar.h"

using namespace Temp;

namespace StackFrame {

//интерфейс для переменной из фрейма
class IAccess {
public:
	virtual ~IAccess() = 0 {};

	virtual const IExpr* getVar() const = 0;
private:
};

//Его нужно переписать к нужному виду
class CAccessList {
public:
	CAccessList() {};
	~CAccessList() {};

	void AddElement( IAccess* elem ) { listOfAccess.push_back(elem); };
	std::list<IAccess*>::iterator GetFirstElement() { return listOfAccess.begin(); };
private:
	std::list<IAccess*> listOfAccess;
};

//Соотв переменная в фрэйме
class InFrame: public IAccess {
public:
	InFrame( CTemp* _var ): var(_var) {};
	~InFrame() {};

	const IExpr* getVar() const;
private:
	CTemp* var;
};

//в регистре
class InReg: public IAccess {
public:
	InReg( CTemp* _var ): var(_var) {};
	~InReg() {};

	const IExpr* getVar() const;
private:
	CTemp* var;
};


//С Этим классов явно не все в порядке
//The class Frame holds information about formal parameters and local variables allocated in this frame.
//To make a new frame for a function f with k formal parameters, call newFrame(f)
//Не делаем интрефейс, так как реализация строго на 1 машине
class CFrame {
public:
	CFrame( CLabel _name ): name(_name) {};

	//static CFrame* NewFrame( CLabel name );

	//This returns an InFrame access with an offset from the frame pointer.
	IAccess* AllocLocal();
	const std::string& ToString() const { name.ToString(); };
	const CAccessList* GetFormals() const { return formals; };
	const CAccessList* GetLocals() const { return locals; };
	CTemp* GetStackPointer() { return stackPointer; };
	CTemp* GetFramePointer() { return framePointer; };

private:
	CLabel name;
	CAccessList* formals;
	CAccessList* locals;
	CTemp* stackPointer;
	CTemp* framePointer;
};

}