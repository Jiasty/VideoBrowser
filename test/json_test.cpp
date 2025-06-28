#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <jsoncpp/json/json.h>

void serialization()
{
	const char* name = "Jiasty";
	int age = 21;
	float score[] = {80.1, 99.5, 66.6};
	
	Json::Value val;
	val["name"] = name;
	val["age"] = age;
	val["score"].append(score[0]);
	val["score"].append(score[1]);
	val["score"].append(score[2]);

	Json::StreamWriterBuilder swb;
	std::unique_ptr<Json::StreamWriter> sw(swb.newStreamWriter());


	std::stringstream ss;

	int ret = sw->write(val, &ss);
	if(ret != 0)
	{
		std::cerr << "write failed" << std::endl;
		return;
	}
	std::cout << ss.str() << std::endl;
}

void deserialization()
{
	std::string str = R"({"name":"Jiasty", "age":21, "score":[11.1, 22.2, 33.3]})";
	Json::Value root; // 存储反序列化的数据
	Json::CharReaderBuilder crb;
	std::unique_ptr<Json::CharReader> cr(crb.newCharReader());
	std::string err;
	
	bool ret = cr->parse(str.c_str(), str.c_str() + str.size(), &root, &err);
	if(!ret)
	{
		std::cout << err << std::endl;
		return;
	}

	std::cout << root["name"].asString() << std::endl << root["age"].asInt() << std::endl;
	for(auto e : root["score"])
	{
		std::cout << e.asFloat() << std::endl;
	}
}


int main()
{
	serialization();

	deserialization();


	return 0;
}

