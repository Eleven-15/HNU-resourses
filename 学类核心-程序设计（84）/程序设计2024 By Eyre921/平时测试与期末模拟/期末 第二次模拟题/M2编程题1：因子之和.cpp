#include <bits/stdc++.h>
using namespace std;
long long n,sum;
int main(){
    cin >> n;
    for (long long i = 1; i<=n;i++){
        if (n % i == 0)
            sum += i;
    }
    cout << sum;
}

/*
*M2编程题1：因子之和
【问题描述】对输入的一个整数X，找出其所有的因子，并对其求和，输出求和的结果。

【输入形式】

输入整数X

【输出形式】

         输出整数X所有的因子之和

【样例输入】

10

【样例输出】

18
【样例说明】

10的所有因子是1,2,5,10,1+2+5+10=18
【评分标准】
 * */