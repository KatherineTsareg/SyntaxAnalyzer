#pragma once
#include "TableRowStruct.h"

typedef std::vector<TableRow> Table;

struct TempStates
{
	size_t table_pos = 0; //нумерация строк таблицы начинается с 0
	size_t sequence_pos = 0;
	std::stack<int> stack;
};


class CRunner
{
public:
	CRunner();
	void SetTable(Table const& table);
	bool Run(std::vector<std::string> const& sequence);
	~CRunner();
private:
	Table m_table;

	void DoShift(TempStates & states);
	void PushInStack(TempStates & states);
	bool Transit(TempStates & states, size_t seq_length);
	bool RunImpl(std::vector<std::string> const& sequence);
};

