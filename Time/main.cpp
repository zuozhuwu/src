#include "db/Time/Time.h"
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "db/Json/json.hpp"

using namespace std;
using namespace configor;
int main()
{
	json j;
	j["number"] = 1;
	j["float"] = 1.5;
	j["string"] = "this is a string";
	j["boolean"] = true;
	j["user"]["id"] = 10;
	j["user"]["name"] = "Nomango";

	cout<<j<<endl;

	string str = "{\"boolean\":true,\"float\":1.5,\"number\":1,\"string\":\"this is a string\",\"user\":{\"id\":10,\"name\":\"Nomango\"}}";

	json ja = json::parse(str);

	std::ofstream ofs("sample.json");

	ofs<<ja;

	ofs.close();

	std::ifstream ifs("sample.json");
	json jc;
	ifs>>jc;

	jc["wzz"] = "zuozhuwu";
	jc["name"] = "wushuao";

	cout<<jc;

	

	ifs.close();	
	

	return 0;
}
