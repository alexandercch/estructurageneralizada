#ifndef CNODE_H
#define CNODE_H
#define OUT_OF_REGION -5

#define DEFAULT_LABEL_VALUE -1
#define DEFAULT_AREA_VALUE 1.0
#define DEFAULT_VISITED_VALUE false

#define INVALID_NEIGHBOR_LABEL_VALUE -2

class CNode
{
public:
	typedef int NodeType;
    CNode();
    CNode(const CNode &_node );
    CNode(NodeType _data);
    virtual ~CNode();

    void operator=(CNode &_node);

	NodeType m_data;
    bool    m_visited;
    int     m_label;//will hold the label number assigned
    float   m_area;
protected:
private:
};

CNode::CNode():m_visited(DEFAULT_VISITED_VALUE), m_label(DEFAULT_LABEL_VALUE), m_area(DEFAULT_AREA_VALUE)
{
}

CNode::CNode(NodeType _data):m_visited(DEFAULT_VISITED_VALUE), m_label(DEFAULT_LABEL_VALUE), m_area(DEFAULT_AREA_VALUE)
{
}

CNode::CNode(const CNode &_node ):m_data(_node.m_data),m_visited(_node.m_visited),m_label(_node.m_label), m_area(_node.m_area)
{
}

void CNode::operator=(CNode &_node)
{
    m_data      = _node.m_data;
    m_visited   = _node.m_visited;
    m_label     = _node.m_label;
    m_area      = _node.m_area;
}

CNode::~CNode()
{
    //dtor
}

#endif // CNODE_H
