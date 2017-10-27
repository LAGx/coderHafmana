#pragma once
#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;

template <class F, S >
class Pair{
	Pair
	F up; 
	S low;
}

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

	void createCodes();//TODO must

	string getMessageInCode();//TODO must

public:

	void showExtend();

	void generateFile(string fileName = "message.haf");//TODO must

	void createTableFromFile(string fileName = "message.txt");//TODO must

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