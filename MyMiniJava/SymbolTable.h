#pragma once
#include "ClassInfo.h"
#include <map>
#include <utility>

namespace SymbolsTable {
	static std::map< std::string, CClassInfo* > table; //остальное избыточно.
}
