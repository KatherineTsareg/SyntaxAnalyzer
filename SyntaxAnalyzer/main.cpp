#include "stdafx.h"
#include "TableRowStruct.h"
#include "Runner.h"
#include "Tables.h"


int main()
{

	CRunner runner;
	runner.SetTable(LL1_table);
	runner.Run({ "MAIN", "OPEN", "PRINT", "(", "(", "(", "(", "INT", "*", "INT", ")", "-", "(", "INT", "%", "INT", ")", ")", "/", "INT", ")", "==", "(", "INT", "+", "INT", ")", ")", "NEWLINE", "CLOSE" });
	return 0;
}