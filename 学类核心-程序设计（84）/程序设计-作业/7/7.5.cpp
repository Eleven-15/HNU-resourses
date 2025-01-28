//激光镜像问题的解法，供大家参考

#include <iostream>
using namespace std;


//定义了用于表示单元格的类
class unit{
public:
    bool isEmpty;//true表示该单元格为透明，false表示该单元格为不透明
    int fx[2][2];//分别记录当前单元格四个方向激光穿越的次数
    unit(){//利用构造函数完成单元格的初始化
        fx[0][0]=fx[0][1]=fx[1][0]=fx[1][1]=0;
        isEmpty=true;
    }
};

//小技巧：光线的发射方向利用dx（行）和dy（列）两个增量
//东北方向: dx=1 dy=-1 对应 fx[1,0]
//西北方向: dx=-1 dy=-1 对应 fx[0,0]
//东南方向: dx=1 dy=1 对应 fx[1,1]
//西南方向: dx=-1 dy=1 对应 fx[0,1]
//计算方法：fx[(dx+1)/2][(dy+1)/2]


//小技巧：题目中限定了n和m的最大值为1000
//我们多声明两行两列（全部设置成不透明），以便实现边界和中心单元的统一处理
unit units[1002][1002];


int main()
{
    int n,m,k;cin>>n>>m>>k;
    //将n*m阵列的外面一圈单元格全部设置成不透明
    for(int i=0;i<m+2;i++){ //第0、n+1行
        units[0][i].isEmpty=units[n+1][i].isEmpty=false;
    }
    for(int i=0;i<n+2;i++){//第0、m+1列
        units[i][0].isEmpty=units[i][m+1].isEmpty=false;
    }
    
    //输入不透明单元格行列
    for(int i=0;i<k;i++){
        int x,y;cin>>x>>y;
        units[x][y].isEmpty=false;
    }

    //输入光源
    int x,y;//当前行列
    string fx;
    cin>>x>>y>>fx;

    int dx,dy;//将方向转化成dx和dy
    if(fx=="NE"){//东北
        dx=1;dy=-1;
    }
    else if(fx=="NW"){//西北
        dx=-1;dy=-1;
    }
    else if(fx=="SE"){//东南
        dx=1;dy=1;
    }
    else{//西南
        dx=-1;dy=1;
    }

    //用于统计陷入死循环前经过了多少个单元格
    int sum=0;
    while(true){
        //该单元格发射方向经过次数为1，结束循环
        if(units[x][y].fx[(dx+1)/2][(dy+1)/2]!=0) break; 
        
        //设置对应方向的经过次数为1
        units[x][y].fx[(dx+1)/2][(dy+1)/2]=1; 
        
        //只经过了一次，进行统计
        if(units[x][y].fx[0][0]+units[x][y].fx[0][1]+units[x][y].fx[1][0]+units[x][y].fx[1][1]==1){ 
            sum++;
        }
        
        if(units[x+dx][y+dy].isEmpty) {
            //前进方向单元格透明,发生穿越
            x+=dx;
            y+=dy;
        }
        else if(units[x+dx][y+dy].isEmpty==false 
                &&units[x+dx][y].isEmpty==false
                &&units[x][y+dy].isEmpty==false ) {
            //前进方向上三个单元格都不透明,发生反射
            dx=-dx;
            dy=-dy;
        }
        else if(units[x+dx][y+dy].isEmpty==false 
                &&units[x+dx][y].isEmpty==false ) {
            //x方向发生发射
            y+=dy;
            dx=-dx;
        }
        else if(units[x+dx][y+dy].isEmpty==false //折射
                &&units[x][y+dy].isEmpty==false ) {
            //y方向发生发射
            x+=dx;
            dy=-dy;
        }
        else{ //反射
            dx=-dx;
            dy=-dy;
        }
    }
    cout<<sum;
    return 0;
}
