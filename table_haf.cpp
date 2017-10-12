#include "table_haf.h"
#include <exception>
#include <stdexcept>

#define EPSILON 0.00001

using namespace std;


string Table::Line::getCode(){

}

void Table::createProbalityTable(string wholeText){

}

void Table::createCodes(){

}

string Table::getMessageCode(){
	return "";
}

void Table::showExtend(){

}

void Table::createTableFromConsole(){
	string input = "";
	cout << "input message: " << endl;
	while(input == "")
		cin >> input;
	text = input;
	cout << "ok. start generating table." << endl;

	createProbalityTable(text);
	createCodes();
	cout << "ok. table generating end." << endl;
}



//////////////////////////////////////////////////////////////////////////////////////
////////////////---------------------TEST-----------------------////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

TableTest::TableTest(){
	table = new Table();

	testCreateProbalityTable();
	testCreateCodes();
	testGetMessageCode();

}

void TableTest::testCreateProbalityTable( ){
	table->createProbalityTable(test_str);

	for(auto line : table->lines){
		if(line.symbol == 'b')
			isProbalityGood = (2/7 - EPSILON >  line.probality && line.probality < 2/7+EPSILON  ) ?  true :  false;
		else if(line.symbol == 'e')
			isProbalityGood = (3/7 - EPSILON >  line.probality && line.probality < 3/7+EPSILON  ) ?  true :  false;
		else if(line.symbol == 'p')
			isProbalityGood = (1/7 - EPSILON >  line.probality && line.probality < 1/7+EPSILON  ) ?  true :  false;
		else if(line.symbol == 'a')
			isProbalityGood = (1/7 - EPSILON >  line.probality && line.probality < 1/7+EPSILON  ) ?  true :  false;
		else
			throw runtime_error(("no such symbol in test" + line.symbol));

		if(isProbalityGood == false)
			break;
	}
}

void TableTest::testCreateCodes(){
	table->createCodes();

	for(auto line : table->lines){
		if(line.symbol == 'b')
			isCodesGood = (line.getCode() == "10") ?  true :  false;
		else if(line.symbol == 'e')
			isCodesGood = (line.getCode() == "0") ?  true :  false;
		else if(line.symbol == 'p')
			isCodesGood = (line.getCode() == "110" || line.getCode() == "111") ?  true :  false;
		else if(line.symbol == 'a')
			isCodesGood = (line.getCode() == "110" || line.getCode() == "111") ?  true :  false;
		else
			throw runtime_error(("no such symbol in test" + line.symbol));

		if(isCodesGood == false)
			break;
	}
}

void TableTest::testGetMessageCode(){
	isMessageCodeGood = (table->getMessageCode() == "1000011110110" || table->getMessageCode() == "1000011010111") ? true : false;
}

TableTest::~TableTest(){
	delete table;
}

TEST_F(TableTest, createProbalityTable_Test){
	EXPECT_EQ(true, isProbalityGood);
}

TEST_F(TableTest, createCodes_Test){
	EXPECT_EQ(true, isCodesGood);
}

TEST_F(TableTest, messageCode_Test){
	EXPECT_EQ(true, isMessageCodeGood);
}