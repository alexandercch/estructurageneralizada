/**
    Seminario de Tesis 10
    CGraphImage2D.h
    Purpose: Is a child class from CGraph will hold a 2D matrix

    @author Alex Ccacyahuillca
    @version 1.0 04/015
*/

#ifndef CGRAPHIMAGE2D_H_INCLUDED
#define CGRAPHIMAGE2D_H_INCLUDED
#include "CGraph.h"
#include "CGraphIterator2D.h"

#define NUMBER_OF_NEIGHBOURS_2D 4

template<class T>
class CGraphImage2D
{
public:
	typedef unsigned char IType;
    typedef CGraphIterator2D<T> iterator;
    typedef typename CGraph<T>::node node;

    //members
    node **m_labeled_matriz;//this will hold the segmented data
	CImg<IType> *m_imagen;//this will hold the actual data

    int m_rows, m_cols;
    int m_number_of_neighbors;

	int m_nchannels;

    //methods
    CGraphImage2D ();
    virtual ~CGraphImage2D ();

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
        @param _rows the number of rows of the 2D matrix graph
        @param _cols the number of cols of the 2D matrix graph
    */
    void config(int _rows, int _cols);

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
	int get_pixel(int _row, int _col);

	/**
	Set actual data from the graph
	@param _row the row in the image
	@param _col the column in the image
	@param pixel the colorto go into the image
	*/
	void set_pixel(int _row, int _col, int pixel);

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
    void set_at(iterator& iter, T& data);

    /**
        Copy all data from other graph, first sets to the new dimensions
        and begin the copy.
        @param _graph pointer to a same class graph
    */
    void operator=(CGraphImage2D &_graph);

protected:
private:
    iterator *m_ibegin, *m_iend;
    //end pointer
};

template<class T>
CGraphImage2D<T>::CGraphImage2D ():
m_number_of_neighbors(NUMBER_OF_NEIGHBOURS_2D),
m_ibegin(new iterator),
m_iend(new iterator),
m_rows(0),
m_cols(0)
{
}

template<class T>
CGraphImage2D <T>::~CGraphImage2D ()
{
    //dtor
    for(int i = 0; i < m_rows; ++i)
        delete[] m_labeled_matriz[i];
    delete[] m_labeled_matriz;
}

template<class T>
void CGraphImage2D <T>::config(int _rows, int _cols)
{
	m_labeled_matriz = new node*[_rows];
	for (int i = 0; i < _rows; ++i)
	{
		m_labeled_matriz[i] = new node[_cols];
	}
    //cout<<"iterators configuration!"<<endl;
    m_ibegin->m_current_row		= 0;
    m_ibegin->m_current_column	= 0;
    m_ibegin->m_total_rows		= m_rows;
    m_ibegin->m_total_columns	= m_cols;

	m_ibegin->m_pgraph = this;

    m_iend->m_current_row		= m_rows;
    m_iend->m_current_column	= m_cols;  
	
    //cout<<"success!"<<endl;
}

template<class T>
typename CGraphImage2D<T>::iterator* CGraphImage2D<T>::begin()
{
    return m_ibegin;
}

template<class T>
typename CGraphImage2D<T>::iterator* CGraphImage2D<T>::end()
{
    return m_iend;
}

template<class T>
void CGraphImage2D <T>::load_data(string filename)
{
	m_imagen = new CImg<IType>(filename.c_str());
	m_rows = m_imagen->height();
	m_cols = m_imagen->width();
	m_nchannels = (int)(m_imagen->spectrum() == 3);
	
	config(m_rows, m_cols);
}

template<class T>
int CGraphImage2D<T>::weight()
{
    return m_rows*m_cols; //number of elements
}

template<class T>
int CGraphImage2D<T>::area()
{
    return m_rows*m_cols; //number of area in pixels
}

template<class T>
void CGraphImage2D<T>::operator=(CGraphImage2D <T> &_graph)
{
    config(_graph.m_rows, _graph.m_cols);//config reset/set size of the matrix
    for(int i=0; i< m_rows; ++i)
        for(int j=0; j< m_cols; ++j)
            m_labeled_matriz[i][j] = _graph.m_labeled_matriz[i][j];
}

template<class T>
void CGraphImage2D<T>::set_at(iterator& iter, T& data)
{    
    iter->m_data = data;
}

template<class T>
int CGraphImage2D<T>::get_pixel(int _row, int _col)
{	
	int r, g, b;
	int pixel = 0;
	r = (int)(*m_imagen)(_col, _row, 0, 0);
	g = (int)(*m_imagen)(_col, _row, 0, 1 * m_nchannels);
	b = (int)(*m_imagen)(_col, _row, 0, 2 * m_nchannels);
	pixel |= r;
	pixel <<= 8;
	pixel |= g;
	pixel <<= 8;
	pixel |= b;
	return pixel;
}

template<class T>
void CGraphImage2D<T>::set_pixel(int _row, int _col, int pixel)
{
	unsigned char r, g, b;
	r = (unsigned char)(pixel >> 16);
	g = (unsigned char)(pixel >> 8);
	b = (unsigned char)(pixel);
	(*m_imagen)(_col, _row, 0) = r;
	(*m_imagen)(_col, _row, 1 * m_nchannels) = g;
	(*m_imagen)(_col, _row, 2 * m_nchannels) = b;
}

template<class T>
inline void CGraphImage2D<T>::displayLabeledGraph()
{
	CColor color;
	CImage img(m_cols, m_rows);
	for (int row = 0; row < m_rows; row++) {
		for (int col = 0; col < m_cols; col++) {
			img.set_pixel(row, col, color(m_labeled_matriz[row][col].m_label));
		}
	}
	img.display();
}

template<class T>
void CGraphImage2D<T>::display()
{
	m_imagen->display();
}

#endif // CGRAPHIMAGE2D_H_INCLUDED