#include "table_haf.h"
#include <exception>
#include <stdexcept>
#include <TextTable.h>
#include <map>
#include <algorithm>
#include <cmath>

#define EPSILON 0.01

using namespace std;

typedef unsigned int id;

string Table::Line::getCode(){
	string str_code = "";
	for(auto c : code){
		switch(c){
			case Binary::zero: str_code += '0';
				break;
			case Binary::one: str_code += '1';
				break;
		}
	}
	return str_code;
}

Table::Line::Line(char symbol, double probality){
	this->symbol = symbol;
	this->probality = probality;
}


void Table::createProbalityTable(string wholeText){
	text = wholeText;
	int length = text.length();

	vector<char> symbols;
	map<char, int> countOf;

	///fill symbols and probality
	for(char c : text){
		if(std::find(symbols.begin(), symbols.end(), c) != symbols.end()){//if exit this symbol
			countOf[c] = countOf[c]+1;
		}else{
			symbols.push_back(c);
			 countOf.insert( make_pair(c, 1));
		}
	}

	///create lines
	for(char s : symbols)
		lines.push_back(new Line(s, double(countOf[s])/length));
	

	///sort by probality
	sort(lines.begin(), lines.end(), [](const Line* a, const Line* b) {
		return a->probality > b->probality;
	});
}


void Table::createCodes(){
	//vector<double, vector<Line*>> lines_group;
	vector<Pair<double, vector<Line*>>> lines_group;
	for(auto c : lines){
		lines_group.push_back(new Pair<double, vector<Line*>>());
	}

}


string Table::getMessageInCode(){
	return "";
}

Table::~Table(){
	for(auto v : lines)
		delete v;
}

Table::Range::Range(int up,int down, int level){
	this->up = up;
	this->down = down;
	this->level = level;
}

void Table::Range::operator=(Range &rn){
	this->up = rn.up;
	this->down = rn.down;
	this->level = rn.level;
}

int  Table::Range::length(){
	return abs(up - down);
}

void Table::showExtend(){

	TextTable t( '-', '|', '+' );
		t.add( " symbol  " );
    		t.add( " probality  " );
    		t.add( " code    " );
    		t.add(" length of code  ");
    		t.add(" length of code * probality  ");
    		t.endOfRow(); 

	for(auto line : lines){
		t.add(string() + line->symbol);
		t.add(to_string(line->probality));
		t.add(line->getCode());
		t.add(to_string(line->getCode().size()));
		t.add(to_string(line->getCode().size() * line->probality));
		t.endOfRow(); 
	}
	t.setAlignment( 2, TextTable::Alignment::LEFT );
    	cout << t;
}

void Table::createTableFromConsole(){
	string input = "";
	cout << "input message: " << endl;
	while(input == "")
		cin >> input;
	text = input;
	cout << "-ok. start generating table." << endl;

	createProbalityTable(text);
	createCodes();
	cout << "-ok. end generating table." << endl;
}





//////////////////////////////////////////////////////////////////////////////////////
////////////////---------------------TEST-----------------------////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

TableTest::TableTest(){
	table = new Table();

	testCreateProbalityTable();
	testCreateCodes();
	testGetMessageInCode();

	table->showExtend();
}

void TableTest::testCreateProbalityTable( ){
	table->createProbalityTable("39wefnhwbfuowbfibwiufe45564465");

	for(auto line : table->lines){
		if(line->symbol == 'b')
			isProbalityGood = (2/7 - EPSILON <  line->probality && line->probality > 2/7+EPSILON  ) ?  true :  false;
		else if(line->symbol == 'e')
			isProbalityGood = (3/7 - EPSILON <  line->probality && line->probality > 3/7+EPSILON  ) ?  true :  false;
		else if(line->symbol == 'p')
			isProbalityGood = (1/7 - EPSILON <  line->probality && line->probality > 1/7+EPSILON  ) ?  true :  false;
		else if(line->symbol == 'a')
			isProbalityGood = (1/7 - EPSILON <  line->probality && line->probality > 1/7+EPSILON  ) ?  true :  false;
		//else
		//	throw runtime_error(("no such symbol in test" + line->symbol));

		if(isProbalityGood == false)
			break;
	}
}

void TableTest::testCreateCodes(){
	table->createCodes();

	for(auto line : table->lines){
		if(line->symbol == 'b')
			isCodesGood = (line->getCode() == "10") ?  true :  false;
		else if(line->symbol == 'e')
			isCodesGood = (line->getCode() == "0") ?  true :  false;
		else if(line->symbol == 'p')
			isCodesGood = (line->getCode() == "110" || line->getCode() == "111") ?  true :  false;
		else if(line->symbol == 'a')
			isCodesGood = (line->getCode() == "110" || line->getCode() == "111") ?  true :  false;
		//else
			//throw runtime_error(("no such symbol in test" + line->symbol));

		if(isCodesGood == false)
			break;
	}
}

void TableTest::testGetMessageInCode(){
	isMessageInCodeGood = (table->getMessageInCode() == "1000011110110" || table->getMessageInCode() == "1000011010111") ? true : false;
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
	EXPECT_EQ(true, isMessageInCodeGood);
}