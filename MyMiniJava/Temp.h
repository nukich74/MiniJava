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
	explicit CTemp( const std::string _name ) : name(_name) {};
	~CTemp() {};

	const std::string& ToString() const { return name; };
private:
	std::string name;
	static int infiniteSetCounter;
};

//Класс метка
class CLabel {
public:
	//returns a new CLabel from an infinite set of CLabels
	CLabel();
	explicit CLabel( const std::string _name ): name(_name) {};
	~CLabel() {};

	const std::string& ToString() const { return name; };
private:
	std::string name;
	static int infiniteSetLabelCounter;
};
/*
class CTempList {
public:
	CTempList() {};
	~CTempList() {};

	void AddElement( const CTemp& elem ) { listOfCTemps.push_back(elem); };
	std::list<CTemp>::iterator GetFirstElement() { return listOfCTemps.begin(); };
private:
	std::list<CTemp> listOfCTemps;
};


class CLabelList {
public:
	CLabelList() {};
	~CLabelList() {};

	void AddElement( const CLabel& elem ) { listOfCLabels.push_back(elem); };
	std::list<CLabel>::iterator GetFirstElement() { return listOfCLabels.begin(); };
private:
	std::list<CLabel> listOfCLabels;
};
*/
}