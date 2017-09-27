#pragma once
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class CImeshUtils {
public:
	CImeshUtils();
	~CImeshUtils();

	bool process_imesh_task_file(string filename);

};


inline bool CImeshUtils::process_imesh_task_file(string file_name)
{
	ifstream file_in(file_name.c_str());
	string line;
	string command;

	while (getline(file_in, line)) {
		istringstream iss(line);
		iss >> command;


	}

	return false;
}


CImeshUtils::CImeshUtils()
{
}

inline CImeshUtils::~CImeshUtils()
{
}