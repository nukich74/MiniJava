// Автор: Федюнин Валерий
// Набор классов для анализа времени жизни переменных

#include "LivenessAnalysis.h"

#include <assert.h>


namespace Assembler {

// =====================================================================================================================

CGraph::CGraph( int size ) : nodes( size ) {}


void CGraph::AddEdge( int from, int to )
{
	assert( from < int( nodes.size() ) );
	assert( to < int( nodes.size() ) );

	nodes[from].out.push_back( to );
	nodes[to].in.push_back( from );
}


int CGraph::Size() const
{
	return nodes.size();
}


const CNode& CGraph::GetNode( int index ) const
{
	return nodes[index];
}

// =====================================================================================================================

CWorkFlowGraph::CWorkFlowGraph( const std::map<std::string, std::list<const IAsmInstr*>>& asmFunctions ) : graph( 0 )
{
	buildNodes( asmFunctions );
	buildMaps( asmFunctions );
}


// строит граф из необходимого количества без ребер
void CWorkFlowGraph::buildNodes( const std::map<std::string, std::list<const IAsmInstr*>>& asmFunctions )
{
	int graphSize = 0;
	for( auto func : asmFunctions ) {
		graphSize += func.second.size();
	}
	graph = CGraph( graphSize );
}


// строит соответствия, необходимые для построения графа
void CWorkFlowGraph::buildMaps( const std::map<std::string, std::list<const IAsmInstr*>>& asmFunctions )
{
	int nodeIndex = 0;
	for( auto func : asmFunctions ) {
		functions.insert( std::make_pair( func.first, nodeIndex ) );
		for( auto cmd : func.second ) {
			// TODO: добавить какую-либо нормальную проверку того, что инструкция является меткой
			std::string command = cmd->FormatInstr( Temp::CTempMap() );
			if( command.length() > 1 && command.back() == ':' ) {
				// если инструкция является меткой то добавим ее в соответствие
				labels.insert( std::make_pair( command.substr( 0, command.length() - 1 ), nodeIndex ) );
			}
			++nodeIndex;
		}
	}
}


// строит ребра в графе
void CWorkFlowGraph::addEdges()
{
	// TODO:
	// для начала необходимо разобраться, как можно выведать из инструкции ее тип
}

}