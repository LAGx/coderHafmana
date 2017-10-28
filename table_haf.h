#pragma once
#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;

template <class F, class S >
class Pair{
public:
	Pair(F _up, S _low): up(_up), low(_low)
		{}
	F up; 
	S low;
};

enum Binary{
	zero,
	one,
	none
};

class TableTest;

class Table{
friend TableTest;
private:

	struct Line{
		char symbol = 0;
		double probality = 0.0;
		vector<Binary> code;

		Line(char symbol = 0, double probality = 0.0);

		string getCode();
	};

	string text = "";

	vector<Line*> lines;

	void createProbalityTable(string wholeText);

	void createCodes();

	string getMessageInCode();

	string getAsciiTable();	/// [ascii code][code symbol]\n
				/// 00000000\n - end of table

public:

	void showExtend();

	void createTableFromFile(string input = "message.txt", string output = "message.haf");

	void createTableFromConsole();

	~Table();
};



struct TableTest:testing::Test{
	Table* table = nullptr;

	string test_str = "beeepba";// 3 - e, 2 -b, 1 - p, 1 - a//n=7
	
	bool isProbalityGood = false;
	void testCreateProbalityTable();

	bool isCodesGood = false;
	void testCreateCodes();

	bool isMessageInCodeGood = false;
	void testGetMessageInCode();


	TableTest();
	~TableTest();
};