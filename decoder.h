#include <string>

using namespace std;


class Decoder{
public:

	static string decode(string inpufFile = "message.haf");
	static void decode_f(string inputFile = "message.haf", string outputFile = "message_dec.txt");

};