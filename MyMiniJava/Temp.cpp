//Borin Pavel

#include "Temp.h"
using namespace Temp;


int CTemp::infiniteSetCounter = 0;
int CLabel::infiniteSetLabelCounter = 0;

CTemp::CTemp()
{
	name = std::to_string(infiniteSetCounter) + "tempName";
	infiniteSetCounter++;
}

CLabel::CLabel()
{
	name = std::to_string(infiniteSetLabelCounter) + "labelName";
	infiniteSetLabelCounter++;
}