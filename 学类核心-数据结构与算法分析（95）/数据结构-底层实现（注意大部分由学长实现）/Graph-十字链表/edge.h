#ifndef _EDGE_H
#define _EDGE_H

class Edge            //边类
{
private:
    int tailnum,headnum;//弧头弧尾的下标
    int _weight;        //权值
    Edge *tailp;        //指向tail相同的下一条边
    Edge *headp;        //指向head相同的下一条边
public:
    Edge(int tl,int hd,Edge *t0p,Edge *hp,int wgt=1)
    {
        tailnum=tl;
        headnum=hd;
        tailp=t0p;
        headp=hp;
        _weight=wgt;
    }
    void setWeight(int wgt) { _weight=wgt; } //更改权值
    void setTailp(Edge *tp) { tailp=tp; }  //重设tail的下一条出边
    void setHeadp(Edge *hp) { headp=hp; }    //重设head的下一条入边
    int weight() { return _weight; }         //返回权值
    int tail() { return tailnum; }           //返回弧尾
    int head() { return headnum; }           //返回弧头
    Edge* tailNext() { return tailp; }       //弧尾的下一条出边
    Edge* headNext() { return headp; }       //弧头的下一条入边
};

#endif
