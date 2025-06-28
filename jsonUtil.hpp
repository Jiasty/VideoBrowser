// util.hpp
#ifndef __MY_UTIL__
#define __MY_UTIL__
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <jsoncpp/json/json.h>
namespace aod
{
    class JsonUtil
    {
         public:
         static bool Serialize(const Json::Value &root, std::string *str);
         static bool UnSerialize(const std::string &str, Json::Value *root);
    };
}
#endif
