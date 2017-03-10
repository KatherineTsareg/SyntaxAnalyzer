#include "stdafx.h"
#include "TableRowStruct.h"
#include "Runner.h"
#include "Tables.h"


int main()
{

	CRunner runner;
	runner.SetTable(LL1_table);
	runner.Run({ "FUNCTIONID", "OPEN", "CLOSE", "MAIN" });
	return 0;
}