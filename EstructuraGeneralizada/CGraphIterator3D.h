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

#include "CGraph.h"
#include "CGraphIterator.h"

//this arrays are for the navigation through neigbours around a cell
int row_step3d[6]= { 0,-1, 0, 1, 0, 0};
int col_step3d[6]= { 0, 0,-1, 0, 1, 0};
int lay_step3d[6]= {-1, 0, 0, 0, 0, 1};

#define RS3D row_step3d
#define CS3D col_step3d
#define LS3D lay_step3d


class CGraphImage3D;

class CGraphIterator3D:public CGraphIterator
{
public:
    typedef CGraph::node node;
    typedef CGraphIterator3D self;

	//members
	int m_current_row, m_prowbegin;
	int m_current_column;
	int m_current_layer;
	int m_total_rows;
	int m_total_columns;
	int m_total_layers;

	CGraphImage3D *m_pgraph;

    //overloaded operators
    void operator=(CGraphIterator3D *iter);
    void operator=(CGraphIterator3D iter);
    void operator++(int);
    bool operator==(CGraphIterator3D *iter);
    bool operator!=(CGraphIterator3D *iter);
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
    //node* neighbor_node_at(int i);

    /**
        return the neighbor iterator at position i
        @param i neighbor number, see CGraphImage3D::number of neighbors
    */
    self neighbor_at(int i);

protected:
private:
};


CGraphIterator3D::CGraphIterator3D()
{
};

CGraphIterator3D::~CGraphIterator3D()
{
};

void CGraphIterator3D::operator=(CGraphIterator3D iter)
{
	m_total_rows = iter.m_total_rows;
	m_total_columns = iter.m_total_columns;
	m_total_layers = iter.m_total_layers;

	m_current_row = iter.m_current_row;
	m_current_column = iter.m_current_column;
	m_current_layer = iter.m_current_layer;

	m_prowbegin = iter.m_current_row;
	m_pgraph = iter.m_pgraph;
};

void CGraphIterator3D::operator=(CGraphIterator3D *iter)
{
	m_total_rows = iter->m_total_rows;
	m_total_columns = iter->m_total_columns;
	m_total_layers = iter->m_total_layers;

	m_current_row = iter->m_current_row;
	m_current_column = iter->m_current_column;
	m_current_layer = iter->m_current_layer;

	m_prowbegin = iter->m_current_row;
	m_pgraph = iter->m_pgraph;
};

bool CGraphIterator3D::operator==(CGraphIterator3D *iter)
{
	return m_current_row == iter->m_current_row;// && m_pcol==iter->m_pcol;
};

bool CGraphIterator3D::operator!=(CGraphIterator3D *iter)
{
	return !(m_current_row == iter->m_current_row);// && m_pcol==iter->m_pcol);
};

void CGraphIterator3D::operator++(int)
{
	//detect if current layer is in the final layer
	if (++m_current_layer < m_total_layers)
		return;//if not go to next layer
	if (++m_current_column < m_total_columns) {
		m_current_layer = 0;//cout<<"*";
		return;//if not go to next column
	}//if it is go the next row and column to the initial column
	if (++m_current_row < m_total_rows) {
		m_current_column = 0;
		m_current_layer = 0;
	}
};


CGraphIterator3D::node* CGraphIterator3D::operator->()
{
	return &(m_pgraph->m_labeled_matriz[m_current_row][m_current_column][m_current_layer]);
};

CGraphIterator3D::node* CGraphIterator3D::operator*()
{
	return &(m_pgraph->m_labeled_matriz[m_current_row][m_current_column][m_current_layer]);
};

///TODO fix width pointer distance (unfinished method)
/*
typename CGraphIterator3D::node* CGraphIterator3D::neighbor_node_at(int i)
{

return &((m_current_row + RS3D[i]) + CS3D[i]);
};*/

CGraphIterator3D::self CGraphIterator3D::neighbor_at(int i)
{
	self neighbor;

	neighbor.m_total_rows = m_total_rows;
	neighbor.m_total_columns = m_total_columns;
	neighbor.m_total_layers = m_total_layers;

	neighbor.m_current_row = m_current_row + RS3D[i];
	neighbor.m_current_column = m_current_column + CS3D[i];
	neighbor.m_current_layer = m_current_layer + LS3D[i];

	neighbor.m_pgraph = m_pgraph;

	return neighbor;
};


inline int CGraphIterator3D::getData()
{
	return  m_pgraph->get_pixel(m_current_row, m_current_column, m_current_layer);
}

inline float CGraphIterator3D::getArea()
{
	return m_pgraph->m_labeled_matriz[m_current_row][m_current_column][m_current_layer].m_area;
}

inline void CGraphIterator3D::setData(int data)
{
	m_pgraph->set_pixel(m_current_row, m_current_column, m_current_layer, data);
}

inline bool CGraphIterator3D::isInside()
{
	return	0 <= m_current_row && m_current_row < m_total_rows &&
		0 <= m_current_column && m_current_column < m_total_columns &&
		0 <= m_current_layer && m_current_layer < m_total_layers;
}

inline void CGraphIterator3D::print()
{
	cout << m_current_row << " " << m_current_column << " " << m_current_layer << " - "
		<< m_total_rows << " " << m_total_columns << " " << m_total_layers << endl;
}



#endif // CGRAPHITERATOR3D_H
