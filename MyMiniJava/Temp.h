//Borin Pavel
//CTemp, CLabel classes

#pragma once
#include <string>
#include <list>
#include <vector>


namespace Temp
{

//класс временной переменной
class CTemp {
public:
	//returns a new CTemporary from an infinite set of CTemps
	CTemp();
	CTemp( const CTemp& temp ) : name( temp.ToString() ) {};
	explicit CTemp( const std::string& _name ) : name(_name) {};
	~CTemp() {};

	const std::string ToString() const { return name; };
private:
	std::string name;
	static int infiniteSetCounter;
};

//Класс метка
class CLabel {
public:
	//returns a new CLabel from an infinite set of CLabels
	CLabel();
	explicit CLabel( const std::string& _name ): name(_name) {};
	~CLabel() {};

	const std::string ToString() const { return name; };
private:
	std::string name;
	static int infiniteSetLabelCounter;
};

class CTempMap {
public:
	std::string tempMap( Temp::CTemp* tmp ) { return tmp->ToString(); }
};

class CTempList {
public:
	CTempList( const CTemp* _temp, const CTempList* _tmpList ) :
		temp(_temp), tmpList(_tmpList) {};

	const CTemp* GetCurrent() const { return temp; };
	const CTempList* GetNext() const { return tmpList; };
private:
	const CTemp* temp;
	const CTempList* tmpList;
};

class CLabelList {
public:
	CLabelList( const CLabel* _lbl, const CLabelList* _lblList ) :
		label(_lbl), labelList(_lblList) {};

	const CLabel* GetCurrent() const { return label; };
	const CLabelList* GetNext() const { return labelList; };
private:
	const CLabel* label;
	const CLabelList* labelList;
};

}