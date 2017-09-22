#ifndef CAPPUTILS_H
#define CAPPUTILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>  /* defines FILENAME_MAX */

//#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
/*#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif*/

using namespace std;

//this class will provide statistic, last, conversion and another useful functions
//in order to dont show this in the main file keep the main file clean :)
class CAppUtils
{
public:
    CAppUtils();
    ~CAppUtils();
    //members
    clock_t m_startTime;

    void begin_counter();
    void show_duration();
    static string get_working_directory(bool show);
	static string handle_params(int argc, char* argv[]);
	inline static bool file_exist(const std::string& name);
	static string int_to_str(int n);
	static void set_vector_name(string filename, vector<string>& file_name_vector);
	static string get_file_name(string path);
private:
};

string CAppUtils::get_file_name(string path) {
	int slash_pos = 0;
	slash_pos = path.rfind('\\');
	if (slash_pos == string::npos)
		slash_pos = -1;
	return path.substr(slash_pos + 1, path.size());
}

inline bool CAppUtils::file_exist(const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}

string CAppUtils::handle_params(int argc, char* argv[]) {
	string task_file;
	if (argc > 2) {
		task_file = argv[1];
		string path = get_working_directory() + task_file;
		cout << "PATH --> " << path << endl;
		if (file_exist(path)) return path;
		exit(EXIT_FAILURE);
	}
	else {
		cout << "NO FILE TASK PROVIDED!, PLEASE PROVIDE A TASKS FILE NAME AS COMMAND LINE ARGUMENT." << endl;
		exit(EXIT_FAILURE);
	}
}

void CAppUtils::set_vector_name(string filename, vector<string>& file_name_vector) {
	int point_pos, layer_counter = 0;
	string name, ext, newname, number;
	point_pos = filename.rfind('.');
	name = filename.substr(0, point_pos);
	ext = filename.substr(point_pos, filename.size());	
	for (int i = 0; i< 10000; ++i)
	{
		layer_counter = i;
		number = CAppUtils::int_to_str(layer_counter);

		newname = name + number + ext;
		ifstream entrada(newname.c_str());
		if (entrada)
		{
			file_name_vector.push_back(newname);
			continue;
		}
		else break;
	}
}

void CAppUtils::begin_counter()
{
    m_startTime = clock();
};
void CAppUtils::show_duration()
{
    cout << double( clock() - m_startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
};


string CAppUtils::get_working_directory(bool show=true)
{
    char cCurrentPath[FILENAME_MAX];
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
        printf("CANT GET CURRENT WORKING DIRECTORY.\n");
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
	if(show)
		printf("The current working directory is %s\n", cCurrentPath);
	string current_working_directory(cCurrentPath);
	return current_working_directory;
};

string CAppUtils::int_to_str(int n)
{
    char *buffer = new char[64];
    sprintf(buffer,"%d", n);
    string res = buffer;
    delete[] buffer;
    return res;
}

CAppUtils::CAppUtils()
{
};

CAppUtils::~CAppUtils()
{
};

#endif //CAPPUTILS_H
