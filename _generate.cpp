#include <iostream>
#include <gtest/gtest.h>

using namespace std;
/*
struct Texas{
	float age;

	Texas(int age = 0){
		this->age = age;
	}
};

struct TexasTest : testing::Test{
	Texas*  texas = nullptr;

	TexasTest(){
		texas = new Texas();
	}

	~TexasTest(){
		delete texas;
	}
}; 
TEST_F(TexasTest, IsAgeZero){
	EXPECT_EQ(0, texas->age);
}
*/

int main(int argc, char* argv[]){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}