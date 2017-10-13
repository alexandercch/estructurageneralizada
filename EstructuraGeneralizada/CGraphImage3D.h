/**
	Seminario de Tesis 10
	CGraphImage3D.h
	Purpose: Is a child class will hold a 3D matrix

	@author Alex Ccacyahuillca
	@version 1.0 04/015
*/

#ifndef CIMAGE3D_H
#define CIMAGE3D_H

#include "CGraph.h"
#include "CGraphIterator3D.h"

#define NUMBER_OF_NEIGHBOURS_3D 6


class CGraphImage3D : public CGraph
{
public:
	typedef unsigned char IType;
	typedef CGraphIterator3D iterator;
	typedef CGraph::node node;
	typedef CGraph::node::NodeType NodeType;

	//members
	node ***m_labeled_matriz;//this will hold the data
	CImg<IType> **m_imagen;//for 3d images

	int m_rows, m_cols, m_lays;
	int m_number_of_neighbors;

	int m_nchannels;

	//methods
	CGraphImage3D();
	virtual ~CGraphImage3D();

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
		@param _rows the number of rows of the 3D matrix graph
		@param _cols the number of columns of the 3D matrix graph
		@param _lays the number of layers of the 3D matrix graph
	*/
	void config(int _rows, int _cols, int _lays);

	/**
		Read data from file
		@param filename path to the data file
	*/
	void load_data(string filename);

	/**
	Get actual data from the graph
	@param _row the row in the image
	@param _col the column in the image
	*/
	int get_pixel(int _row, int _col, int _lay);

	/**
	Set actual data from the graph
	@param _row the row in the image
	@param _col the column in the image
	@param pixel the colorto go into the image
	*/
	void set_pixel(int _row, int _col, int _lay, int pixel);

	/**
	Displays an image colored by the values of
	m_labeled_matriz
	*/
	void displayLabeledGraph();

	/**
	Displays the actual image contained
	*/
	void display();


	//methods - iteration
	/**
		@return a pointer to the beginning of the Graph
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
	void operator=(CGraphImage3D &_graph);

protected:
private:
	iterator *m_ibegin, *m_iend;
};


CGraphImage3D::CGraphImage3D() :
	m_number_of_neighbors(NUMBER_OF_NEIGHBOURS_3D),
	m_ibegin(new iterator),
	m_iend(new iterator),
	m_rows(0),
	m_cols(0),
	m_lays(0)
{
}

CGraphImage3D ::~CGraphImage3D()
{
	//dtor
	for (int i = 0; i < m_rows; ++i) {
		for (int j = 0; j < m_cols; ++j)
			delete[] m_labeled_matriz[i][j];
		delete[] m_labeled_matriz[i];
	}
	delete[] m_labeled_matriz;
}

void CGraphImage3D ::config(int _rows, int _cols, int _lays)
{
	m_rows = _rows;
	m_cols = _cols;
	m_lays = _lays;
	m_labeled_matriz = new node**[_rows];
	for (int i = 0; i < _rows; ++i)
	{
		m_labeled_matriz[i] = new node*[_cols];
		for (int j = 0; j < _cols; ++j)
			m_labeled_matriz[i][j] = new node[_lays];
	}
	//cout<<"iterators configuration!"<<endl;
	m_ibegin->m_current_row = 0;
	m_ibegin->m_current_column = 0;
	m_ibegin->m_current_layer = 0;

	m_ibegin->m_total_rows = m_rows;
	m_ibegin->m_total_columns = m_cols;
	m_ibegin->m_total_layers = m_lays;

	m_ibegin->m_pgraph = this;

	m_iend->m_current_row = m_rows;
	m_iend->m_current_column = m_cols;
	m_iend->m_current_layer = m_lays;

	//cout<<"success!"<<endl;
}

inline void CGraphImage3D::displayLabeledGraph()
{
	int middleImage = m_lays / 2;
	CColor color;
	CImage img(m_rows, m_cols);
	for (int row = 0; row < m_rows; row++) {
		for (int col = 0; col < m_cols; col++) {
			img.set_pixel(row, col, color(m_labeled_matriz[row][col][middleImage].m_label));
		}
	}
	img.display();
}

inline void CGraphImage3D::display()
{
	///we choose an intermediate layer	
	///dont forget to erase it ;)
	m_imagen[m_lays / 2]->display();
}

CGraphImage3D::iterator* CGraphImage3D::begin()
{
	return m_ibegin;
}

CGraphImage3D::iterator* CGraphImage3D::end()
{
	return m_iend;
}

void CGraphImage3D ::load_data(string filename)
{
	vector<string> file_name_vector;
	CAppUtils::set_vector_name(filename, file_name_vector);
	
	this->m_lays = file_name_vector.size();
	m_imagen = new CImg<IType>*[this->m_lays];
	
	for (int i = 0; i < this->m_lays; ++i)
	{
		m_imagen[i] = new CImg<IType>(file_name_vector[i].c_str());
		if (!i)//chekeamos las dimenciones de la primera imagen y l
		{
			m_rows = m_imagen[i]->height();
			m_cols = m_imagen[i]->width();
		}
	}
	
	m_nchannels = (int)(m_imagen[0]->spectrum() == 3);
	config(m_rows, m_cols, m_lays);
}

inline int CGraphImage3D::get_pixel(int _row, int _col, int _lay)
{
	return (int)(*m_imagen[_lay])(_col, _row, 0);
	//we return this beacuse we are testing with one channel images

	int r, g, b, pos;// , msize;//matrix size (height x widht x layers)
	unsigned int pixel = 0;
	pos = m_cols * _row + _col;
	//msize = m_height * m_width;
	r = m_imagen[_lay]->data()[pos];
	//g = m_imagenes[layer]->data()[msize + pos];
	//b = m_imagenes[layer]->data()[msize*2 + pos];
	//pixel=255<<8;
	pixel |= r;
	pixel <<= 16;//8;
	/*pixel |= g;
	pixel <<= 8;
	pixel |= b;*/
	return pixel;
}

inline void CGraphImage3D::set_pixel(int _row, int _col, int _lay, int pixel)
{
	unsigned char r, g, b;
	r = (unsigned char)(pixel >> 16);
	g = (unsigned char)(pixel >> 8);
	b = (unsigned char)(pixel);
	(*m_imagen[_lay])(_col, _row, 0) = r;
	(*m_imagen[_lay])(_col, _row, 1) = g;
	(*m_imagen[_lay])(_col, _row, 2) = b;
}

int CGraphImage3D::weight()
{
	return m_rows*m_cols*m_lays;//number of elements
}

int CGraphImage3D::area()
{
	return m_rows*m_cols*m_lays; //number of area in pixels
}

void CGraphImage3D::operator=(CGraphImage3D  &_graph)
{
	config(_graph.m_rows, _graph.m_cols, _graph.m_lays);
	for (int i = 0; i < m_rows; ++i)
		for (int j = 0; j < m_cols; ++j)
			for (int k = 0; k < m_lays; ++k)
				m_labeled_matriz[i][j][k] = _graph.m_labeled_matriz[i][j][k];
}

void CGraphImage3D::set_at(iterator& iter, NodeType& data)
{
	///TODO check whether it can be resolved in this way, iter->m_data = data;
	m_labeled_matriz[iter.m_current_row][iter.m_current_column][iter.m_current_layer].m_data = data;
}

#endif // CIMAGE3D_H
