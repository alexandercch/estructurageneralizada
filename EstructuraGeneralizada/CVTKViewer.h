#pragma once
#include <string>
#ifdef READUGRID_EXPORTS
#define READUGRID_API __declspec(dllexport) 
#else
#define READUGRID_API __declspec(dllimport) 
#endif



using namespace std;

class READUGRID_API CVTKViewer
{
public:
	void display_vtk_file(string filename);
	void set_graph_from_vtk_file(string filename, int ***graph, int **color, double **area, int *number_of_neighbors, int *size);
	void set_vtk_file_from_graph(string filename_sorce, string filename_output, int **color, int number_of_neighbors, int size);
	void check_colors(int **color, int size);
};
