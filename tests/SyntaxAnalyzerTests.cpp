#include "stdafx.h"
#include "../SyntaxAnalyzer/Runner.h"

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

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	CRunner runner;
	runner.SetTable(table);

	BOOST_CHECK(runner.Run({ "PROG","id","var","id","begin","st","end" }));
	BOOST_CHECK(runner.Run({ "PROG","id","var","id",",", "id","begin","st","end" }));
	BOOST_CHECK(runner.Run({ "PROG","id","var","id",",", "id","begin","st", "st","end" }));

	BOOST_CHECK(!runner.Run({ "PROG","id","end" }));
	BOOST_CHECK(!runner.Run({ "PROG","id","end" }));
	/*BOOST_CHECK(!runner.Run({ "PROG","id","var","id",",","id","begin","st" }));
	BOOST_CHECK(!runner.Run({ "PROG","id","var","id",",","id","begin","st", "st" }));*/
}