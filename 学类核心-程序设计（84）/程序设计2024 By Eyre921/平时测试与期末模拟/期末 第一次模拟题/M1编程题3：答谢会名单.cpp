#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ����ͻ��ṹ��
struct Customer
{
    string name;
    double balance;
    int date; // ʹ��������ʾ���ڣ���ʽΪYYYYMMDD

    // ���캯��
    Customer(string n, double b, int d) : name(n), balance(b), date(d) {}
};

// �ȽϺ�������������
bool compareCustomers(const Customer &a, const Customer &b)
{
    if (a.balance != b.balance)
        return a.balance > b.balance; // ����
    if (a.date != b.date)
        return a.date < b.date; // ��������
    return a.name < b.name; // ��������
}

int main()
{
    vector<Customer> customers;
    string name;
    double balance;
    int date;

    // ��ȡ����
    while (cin >> name)
    {
        if (name == "end") break;
        cin >> balance >> date;
        customers.emplace_back(name, balance, date);
    }

    // ����
    sort(customers.begin(), customers.end(), compareCustomers);

    // ������
    for (const auto &cust: customers)
    {
        cout << cust.name << endl;
    }

    return 0;
}
/*
������������ĳ�������վ��д�л�ᣬ�ֶ������ɿͻ���Ϣ����"end"��Ϊ�������밴�ͻ����Ӵ�С���������������ͻ������ͬʱ�����������Ⱥ����򣬿���������ͬ���տͻ����������������С�

��������ʽ��������������У�ÿ�а����ͻ������ͻ����Ϳ�������(������)���Կո���Ϊ�ָ������һ��Ϊ"end"

�������ʽ��������������У�ÿ��ֻ�����ͻ�����.

���������롿

Alice 5000.0 20220101
Bob 8000.0 20211215
Amy 7000.0 20220205
Charlie 6000.0 20220120
Tom 7000.0 20211130
end
�����������

Bob
Tom
Amy
Charlie
Alice
������˵����

����������Bob���ڵ�һλ��Tom��Amy�����ͬ���򿪻����ڸ�ǰ��Tom����ǰ�档

�����ݹ�ģ��

�ͻ��������ڵ���1��С�ڵ���100���ͻ������ܰ���С����50%�Ĳ�����������û���ظ����ұ�֤ÿ�������еĿͻ�����������ͬ�ͻ����в������ո����

����ʾ��

��ȷ���ÿ������ڵ��������ͣ�����ֱ�ӱȽϡ�
 */