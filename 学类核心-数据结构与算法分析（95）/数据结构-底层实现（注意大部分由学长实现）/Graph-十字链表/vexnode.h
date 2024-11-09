#ifndef _VEXNODE_H
#define _VEXNODE_H

template <typename E>   //顶点类
class VexNode
{
public:
    E vex;           //标号
    Edge *outedge;   //储存出边
    Edge *inedge;    //储存入边
    VexNode()
    {
        outedge=inedge=NULL;
    }
};

#endif
