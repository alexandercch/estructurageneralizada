/**
    Seminario de Tesis 10
    main.cpp
    Purpose: This file use the Generalized Graph and and the Imesh Algorithm
             to perform the image segmentation over the 4 context of structures
             to know images 2D, 3D, and meshes 2D, 3D.

    @author Alex Ccacyahuillca
    @version 1.0 04/015
*/
#include <iostream>
#include <string>

#include "TestImesh.h"
#include "CAppUtils.h"

using namespace std;

int main(int argc, char* argv[])
{
	string file_tasks = CAppUtils::handle_params(argc, argv);
	printf("file_task %&s", file_tasks);

	Sleep(15000);


	Imesh_Test_2D_Images();
	//Imesh_Test_3D_Images();
	//Imesh_Test_ND_Meshes();

	Sleep(10000);	
    return 0;
}

/*
void do_mesh1()
{
    cout<<"Testing mesh segmentation:"<<endl;
    cout<<"File:"<<DATA_PATH + data_file<<endl;
    CGraphMeshND<int> in;

    cout<<"loading..."<<endl;
    app_utils.begin_counter();
    graph_utils.AdjacentListToMesh(&in, DATA_PATH + data_file);
    app_utils.show_duration();

    CSegmentator<CGraphMeshND<int> > seg(&in);

    cout<<"Begin segmentation:"<<endl;
    app_utils.begin_counter();
    seg.binary_segmentation();
    app_utils.show_duration();
    cout<<"End Segmentation."<<endl<<endl;

    cout<<"Saving file:"<<endl;
    app_utils.begin_counter();
    graph_utils.MeshToAdjacentList(&in,DATA_PATH + data_file + "out");
    app_utils.show_duration();
    cout<<"end saving."<<endl<<endl;
    //grafo_salida.print_mesh();
}*/


/*
void do_mesh2()
{
    cout<<"Testing mesh segmentation:"<<endl;
    cout<<"File:"<<DATA_PATH + data_file<<endl;
    CGraphMeshND<int> in;

    cout<<"loading..."<<endl;
    app_utils.begin_counter();
    graph_utils.AdjacentListToMesh(&in, DATA_PATH + data_file);
    app_utils.show_duration();

    CSegmentator<CGraphMeshND<int> > seg(&in);
    seg.m_segmentation_difference=segmentation_difference;
    seg.m_nregions_asmv = nmeshes_asmv;
    seg.m_nregions_asms = nmeshes_asms;

    cout<<"Segmentando"<<endl;
    cout<<"ACV"<<endl;
    app_utils.begin_counter();
    seg.group_neighbor_cells();
    app_utils.show_duration();


    cout<<"Labeled Mesh to Graph"<<endl;
    app_utils.begin_counter();
    graph_utils.LabeledMeshToNDGraph(&in, "..\\Results\\labeledgraph.txt");
    app_utils.show_duration();
    //cout<<"Labeled Mesh to Graph"<<endl;

    cout<<"ASm_V"<<endl;
    app_utils.begin_counter();
    seg.group_neighbor_regions();
    app_utils.show_duration();

    cout<<"Saving file:"<<endl;
    app_utils.begin_counter();
    graph_utils.OverlapedNDGraphToFile(&in,&(seg.m_meshregionV), "..\\Results\\overlapedgraph.txt");
    app_utils.show_duration();
    cout<<"end saving."<<endl<<endl;

    cout<<"hello"<<endl;
    //grafo_salida.print_mesh();
}
*/

