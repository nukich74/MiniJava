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


} // namespace Assembler