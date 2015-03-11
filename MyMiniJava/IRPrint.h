//Stolbov Igor
#pragma once

#include <map>

namespace IRTree
{
	class CMove;
	class CExp;
	class CJump;
	class CCjump;
	class CSeq;
	class CConst;
	class CName;
	class CTemp;
	class CBinop;
	class CMem;
	class CCall;
	class CEseq;
	class CExpList;


	class CPrinter {
	public:
		CPrinter( );

		void Print( const CMove* node );
		void Print( const CExp* node );
		void Print( const CJump* node );
		void Print( const CCjump* node );
		void Print( const CSeq* node );
		void Print( const CConst* node );
		void Print( const CName* node );
		void Print( const CTemp* node );
		void Print( const CBinop* node );
		void Print( const CMem* node );
		void Print( const CCall* node );
		void Print( const CEseq* node );
		void Print( const CExpList* node );
	private:
		std::map<const void*, int> ids;
		std::map<const void*, int> parents;
		static int minId;
	};

}