// Borin Pavel
// Assembler Instruction classes

#include <string>
#include <Temp.h>

namespace Assembler {

class IAsmInstr { 
public:
	virtual const Temp::CTempList* UsedVars() const = 0;
	virtual const Temp::CTempList* Defines() const = 0;
	virtual const Temp::CLabelList* Jumps() const = 0;
	virtual const Temp::CTempList* Destination() const = 0;
	virtual const Temp::CTempList* Source() const = 0;
	virtual std::string FormatInstr( Temp::CTempMap tmpMap ) const = 0;
}; 

class COper : public IAsmInstr {
public:
	COper( const std::string& _asmCmd, const Temp::CTempList* _dst, 
		const Temp::CTempList* _src, const Temp::CLabelList* _lblList = 0 ) :
		asmCmd( _asmCmd ), dst( _dst ), src( _src ), lblList( _lblList ) {};
		
	const Temp::CTempList* UsedVars() const { return src; }
	const Temp::CTempList* Defines() const { return dst; }
	const Temp::CLabelList* Jumps() const { return lblList; }
	const Temp::CTempList* Destination() const { return 0; }
	const Temp::CTempList* Source() const { return 0; }
	std::string FormatInstr( Temp::CTempMap tmpMap ) const { return ""; };
		
protected:
	const std::string asmCmd;
	const Temp::CTempList* dst;
	const Temp::CTempList* src;
	const Temp::CLabelList* lblList;
};

class CMove : public COper {
public:
	CMove( const std::string& _asmCmd, const Temp::CTempList* _dst, 
		const Temp::CTempList* _src, const Temp::CLabelList* _lblList = 0 ) :
		COper( _asmCmd, _dst, _src, _lblList ) {};
	const Temp::CTempList* Destination() const { return dst; }
	const Temp::CTempList* Source() const { return src; }
};

class CLabel : public IAsmInstr {
public:
	CLabel( const Temp::CLabelList* _lblList ) :
		lblList( _lblList ) {};

	const Temp::CTempList* UsedVars() const { return 0; }
	const Temp::CTempList* Defines() const { return 0; }
	const Temp::CLabelList* Jumps() const { return lblList; }
	const Temp::CTempList* Destination() const { return 0; }
	const Temp::CTempList* Source() const { return 0; }
	std::string FormatInstr( Temp::CTempMap tmpMap ) const { return ""; };
private:
	const Temp::CLabelList* lblList;
};

};