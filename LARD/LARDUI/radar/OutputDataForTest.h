#ifndef ___OUT_PUT_DATA_FOR_TEST_H___
#define ___OUT_PUT_DATA_FOR_TEST_H___

#include <string>
#include <fstream>


extern std::ofstream DATA_FILE_FOR_TEST;

void OpenDataFileForTest(const std::string& file_name);

void CloseDataFileForTest();





















#endif