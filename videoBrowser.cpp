#include "fileUtil.hpp"


void fileTest()
{
	file_sp::fileUtil("./www").CreateDirectory();
	file_sp::fileUtil("./www/index.html").SetContent("<html></html>");
	std::string content;
	file_sp::fileUtil("./www/index.html").GetContent(&content);
	std::cout << content << file_sp::fileUtil("./www/index.html").FileSize() << std::endl;
}

int main()
{
	fileTest();

	return 0;
}
