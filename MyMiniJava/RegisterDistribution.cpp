// Автор: Федюнин Валерий
// Набор классов для распределения регистров по переменным

#include "RegisterDistribution.h"

#include <assert.h>


namespace Assembler {

CInterferenceGraph::CInterferenceGraph( const std::list<const IAsmInstr*>& asmFunction,
	const std::vector<const std::string>& registers ) : liveInOut( asmFunction ), registers( registers )
{
	int cmdIndex = 0;
	for( auto cmd : asmFunction ) {
		if( dynamic_cast<const CMove*>( cmd ) == nullptr ) {
			// для каждой не move инструкции добавить ребра между всеми такими переменными a и b
			// где a принадлежит определяемым в данной инструкции переменным
			// b - из множества liveOut
			for( auto a : liveInOut.GetDefines( cmdIndex ) ) {
				for( auto b : liveInOut.GetLiveOut( cmdIndex ) ) {
					addNode( a );
					addNode( b );
					addEdge( a, b );
				}
			}
		} else {
			// для каждой move инструкции добавить ребра между всеми такими переменными a и b
			// где a - куда делается MOVE (c->a)
			// b из множества liveOut
			std::string a = dynamic_cast< const CMove* >( cmd )->Destination()->GetCurrent()->ToString();
			for( auto b : liveInOut.GetLiveOut( cmdIndex ) ) {
				addNode( a );
				addNode( b );
				addEdge( a, b );
			}
			std::string b = dynamic_cast< const CMove* >( cmd )->Source()->GetCurrent()->ToString();
			addNode( b );
			addMoveEdge( a, b );
		}
	}
}


// добавляет вершину в граф, если таковой еще нет
void CInterferenceGraph::addNode( const std::string& name )
{
	if( nodeMap.find( name ) != nodeMap.end() ) {
		return;
	}
	nodeMap.insert( std::make_pair( name, nodes.size() ) );
	nodes.emplace_back();
	for( auto nodeEdges : edges ) {
		nodeEdges.push_back( ET_NoEdge );
	}
	edges.emplace_back( nodes.size(), ET_NoEdge );
}


// добавляет move-ребро в граф
void CInterferenceGraph::addMoveEdge( const std::string& from, const std::string& to )
{
	int u = nodeMap[from];
	int v = nodeMap[to];
	// MOVE-ребро добавляется только тогда, когда не было никакого ребра между этими вершинами
	if( edges[u][v] == ET_NoEdge ) {
		edges[u][v] = ET_MoveEdge;
		edges[v][u] = ET_MoveEdge;
	}
}


// добавляет простую зависимость в граф
void CInterferenceGraph::addEdge( const std::string& from, const std::string& to )
{
	int u = nodeMap[from];
	int v = nodeMap[to];
	edges[u][v] = ET_Edge;
	edges[v][u] = ET_Edge;
}


// раскрасить граф
void CInterferenceGraph::paint()
{
	addRegisterColors();
	while( hasNonColoredNonStackedNodes() ) {
		int node = getColorableNode();
		if( node == -1 ) {
			node = getMaxInterferingNode();
			uncoloredNodes.push_back( node );
		}
		pulledNodes.push( node );
		nodes[node].InStack = true;
	}
	// пока что считаем, что у нас по-любому хватит регистров
	assert( uncoloredNodes.empty() );
	while( !pulledNodes.empty() ) {
		int currNode = pulledNodes.top();
		pulledNodes.pop();
		std::vector<char> usedColors( registers.size(), 0 );
		for( int i = 0; i < nodes.size(); ++i ) {
			if( edges[currNode][i] != ET_NoEdge  &&  nodes[i].Color != -1 ) {
				usedColors[nodes[i].Color] = 1;
			}
		}
		for( int i = 0; i < usedColors.size(); ++i ) {
			if( !usedColors[i] ) {
				nodes[currNode].Color = i;
				break;
			}
		}
	}
}


// красит вершины, соответствующие регистрам
void CInterferenceGraph::addRegisterColors()
{
	for( int i = 0; i < registers.size(); ++i ) {
		auto regNode = nodeMap.find( registers[i] );
		if( regNode != nodeMap.end() ) {
			// если в графе есть вершина, соответствующая этому регистру, 
			// то она должна быть покрашена до запуска основного алгоритма покраски
			nodes[regNode->second].Color = i;
		}
	}
}


// остались ли в графе вершины, которые не положены в стек
// и не имеют цвет
bool CInterferenceGraph::hasNonColoredNonStackedNodes() const
{
	for( int i = 0; i < nodes.size(); ++i ) {
		if( nodes[i].Color == -1 && !nodes[i].InStack ) {
			return true;
		}
	}
	return false;
}


// номер вершины, которую в данный момент возможно покрасить
// или -1 если такой вершины в графе нет
int CInterferenceGraph::getColorableNode() const
{
	int colorsNum = registers.size();

	for( int i = 0; i < edges.size(); ++i ) {
		if( getNeighbourNum( i ) < colorsNum ) {
			return i;
		}
	}

	return -1;
}


// номер вершины с наибольшим кол-вом соседей
int CInterferenceGraph::getMaxInterferingNode() const
{
	int maxNeighbour = -1;
	int nodeIndex = -1;
	for( int i = 0; i < nodes.size(); ++i ) {
		int currNeighbour = getNeighbourNum( i );
		if( currNeighbour > maxNeighbour ) {
			maxNeighbour = currNeighbour;
			nodeIndex = i;
		}
	}
	return nodeIndex;
}


// кол-во соседей у текущей вершины
// не учитывает вершины, расположенные на стеке
int CInterferenceGraph::getNeighbourNum( int nodeIndex ) const
{
	int neighbours = 0;
	for( int i = 0; i < edges[nodeIndex].size(); ++i ) {
		if( edges[nodeIndex][i] != ET_NoEdge  &&  !nodes[i].InStack ) {
			neighbours++;
		}
	}
	return neighbours;
}

//======================================================================================================================



} // namespace Assembler