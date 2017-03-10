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
	BOOST_AUTO_TEST_CASE(function_cases)
	{
		CRunner runner;
		runner.SetTable(LL1_table);
		//םמנלאכüםמ
		BOOST_CHECK(runner.Run({"MAIN", "OPEN", "CLOSE"}));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "NEWLINE", "NEWLINE", "CLOSE" }));
		//םוע "(" ןמסכו FUNCTIONID
		BOOST_CHECK(!runner.Run({"FUNCTIONID", "OPEN", "CLOSE", "MAIN"}));


		BOOST_CHECK(runner.Run({ "FUNCTIONID", "(", "TYPENAME", "ID",")", "OPEN", "PRINT", "(", "INT", "+", "INT", ")", "NEWLINE", "CLOSE", "MAIN", "OPEN", "CALL", "FUNCTIONID", "(", "INT", ",", "INT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "FUNCTIONID", "(", "TYPENAME", "ID",")", "OPEN", "PRINT", "(", "INT", "+", "INT", ")", "NEWLINE", "CLOSE",
			"FUNCTIONID", "(", "TYPENAME", "ID",")", "OPEN", "PRINT", "(", "INT", "+", "INT", ")", "NEWLINE", "CLOSE",
			"MAIN", "OPEN", "CALL", "FUNCTIONID", "(", "INT", ",", "INT", ")", "NEWLINE",
			"CALL", "FUNCTIONID", "(", "INT", ",", "INT", ")", "NEWLINE", "CLOSE" }));
	}

	BOOST_AUTO_TEST_CASE(valid_MAIN_cases)
	{
		CRunner runner;
		runner.SetTable(LL1_table);
	
		//םוע MAIN
		BOOST_CHECK(!runner.Run({ "OPEN", "CALL", "FUNCTION", "CLOSE" }));
		//םמנל
		BOOST_CHECK(runner.Run({ "MAIN","OPEN", "CONST","TYPENAME","ID","=","<","INT", ",", "INT", ">", "NEWLINE",  "CLOSE" }));
	}

	BOOST_AUTO_TEST_CASE(arith_cases)
	{
		CRunner runner;
		runner.SetTable(LL1_table);

		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "INT", "+", "INT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({"MAIN", "OPEN", "PRINT", "(" ,"INT", "*", "INT", ")", "NEWLINE", "CLOSE"}));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "FLOAT", "==", "INT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "INT", "-", "FLOAT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "FLOAT", "/", "FLOAT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "INT", "==", "INT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "INT", "!=", "INT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "INT", "%", "INT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "INT", "<", "INT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "INT", ">", "INT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "INT", "<=", "INT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "INT", ">=", "INT", ")", "NEWLINE", "CLOSE" }));

		//ÑËÎÆÍÛÅ
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "(", "(", "INT", "+", "INT", ")", "-", "(", "INT", "-", "INT", ")", ")", "/", "INT", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "(", "INT", "%", "INT", ")", "!=", "(", "INT", "+", "(", "INT", "-", "INT", ")", "*", "(", "INT", "/", "INT", ")", ")", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "PRINT", "(", "(", "(", "(", "INT", "*", "INT", ")", "-", "(", "INT", "%", "INT", ")", ")", "/", "INT", ")", "==", "(", "INT", "+", "INT", ")", ")", "NEWLINE", "CLOSE" }));
	

		BOOST_CHECK(!runner.Run({ "MAIN", "OPEN", "PRINT", "(", "(", "INT", "%", "INT", ")", "!=", "(", "INT", "+", "(", "(", "INT", "-", "INT", ")", "*", "(", "INT", "/", "INT", ")", ")", ")", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(!runner.Run({"MAIN", "OPEN", "PRINT", "(", "-", "INT", "+", "INT", ")", "NEWLINE", "CLOSE"}));

	}

	BOOST_AUTO_TEST_CASE(assignment_cases)
	{
		CRunner runner;
		runner.SetTable(LL1_table);

		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "TYPENAME", "ID", "=", "<", "INT", ",", "INT", ",", "INT", ",", "INT",">", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "TYPENAME", "ID", "=", "<", "FLOAT", ",", "FLOAT", ",", "FLOAT", ",", "FLOAT", ">", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "TYPENAME", "ID", "=", "<",">", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "TYPENAME", "ID", "=", "<",">", "NEWLINE", "TYPENAME", "ID", "=", "<","INT", ",", "INT",">", "NEWLINE", "LIST", "OF", "TYPENAME", "ID", "=", "ID","VAL", "NEWLINE", "CLOSE" }));
	}


	BOOST_AUTO_TEST_CASE(while_cases)
	{
		CRunner runner;
		runner.SetTable(LL1_table);

		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "WHILE", "(", "INT", "==", "INT", ")", "NEWLINE", "OPEN", "RETURN", "BOOL", "NEWLINE", "CLOSE", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "DO", "OPEN", "RETURN", "BOOL", "NEWLINE", "CLOSE", "WHILE", "(", "INT", "==", "INT", ")", "NEWLINE", "CLOSE" }));
	}


	BOOST_AUTO_TEST_CASE(if_else_cases)
	{
		CRunner runner;
		runner.SetTable(LL1_table);

		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "IF", "(" , "INT", "+", "FLOAT", ")", ">=", "INT", "NEWLINE", "OPEN", "CALL", "FUNCTIONID", "(", ")", "NEWLINE", "PRINT", "BOOL", "NEWLINE", "CLOSE", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "IF", "ID", "VAL", "==", "BOOL", "NEWLINE", "OPEN", "PRINT", "BOOL", "NEWLINE", "CLOSE", "ELIF", "INT", "==", "FLOAT", "OPEN", "PRINT", "INT", "NEWLINE", "CLOSE", "ELSE", "OPEN", "PRINT", "INT", "NEWLINE", "CLOSE", "NEWLINE", "CLOSE" }));
	}

	BOOST_AUTO_TEST_CASE(index_cases)
	{
		CRunner runner;
		runner.SetTable(LL1_table);
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "LIST", "OF", "TYPENAME", "ID", "=", "<", "FLOAT", ",", "FLOAT", ">", "NEWLINE", "TYPENAME", "ID", "=", "ID", "[", "INT", "]", "VAL", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "LIST", "OF", "TYPENAME", "ID", "=", "<", "INT", ",", "INT", ">", "NEWLINE", "ID", "[", "INT", "]", "VAL", "=", "INT", "NEWLINE", "CLOSE" }));
	
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "LIST", "OF", "LIST", "OF", "TYPENAME", "ID", "=", "<", "<", "INT", ">", ",", "<", "INT", ">", ">", "NEWLINE", "ID", "[", "INT", "]", "[", "INT", "]", "VAL", "=", "INT", "NEWLINE", "CLOSE" }));
		BOOST_CHECK(runner.Run({ "MAIN", "OPEN", "LIST", "OF", "LIST", "OF", "TYPENAME", "ID", "=", "<", "<", "INT", ">", ",", "<", "INT", ">", ">", "NEWLINE", "TYPENAME", "ID", "=", "ID", "[", "INT", "]", "[", "INT", "]", "VAL", "NEWLINE", "CLOSE" }));
	}

BOOST_AUTO_TEST_SUITE_END()

