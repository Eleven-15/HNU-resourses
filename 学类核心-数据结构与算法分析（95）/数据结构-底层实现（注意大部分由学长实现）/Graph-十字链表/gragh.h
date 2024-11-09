#ifndef _GRAGH_H
#define _GRAGH_H

template <typename E>    //E为标号的类型
class Graph{
public:
    Graph() {}           //构造函数
    virtual ~Graph() {}  //析构

    //返回顶点和边的数量
    virtual int n() = 0;  //顶点
    virtual int e() = 0;  //边

    //返回v的第一个相邻顶点的下标
    virtual int firstOut(int v) = 0;  //出边
    virtual int firstIn(int v) = 0;   //入边

    //返回v的下一个相邻顶点的下标
    virtual int nextOut(int v) = 0;
    virtual int nextIn(int v) = 0;

    //查找，设置，获取顶点的标号
    virtual int locateVex(E u) =0; //查找标号
    virtual E getVex(int v)=0;
    virtual void putVex(int v,E value) =0;

    //建立，删除边,获取边的权值
    virtual void setEdge(int v1,int v2,int wght) = 0;
    virtual void delEdge(int v1,int v2) = 0;
    virtual int weight(int v1, int v2) =0;

    //设置，获取标记
    virtual int getMark(int v) =0;
    virtual void setMark(int v, int value) =0;
};

#endif
