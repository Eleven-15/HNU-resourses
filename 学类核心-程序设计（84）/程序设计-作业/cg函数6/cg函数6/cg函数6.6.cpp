#include <bits/stdc++.h>
using namespace std;
int changdu(char* a);
int main()
{
    char a[10000];
    cin.getline(a, 10000);
    int sum = changdu(a);
    cout << sum << endl;
    return 0;
}
int changdu(char* a)
{
    int sum = 0;
    for (int i = 0; i < strlen(a); i++)//strlen()�����Ϳ��Լ����ַ����鳤��
    {
        if (a[i] != '\0')
            sum++;
    }
    return sum;
}

