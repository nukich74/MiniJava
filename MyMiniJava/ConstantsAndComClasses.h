#pragma once

namespace IRTree {



enum BinOp {
	BO_Plus,
	BO_Minus,
	BO_Mult,
	BO_Div,
	BO_And,
	BO_Less
};

enum TEJump {
	CJ_EQ, 
	CJ_NE, 
	CJ_LT, 
	CJ_GT, 
	CJ_LE, 
	CJ_GE, 
	CJ_ULT,
	CJ_ULE,
	CJ_UGT,
	CJ_UGE
};

}
