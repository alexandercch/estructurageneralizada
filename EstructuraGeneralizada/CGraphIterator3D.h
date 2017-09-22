/**
    Seminario de Tesis 10
    CGraphIterator3D.h
    Purpose: Is the iterator of CGraphImage3D, inherits from CGraphIterator
        in order to be a compatible iteration in the generalized graph
    @author Alex Ccacyahuillca
    @version 1.0 04/015
*/

#ifndef CGRAPHITERATOR3D_H
#define CGRAPHITERATOR3D_H

#include "CGraphIterator.h"

//this arrays are for the navigation through neigbours around a cell
int row_step3d[6]= { 0,-1, 0, 1, 0, 0};
int col_step3d[6]= { 0, 0,-1, 0, 1, 0};
int lay_step3d[6]= {-1, 0, 0, 0, 0, 1};

#define RS3D row_step3d
#define CS3D col_step3d
#define LS3D lay_step3d

template<class T>
class CGraphImage3D;

template< class T>
class CGraphIterator3D:public CGraphIterator<T>
{
public:
    typedef typename CGraphImage3D<T>::node node;
    typedef CGraphIterator3D<T> self;

	//members
	int m_current_row, m_prowbegin;
	int m_current_column;
	int m_current_layer;
	int m_total_rows;
	int m_total_columns;
	int m_total_layers;

	CGraphImage3D<T> *m_pgraph;

    //overloaded operators
    void operator=(CGraphIterator3D<T> *iter);
    void operator=(CGraphIterator3D<T> iter);
    void operator++(int);
    bool operator==(CGraphIterator3D<T> *iter);
    bool operator!=(CGraphIterator3D<T> *iter);
    node* operator->();
    node* operator*();

	/**
	Methods for accesing the graph data
	*/
	int		getData();
	void	setData(int data);
	float	getArea();
	bool	isInside();
	void	print();

    /**
		Contructor and desctructor, news and deletes
	*/
    CGraphIterator3D();
    virtual ~CGraphIterator3D();

    /**
        return the neighbor node at the position i
        @param i neighbor number, see CGraphImage3D::number of neighbors
    */
    node* neighbor_node_at(int i);

    /**
        return the neighbor iterator at position i
        @param i neighbor number, see CGraphImage3D::number of neighbors
    */
    self neighbor_at(int i);

protected:
private:
};

template< class T>
CGraphIterator3D<T>::CGraphIterator3D()
{
};

template< class T>
CGraphIterator3D<T>::~CGraphIterator3D()
{
};

template< class T>
void CGraphIterator3D<T>::operator=(CGraphIterator3D<T> iter)
{
	m_total_rows	= iter.m_total_rows;
	m_total_columns = iter.m_total_columns;
	m_total_layers	= iter.m_total_layers;

	m_current_row	= iter.m_current_row;
	m_current_column= iter.m_current_column;
	m_current_layer = iter.m_current_layer;

	m_prowbegin		= iter.m_current_row;
	m_pgraph		= iter.m_pgraph;
};
template< class T>
void CGraphIterator3D<T>::operator=(CGraphIterator3D<T> *iter)
{
	m_total_rows	= iter->m_total_rows;
	m_total_columns = iter->m_total_columns;
	m_total_layers	= iter->m_total_layers;

	m_current_row	= iter->m_current_row;
	m_current_column= iter->m_current_column;
	m_current_layer = iter->m_current_layer;

	m_prowbegin		= iter->m_current_row;
	m_pgraph		= iter->m_pgraph;
};

template< class T>
bool CGraphIterator3D<T>::operator==(CGraphIterator3D<T> *iter)
{
    return m_current_row == iter->m_current_row;// && m_pcol==iter->m_pcol;
};

template< class T>
bool CGraphIterator3D<T>::operator!=(CGraphIterator3D<T> *iter)
{
    return !(m_current_row == iter->m_current_row);// && m_pcol==iter->m_pcol);
};

template< class T>
void CGraphIterator3D<T>::operator++(int)
{
    
    //detect if current layer is in the final layer
    if( ++m_current_layer < m_total_layers)
        return;//if not go to next layer
    if( ++m_current_column < m_total_columns){
        m_current_layer = 0;//cout<<"*";
        return;//if not go to next column
    }//if it is go the next row and column to the initial column
    if (++m_current_row < m_total_rows){
        m_current_column = 0;
        m_current_layer = 0;        
    }
};

template< class T>
typename CGraphIterator3D<T>::node* CGraphIterator3D<T>::operator->()
{
    return &(m_pgraph->m_labeled_matriz[m_current_row][m_current_column][m_current_layer]);
};

template< class T>
typename CGraphIterator3D<T>::node* CGraphIterator3D<T>::operator*()
{
	return &(m_pgraph->m_labeled_matriz[m_current_row][m_current_column][m_current_layer]);
};

template< class T>
typename CGraphIterator3D<T>::node* CGraphIterator3D<T>::neighbor_node_at(int i)
{
    ///TODO fix width pointer distance
    return ((*(m_prow + RS3D[i]) + CS3D[i]));
};

template< class T>
typename CGraphIterator3D<T>::self CGraphIterator3D<T>::neighbor_at(int i)
{
    self neighbor;

	neighbor.m_total_rows	= m_total_rows;
	neighbor.m_total_columns= m_total_columns;
	neighbor.m_total_layers = m_total_layers;

	neighbor.m_current_row		= m_current_row + RS3D[i];
	neighbor.m_current_column	= m_current_column + CS3D[i];
	neighbor.m_current_layer	= m_current_layer + LS3D[i];

	neighbor.m_pgraph = m_pgraph;

	return neighbor;
};


template<class T>
inline int CGraphIterator3D<T>::getData()
{
	return  m_pgraph->get_pixel(m_current_row, m_current_column, m_current_layer);
}

template<class T>
inline float CGraphIterator3D<T>::getArea()
{
	return m_pgraph->m_labeled_matriz[m_current_row][m_current_column][m_current_layer].m_area;
}

template<class T>
inline void CGraphIterator3D<T>::setData(int data)
{
	m_pgraph->set_pixel(m_current_row, m_current_column, m_current_layer, data);
}

template<class T>
inline bool CGraphIterator3D<T>::isInside()
{
	return	0 <= m_current_row && m_current_row < m_total_rows &&
			0 <= m_current_column && m_current_column < m_total_columns &&
			0 <= m_current_layer && m_current_layer < m_total_layers;
}

template<class T>
inline void CGraphIterator3D<T>::print()
{
	cout	<< m_current_row << " " << m_current_column << " " << m_current_layer << " - "
			<< m_total_rows << " " << m_total_columns << " " << m_total_layers << endl;
}









#endif // CGRAPHITERATOR3D_H
