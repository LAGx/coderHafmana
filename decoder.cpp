#include "decoder.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <bitset>

#define DEBAG

using namespace std;


string Decoder::decode(string inpufFile){
	ifstream file_i(inpufFile);
 
   	if (!file_i.is_open()) 
		cout << "no such file: " << inpufFile << endl;
    	
    	string line, in_code = "", decoding;
    	map<string, char> code;
    	bool isMessage = false;

    	while(getline(file_i, line)){
    		if(line == "00000000"){	
    			isMessage = true;
    			continue;
    		}

    		if(!isMessage){ //fill code
    			code[line.substr(8)] = static_cast<char>(std::bitset<8>(line.substr(0, 8)).to_ulong());
#if DEBAG
    			cout <<line.substr(0, 8) << ": " << static_cast<char>(std::bitset<8>(line.substr(0, 8)).to_ulong())  << " : " << line.substr(9) << endl;
#endif
    		}else{//create coder line
    			in_code += line;
    		}
    	}

    	file_i.close();

    	string buff = "";
    	map<string, char>::iterator iter;
    	for(char c: in_code){
    		buff += c;
    		iter = code.find(buff);
    		if(iter != code.end()){
    			decoding += code[buff];
#if DEBAG
    			cout << buff << " ";
#endif
    			buff = "";
    		}
    	}

    	return decoding;
}


void Decoder::decode_f(string inputFile, string outputFile){
	string text = Decoder::decode(inputFile);

    	std::ofstream file_o(outputFile, std::ios::trunc);
	
	file_o << text << endl;

	file_o.close();
}