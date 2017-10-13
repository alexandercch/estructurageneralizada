/**
    Seminario de Tesis 10
    CColor.h
    Purpose: This is an abstrac class to define a generic interator for the 3 3 structual contexts.

    @author Alex Ccacyahuillca
    @version 1.0 04/015
*/
#ifndef CGRAPHITERATOR_H_INCLUDED
#define CGRAPHITERATOR_H_INCLUDED

class CGraphIterator
{
public:
    CGraphIterator();
    virtual ~CGraphIterator();

    //overloaded operators
    void operator=(CGraphIterator *iter);
    void operator=(CGraphIterator iter);
    bool operator==(CGraphIterator *iter);
    bool operator!=(CGraphIterator *iter);
    void operator++(int);
};

CGraphIterator::CGraphIterator()
{
};

CGraphIterator::~CGraphIterator()
{
};

#endif // CGRAPHITERATOR_H_INCLUDED
