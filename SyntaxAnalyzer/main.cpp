#include "stdafx.h"
#include "TableRowStruct.h"
#include "Runner.h"


typedef std::vector<TableRow> Table;


int main()
{
	Table table = {
		{ { "PROG" },0,1,0,1,0 },
		{ { "PROG" },1,2,0,1,0 },
		{ { "id" },1,3,0,1,0 },
		{ { "var" },0,7,1,1,0 },
		{ { "begin" },1,5,0,1,0 },
		{ { "st" },0,18,1,1,0 },
		{ { "end" },1,-1,0,1,1 },
		{ { "var" },0,8,0,1,0 },
		{ { "var" },1,9,0,1,0 },
		{ { "id" },0,10,0,1,0 },
		{ { "id" },0,11,0,1,0 },
		{ { "id" },1,12,0,1,0 },
		{ { "begin","," },0,13,0,1,0 },
		{ { "," },0,15,0,0,0 },
		{ { "begin" },0,17,0,1,0 },
		{ { "," },1,16,0,1,0 },
		{ { "id" },0,10,0,1,0 },
		{ { "begin" },0,-1,0,1,0 },
		{ { "st" },0,19,0,1,0 },
		{ { "st" },1,20,0,1,0 },
		{ { "st","end" },0,21,0,1,0 },
		{ { "st" },0,23,0,0,0 },
		{ { "end" },0,24,0,1,0 },
		{ { "st","end" },0,18,0,1,0 },
		{ { "end" },0,-1,0,1,0 },
	};

	CRunner runner;
	runner.SetTable(table);
	/*runner.Run({ "PROG","id","var","id","begin","st","end" });
	runner.Run({ "PROG","id","var","id",",", "id","begin","st","end" });
	runner.Run({ "PROG","id","var","id",",", "id","begin","st", "st","end" });
	runner.Run({ "PROG","id","end" });
	runner.Run({ "PROG","id","var","id",",","id","begin","st" });
	runner.Run({ "PROG","id","var","id",",","id","begin","st", "st" });*/
	return 0;
}