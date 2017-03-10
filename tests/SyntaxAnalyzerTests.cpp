#include "stdafx.h"
#include "../SyntaxAnalyzer/Runner.h"
#include "../SyntaxAnalyzer/Tables.h"


BOOST_AUTO_TEST_SUITE(NLG_EXAMPLE_TABLE)
	BOOST_AUTO_TEST_CASE(valid_sequence)
	{
		CRunner runner;
		runner.SetTable(table);

		BOOST_CHECK(runner.Run({ "PROG","id","var","id","begin","st","end" }));
		BOOST_CHECK(runner.Run({ "PROG","id","var","id",",", "id","begin","st","end" }));
		BOOST_CHECK(runner.Run({ "PROG","id","var","id",",", "id","begin","st", "st","end" }));
		BOOST_CHECK(runner.Run({ "PROG","id","var","id",",", "id","begin","st", "st", "st","end" }));
	}
	
	BOOST_AUTO_TEST_CASE(invalid_sequence_unexpected_token)
	{
		CRunner runner;
		runner.SetTable(table);

		BOOST_CHECK(!runner.Run({ "PROG","id","end" }));
		BOOST_CHECK(!runner.Run({ "PROG","id","var","id",",","id", ",","begin","st","end" }));
		BOOST_CHECK(!runner.Run({ "PROG","id","var","id",",", "id","begin","end" }));
	}

	BOOST_AUTO_TEST_CASE(invalid_sequence_unexpected_end_of_sequence)
	{
		CRunner runner;
		runner.SetTable(table);

		BOOST_CHECK(!runner.Run({ "PROG","id","var","id",",","id","begin","st" }));
		BOOST_CHECK(!runner.Run({ "PROG","id","var","id",",","id","begin","st", "st" }));
	}
	BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(LL1_TABLE)
BOOST_AUTO_TEST_CASE(valid_sequence)
{
	CRunner runner;
	runner.SetTable(LL1_table);

	BOOST_CHECK(runner.Run({ "MAIN","OPEN", "CONST","TYPENAME","ID","=","<","INT", ",", "INT", ">", "CLOSE" }));
	BOOST_CHECK(runner.Run({"MAIN", "OPEN", "CLOSE"}));
	BOOST_CHECK(runner.Run({"FUNCTIONID", "OPEN", "CLOSE", "MAIN"}));
	BOOST_CHECK(runner.Run({"OPEN", "CALL", "FUNCTION", "CLOSE"}));
}

/*BOOST_AUTO_TEST_CASE(invalid_sequence_unexpected_token)
{
	CRunner runner;
	runner.SetTable(table);

	BOOST_CHECK(!runner.Run({ "PROG","id","end" }));
	BOOST_CHECK(!runner.Run({ "PROG","id","var","id",",","id", ",","begin","st","end" }));
	BOOST_CHECK(!runner.Run({ "PROG","id","var","id",",", "id","begin","end" }));
}

BOOST_AUTO_TEST_CASE(invalid_sequence_unexpected_end_of_sequence)
{
	CRunner runner;
	runner.SetTable(table);

	BOOST_CHECK(!runner.Run({ "PROG","id","var","id",",","id","begin","st" }));
	BOOST_CHECK(!runner.Run({ "PROG","id","var","id",",","id","begin","st", "st" }));
}*/
BOOST_AUTO_TEST_SUITE_END()