#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 定义客户结构体
struct Customer
{
    string name;
    double balance;
    int date; // 使用整数表示日期，格式为YYYYMMDD

    // 构造函数
    Customer(string n, double b, int d) : name(n), balance(b), date(d) {}
};

// 比较函数，用于排序
bool compareCustomers(const Customer &a, const Customer &b)
{
    if (a.balance != b.balance)
        return a.balance > b.balance; // 余额降序
    if (a.date != b.date)
        return a.date < b.date; // 日期升序
    return a.name < b.name; // 名称升序
}

int main()
{
    vector<Customer> customers;
    string name;
    double balance;
    int date;

    // 读取输入
    while (cin >> name)
    {
        if (name == "end") break;
        cin >> balance >> date;
        customers.emplace_back(name, balance, date);
    }

    // 排序
    sort(customers.begin(), customers.end(), compareCustomers);

    // 输出结果
    for (const auto &cust: customers)
    {
        cout << cust.name << endl;
    }

    return 0;
}
/*
【问题描述】某银行年终举行答谢会，现读入若干客户信息，以"end"作为结束。请按客户余额从大到小给出邀请名单，客户余额相同时按开户日期先后排序，开户日期相同则按照客户姓名进行升序排列。

【输入形式】输入包括若干行，每行包括客户名、客户余额和开户日期(年月日)，以空格作为分隔，最后一行为"end"

【输出形式】输出包括若干行，每行只包含客户名称.

【样例输入】

Alice 5000.0 20220101
Bob 8000.0 20211215
Amy 7000.0 20220205
Charlie 6000.0 20220120
Tom 7000.0 20211130
end
【样例输出】

Bob
Tom
Amy
Charlie
Alice
【样例说明】

根据余额降序，则Bob排在第一位，Tom和Amy余额相同，则开户日期更前的Tom排在前面。

【数据规模】

客户人数大于等于1，小于等于100，客户余额可能包含小数，50%的测试用例数据没有重复，且保证每个测试中的客户姓名互不相同客户名中不包含空格符。

【提示】

正确设置开户日期的数据类型，方便直接比较。
 */