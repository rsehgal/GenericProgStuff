#ifndef _MYTYPES_H_
#define _MYTYPES_H_

template<class T>
class MyTypes{
    T fVar;
public:
    MyTypes(){}
    ~MyTypes(){}
    T Get(){return fVar;}

};

#endif