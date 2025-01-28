//���⾵������Ľⷨ������Ҳο�

#include <iostream>
using namespace std;


//���������ڱ�ʾ��Ԫ�����
class unit{
public:
    bool isEmpty;//true��ʾ�õ�Ԫ��Ϊ͸����false��ʾ�õ�Ԫ��Ϊ��͸��
    int fx[2][2];//�ֱ��¼��ǰ��Ԫ���ĸ����򼤹⴩Խ�Ĵ���
    unit(){//���ù��캯����ɵ�Ԫ��ĳ�ʼ��
        fx[0][0]=fx[0][1]=fx[1][0]=fx[1][1]=0;
        isEmpty=true;
    }
};

//С���ɣ����ߵķ��䷽������dx���У���dy���У���������
//��������: dx=1 dy=-1 ��Ӧ fx[1,0]
//��������: dx=-1 dy=-1 ��Ӧ fx[0,0]
//���Ϸ���: dx=1 dy=1 ��Ӧ fx[1,1]
//���Ϸ���: dx=-1 dy=1 ��Ӧ fx[0,1]
//���㷽����fx[(dx+1)/2][(dy+1)/2]


//С���ɣ���Ŀ���޶���n��m�����ֵΪ1000
//���Ƕ������������У�ȫ�����óɲ�͸�������Ա�ʵ�ֱ߽�����ĵ�Ԫ��ͳһ����
unit units[1002][1002];


int main()
{
    int n,m,k;cin>>n>>m>>k;
    //��n*m���е�����һȦ��Ԫ��ȫ�����óɲ�͸��
    for(int i=0;i<m+2;i++){ //��0��n+1��
        units[0][i].isEmpty=units[n+1][i].isEmpty=false;
    }
    for(int i=0;i<n+2;i++){//��0��m+1��
        units[i][0].isEmpty=units[i][m+1].isEmpty=false;
    }
    
    //���벻͸����Ԫ������
    for(int i=0;i<k;i++){
        int x,y;cin>>x>>y;
        units[x][y].isEmpty=false;
    }

    //�����Դ
    int x,y;//��ǰ����
    string fx;
    cin>>x>>y>>fx;

    int dx,dy;//������ת����dx��dy
    if(fx=="NE"){//����
        dx=1;dy=-1;
    }
    else if(fx=="NW"){//����
        dx=-1;dy=-1;
    }
    else if(fx=="SE"){//����
        dx=1;dy=1;
    }
    else{//����
        dx=-1;dy=1;
    }

    //����ͳ��������ѭ��ǰ�����˶��ٸ���Ԫ��
    int sum=0;
    while(true){
        //�õ�Ԫ���䷽�򾭹�����Ϊ1������ѭ��
        if(units[x][y].fx[(dx+1)/2][(dy+1)/2]!=0) break; 
        
        //���ö�Ӧ����ľ�������Ϊ1
        units[x][y].fx[(dx+1)/2][(dy+1)/2]=1; 
        
        //ֻ������һ�Σ�����ͳ��
        if(units[x][y].fx[0][0]+units[x][y].fx[0][1]+units[x][y].fx[1][0]+units[x][y].fx[1][1]==1){ 
            sum++;
        }
        
        if(units[x+dx][y+dy].isEmpty) {
            //ǰ������Ԫ��͸��,������Խ
            x+=dx;
            y+=dy;
        }
        else if(units[x+dx][y+dy].isEmpty==false 
                &&units[x+dx][y].isEmpty==false
                &&units[x][y+dy].isEmpty==false ) {
            //ǰ��������������Ԫ�񶼲�͸��,��������
            dx=-dx;
            dy=-dy;
        }
        else if(units[x+dx][y+dy].isEmpty==false 
                &&units[x+dx][y].isEmpty==false ) {
            //x����������
            y+=dy;
            dx=-dx;
        }
        else if(units[x+dx][y+dy].isEmpty==false //����
                &&units[x][y+dy].isEmpty==false ) {
            //y����������
            x+=dx;
            dy=-dy;
        }
        else{ //����
            dx=-dx;
            dy=-dy;
        }
    }
    cout<<sum;
    return 0;
}
