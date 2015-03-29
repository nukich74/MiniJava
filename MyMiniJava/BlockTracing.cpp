#include "BlockTracing.h"
#include <set>

namespace Canon {

	using namespace IRTree;

	Tracer::Tracer() 
	{
		doneLabel = new Temp::CLabel();
	}

	void Tracer::findBlocks( const IRTree::CStmtList* list ) {
		for( const IRTree::CStmtList* curVertex = list; !curVertex;  ) {
			const CLabel* label = dynamic_cast<const CLabel*>( curVertex->GetCurrent() );
			blockSequence.push_back( CBlock() );
			int last = blockSequence.size() - 1;

			//берем метку, если она есть создаем по нее блок, если нет, то создаем рандомную
			if( label ) {
				blockSequence[last].rootLabel = label->label->ToString();
				blockSequence[last].stms.push_back( curVertex->GetCurrent() );
			} else {
				std::string newLabelName( "RandomLabel" + std::to_string( std::rand() ) );
				blockSequence[last].stms.push_back( new CLabel( new Temp::CLabel( newLabelName ) ) );
				blockSequence[last].rootLabel = newLabelName;
			}
			//идем к следующему stmt
			curVertex = static_cast<const CStmtList*>( list->GetNextStmts() );

			//обрабатываем все остальные stmts
			while( true ) {
				if( dynamic_cast<const CJump*>( curVertex->GetCurrent() ) ||  
					dynamic_cast<const CCJump*>( curVertex->GetCurrent() ) ) { 
					//если jump или cjump, то просто добавляем их и получается, что блок кончился переходим к сл stmt в списке
					blockSequence[last].stms.push_back( curVertex->GetCurrent() );
					curVertex = static_cast<const CStmtList*>( curVertex->GetNextStmts() );
					break;					
				} else if( dynamic_cast<const CLabel*>( curVertex->GetCurrent() ) ) {
					//если это какая-то метка, то добавляем в текуйщий блок jump на нее и снова выходим
					//но не меняем curVertex, т.к. новую метку нужно обработать
					blockSequence[last].stms.push_back( new CJump( dynamic_cast<const CLabel*>( curVertex->GetCurrent() )->label ) ); 
					break;
				} else if( !curVertex->GetCurrent() ) {
					//если это null, то значит список кончился, но последний блок не заканчивается jump или cjump и 
					//добавляем jump на метку done
					blockSequence[last].stms.push_back( new CJump( doneLabel ) );
					curVertex = static_cast<const CStmtList*>( curVertex->GetNextStmts() );
					break;
				} else {
					//в остальных случаях добавляем stmt в последний блок
					blockSequence[last].stms.push_back( curVertex->GetCurrent() );
					curVertex = static_cast<const CStmtList*>( curVertex->GetNextStmts() );
				}
			}
		}
	}

	void Tracer::sortBlocks() {
	}
}