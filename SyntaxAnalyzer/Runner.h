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

	size_t m_current_line = 1;
	size_t m_current_position = 1;

	void DoShift(TempStates & states, bool isNewLine);
	void PushInStack(TempStates & states);
	bool Transit(TempStates & states, size_t seq_length);
	bool RunImpl(std::vector<std::string> const& sequence);
};

