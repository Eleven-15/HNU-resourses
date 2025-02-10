# include <iostream>

using namespace std;
void getMaxSum(int a[], int n, int &Left, int &Right);

int main()
{
    int n;
    cin>>n;

    int *p=new int[n];

    for(int i=0; i<n; i++)
        cin>>p[i];

    int Left ＝ 0;
    int Right ＝ 0;
    getMaxSum(p,n,Left,Right);

    cout<<Left<<" "<<Right<<endl;
    delete[] p;

    return 0;
}

void getMaxSum(int a[], int n, int &Left, int &Right)
{
    int sum = 0;
    int result = 0;
    // 遍历思路
        // 以每一个数组索引为起点
    for (int i = 0; i < n; i++){
        // 遍历到每一个终点
        // 从i开始设置起点
        for (int j = i; j < n; j++){
            // sum 为从i开始到j所有数字的和
            for (int k = i; k <= j; k++){
                sum += a[k];
            } 
            // 更新最大值
            if (sum > result){
                result = sum;
                Left = i;
                Right = j;
            }
            // 重置临时和
            sum = 0;
        }
    }
}
