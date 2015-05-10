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

private:
	// узлы графа
	// вся информация о ребрах хранится внутри вершин
	std::vector<CNode> nodes;
};


// Граф потока управления
class CWorkFlowGraph {
public:
	// Конструктор
	// принимает на вход map где ключ - имя функции а значение - список ассемблерных команд
	explicit CWorkFlowGraph( const std::map<std::string, std::list<const IAsmInstr*>>& asmFunctions );

	// Количество вершин в графе
	int Size() const;

	// Список вершин имеющих ребро в данную
	const std::vector<int>& GetInEdges( int nodeIndex ) const;

	// Список вершин имеющих ребро из данной
	const std::vector<int>& GetOutEdges( int nodeIndex ) const;

	const CGraph& GetGraph() const;

private:
	// граф
	CGraph graph;

	// соответствие между метками и вершинами графа
	std::map<std::string, int> labels;

	// соответствие между функциями и вершинами графа
	std::map<std::string, int> functions;

	void buildNodes( const std::map<std::string, std::list<const IAsmInstr*>>& asmFunctions );
	void buildMaps( const std::map<std::string, std::list<const IAsmInstr*>>& asmFunctions );
	void addEdges();
};


// Граф подсчета live-in live-out (за подробностями см "Modern Compiler Implementation in Java 4 ed." глава 10
class CLiveInOutCalculator {
public:
	// Конструктор
	// принимает на вход map где ключ - имя функции а значение - список ассемблерных команд
	explicit CLiveInOutCalculator( const std::map<std::string, std::list<const IAsmInstr*>>& asmFunctions );

	// получить список live-in переменных
	const std::set<std::string>& GetLiveIn( int nodeIndex ) const;

	// получить список live-out переменных
	const std::set<std::string>& GetLiveOut( int nodeIndex ) const;

private:
	// граф потока управления
	CWorkFlowGraph workflow;

	// множества live-in и live-out переменных для каждой из вершин графа
	std::vector<std::set<std::string>> liveIn;
	std::vector<std::set<std::string>> liveOut;

	// вектор с ассемблерными командами
	std::vector<const IAsmInstr*> commands;

	bool theSame( const std::set<std::string>& x, const std::set<std::string>& y ) const;
	void buildCommands( const std::map<std::string, std::list<const IAsmInstr*>>& asmFunctions  );
};
} // namespace Assembler