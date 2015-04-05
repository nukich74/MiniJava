#include "BlockTracing.h"
#include <set>

namespace Canon {

	using namespace IRTree;

	Tracer::Tracer() 
	{
		doneLabel = new Temp::CLabel();
	}

	CStmtList* Tracer::Transform( const CStmtList* list ) {
		findBlocks( list );
		//��������� ���� � ������ done.
		blockSequence.push_back( CBlock() );
		int last = blockSequence.size() - 1;
		blockSequence[last].stms.push_back( new CLabel( doneLabel ) );
		//���������
		sortBlocks();
		CStmtList* result = 0;
		for( int i = resultVector.size() - 1; i >= 0; i-- ) {
			int len = blockSequence[resultVector[i]].stms.size();
			if( blockSequence[resultVector[i]].isInverted ) {
				const CCJump* cjump = dynamic_cast<const CCJump*>( blockSequence[resultVector[i]].stms[len - 1] );
				result = new CStmtList( new CCJump( CCJump::BuildNotCondition( cjump->relop ), 
					cjump->left, cjump->right, cjump->ifTrue, cjump->ifFalse ), result );
				len--;
			} else if( blockSequence[resultVector[i]].isNoConditions ) {
				const CCJump* cjump = dynamic_cast<const CCJump*>( blockSequence[resultVector[i]].stms[len - 1] );
				Temp::CLabel* tLabel = new Temp::CLabel();
				CCJump* newHead = new CCJump( cjump->relop, cjump->left, cjump->right, cjump->ifTrue, tLabel );
				result = new CStmtList( new CLabel( tLabel ), 
					new CStmtList( new CJump( cjump->ifFalse ), result ) );
				result = new CStmtList( newHead, result );
				len--;
			}
			for( int j = len - 1; j >= 0; j-- ) {
				result = new CStmtList( blockSequence[resultVector[i]].stms[j], result );
			}
		}
		return result;
	}

	void Tracer::findBlocks( const IRTree::CStmtList* list ) {
		for( const IRTree::CStmtList* curVertex = list; !curVertex;  ) {
			const CLabel* label = dynamic_cast<const CLabel*>( curVertex->GetCurrent() );
			blockSequence.push_back( CBlock() );
			int last = blockSequence.size() - 1;

			//����� �����, ���� ��� ���� ������� �� ��� ����, ���� ���, �� ������� ���������
			if( label ) {
				blockSequence[last].rootLabel = label->label->ToString();
				blockSequence[last].stms.push_back( curVertex->GetCurrent() );
			} else {
				std::string newLabelName( "RandomLabel" + std::to_string( std::rand() ) );
				blockSequence[last].stms.push_back( new CLabel( new Temp::CLabel( newLabelName ) ) );
				blockSequence[last].rootLabel = newLabelName;
			}
			//���� � ���������� stmt
			curVertex = static_cast<const CStmtList*>( list->GetNextStmts() );

			//������������ ��� ��������� stmts
			while( true ) {
				if( dynamic_cast<const CJump*>( curVertex->GetCurrent() ) ||  
					dynamic_cast<const CCJump*>( curVertex->GetCurrent() ) ) { 
					//���� jump ��� cjump, �� ������ ��������� �� � ����������, ��� ���� �������� ��������� � �� stmt � ������
					blockSequence[last].stms.push_back( curVertex->GetCurrent() );
					curVertex = static_cast<const CStmtList*>( curVertex->GetNextStmts() );
					break;					
				} else if( dynamic_cast<const CLabel*>( curVertex->GetCurrent() ) ) {
					//���� ��� �����-�� �����, �� ��������� � �������� ���� jump �� ��� � ����� �������
					//�� �� ������ curVertex, �.�. ����� ����� ����� ����������
					blockSequence[last].stms.push_back( new CJump( dynamic_cast<const CLabel*>( curVertex->GetCurrent() )->label ) ); 
					break;
				} else if( !curVertex->GetCurrent() ) {
					//���� ��� null, �� ������ ������ ��������, �� ��������� ���� �� ������������� jump ��� cjump � 
					//��������� jump �� ����� done
					blockSequence[last].stms.push_back( new CJump( doneLabel ) );
					curVertex = static_cast<const CStmtList*>( curVertex->GetNextStmts() );
					break;
				} else {
					//� ��������� ������� ��������� stmt � ��������� ����
					blockSequence[last].stms.push_back( curVertex->GetCurrent() );
					curVertex = static_cast<const CStmtList*>( curVertex->GetNextStmts() );
				}
			}
		}
	}

	void Tracer::dfs( int blockId, std::vector<int>& used ) {
		resultVector.push_back( blockId );
		used[blockId] = true;
		int lastStmtId = blockSequence[blockId].stms.size() - 1;
		const IStmt* lastCur = blockSequence[blockId].stms[lastStmtId];
		const CJump* jump = dynamic_cast<const CJump*>( lastCur );
		const CCJump* cjump = dynamic_cast<const CCJump*>( lastCur );
		if( jump ) {
			auto targetIter = labelMap.find( dynamic_cast<const Temp::CLabel*>( jump->label ) );
			if( targetIter == labelMap.end() ) {
				assert( false );
			}
			int targetId = targetIter->second;
			if( !used[targetId] ) {
				dfs( targetId, used );
			}
		} else if( cjump ) {
			auto falseIter = labelMap.find( dynamic_cast<const Temp::CLabel*>( cjump->ifTrue ) );
			auto trueIter = labelMap.find( dynamic_cast<const Temp::CLabel*>( cjump->ifFalse ) );
			if( falseIter == labelMap.end() || trueIter == labelMap.end() ) {
				assert( false );
			} else {
				if( !used[falseIter->second] ) {
					dfs( falseIter->second, used );
				} else if( !used[trueIter->second] ) {
					blockSequence[blockId].isInverted = true;
					dfs( trueIter->second, used );		
				} else {
					blockSequence[blockId].isNoConditions = true;
				}
			}
		} else {
			assert( false );
		}
	}

	void Tracer::sortBlocks() {
		std::vector< int > used( blockSequence.size(), 0 );

		for( int i = 0; i < blockSequence.size(); i++ ) {
			labelMap.insert( std::make_pair( dynamic_cast<const Temp::CLabel*>( blockSequence[i].stms[0] ), i ) );
		}

		for( int i = 0; i < blockSequence.size(); i++ ) {
			if( !used[i] ) {
				dfs( i, used );
			}		
		}
	}
}