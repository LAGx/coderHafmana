#pragma once
#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;

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

		Line(char symbol = 0, double probality = 0.0);//TODO must

		string getCode();//TODO must
	};

	string text = "";

	vector<Line> lines;

	void createProbalityTable(string wholeText);//TODO must

	void createCodes();//TODO must

	string getMessageCode();//TODO must

public:

	void showExtend();//TODO must

	void generateFile(string fileName = "message.haf");

	void createTableFromFile(string fileName = "message.txt");

	void createTableFromConsole();//TODO must
};



struct TableTest:testing::Test{
	Table* table = nullptr;

	string test_str = "beeepba";// 3 - e, 2 -b, 1 - p, 1 - a//n=7

	bool isProbalityGood = false;
	void testCreateProbalityTable();

	bool isCodesGood = false;
	void testCreateCodes();

	bool isMessageCodeGood = false;
	void testGetMessageCode();


	TableTest();
	~TableTest();
};