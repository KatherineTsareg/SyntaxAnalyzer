#include "stdafx.h"
#include "TableRowStruct.h"
#include "Runner.h"
#include "Tables.h"

using namespace std;

int main()
{

	CRunner runner;
	runner.SetTable(LL1_table);

	ifstream ifs;
	ifs.open("lexerLog.txt", ios::out | ios::trunc);
	ifs.close();
	system("java -jar s.jar input.txt");

	ifs.open("lexerLog.txt");
	vector<string> tokens;
	string currentToken;
	while (ifs >> currentToken)
	{
		tokens.push_back(currentToken);
	}

	ifs.close();

	runner.Run(tokens);
	
	return 0;
}
