//Borin Pavel

#include "Temp.h"
using namespace Temp;


int CTemp::infiniteSetCounter = 0;
int CLabel::infiniteSetLabelCounter = 0;

CTemp::CTemp()
{
	name = "tempName_" + std::to_string(infiniteSetCounter);
	infiniteSetCounter++;
}

CLabel::CLabel()
{
	name = "labelName_" + std::to_string(infiniteSetLabelCounter);
	infiniteSetLabelCounter++;
}