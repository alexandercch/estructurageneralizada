#pragma once
#include <string>
#include <fstream>
#include <sstream>

#include "CGraph.h"
#include "CGraphImage2D.h"
#include "CGraphImage3D.h"
#include "CGraphMeshND.h"

#define IMG_2D "IMG_2D"
#define IMG_3D "IMG_3D"
#define MESH_2D "MESH_2D"
#define MESH_3D "MESH_2D"

using namespace std;

class CImeshUtils {
public:
	CImeshUtils();
	~CImeshUtils();

	bool process_imesh_task_file(string filename);
	void graph_loader(CGraph *&graph, string graph_type, string filename);

};

void CImeshUtils::graph_loader(CGraph *&graph, string graph_type, string filename) {
	if (graph_type == IMG_2D) {
		graph = new CGraphImage2D();
	}
	else if (graph_type == IMG_3D) {
		graph = new CGraphImage3D();
	}
	else if (graph_type == MESH_2D || graph_type == MESH_3D) {
		graph = new CGraphMeshND();
	}
	else 
		throw invalid_argument("[graph_loader] unrecognized type of graph.");
}

inline bool CImeshUtils::process_imesh_task_file(string file_name)
{
	ifstream file_in(file_name.c_str());
	string line;
	string command, value, graph_type, graph_file_name;
	CGraph *graph;

	while (getline(file_in, line)) {
		istringstream iss(line);
		iss >> command;

		if (command == "LOAD_GRAPH")
		{
			iss >> graph_type >> graph_file_name;
			graph_loader(graph, graph_type, graph_file_name);
		}
		else if (command == "LOAD_GRAPH") {
			
		}
		
	
	}

	return false;
}


CImeshUtils::CImeshUtils()
{
}

inline CImeshUtils::~CImeshUtils()
{
}