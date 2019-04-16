#include "OutputDataForTest.h"

std::ofstream DATA_FILE_FOR_TEST;



void OpenDataFileForTest(const std::string& file_name)
{
	DATA_FILE_FOR_TEST.open(file_name.c_str());
}

void CloseDataFileForTest()
{
	DATA_FILE_FOR_TEST.close();
}
