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


int CWorkFlowGraph::Size() const
{
	return graph.Size();
}


const std::vector<int>& CWorkFlowGraph::GetInEdges( int nodeIndex ) const
{
	assert( nodeIndex < graph.Size() );
	return graph.GetNode( nodeIndex ).in;
}


const std::vector<int>& CWorkFlowGraph::GetOutEdges( int nodeIndex ) const
{
	assert( nodeIndex < graph.Size() );
	return graph.GetNode( nodeIndex ).out;
}


const CGraph& CWorkFlowGraph::GetGraph() const
{
	return graph;
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

// =====================================================================================================================


class CTopSort {
public:
	// Топологическая сортировка графа, начиная с вершины start
	// притом недостижимые вершины игнорируются
	static std::vector<int> topSort( const CGraph& graph, int start )
	{
		res.clear();
		marked.clear();
		marked.resize( graph.Size(), false );

		dfs( graph, start );

		std::reverse( res.begin(), res.end() );
		return res;
	}

	static std::vector<int> topSort(const CWorkFlowGraph& workflow, int start) 
	{
		return topSort( workflow.GetGraph(), start );
	}

private:
	// вектор в котором будет хранится результат
	static std::vector<int> res;
	// вектор с пометками, была ли посещена обходом данная вершина
	static std::vector<bool> marked;

	// обход в глубину с запоминанием порядка выхода (для топологической соритровки)
	static void dfs( const CGraph& graph, int nodeIndex )
	{
		marked[nodeIndex] = true;
		auto node = graph.GetNode( nodeIndex );

		for( auto neighbour : node.out ) {
			if( !marked[neighbour] ) {
				dfs( graph, neighbour );
			}
		}

		res.push_back( nodeIndex );
	}
};

std::vector<int> CTopSort::res = std::vector<int>();
std::vector<bool> CTopSort::marked = std::vector<bool>();

// =====================================================================================================================

CLiveInOutCalculator::CLiveInOutCalculator( const std::map<std::string, std::list<const IAsmInstr*>>& asmFunctions ) :
	workflow( asmFunctions ), liveIn( workflow.Size() ), liveOut( workflow.Size() )
{
	bool setsChanged = true;
	int mainFuncIndex = 0; // TODO: нормально найти начальную вершину
	std::vector<int> revTopsort = CTopSort::topSort( workflow, mainFuncIndex );
	buildCommands( asmFunctions );

	std::reverse( revTopsort.begin(), revTopsort.end() );
	while( setsChanged ) {
		setsChanged = false;
		for( auto nodeIndex : revTopsort ) {
			std::set<std::string> newLiveIn = liveOut[nodeIndex];

			// out[n] - def[n]
			auto currList = commands[nodeIndex]->Defines();
			while( currList != nullptr  &&  currList->GetCurrent() != nullptr ) {
				auto inSet = newLiveIn.find( currList->GetCurrent()->ToString() );
				if( inSet != newLiveIn.end() ) {
					newLiveIn.erase( inSet );
				}
				currList = currList->GetNext();
			}
				
			// in[n] = use[n] V ( out[n] - def[n] )
			currList = commands[nodeIndex]->UsedVars();
			while( currList != nullptr  &&  currList->GetCurrent() != nullptr ) {
				newLiveIn.insert( currList->GetCurrent()->ToString() );
				currList = currList->GetNext();
			}

			// out[n] = V in[s]		where s in succ[n]
			std::set<std::string> newLiveOut;
			for( auto succ : workflow.GetOutEdges( nodeIndex ) ) {
				for( auto var : liveIn[succ] ) {
					newLiveOut.insert( var );
				}
			}

			// если хоть у одной вершины изменилось множество live-in или live-out 
			// то необходимо провести еще итерацию алгоритма
			if( !theSame( newLiveIn, liveIn[nodeIndex] ) || !theSame( newLiveOut, liveOut[nodeIndex] ) ) {
				setsChanged = true;
				liveIn[nodeIndex] = newLiveIn;
				liveOut[nodeIndex] = newLiveOut;
			}
		}
	}
}


const std::set<std::string>& CLiveInOutCalculator::GetLiveIn( int nodeIndex ) const
{
	assert( nodeIndex < int( liveIn.size() ) );

	return liveIn[nodeIndex];
}


const std::set<std::string>& CLiveInOutCalculator::GetLiveOut( int nodeIndex ) const
{
	assert( nodeIndex < int( liveOut.size() ) );

	return liveOut[nodeIndex];
}


bool CLiveInOutCalculator::theSame( const std::set<std::string>& x, const std::set<std::string>& y ) const
{
	if( x.size() != y.size() ) {
		return false;
	}

	auto xIt = x.begin();
	auto yIt = y.begin();

	while( xIt != x.end() ) {
		if( *xIt != *yIt ) {
			return false;
		}
		++xIt;
		++yIt;
	}

	return true;
}


void CLiveInOutCalculator::buildCommands( const std::map<std::string, std::list<const IAsmInstr*>>& asmFunctions )
{
	commands.clear();
	commands.reserve( workflow.Size() );
	for( auto func : asmFunctions ) {
		for( auto cmd : func.second ) {
			commands.push_back( cmd );
		}
	}
}

} // namespace Assembler