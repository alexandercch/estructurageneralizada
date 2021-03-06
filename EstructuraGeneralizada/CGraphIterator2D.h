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

#include "CGraph.h"
#include "CGraphIterator.h"

//this arrays are for the navigation through neigbours around a cell
int row_step2d[4]= {-1, 0, 1, 0};
int col_step2d[4]= { 0, 1, 0,-1};

#define RS2D row_step2d
#define CS2D col_step2d

class CGraphImage2D;

class CGraphIterator2D:public CGraphIterator
{
public:
    typedef CGraph::node node;
    typedef CGraphIterator2D self;

    //members
    int m_current_row, m_prowbegin;
    int m_current_column;
    int m_total_rows;
    int m_total_columns;

	CGraphImage2D *m_pgraph;

    //overloaded operators
    void operator=(CGraphIterator2D *iter);
    void operator=(CGraphIterator2D iter);
    void operator++(int);
    bool operator==(CGraphIterator2D *iter);
    bool operator!=(CGraphIterator2D *iter);
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
    //node* neighbor_node_at(int i);

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



CGraphIterator2D::CGraphIterator2D()
{
};


CGraphIterator2D::~CGraphIterator2D()
{
};


void CGraphIterator2D::operator=(CGraphIterator2D iter)
{
	m_total_rows = iter.m_total_rows;
	m_total_columns = iter.m_total_columns;

	m_current_row = iter.m_current_row;
	m_current_column = iter.m_current_column;

	m_prowbegin = iter.m_current_row;
	m_pgraph = iter.m_pgraph;
};


void CGraphIterator2D::operator=(CGraphIterator2D *iter)
{
	m_total_rows = iter->m_total_rows;
	m_total_columns = iter->m_total_columns;

	m_current_row = iter->m_current_row;
	m_current_column = iter->m_current_column;

	m_pgraph = iter->m_pgraph;
	m_prowbegin = iter->m_current_row;
};


bool CGraphIterator2D::operator==(CGraphIterator2D *iter)
{
	return m_current_row == iter->m_current_row;
};


bool CGraphIterator2D::operator!=(CGraphIterator2D *iter)
{
	return !(m_current_row == iter->m_current_row);
};



void CGraphIterator2D::operator++(int)
{
	//check column counter doesnot exceds the number of columns
	if (++m_current_column < m_total_columns) {
		return;//enough for now
	}//if it exceds go the next row and column equals to zero
	if (++m_current_row < m_total_rows) {
		m_current_column = 0;
	}
};


CGraphIterator2D::node* CGraphIterator2D::operator->()
{
	return &(m_pgraph->m_labeled_matriz[m_current_row][m_current_column]);
};


CGraphIterator2D::node* CGraphIterator2D::operator*()
{
	return &m_pgraph->m_labeled_matriz[m_current_row][m_current_column];
};

///TODO fix width pointer distance(unfinished method)
/*
typename CGraphIterator2D::node* CGraphIterator2D::neighbor_node_at(int i)
{
///TODO fix width pointer distance
return (*(m_current_row + RS2D[i]) + CS2D[i]);
};
*/


CGraphIterator2D::self CGraphIterator2D::neighbor_at(int i)
{
	self neighbor;

	neighbor.m_total_rows = m_total_rows;
	neighbor.m_total_columns = m_total_columns;

	neighbor.m_current_row = m_current_row + RS2D[i];
	neighbor.m_current_column = m_current_column + CS2D[i];

	neighbor.m_pgraph = m_pgraph;

	return neighbor;
};


int CGraphIterator2D::getData()
{
	return  m_pgraph->get_pixel(m_current_row, m_current_column);
}


float CGraphIterator2D::getArea()
{
	return m_pgraph->m_labeled_matriz[m_current_row][m_current_column].m_area;
}


void CGraphIterator2D::setData(int data)
{
	m_pgraph->set_pixel(m_current_row, m_current_column, data);
}


inline bool CGraphIterator2D::isInside()
{
	return 0 <= m_current_row && m_current_row < m_total_rows && 0 <= m_current_column && m_current_column < m_total_columns;
}



inline void CGraphIterator2D::print()
{
	cout << m_current_row << " " << m_current_column << " - " << m_total_rows << " " << m_total_columns << endl;
}


#endif // CGRAPHITERATOR2D_H_INCLUDED
