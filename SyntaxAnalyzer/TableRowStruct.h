#pragma once
#include "stdafx.h"

struct TableRow
{
	std::set<std::string> start_set;
	bool shift;
	int transition;
	bool is_stack;
	bool is_error;
	bool is_end;
};

