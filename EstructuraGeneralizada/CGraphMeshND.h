/**
	Seminario de Tesis 10
	CGraphMeshND.h
	Purpose: Is a child class from CGraph will hold a mesh in any
		dimension, the dimencion is defined in the number of neighbors
		member
	@author Alex Ccacyahuillca
	@version 1.0 04/015
*/

#ifndef CGRAPHMESHND_H_INCLUDED
#define CGRAPHMESHND_H_INCLUDED

#include "CGraph.h"
#include "CGraphIteratorND.h"

class CGraphMeshND : public CGraph
{
public:
	typedef CGraphIteratorND iterator;
	typedef CGraph::node node;
	typedef CGraph::node::NodeType NodeType;

	//members
	node *m_nodes;
	int **m_adj_list;
	int m_number_of_neighbors, m_size;//number of neighbours, define the dimension, m_size

	//methods
	CGraphMeshND();
	virtual ~CGraphMeshND();

	/**
		@return the total number of elements
	*/
	int weight();

	/**
		@return the total space used by the graph (i.e. area, volumen, etc)
	*/
	int area();

	/**
		Sets the size of the graph
		@param size the number of elements the graph will hold
		@param dimension the number neighbors each node will containt
		in this case that number will also define de dimension of the
		mesh(2D, 3D, ND).
	*/
	void config(int size, int dimension);

	/**
		Read data from file
		@param filename path to the data file
	*/
	void load_data(string filename);

	//methods - iteration
	/**
		@return a pointer to the beginning of the Graph, and the same
				for end method.
	*/
	iterator* begin();
	iterator* end();

	/**
		Set an specific element with the specific data
		@param iter the iterator that point to the node
		@param data the data to put in the place pointed by iter
	*/
	void set_at(iterator& iter, NodeType& data);

	/**
		Copy all data from other graph, first sets to the new dimensions
		and begin the copy.
		@param _graph pointer to a same class graph
	*/
	void operator=(CGraphMeshND &_graph);


	void print_mesh();//beacause still we dont draw a mesh we print its values temporaly
	void set_pointer_iterators();
private:
	iterator *m_ibegin, *m_iend;
};

CGraphMeshND::CGraphMeshND() :
	m_ibegin(new iterator),
	m_iend(new iterator),
	m_size(0),
	m_number_of_neighbors(0)
{

}
CGraphMeshND::~CGraphMeshND()
{
	cout << "m_size:" << m_size << " ";
	cout << "~";
	for (int i = 0; i < m_size; ++i)
		delete[] m_adj_list[i];
	delete[] m_adj_list;
	delete[] m_nodes;
	cout << "dtor" << endl;
}


void CGraphMeshND::config(int size, int dimension) //dimensio should be 2 or 3
{
	m_size = size;
	dimension++;
	m_number_of_neighbors = dimension;
	m_nodes = new node[size + 1];
	m_adj_list = new int*[size];
	for (int i = 0; i < size; ++i)
	{
		m_adj_list[i] = new int[dimension];
	}

	//set begin and end iterators
	set_pointer_iterators();
}


CGraphMeshND::iterator* CGraphMeshND::begin()
{
	return m_ibegin;
}


CGraphMeshND::iterator* CGraphMeshND::end()
{
	return m_iend;
}


void CGraphMeshND::set_at(iterator& iter, NodeType& data)
{
	m_nodes[iter.m_index].m_data = data;
}


void CGraphMeshND::operator=(CGraphMeshND &_graph)
{
	config(_graph.m_size, _graph.m_number_of_neighbors - 1);
	for (int i = 0; i < _graph.m_size; ++i)
	{
		m_nodes[i] = _graph.m_nodes[i];
		for (int j = 0; j < _graph.m_number_of_neighbors; ++j)
		{
			m_adj_list[i][j] = _graph.m_adj_list[i][j];
		}
	}
}


void CGraphMeshND::load_data(string filename)
{
	ifstream in(filename.c_str());
	int size, dimension, data, neighbor;
	in >> size >> dimension;
	config(size, dimension);
	for (int i = 0; i < size; ++i)
	{
		in >> data;
		m_nodes[i].m_data = data;
		for (int j = 0; j < dimension + 1; ++j)
		{
			in >> neighbor;
			m_adj_list[i][j] = neighbor;
		}
	}
}


int CGraphMeshND::weight()
{
	return m_size;
}


int CGraphMeshND::area()
{
	float tarea = 0.0;
	for (int i = 0; i < m_size; ++i)
		tarea += m_nodes[i].m_area;
	return tarea;
}



void CGraphMeshND::print_mesh()
{
	for (int i = 0; i < m_size; ++i)
	{
		cout << m_nodes[i].m_data << endl;
	}
}

inline void CGraphMeshND::set_pointer_iterators()
{
	m_ibegin->m_pgraph = this;
	m_ibegin->m_index = 0;

	m_iend->m_pgraph = this;
	m_iend->m_index = m_size;
	///this node is setted to invalid to be pointed for the border
	///cells of the mesh, in wich case has less neighbors than others
	m_nodes[m_size].m_label = INVALID_NEIGHBOR_LABEL_VALUE;
}
#endif // CGRAPHMESHND_H_INCLUDED
