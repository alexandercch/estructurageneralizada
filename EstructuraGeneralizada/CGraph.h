/**
    Seminario de Tesis 10
    CGraph.h
    Purpose: Is mother class to the other graph structural context
             and only defines the principal atributes of a graph

    @author Alex Ccacyahuillca
    @version 1.0 04/015
*/

#ifndef CGRAPH_H
#define CGRAPH_H

#include "CNode.h"
#include "CImage.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//CGraph es la carcaza que pretendemos hacer
class CGraph
{
public:
    typedef CNode node;

    //methods
    CGraph();
    virtual ~CGraph();

    /**
        @return the total number of elements
    */
    virtual int weight() = 0;//number of nodes

    /**
        @return the total space used by the graph (i.e. area, volumen, etc)
    */
	virtual int area() = 0;//image area

    /**
        Read data from file
        @param filename path to the data file
    */
	virtual void load_data(string filename) = 0;

protected:
private:
};

CGraph::CGraph()
{
    //ctor
}

CGraph::~CGraph()
{
    //dtor
}

#endif // CGRAPH_H
