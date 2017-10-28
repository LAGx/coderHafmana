#include <iostream>
#include <gtest/gtest.h>
#include "table_haf.h"

using namespace std;
#define DEBAG 

int main(int argc, char* argv[]){

	//testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS();

	Table t;
	t.createTableFromFile();
#if DEBAG
	t.showExtend();
#endif
	
	return 0;

}