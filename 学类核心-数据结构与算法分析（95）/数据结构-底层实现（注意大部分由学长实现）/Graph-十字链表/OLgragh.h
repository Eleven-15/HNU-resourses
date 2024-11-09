#ifndef _OLGRAGH_H
#define _OLGRAGH_H

#include"gragh.h"
#include"edge.h"
#include"vexnode.h"


template <typename E>
class OLGragh : public Graph<E> //十字链表实现
{
private:
    int numVertex,numEdge;  //顶点和边的数量
    VexNode<E> *vexarray;   //顶点数组
    int *mark;              //标记数组
    Edge **outCurr;         //保存出边链表的当前位置
    Edge **inCurr;          //保存入边链表的当前位置

    void Init(int n)        //初始化一个含n个顶点的图
    {                       //由于顶点标号类型不确定，故未初始化顶点数组，请根据标号类型手动初始化顶点数组
        numEdge=0;
        numVertex=n;
        outCurr = new Edge* [n];
        inCurr = new Edge* [n];
        mark = new int[n];
        vexarray = new VexNode<E>[n];
        for(int i=0;i<n;i++)
        {
            mark[i]=0;
            inCurr[i]=outCurr[i]=NULL;
        }
    }

public:
    OLGragh(int n) { Init(n); }
    ~OLGragh()
    {
        delete [] mark;
        delete [] outCurr;
        delete [] inCurr;
        for(int i=0;i<numVertex;i++)
        {
            Edge *next=vexarray[i].outedge;
            Edge *curr=NULL;
            while(next != NULL)
            {
                curr=next;
                next=curr->tailNext();
                delete curr;
            }
            delete curr;
        }
        delete [] vexarray;
    }

    //返回顶点和边的数量
    int n(){ return numVertex; }
    int e(){ return numEdge; }

    //返回v的第一个出边相邻顶点
    int firstOut(int v)
    {
        outCurr[v] = vexarray[v].outedge;
        if(outCurr[v])
            return outCurr[v]->head() ;
        return -1;   //无边的情况
    }

    //返回v的下一个出边相邻顶点
    int nextOut(int v)
    {
        if(!outCurr[v])
            return -1;
        outCurr[v]=outCurr[v]->tailNext();
        if(outCurr[v])
            return outCurr[v]->head();
        return -1;   //已经是最后一个顶点
    }

    //返回v的第一个入边相邻顶点
    int firstIn(int v)
    {
        inCurr[v]=vexarray[v].inedge;
        if(inCurr[v])
            return inCurr[v]->tail();
        return -1;   //无边的情况
    }

    //返回v的下一个入边相邻顶点
    int nextIn(int v)
    {
        if(!inCurr[v])
            return -1;
        inCurr[v]=inCurr[v]->headNext();
        if(inCurr[v])
            return inCurr[v]->tail();
        return -1;   //已经是最后一个顶点
    }

    int locateVex(E u)  //查找标号
    {
        int i;
        for(i=0;i<numVertex;i++)
        {
            if(vexarray[i].vex == u) return i;
        }
        return -1;     //查找失败的情况
    }

    E getVex(int v) //返回标号
    {
        return vexarray[v].vex;
    }

    void putVex(int v,E value) //设置标号
    {
        vexarray[v].vex=value;
    }

    //建立，删除边
    void setEdge(int v1,int v2,int wght=1)
    {
        vexarray[v1].outedge=vexarray[v2].inedge=new Edge(v1,v2,vexarray[v1].outedge,vexarray[v2].inedge,wght);
        numEdge++;
    }

    void delEdge(int v1,int v2)   //删除边后对应顶点的tmp指针失效,next函数不能返回正确的结果，应重新使用first
    {
        outCurr[v1]=inCurr[v2]=NULL; //防止出现野指针
        Edge *del=NULL;
        Edge *curr=NULL;
        Edge *next=vexarray[v1].outedge;
        while(next != NULL)       //从v1的边中删除
        {
            if(next->head()==v2)
            {
                del=next;
                if(curr==NULL)  //<v1,v2>是v1的第一条出边的情况
                    vexarray[v1].outedge=del->tailNext();
                else
                    curr->setTailp(del->tailNext());
            }
            curr=next;
            next=curr->tailNext();
        }
        curr=NULL;
        next=vexarray[v2].inedge;
        while(next != NULL)       //从v2的边中删除
        {
            if(next->tail()==v1)
            {
                del=next;
                if(curr==NULL)  //<v1,v2>是v2的第一条入边的情况
                    vexarray[v2].inedge=del->headNext();
                else
                    curr->setHeadp(del->headNext());
            }
            curr=next;
            next=curr->headNext();
        }
        if(del != NULL)
            numEdge--;
        delete del;
    }

    int weight(int v1, int v2)  //获取给定边的权值
    {
        Edge *curr=vexarray[v1].outedge;
        while(curr!=NULL)
        {
            if(curr->head() == v2)
                return curr->weight();
            curr=curr->tailNext();
        }
        return 0;
    }

    virtual int getMark(int v) //获取标记
    {
        return mark[v];
    }

    virtual void setMark(int v, int value) //设置标记
    {
        mark[v]=value;
    }
};

#endif
