#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include <bitset>
#include <utility>
#include <algorithm>
using namespace std;

template <class F, class S >
class Pair{
public:
	Pair(F _up, S _low): up(_up), low(_low)
		{}
	F up; 
	S low;
};

int main(){
	string message = "overcome difficulties with the mind, and threat with experience!";
	vector<string> third_codes; 

	cout << "\nInput string:\n" << message << endl;
	cout << "\nIn ascii: "<< endl;
	string all_code = "";
	for(char c: message){
		cout << bitset<8>(c) << " ";
		all_code += bitset<8>(c).to_string();
	}
	cout << endl;

	cout << "\nDividing by 3 symbols:"<< endl;
	//divide
	string buff = "";
	int iter = 0;
	for(char c: all_code){
		if(iter == 3){
			third_codes.push_back(buff);
			buff = "";
			iter = 0;
		}else{
			buff += c;
			iter += 1;
		}
	}

	for(auto l: third_codes){
		cout << l << " ";
	}
	cout << endl;

	vector<Pair<string, int>> table;

	for(string s: third_codes){
		vector<Pair<string, int>>::iterator it =  find_if(table.begin(), table.end(), [&s](const Pair<string, int>& a){
			return a.up == s;
		});

		if(table.end() == it)
			table.push_back(Pair<string, int>(s, 1));
		else
			it->low += 1;
	}

	sort(table.begin(), table.end(), [](const Pair<string, int>& a, const Pair<string, int>& b){
		return a.low < b.low;
	});

	cout << "\nsbl" << " : " << "val" << endl; 

	for(vector<Pair<string, int>>::iterator it = table.begin();it != table.end();it++){
		cout << it->up << " : " << it->low << endl; 
	}

	return 0;
}