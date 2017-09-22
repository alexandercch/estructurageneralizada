#pragma once
#include <iostream>
#include "CGraphImage3D.h"
#include "CGraphImage2D.h"
#include "CGraphMeshND.h"
#include "CSegmentator.h"
#include "CImage.h"
#include "CGraphUtils.h"
#include "CAppUtils.h"

using namespace std;

//some config vars
const string PATH_DATA_DIRECTORY = "..\\Data\\";
const string PATH_RESULT_DIRECTORY = "..\\Results\\";
//parameter filled by input
string image_file;
string process_name;
int segmentation_difference;
int nmeshes_asmv;
int nmeshes_asms;

//helper objects
CAppUtils app_utils; //to take time
CGraphUtils<int> graph_utils; //handle images to graph convertions


void do_binary_segmentation_process() {
	CGraphImage2D<int> in;
	in.load_data(PATH_DATA_DIRECTORY + image_file);
	CSegmentator<CGraphImage2D<int> > seg(&in);

	cout << "Begin binary proccess." << endl;
	app_utils.begin_counter();

	seg.binary_segmentation();
	app_utils.show_duration();

	in.display();
}

void do_imesh_segmentation_process()
{
	CGraphImage2D<int> in;
	in.load_data(PATH_DATA_DIRECTORY + image_file);

	CSegmentator<CGraphImage2D<int> > seg(&in);

	cout << "Begin imesh process." << endl;
	cout << "Segmentation Difference: " << segmentation_difference << endl;

	seg.m_segmentation_difference = segmentation_difference;
	seg.m_nregions_asmv = nmeshes_asmv;
	seg.m_nregions_asms = nmeshes_asms;

	cout << "ACV" << endl;
	app_utils.begin_counter();
	seg.group_neighbor_cells();
	app_utils.show_duration();

	in.displayLabeledGraph();

	cout << "ASm_V  with: " << nmeshes_asmv << " regions." << endl;
	app_utils.begin_counter();
	seg.group_neighbor_regions();
	app_utils.show_duration();

	CImage imagen(in.m_rows, in.m_cols);
	graph_utils.OverlapedGraphToImage2D(&in, &(seg.m_meshregionV), &imagen);
	imagen.display();

	cout << "ASm_S with" << nmeshes_asms << " regions." << endl;
	app_utils.begin_counter();
	seg.group_similar_regions();
	app_utils.show_duration();

	graph_utils.OverlapedGraphToImage2D(&in, &(seg.m_meshregionV), &imagen);
	imagen.display();
}

void dump_labeled_graph(CGraphImage3D<int>* graph, string filename) {
	ofstream out(filename.c_str());
	for (int k = 0; k < graph->m_lays; ++k) {
		for (int i = 0; i < graph->m_rows; ++i) {
			for (int j = 0; j < graph->m_cols; ++j) {
				out << graph->m_labeled_matriz[i][j][k].m_label << '\t';
			}
			out << endl;
		}
		out << endl << endl;
	}
}

void do_imesh_segmentation_process_3d()
{
	CGraphImage3D<int> in;
	//reading files!
	cout << "reading files!" << endl;
	app_utils.begin_counter();
	in.load_data(PATH_DATA_DIRECTORY + image_file);
	app_utils.show_duration();

	cout << endl << "setting up graph!" << endl;
	app_utils.begin_counter();
	CSegmentator<CGraphImage3D<int> > seg(&in);
	app_utils.show_duration();

	cout << endl << "Begin imesh process." << endl;
	cout << "Segmentation Difference: " << segmentation_difference << endl;

	seg.m_segmentation_difference = segmentation_difference;
	seg.m_nregions_asmv = nmeshes_asmv;
	seg.m_nregions_asms = nmeshes_asms;

	cout << endl << "ACV" << endl;
	app_utils.begin_counter();
	seg.group_neighbor_cells();
	app_utils.show_duration();
	cout << "Regions created : " << seg.m_meshregionV.size() << endl << endl;

	in.displayLabeledGraph();

	cout << "ASm_V  with: " << nmeshes_asmv << " regions." << endl;
	app_utils.begin_counter();
	seg.group_neighbor_regions();
	app_utils.show_duration();

	CImage imagen(in.m_rows, in.m_cols, in.m_lays);
	graph_utils.OverlapedGraphToImage3D(&in, &(seg.m_meshregionV), &imagen);
	imagen.display3d();

	cout << endl << "ASm_S with " << nmeshes_asms << " regions." << endl;
	app_utils.begin_counter();
	seg.group_similar_regions();
	app_utils.show_duration();

	graph_utils.OverlapedGraphToImage3D(&in, &(seg.m_meshregionV), &imagen);
	imagen.display3d();

	//save result to file
	string result_file = CAppUtils::get_file_name(image_file) + ".txt";
	cout << "Dumping segmentation to file: " << PATH_RESULT_DIRECTORY + result_file << endl;
	app_utils.begin_counter();
	graph_utils.Overlaped3DGraphToFile(&in, &(seg.m_meshregionV), PATH_RESULT_DIRECTORY + result_file);
	app_utils.show_duration();
}

void do_imesh_segmentation_process_vtk_nd()//new reading method
{
	//display vtk file
	graph_utils.VTKDisplayMesh(PATH_DATA_DIRECTORY + image_file);

	CGraphMeshND<int> in;
	//reading files!
	cout << "reading files!" << endl;
	app_utils.begin_counter();
	graph_utils.VTKGridToMesh(&in, PATH_DATA_DIRECTORY + image_file);
	app_utils.show_duration();
	cout << endl << "setting up graph!" << endl;

	app_utils.begin_counter();
	CSegmentator<CGraphMeshND<int> > seg(&in);
	app_utils.show_duration();

	cout << endl << "Begin imesh process." << endl;
	cout << "Segmentation Difference: " << segmentation_difference << endl;

	seg.m_segmentation_difference = segmentation_difference;
	seg.m_nregions_asmv = nmeshes_asmv;
	seg.m_nregions_asms = nmeshes_asms;

	cout << endl << "ACV" << endl;
	app_utils.begin_counter();
	seg.group_neighbor_cells();
	app_utils.show_duration();
	cout << "Regions created : " << seg.m_meshregionV.size() << endl << endl;

	//in.displayLabeledGraph();

	cout << "ASm_V  with: " << nmeshes_asmv << " regions." << endl;
	app_utils.begin_counter();
	seg.group_neighbor_regions();
	app_utils.show_duration();

	//CImage imagen(in.m_rows, in.m_cols, in.m_lays);
	//graph_utils.OverlapedGraphToImage3D(&in, &(seg.m_meshregionV), &imagen);
	//imagen.display3d();

	
	cout << endl << "ASm_S with " << nmeshes_asms << " regions." << endl;
	app_utils.begin_counter();
	seg.group_similar_regions();
	app_utils.show_duration();
	

	//graph_utils.OverlapedGraphToImage3D(&in, &(seg.m_meshregionV), &imagen);
	//imagen.display3d();
	//Sleep(5000);
	//save result to file
	string result_file = CAppUtils::get_file_name(image_file) + ".proceced.vtu";
	cout << "Dumping segmentation to file: " << PATH_RESULT_DIRECTORY + result_file << endl;
	//Sleep(15000);
	app_utils.begin_counter();
	//graph_utils.MeshToAdjacentList(&in, PATH_RESULT_DIRECTORY + result_file);
	graph_utils.OverlapedNDMeshToVTKGrid(&in, &(seg.m_meshregionV), PATH_DATA_DIRECTORY + image_file, PATH_RESULT_DIRECTORY + result_file);
	app_utils.show_duration();
}

void do_imesh_segmentation_process_scalar_vtk_nd()//new reading method
{
	//display vtk file
	graph_utils.VTKDisplayMesh(PATH_DATA_DIRECTORY + image_file);

	CGraphMeshND<int> in;
	int nregions;
	//reading files!
	cout << "reading files!" << endl;
	app_utils.begin_counter();
	graph_utils.VTKGridToMesh(&in, PATH_DATA_DIRECTORY + image_file);
	app_utils.show_duration();
	cout << endl << "setting up graph!" << endl;

	app_utils.begin_counter();
	CSegmentator<CGraphMeshND<int> > seg(&in);
	app_utils.show_duration();

	cout << endl << "Begin imesh process." << endl;
	cout << "Segmentation Difference: " << segmentation_difference << endl;

	seg.m_segmentation_difference = segmentation_difference;
	seg.m_nregions_asmv = nmeshes_asmv;
	seg.m_nregions_asms = nmeshes_asms;

	cout << endl << "ACV" << endl;
	app_utils.begin_counter();
	seg.group_neighbor_cells();
	app_utils.show_duration();
	cout << "Regions created : " << seg.m_meshregionV.size() << endl << endl;

	cout << "ASm_V  with: " << nmeshes_asmv << " regions." << endl;
	app_utils.begin_counter();
	seg.group_neighbor_regions();
	app_utils.show_duration();	

	nregions = graph_utils.nnon_overlaped_regions<vector< CMeshRegion<CGraphMeshND<int> >* > >(&(seg.m_meshregionV));
	cout << "Non Overlaped Regions : " << nregions << endl << endl;


	cout << endl << "ASm_S with " << nmeshes_asms << " regions." << endl;
	app_utils.begin_counter();
	seg.group_similar_regions();
	app_utils.show_duration();
	nregions = graph_utils.nnon_overlaped_regions<vector< CMeshRegion<CGraphMeshND<int> >* > >(&(seg.m_meshregionV));
	cout << "Non Overlaped Regions : " << nregions << endl << endl;

	string result_file = CAppUtils::get_file_name(image_file) + ".proceced.vtu";
	cout << "Dumping segmentation to file: " << PATH_RESULT_DIRECTORY + result_file << endl;
	
	app_utils.begin_counter();
	//graph_utils.MeshToAdjacentList(&in, PATH_RESULT_DIRECTORY + result_file);
	graph_utils.OverlapedNDMeshToVTKGrid(&in, &(seg.m_meshregionV), PATH_DATA_DIRECTORY + image_file, PATH_RESULT_DIRECTORY + result_file);
	app_utils.show_duration();
}



int Imesh_Test_2D_Images()
{
	//freopen("out.txt", "w", stdout);
	/**
	input file format:
	filename
	process name
	segmentation differente
	number of meshes for asmv
	number of meshes for asms
	*/

	//freopen("input_2d_average.txt", "r", stdin);
	freopen("input_2d_ok.txt", "r", stdin);

	freopen("cimgelog.txt", "w", stderr);

	while (cin >> image_file, image_file != "")
	{
		cin >> process_name;
		cin >> segmentation_difference;
		cin >> nmeshes_asmv;
		cin >> nmeshes_asms;

		//system("cls");
		cout << "op:" << process_name << endl
			<< "seg diff:" << segmentation_difference << endl
			<< "# of meshes asmv:" << nmeshes_asmv << endl
			<< "# of meshes asms:" << nmeshes_asms << endl;

		if (process_name == "BYNARY_SEGMENTATION")
		{
			do_binary_segmentation_process();
		}
		else if (process_name == "IMESH_SEGMENTATION") {
			do_imesh_segmentation_process();
		}
		image_file = "";
	}
	return 0;
}

int Imesh_Test_3D_Images()
{
	//freopen("out.txt", "w", stdout);
	/**
	input file format:
	filename
	process name
	segmentation differente
	number of meshes for asmv
	number of meshes for asms
	*/

	//freopen("input_3d_test.txt", "r", stdin);
	freopen("input_3d_ok1.txt", "r", stdin);

	freopen("cimgelog.txt", "w", stderr);

	while (cin >> image_file, image_file != "")
	{
		cin >> process_name;
		cin >> segmentation_difference;
		cin >> nmeshes_asmv;
		cin >> nmeshes_asms;

		//system("cls");
		cout << "file: " << image_file << endl
			<< "op: " << process_name << endl
			<< "seg diff: " << segmentation_difference << endl
			<< "# of meshes asmv: " << nmeshes_asmv << endl
			<< "# of meshes asms: " << nmeshes_asms << endl << endl;

		if (process_name == "BYNARY_SEGMENTATION")
		{
			do_binary_segmentation_process();
		}
		else if (process_name == "IMESH_SEGMENTATION") {
			do_imesh_segmentation_process_3d();
		}
		image_file = "";
	}
	return 0;
}

int Imesh_Test_ND_Meshes()
{
	//freopen("out.txt", "w", stdout);
	/**
	input file format:
	filename
	process name
	segmentation differente
	number of meshes for asmv
	number of meshes for asms
	*/

	//freopen("input_nd_ok.txt", "r", stdin);
	freopen("input_nd_test.txt", "r", stdin);

	freopen("cimgelog.txt", "w", stderr);

	while (cin >> image_file, image_file != "")
	{
		cin >> process_name;
		cin >> segmentation_difference;
		cin >> nmeshes_asmv;
		cin >> nmeshes_asms;

		//system("cls");
		cout << "file: " << image_file << endl
			<< "op: " << process_name << endl
			<< "seg diff: " << segmentation_difference << endl
			<< "# of meshes asmv: " << nmeshes_asmv << endl
			<< "# of meshes asms: " << nmeshes_asms << endl << endl;

		if (process_name == "BYNARY_SEGMENTATION")
		{
			do_binary_segmentation_process();
		}
		else if (process_name == "IMESH_SEGMENTATION") {
			//do_imesh_segmentation_process_nd();
			do_imesh_segmentation_process_vtk_nd();
		}
		else if (process_name == "IMESH_SEGMENTATION_SCALAR_VTK" ){
			//for files with scalar values instead of rgb colors
			do_imesh_segmentation_process_scalar_vtk_nd();
		}

		image_file = "";
	}
	return 0;
}


void do_imesh_segmentation_process_nd()//old reading method
{	
	graph_utils.VTKDisplayMesh(PATH_DATA_DIRECTORY + image_file);
	CGraphMeshND<int> in;
	//reading files!
	cout << "reading files!" << endl;
	app_utils.begin_counter();
	graph_utils.AdjacentListToMesh(&in, PATH_DATA_DIRECTORY + image_file);
	app_utils.show_duration();
	cout << endl << "setting up graph!" << endl;

	app_utils.begin_counter();
	CSegmentator<CGraphMeshND<int> > seg(&in);
	app_utils.show_duration();

	cout << endl << "Begin imesh process." << endl;
	cout << "Segmentation Difference: " << segmentation_difference << endl;

	seg.m_segmentation_difference = segmentation_difference;
	seg.m_nregions_asmv = nmeshes_asmv;
	seg.m_nregions_asms = nmeshes_asms;

	cout << endl << "ACV" << endl;
	app_utils.begin_counter();
	seg.group_neighbor_cells();
	app_utils.show_duration();
	cout << "Regions created : " << seg.m_meshregionV.size() << endl << endl;

	//in.displayLabeledGraph();

	cout << "ASm_V  with: " << nmeshes_asmv << " regions." << endl;
	app_utils.begin_counter();
	seg.group_neighbor_regions();
	app_utils.show_duration();

	//CImage imagen(in.m_rows, in.m_cols, in.m_lays);
	//graph_utils.OverlapedGraphToImage3D(&in, &(seg.m_meshregionV), &imagen);
	//imagen.display3d();

	cout << endl << "ASm_S with " << nmeshes_asms << " regions." << endl;
	app_utils.begin_counter();
	seg.group_similar_regions();
	app_utils.show_duration();

	//graph_utils.OverlapedGraphToImage3D(&in, &(seg.m_meshregionV), &imagen);
	//imagen.display3d();

	//save result to file
	string result_file = CAppUtils::get_file_name(image_file) + ".txt.proceced";
	cout << "Dumping segmentation to file: " << PATH_RESULT_DIRECTORY + result_file << endl;
	app_utils.begin_counter();
	graph_utils.MeshToAdjacentList(&in, PATH_RESULT_DIRECTORY + result_file);
	app_utils.show_duration();
}

void do_ag2()
{
	//CImage imagen(DATA_PATH + data_file);//true beacuse it is 3d
	cout << "begin ag2 width file:" << image_file << endl;
	//imagen.display();


	CGraphImage2D<int> in;
	in.load_data(PATH_DATA_DIRECTORY + image_file);
	in.display();
	//graph_utils.ImageToGraph2D(&in, &imagen);
	//cout<<":P"<<endl;

	CSegmentator<CGraphImage2D<int> > seg(&in);
	seg.m_segmentation_difference = segmentation_difference;
	seg.m_nregions_asmv = nmeshes_asmv;
	seg.m_nregions_asms = nmeshes_asms;


	cout << "Segmentando" << endl;
	cout << "ACV" << endl;
	app_utils.begin_counter();
	seg.group_neighbor_cells();
	app_utils.show_duration();

	//graph_utils.LabeledGraphToImage2D(&in, &imagen);
	//imagen.display();
	in.displayLabeledGraph();

	cout << "# de regiones:" << seg.m_meshregionV.size() << endl << endl;
	cout << "# de regiones a converger asmv:" << nmeshes_asmv << endl;
	cout << "ASm_V" << endl;
	app_utils.begin_counter();
	seg.group_neighbor_regions();
	app_utils.show_duration();


	CImage imagen(in.m_cols, in.m_rows);
	graph_utils.OverlapedGraphToImage2D(&in, &(seg.m_meshregionV), &imagen);
	imagen.display();

	int nregions =
		graph_utils.nnon_overlaped_regions<vector< CMeshRegion<CGraphImage2D<int> >* > >(&(seg.m_meshregionV));

	cout << "# de regiones:" << nregions << endl << endl;
	cout << "# de regiones a converger asmv:" << nmeshes_asms << endl;
	cout << "ASm_S" << endl;
	app_utils.begin_counter();
	seg.group_similar_regions();
	app_utils.show_duration();

	nregions =
		graph_utils.nnon_overlaped_regions<vector< CMeshRegion<CGraphImage2D<int> >* > >(&(seg.m_meshregionV));

	cout << "# de regiones:" << nregions << endl << endl;

	graph_utils.OverlapedGraphToImage2D(&in, &(seg.m_meshregionV), &imagen);
	imagen.display();
	cout << "end processing width file:" << image_file << endl;
}

void do_ag3()
{

	CGraphImage3D<int> in;
	cout << "reading image 3d" << endl;
	app_utils.begin_counter();
	in.load_data(PATH_DATA_DIRECTORY + image_file);
	app_utils.show_duration();

	CSegmentator<CGraphImage3D<int> > seg(&in);
	seg.m_segmentation_difference = segmentation_difference;
	seg.m_nregions_asmv = nmeshes_asmv;
	seg.m_nregions_asms = nmeshes_asms;

	cout << "Segmentando" << endl;
	cout << "ACV" << endl;
	app_utils.begin_counter();
	seg.group_neighbor_cells();
	app_utils.show_duration();

	cout << "number of regions:" << seg.m_meshregionV.size() << endl;
	cout << "display labeled img" << endl;
	in.displayLabeledGraph();

	cout << "ASm_V" << endl;
	app_utils.begin_counter();
	seg.group_neighbor_regions();
	app_utils.show_duration();

	cout << "overlaped to img" << endl;
	CImage imagen(in.m_cols, in.m_rows);
	graph_utils.OverlapedGraphToImage3D(&in, &(seg.m_meshregionV), &imagen);
	imagen.display();

	cout << "ASm_S" << endl;
	app_utils.begin_counter();
	seg.group_similar_regions();
	app_utils.show_duration();

	cout << "overlaped to img" << endl;
	app_utils.begin_counter();
	graph_utils.OverlapedGraphToImage3D(&in, &(seg.m_meshregionV), &imagen);
	app_utils.show_duration();
	imagen.display3d();

	graph_utils.Overlaped3DGraphToFile(&in, &(seg.m_meshregionV), "..\\Results\\3ddragon.txt");

}

/*void do_bin()
{

CGraphImage2D<int> in;
in.load_data(PATH_DATA_DIRECTORY + data_file);

CSegmentator<CGraphImage2D<int> > seg(&in);
seg.binary_segmentation();

in.display();
}*/


