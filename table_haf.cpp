#include "table_haf.h"
#include <exception>
#include <stdexcept>
#include <TextTable.h>
#include <map>
#include <algorithm>
#include <cmath>
#include <memory>
#include <map>
#include <bitset>
#include <fstream>
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
	vector<shared_ptr<Pair<double, vector<Line*>>>> lines_group;

	for(auto v: lines)
		lines_group.push_back(shared_ptr<Pair<double, vector<Line*>>>
			(new Pair<double, vector<Line*>>(v->probality, vector<Line*>(1,v))));

	auto sort_by_probality = [](vector<shared_ptr<Pair<double, vector<Line*>>>>& lines_group){
		sort(lines_group.begin(), lines_group.end(), [](
			const shared_ptr<Pair<double, vector<Line*>>>& a,
			const shared_ptr<Pair<double, vector<Line*>>>& b
			){
				return a->up > b->up;   //?
		});
	};

	sort_by_probality(lines_group);


	while(lines_group.size()-1){
		for(auto line: (*(lines_group.end()-1))->low)
			line->code.push_back(Binary::one);
		for(auto line: (*(lines_group.end()-2))->low)
			line->code.push_back(Binary::zero);

		vector<Line*> mult_vec;
		mult_vec.insert(mult_vec.end(), ((*(lines_group.end()-1))->low).begin(),  ((*(lines_group.end()-1))->low).end());
		mult_vec.insert(mult_vec.end(), ((*(lines_group.end()-2))->low).begin(),  ((*(lines_group.end()-2))->low).end());

		lines_group.push_back(shared_ptr<Pair<double, vector<Line*>>>
			(new Pair<double, vector<Line*>>((*(lines_group.end()-1))->up + (*(lines_group.end()-2))->up, 
				vector<Line*>(mult_vec))));

		lines_group.erase(lines_group.end()-2);
		lines_group.erase(lines_group.end()-2);

		sort_by_probality(lines_group);

///////////////////////////////////////////////////////////////////////// show details
/*
		TextTable t( '-', '|', '+' );
		t.add( " probality  " );
    		t.add( " vectors " );
    		t.endOfRow(); 

		for(auto line : lines_group){
			t.add(to_string(line->up));

			string str = "";
			for(auto s: line->low)
				str += (string() + s->symbol + " (" + s->getCode() + "), ");
			
			t.add(str);
			t.endOfRow(); 
		}

		t.setAlignment( 2, TextTable::Alignment::LEFT );
    		cout << t;
*/
	}	

	for(auto v: lines)
		reverse(v->code.begin(), v->code.end());

}


string Table::getMessageInCode(){
	string message = "";
	//char -> code
	map<char, string> coding;

	//create coding 
	for(auto line : lines)
		coding[line->symbol] =  line->getCode();
	
	for(char c : text)
		message += coding[c];

	return message;
}

string Table::getAsciiTable(){
	string table = "";
 
	for(auto line : lines)
		table += bitset<8>(line->symbol).to_string() + line->getCode() + "\n";

	return table + "00000000";
}


Table::~Table(){
	for(auto v : lines)
		delete v;
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
	cout << getAsciiTable() << getMessageInCode() << endl;
}

void Table::createTableFromFile(string input, string output){
	ifstream file_i(input);
 
   	if (!file_i.is_open()) 
		cout << "no such file: " << input << endl;
    	
    	string line;
    	while(getline(file_i, line))
    		text += line;
    	
    	file_i.close();

    	std::ofstream file_o(output, std::ios::trunc);
	
	createProbalityTable(text);
	createCodes();

	file_o << getAsciiTable() << endl;
	file_o << getMessageInCode() << endl;

	file_o.close();
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
	table->createProbalityTable(test_str);

	for(auto line : table->lines){
		if(line->symbol == 'b')
			isProbalityGood = (2/7 - EPSILON <  line->probality && line->probality > 2/7+EPSILON  ) ?  true :  false;
		else if(line->symbol == 'e')
			isProbalityGood = (3/7 - EPSILON <  line->probality && line->probality > 3/7+EPSILON  ) ?  true :  false;
		else if(line->symbol == 'p')
			isProbalityGood = (1/7 - EPSILON <  line->probality && line->probality > 1/7+EPSILON  ) ?  true :  false;
		else if(line->symbol == 'a')
			isProbalityGood = (1/7 - EPSILON <  line->probality && line->probality > 1/7+EPSILON  ) ?  true :  false;

		if(isProbalityGood == false)
			break;
	}
}

void TableTest::testCreateCodes(){
	table->createCodes();

	for(auto line : table->lines){
		if(line->symbol == 'b')
			isCodesGood = (line->getCode() == "10" || line->getCode() == "00") ?  true :  false;
		else if(line->symbol == 'e')
			isCodesGood = (line->getCode() == "0" || line->getCode() == "1") ?  true :  false;
		else if(line->symbol == 'p')
			isCodesGood = (line->getCode() == "110" || line->getCode() == "111" || line->getCode() == "010") ?  true :  false;
		else if(line->symbol == 'a')
			isCodesGood = (line->getCode() == "110" || line->getCode() == "111" || line->getCode() == "010") ?  true :  false;

		if(isCodesGood == false)
			break;
	}
}

void TableTest::testGetMessageInCode(){
	isMessageInCodeGood = (table->getMessageInCode() == "1000011110110" || table->getMessageInCode() == "1000011010111") ? true : false;
	cout << table->getMessageInCode() << endl;
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