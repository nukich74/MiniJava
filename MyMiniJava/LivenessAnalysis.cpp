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

CWorkFlowGraph::CWorkFlowGraph( const std::list<const IAsmInstr*>& asmFunction ) : CGraph( asmFunction.size() )
{
	buildLabelMap( asmFunction );
	addEdges( asmFunction );
}


const std::vector<int>& CWorkFlowGraph::GetInEdges( int nodeIndex ) const
{
	assert( nodeIndex < nodes.size() );
	return nodes[nodeIndex].in;
}


const std::vector<int>& CWorkFlowGraph::GetOutEdges( int nodeIndex ) const
{
	assert( nodeIndex < nodes.size() );
	return nodes[nodeIndex].out;
}


// составляет соответствие между метками и вершинами графа
void CWorkFlowGraph::buildLabelMap( const std::list<const IAsmInstr*>& asmFunction )
{
	int nodeIndex = 0;
	for( auto cmd : asmFunction ) {
		// Проверка, ялвяется ли интрукция меткой
		const CLabel* label = dynamic_cast<const CLabel*>( cmd );
		if( label != nullptr ) {
			// если инструкция является меткой то добавим ее в соответствие
			assert( label->Jumps() != nullptr );
			assert( label->Jumps()->GetCurrent() != nullptr );
			labels.insert( std::make_pair( label->Jumps()->GetCurrent()->ToString(), nodeIndex ) );
		}
		++nodeIndex;
	}
}


// добавляет ребра в граф
void CWorkFlowGraph::addEdges( const std::list<const IAsmInstr*>& asmFunction )
{
	int nodeIndex = 0;
	for( auto cmd : asmFunction ) {
		const COper* oper = dynamic_cast<const COper*>( cmd );
		if( oper != nullptr  &&  oper->Jumps() != nullptr  &&  oper->Jumps()->GetCurrent() != nullptr ) {
			AddEdge( nodeIndex, labels[oper->Jumps()->GetCurrent()->ToString()] );
		} else if( nodeIndex + 1 < Size() ) {
			AddEdge( nodeIndex, nodeIndex + 1 );
		}
		nodeIndex++;
	}
}

// =====================================================================================================================

namespace {
// не вижу смысла объявлять это в хедере т.к. это сугубо вспомогательная конструкция
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
} // anonymous namespace

// =====================================================================================================================

CLiveInOutCalculator::CLiveInOutCalculator( const std::list<const IAsmInstr*>& asmFunction ) :
	workflow( asmFunction ), liveIn( workflow.Size() ), liveOut( workflow.Size() )
{
	bool setsChanged = true;
	int mainFuncIndex = 0; // TODO: нормально найти начальную вершину
	std::vector<int> revTopsort = CTopSort::topSort( workflow, mainFuncIndex );
	buildCommands( asmFunction );
	buildDefines( asmFunction );

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


const std::set<std::string>& CLiveInOutCalculator::GetDefines( int nodeIndex ) const
{
	assert( nodeIndex < int( defines.size() ) );

	return defines[nodeIndex];
}


const CWorkFlowGraph& CLiveInOutCalculator::GetGraph() const
{
	return workflow;
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


void CLiveInOutCalculator::buildCommands( const std::list<const IAsmInstr*>& asmFunction ) 
{
	commands.clear();
	std::copy( asmFunction.begin(), asmFunction.end(), std::back_inserter( commands ) );
}


void CLiveInOutCalculator::buildDefines( const std::list<const IAsmInstr*>& asmFunction )
{
	defines.resize( asmFunction.size() );
	int cmdIndex = 0;
	for( auto cmd : asmFunction ) {
		auto def = cmd->Defines();
		while( def != nullptr  &&  def->GetCurrent() != nullptr ) {
			defines[cmdIndex].insert( def->GetCurrent()->ToString() );
			def = def->GetNext();
		}
		++cmdIndex;
	}
}

// =====================================================================================================================

CInterferenceGraph::CInterferenceGraph( const std::list<const IAsmInstr*>& asmFunction ) : CGraph( 0 ),
	liveInOut( asmFunction )
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
					int u = nodeMap[a];
					int v = nodeMap[b];
					AddEdge( u, v );
					AddEdge( v, u );
				}
			}
		} else {
			// для каждой move инструкции добавить ребра между всеми такими переменными a и b
			// где a - куда делается MOVE (c->a)
			// b из множества liveOut
			// TODO: разобраться, в каком порядке перечисляются аргументы команды MOVE в нашем случае
			std::string a = dynamic_cast< const CMove* >( cmd )->UsedVars()->GetCurrent()->ToString();
			for( auto b : liveInOut.GetLiveOut( cmdIndex ) ) {
				addNode( a );
				addNode( b );
				int u = nodeMap[a];
				int v = nodeMap[b];
				AddEdge( u, v );
				AddEdge( v, u );
			}
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
}

} // namespace Assembler