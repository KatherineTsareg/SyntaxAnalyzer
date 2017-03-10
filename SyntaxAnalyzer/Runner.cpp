#include "Runner.h"
#include <exception>

using namespace std;

string ConcatStringSet(const set<string>& stringSet)
{
	string result = "( ";
	for (auto &str : stringSet)
	{
		result += str + " ";
	}

	return result + ")";
}

CRunner::CRunner()
{
}

void CRunner::SetTable(Table const & table)
{
	m_table = table;
}

bool CRunner::RunImpl(std::vector<std::string> const & sequence)
{
	TempStates states;

	for (; states.sequence_pos < sequence.size();)
	{
		if (m_table[states.table_pos].start_set.count(sequence[states.sequence_pos]) == 1) //���� ������� �� ������� ������������� ������������� ���������
		{
			PushInStack(states);
			DoShift(states);
			if (Transit(states, sequence.size()))
			{
				return true;
			}
		}
		else if (m_table[states.table_pos].is_error)// ��������� ������
		{
			throw exception((string("Expected ") + ConcatStringSet(m_table[states.table_pos].start_set) + "at pos " + std::to_string(states.sequence_pos) + ".\nNOT " + sequence[states.sequence_pos]).c_str());
		}
		else //��������� �� ������ ���� � �������
		{
			++states.table_pos;
		}
	}
}

bool CRunner::Run(std::vector<std::string> const& sequence)
{
	try
	{
		RunImpl(sequence);
		cout << "Succses...\n";
		return true;
	}
	catch (const exception & ex)
	{
		cout << ex.what() << endl;
		return false;
	}
}


CRunner::~CRunner()
{
}

void CRunner::DoShift(TempStates & states)
{
	states.sequence_pos += (m_table[states.table_pos].shift ? 1 : 0);//����� �� SEQUENCE
}

void CRunner::PushInStack(TempStates & states)
{
	if (m_table[states.table_pos].is_stack)//����� � ����
	{
		states.stack.push(states.table_pos + 1);
	}
}


//������� ���������� FALSE, ����� ���������, � TRUE, ����� �������� ��������� ���������
bool CRunner::Transit(TempStates & states, size_t seq_length)
{
	if (states.sequence_pos < seq_length)
	{
		if (m_table[states.table_pos].transition >= 0)
		{
			states.table_pos = m_table[states.table_pos].transition;
			return false;
		}

		//���� �������� ��� � ���� �� ������
		if (states.stack.size() > 0)
		{
			states.table_pos = states.stack.top();
			states.stack.pop();
			return false;
		}

		//���� ���� ������ � �������� ��� � ������� �� �����������
		if (!m_table[states.table_pos].is_error)
		{
			++states.table_pos;
			return false;
		}
		throw exception((string("ERROR in ") + std::to_string(states.table_pos)).c_str());
	}

	//������� �����������
	if (m_table[states.table_pos].is_end)
	{
		return true;
	}
	throw exception("DOES NOT EXPECTED END OF SEQUENCE");
}


