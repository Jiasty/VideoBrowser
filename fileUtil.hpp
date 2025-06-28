#ifndef __FILEUTIL__
#define __FILEUTIL__
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace file_sp
{
	class fileUtil
	{
	public:
		fileUtil(const std::string name) : _name(name) {}

		bool Exists()
		{
			int ret = access(_name.c_str(), F_OK);
			if(ret == 0) return true;
			else
			{
				std::cout << "file is not exists!" << std::endl;
				return false;
			}
		}

		// 以字节为单位返回文件大小
        size_t FileSize()
		{
			if(this->Exists() == false) return 0;
			
			struct stat st;
			int ret = stat(_name.c_str(), &st);
			if(ret != 0)
			{
				std::cout << "open file failed" << std::endl;
				return 0;
			}

			return st.st_size;
		}

        bool GetContent(std::string *content)  // 将文件内容写到content中带出
		{
			std::ifstream ifs(_name, std::ios::binary); // 视频图片都是二进制数据
			if(ifs.is_open() == false)
			{
				std::cout << "open file:"  << _name << "failed" << std::endl;
				return false;
			}

			int fsize = this->FileSize();
			content->resize(fsize);
			ifs.read(&(*content)[0], fsize); // @@@注意此处参数
			if(ifs.good() == false)
			{
				std::cout << "read file content failed" << std::endl;
				ifs.close();
				return false;
			}
			ifs.close();
			return true;
		}

        bool SetContent(const std::string content) // 将数据content写入文件
		{
			std::ofstream ofs(_name, std::ios::binary);
			if(ofs.is_open() == false) 
			{
                 std::cout << "open file:"  << _name << "failed" << std::endl;
				 return false;
			}

			ofs.write(content.c_str(), content.size()); // 注意此处参数类型
			if(ofs.good() == false)
			{
				std::cout << "read file content failed" << std::endl;
				ofs.close();
				return false;
			}
			ofs.close();
			return true;
		}

        bool CreateDirectory() // 针对目录时创建目录
		{
			if(this->Exists()) return true;
		
			mkdir(_name.c_str(), 0777);
			return true;	
		}

	private:
		std::string _name; // 文件路径
	};

}

#endif
