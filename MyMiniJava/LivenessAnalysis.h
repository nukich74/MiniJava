// Автор: Федюнин Валерий
// Набор классов для анализа времени жизни переменных

#pragma once

#include "AssemblerInstr.h"

#include <set>
#include <string>
#include <vector>
#include <map>


namespace Assembler {
// Вершина графа
struct CNode {
	// входящие ребра
	std::vector<int> in;
	// исходящие ребра
	std::vector<int> out;
};


// Граф
class CGraph {
public:
	explicit CGraph( int size );
	
	// добавить ребро в граф из вершины from в вершину to
	void AddEdge( int from, int to );

	// Количество вершин в графе
	int Size() const;
	
	// получить вершину
	const CNode& GetNode( int index ) const;

protected:
	// узлы графа
	// вся информация о ребрах хранится внутри вершин
	std::vector<CNode> nodes;
};


// Граф потока управления
class CWorkFlowGraph : public CGraph {
public:
	// Конструктор
	// принимает на вход map где ключ - имя функции а значение - список ассемблерных команд
	explicit CWorkFlowGraph( const std::list<const IAsmInstr*>& asmFunction );

	// Список вершин имеющих ребро в данную
	const std::vector<int>& GetInEdges( int nodeIndex ) const;

	// Список вершин имеющих ребро из данной
	const std::vector<int>& GetOutEdges( int nodeIndex ) const;

private:
	// соответствие между метками и вершинами графа
	std::map<std::string, int> labels;

	void buildLabelMap( const std::list<const IAsmInstr*>& asmFunction );
	void addEdges( const std::list<const IAsmInstr*>& asmFunction );
};


// Граф подсчета live-in live-out (за подробностями см "Modern Compiler Implementation in Java 4 ed." глава 10
class CLiveInOutCalculator {
public:
	// Конструктор
	// принимает на вход map где ключ - имя функции а значение - список ассемблерных команд
	explicit CLiveInOutCalculator( const std::list<const IAsmInstr*>& asmFunction );

	// получить список live-in переменных для некоторой вершины/инструкции
	const std::set<std::string>& GetLiveIn( int nodeIndex ) const;

	// получить список live-out переменных для некоторой вершины/инструкции
	const std::set<std::string>& GetLiveOut( int nodeIndex ) const;

	// получить список объявляемых переменных для некоторой вершины/инструкции
	const std::set<std::string>& GetDefines( int nodeIndex ) const;

	const CWorkFlowGraph& GetGraph() const;

private:
	// граф потока управления
	CWorkFlowGraph workflow;

	// множества live-in и live-out переменных для каждой из вершин графа
	std::vector<std::set<std::string>> liveIn;
	std::vector<std::set<std::string>> liveOut;

	// множества defines
	std::vector<std::set<std::string>> defines;

	// вектор с ассемблерными командами
	std::vector<const IAsmInstr*> commands;

	// 

	bool theSame( const std::set<std::string>& x, const std::set<std::string>& y ) const;
	void buildCommands( const std::list<const IAsmInstr*>& asmFunction );
	void buildDefines( const std::list<const IAsmInstr*>& asmFunction );
};


// Граф взаимосвязанности переменных.
class CInterferenceGraph : public CGraph 
{
public:
	explicit CInterferenceGraph( const std::list<const IAsmInstr*>& asmFunction );

	// получить связанные переменные (компоненты связности)
	std::list<std::list<std::string>> GetInterferingVariables() const;

private:
	// список имен переменных
	std::vector<std::string> variables;

	// соответствие между именами переменных и вершинами графа
	std::map<std::string, int> nodeMap;

	// граф с подсчитанными live-in live-out
	CLiveInOutCalculator liveInOut;

	void addNode( const std::string& name );
};


// Распределение регистров
class CRegisterDistributor
{
public:
	CRegisterDistributor( const std::list<const IAsmInstr*>& asmFunction, const std::vector<std::string>& registerNames );
	
	// получить имя регистра, связанного с данной переменной
	const std::string& GetVariableRegister( const std::string& variable ) const;

private: 
	// список имен регистров
	std::vector<std::string> registerNames;

	// граф взаимосвязанности переменных
	CInterferenceGraph interfereceGraph;

	// соответствие между переменными и индексом в списке имен регистров
	std::map<std::string, int> registerMap;


	void buildInterferenceGraph();
};
} // namespace Assembler