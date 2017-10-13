/**
    Seminario de Tesis 10
    CGraphIteratorND.h
    Purpose: Is the iterator of CGraphMeshND, inherits from CGraphIterator
        in order to be a compatible iteration in the generalized graph
    @author Alex Ccacyahuillca
    @version 1.0 04/015
*/

#ifndef CGRAPHITERATORND_H_INCLUDED
#define CGRAPHITERATORND_H_INCLUDED

#include "CGraph.h"
#include "CGraphIterator.h"


class CGraphMeshND;

class CGraphIteratorND:public CGraphIterator
{
public:
    typedef CGraph::node node;
    typedef CGraphIteratorND self;

    //members
    CGraphMeshND* m_pgraph;
    int m_index;

    //overloaded operators
    void operator=(CGraphIteratorND *iter);
    void operator=(CGraphIteratorND iter);
    void operator++(int);
    bool operator==(CGraphIteratorND *iter);
    bool operator!=(CGraphIteratorND *iter);
    node* operator->();
    node*& operator*();


	/**
	Methods for accesing the graph data
	*/
	int		getData();
	void	setData(int data);
	float	getArea();
	bool	isInside();
	void	print();


    //methods
    CGraphIteratorND();
    virtual ~CGraphIteratorND();

    /**
        return the neighbor node at the position i
        @param i neighbor number, see CGraphMeshND::number of neighbors
    */
    node* neighbor_node_at(int i);

    /**
        return the neighbor iterator at position i
        @param i neighbor number, see CGraphMeshND::number of neighbors
    */
    self neighbor_at(int i);

protected:
private:
};


CGraphIteratorND::CGraphIteratorND()
{
};

CGraphIteratorND::~CGraphIteratorND()
{
};

void CGraphIteratorND::operator=(CGraphIteratorND iter)
{
    m_pgraph    = iter.m_pgraph;
    m_index     = iter.m_index;
};

void CGraphIteratorND::operator=(CGraphIteratorND *iter)
{
    m_pgraph    = iter->m_pgraph;
    m_index     = iter->m_index;
};

bool CGraphIteratorND::operator==(CGraphIteratorND *iter)
{
    return m_index == iter->m_index;// && m_pgraph=iter->m_pgraph;
};

bool CGraphIteratorND::operator!=(CGraphIteratorND *iter)
{
    return m_index != iter->m_index;// || m_pgraph!=iter->m_pgraph;
};

void CGraphIteratorND::operator++(int)
{
    m_index++;
};

CGraphIteratorND::node* CGraphIteratorND::operator->()
{
    return &m_pgraph->m_nodes[m_index];
};

CGraphIteratorND::node*& CGraphIteratorND::operator*()
{
    node* p = &m_pgraph->m_nodes[m_index];
    return p;
}

inline int CGraphIteratorND::getData()
{
	return m_pgraph->m_nodes[m_index].m_data;
}

inline void CGraphIteratorND::setData(int data)
{
	m_pgraph->m_nodes[iter.m_index].m_data = data;
}

inline float CGraphIteratorND::getArea()
{
	return m_pgraph->m_nodes[m_index].m_area;
}

inline bool CGraphIteratorND::isInside()
{
	return  m_index < m_pgraph->m_size;
}

inline void CGraphIteratorND::print()
{
	cout << m_index << endl;
}

CGraphIteratorND::node* CGraphIteratorND::neighbor_node_at(int i)
{
    ///TODO fix width pointer distance
    return &m_pgraph->m_nodes[m_pgraph->m_adj_list[m_index][i]];
};

CGraphIteratorND::self CGraphIteratorND::neighbor_at(int i)
{
    self neighbor;
    neighbor.m_pgraph   = m_pgraph;
    neighbor.m_index    = m_pgraph->m_adj_list[m_index][i];
    return neighbor;
};

#endif // CGRAPHITERATORND_H_INCLUDED
