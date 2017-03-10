#include "stdafx.h"
#include "TableRowStruct.h"
#include "Runner.h"
#include "Tables.h"


int main()
{

	CRunner runner;
	runner.SetTable(LL1_table);

	runner.Run({ "FUNCTIONID", "(", "TYPENAME", "ID",")", "OPEN", "PRINT", "(", "INT", "+", "INT", ")", "NEWLINE", "CLOSE", 
				 "FUNCTIONID", "(", "TYPENAME", "ID",")", "OPEN", "PRINT", "(", "INT", "+", "INT", ")", "NEWLINE", "CLOSE", 
				 "MAIN", "OPEN", "CALL", "FUNCTIONID", "(", "INT", ",", "INT", ")", "NEWLINE", 
				"CALL", "FUNCTIONID", "(", "INT", ",", "INT", ")", "NEWLINE", "CLOSE" });
	return 0;
}