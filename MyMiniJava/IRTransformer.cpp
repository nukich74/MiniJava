#include "IRTransformer.h"

namespace Canon {

	using namespace IRTree;

	const IRTree::CExprList* CMoveCall::Kids() const
	{
		return src->Kids();
	}
	
	//нужно часть вершин мы не хотели менять, чтобы call работал корректно, теперь нужно все перестроить
	//и вернуть на свои места. Просто записываем результат во временную переменную
	const IRTree::IStmt* CMoveCall::Build( const IRTree::CExprList* kids ) const
	{
		return new CMove( dst, src->Build( kids ) );
	}

	const IRTree::CExprList* CExpCall::Kids() const
	{
		return call->Kids();
	}

	//все то же самое, как в CMoveCall, только для expr. 
	const IRTree::IStmt* CExpCall::Build( const IRTree::CExprList* kids ) const
	{
		return new CExp( call->Build( kids ) );
	}

	//nop он и в африке nop.
	CStmExpList* CCanon::nopNull = new CStmExpList( new CExp( new CConst( 0 ) ), 0 );

	//проверка stmt, является ли оно константой.
	bool CCanon::IsNop( const IStmt* a )
	{
		return dynamic_cast<const CExp*>( a ) != 0
			&& dynamic_cast<const CConst*>( ( dynamic_cast<const CExp*>( a ) )->exp ) != 0;
	}

	//если nop, то можно упростить дерево
	const IStmt* CCanon::SimplifySeq( const IStmt* a, const IStmt* b )
	{
		if( IsNop( a ) ) {
			return b;
		} else if( IsNop( b ) ) {
			return a;
		} else {
			return new CSeq( a, b );
		}
	}

	//проверка на коммутативность, чтобы можно было упрощать дерево
	bool CCanon::Commute( const IStmt* a, const IExpr* b )
	{
		return IsNop( a ) || dynamic_cast<const CName*>( b ) != 0 || dynamic_cast<const CConst*>( b ) != 0;
	}

	//просто рекурсивный обход cseq
	const IStmt* CCanon::DoStm( const CSeq* s )
	{
		return SimplifySeq( DoStm( s->left ), DoStm( s->right ) );
	}

	//рекурсивная обработка Move
	const IStmt* CCanon::DoStm( const CMove* s )
	{
		if( dynamic_cast<const CTemp*>( s->dst ) != 0 &&
			dynamic_cast<const CCall*>( s->src ) != 0 ) {
			//встретили конструкцию, которую нужно сохранить, оборачиваем ее в CMoveCall.
			return ReorderStm( new CMoveCall( dynamic_cast<const CTemp*>( s->dst ),
				dynamic_cast<const CCall*>( s->src ) ) );
		} else if( dynamic_cast<const CEseq*>( s->dst ) != 0 ) {
			//Move делается в eseq, тогда делаем сначала stm из eseq, потом записываем
			//exp из eseq в move, короче просто переподвесили вершины. 
			return DoStm( new CSeq( (dynamic_cast<const CEseq*>( s->dst) )->stm,
				new CMove( (dynamic_cast<const CEseq*>( s->dst ) )->expr, s->src ) ) );
		} else {
			return ReorderStm( s );
		}
	}

	//часть рекурсии для обработки CExp
	const IStmt* CCanon::DoStm( const CExp* s )
	{
		if( dynamic_cast<const CCall*>( s->exp ) != 0 ) {
			//оборачиваем вызов функции, результат будет же отброшен, т.к. CExp
			return ReorderStm( new CExpCall( dynamic_cast<const CCall*>( s->exp ) ) );
		} else {
			return ReorderStm( s );
		}
	}

	//часть рекурсии stmt, в первых случаях все корректно и просто рекурсивный вызов для детей
	//иначе проверяем stmt на осмысленность(CExp) или reorder
	const IStmt* CCanon::DoStm( const IStmt* s )
	{
		if( dynamic_cast<const CSeq*>( s ) != 0 ) {
			return DoStm( dynamic_cast<const CSeq*>( s ) );
		} else if( dynamic_cast<const CMove*>( s ) != 0 ) {
			return DoStm( dynamic_cast<const CMove*>( s ) );
		} else if( dynamic_cast<const CExp*>( s ) != 0 ) {
			if( IsNop( s ) ) {
				return 0;
			} else {
				return DoStm( dynamic_cast<const CExp*>( s ) );
			}
		} else {
			return ReorderStm( s );
		}
	}

	//восстанавливаем и упрощаем дерево со stmt в вершине
	const IStmt* CCanon::ReorderStm( const IStmt* s )
	{
		if( s == 0 ) {
			return 0;
		}
		const CStmExpList* x = Reorder( s->Kids() );
		return SimplifySeq( x->stm, s->Build( x->exprs ) );
	}

	//получает некоторый eseq и упрощает его, через проверку на некоммутативность
	//вроде как в простейшем примере из презентации
	const CEseq* CCanon::DoExp( const CEseq* e )
	{
		const IStmt* stmt = DoStm( e->stm );
		const CEseq* b = DoExp( e->expr );
		return new CEseq( SimplifySeq( stmt, b->stm ), b->expr );
	}
	
	//чтобы пользоваться простейшим упрощением, нужно уметь приводить exp к eseq
	const CEseq* CCanon::DoExp( const IExpr* e )
	{
		//если это eseq, то просто пытаемся что-то поменять рекурсивно.
		//иначе это умеет делать специальный reorder
		if( dynamic_cast<const CEseq*>( e ) != 0 ) {
			return DoExp( dynamic_cast<const CEseq*>( e ) );
		} else {
			return ReorderExp( e );
		}
	}

	//вернет корректный eseq, при этом вынеся вроде бы все stmt, которые надо сначала
	//посчитать, чтобы вычислять exp.
	const CEseq* CCanon::ReorderExp( const IExpr* e )
	{
		const CStmExpList* x = Reorder( e->Kids() );
		return new CEseq( x->stm, e->Build( x->exprs ) );
	}

	//принимает на вход список Tree::IExp’ов
	//возвращать два списка
	//Tree.Stm – все действия, которые должны быть проделаны до начала вычислений 
	//(или 𝐸𝑋𝑃(𝐶𝑂𝑁𝑆𝑇(0)), а так же некоммутирующие подвыражения.
	//Tree.ExpList – выражения без Tree.Stm’ов
	const CStmExpList* CCanon::Reorder( const CExprList* exprs )
	{
		if( exprs == 0 ) {
			return nopNull;
		} else {
			const IExpr* a = exprs->GetCurrent();
			if( dynamic_cast<const CCall*>( a ) != 0 ) {
				//встретили функцию, запишем результат в Temp и вернем его, обернув в Eseq
				Temp::CTemp* t = new Temp::CTemp();
				IExpr* e = new CEseq( new CMove( new CTemp( t ), a ), new CTemp( t ) );
				return Reorder( new CExprList( e, exprs->GetNextExprs() ) );
			} else {
				//иначе обрабатываем сам expr
				const CEseq* aa = DoExp( a );
				//и рекурсивно обрабатываем сам список
				const CStmExpList* bb = Reorder( static_cast< const CExprList* >( exprs->GetNextExprs() ) );
				//если коммутируют stmt и expr в вершинах, то упрощаем (simplify) и подвешиваем вершины
				if( Commute( bb->stm, aa->expr ) ) {
					return new CStmExpList( SimplifySeq( aa->stm, bb->stm ),
						new CExprList( aa->expr, bb->exprs ) );
				} else {
					//иначе делаем как в случае 3 презентации. коротко:
					//нужно сохранить результат некоммутирущий и подставить в соответствующие места
					Temp::CTemp* t = new Temp::CTemp();
					return new CStmExpList( SimplifySeq( aa->stm,
						SimplifySeq( new CMove( new CTemp( t ),
						aa->expr ),
						bb->stm ) ),
						new CExprList( new CTemp( t ), bb->exprs ) );
				}
			}
		}
	}
	//работа со списками
	const CStmtList* CCanon::Linear( const CSeq* s, const CStmtList* l )
	{
		return Linear( s->left, Linear( s->right, l ) );
	}
	//два seq переподвешиваем, чтобы получить все seq на одной ветке
	const CStmtList* CCanon::Linear( const IStmt* s, const CStmtList* l )
	{
		if( dynamic_cast<const CSeq*>( s ) != 0 ) {
			return Linear( dynamic_cast<const CSeq*>( s ), l );
		} else {
			return new CStmtList( s, l );
		}
	}
	//основная функция
	const CStmtList* CCanon::Linearize( const IStmt* s )
	{
		if( s == 0 ) {
			return 0;
		} else {
			return Linear( DoStm( s ), 0 );
		}
	}
}