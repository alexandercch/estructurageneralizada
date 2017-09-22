/**
    Seminario de Tesis 10
    CGraphIterator2D.h
    Purpose: Is the iterator of CGraphImage2D, inherits from CGraphIterator
        in order to be a compatible iteration in the generalized graph
    @author Alex Ccacyahuillca
    @version 1.0 04/015
*/

#ifndef CGRAPHITERATOR2D_H_INCLUDED
#define CGRAPHITERATOR2D_H_INCLUDED

#include "CGraphIterator.h"

//this arrays are for the navigation through neigbours around a cell
int row_step2d[4]= {-1, 0, 1, 0};
int col_step2d[4]= { 0, 1, 0,-1};

#define RS2D row_step2d
#define CS2D col_step2d

template<class T>
class CGraphImage2D;

template< class T>
class CGraphIterator2D:public CGraphIterator<T>
{
public:
    typedef typename CGraphImage2D<T>::node node;
    typedef CGraphIterator2D<T> self;

    //members
    int m_current_row, m_prowbegin;
    int m_current_column;
    int m_total_rows;
    int m_total_columns;

	CGraphImage2D<T> *m_pgraph;

    //overloaded operators
    void operator=(CGraphIterator2D<T> *iter);
    void operator=(CGraphIterator2D<T> iter);
    void operator++(int);
    bool operator==(CGraphIterator2D<T> *iter);
    bool operator!=(CGraphIterator2D<T> *iter);
    node* operator->();
    node* operator*();

	/**
		Methods for accesing the graph data 
	*/
	int		getData();
	void	setData(int data);
	float	getArea();
	bool	isInside();
	
	/**
		Contructor and desctructor, news and deletes
	*/
    CGraphIterator2D();
    virtual ~CGraphIterator2D();

    /**
        return the neighbor node at the position i
        @param i neighbor number, see CGraphImage2D::number of neighbors
    */
    node* neighbor_node_at(int i);

    /**
        return the neighbor iterator at position i
        @param i neighbor number, see CGraphImage2D::number of neighbors
    */
    self neighbor_at(int i);

	/**
		Debuggin method...
	*/
	void print();

protected:
private:
};

template< class T>
CGraphIterator2D<T>::CGraphIterator2D()
{
};

template< class T>
CGraphIterator2D<T>::~CGraphIterator2D()
{
};

template< class T>
void CGraphIterator2D<T>::operator=(CGraphIterator2D<T> iter)
{
    m_total_rows	= iter.m_total_rows;
    m_total_columns	= iter.m_total_columns;

    m_current_row	= iter.m_current_row;
    m_current_column= iter.m_current_column;

    m_prowbegin		= iter.m_current_row;
	m_pgraph		= iter.m_pgraph;
};

template< class T>
void CGraphIterator2D<T>::operator=(CGraphIterator2D<T> *iter)
{	
    m_total_rows	= iter->m_total_rows;
    m_total_columns = iter->m_total_columns;

    m_current_row	= iter->m_current_row;
    m_current_column= iter->m_current_column;

	m_pgraph		= iter->m_pgraph;
    m_prowbegin		= iter->m_current_row;	
};

template< class T>
bool CGraphIterator2D<T>::operator==(CGraphIterator2D<T> *iter)
{
    return m_current_row == iter->m_current_row;
};

template< class T>
bool CGraphIterator2D<T>::operator!=(CGraphIterator2D<T> *iter)
{
	return !(m_current_row == iter->m_current_row);
};


template< class T>
void CGraphIterator2D<T>::operator++(int)
{
    //check column counter doesnot exceds the number of columns
    if( ++m_current_column < m_total_columns){
        return;//enough for now
    }//if it exceds go the next row and column equals to zero
    if (++m_current_row < m_total_rows){
        m_current_column = 0;
    }
};

template< class T>
typename CGraphIterator2D<T>::node* CGraphIterator2D<T>::operator->()
{
    return &(m_pgraph->m_labeled_matriz[m_current_row][m_current_column]);
};

template< class T>
typename CGraphIterator2D<T>::node* CGraphIterator2D<T>::operator*()
{
	return &m_pgraph->m_labeled_matriz[m_current_row][m_current_column];
};

template< class T>
typename CGraphIterator2D<T>::node* CGraphIterator2D<T>::neighbor_node_at(int i)
{
    ///TODO fix width pointer distance
    return (*(m_current_row + RS2D[i]) + CS2D[i]);
};

template< class T>
typename CGraphIterator2D<T>::self CGraphIterator2D<T>::neighbor_at(int i)
{
    self neighbor;    

    neighbor.m_total_rows		= m_total_rows;
    neighbor.m_total_columns	= m_total_columns;

    neighbor.m_current_row		= m_current_row + RS2D[i];
    neighbor.m_current_column	= m_current_column + CS2D[i];

	neighbor.m_pgraph			= m_pgraph;

    return neighbor;
};

template<class T>
inline int CGraphIterator2D<T>::getData()
{	
	return  m_pgraph->get_pixel(m_current_row, m_current_column);
}

template<class T>
inline float CGraphIterator2D<T>::getArea()
{
	return m_pgraph->m_labeled_matriz[m_current_row][m_current_column].m_area;
}

template<class T>
inline void CGraphIterator2D<T>::setData(int data)
{
	m_pgraph->set_pixel(m_current_row, m_current_column, data);
}

template<class T>
inline bool CGraphIterator2D<T>::isInside()
{
	return 0 <= m_current_row && m_current_row < m_total_rows && 0<= m_current_column && m_current_column < m_total_columns;
}


template<class T>
inline void CGraphIterator2D<T>::print()
{
	cout << m_current_row << " " << m_current_column << " - " << m_total_rows << " " << m_total_columns << endl;
}


#endif // CGRAPHITERATOR2D_H_INCLUDED
