#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, a, d;
    cin >> n >> m >> a >> d;

    // 创建数组，存储员工进入的时刻和客人到来的时刻
    vector<int> values(n + m);

    // 输入m个客人到达的时刻
    for (int i = 0; i < m; i++) {
        cin >> values[i];
    }

    // 计算n个员工到达的时刻并添加到values数组
    for (int i = 0; i < n; i++) {
        values[i + m] = (i + 1) * a;
    }

    // 对所有时刻进行排序
    sort(values.begin(), values.end());

    // 计算自动门打开的次数
    int lastSelectedTime = values[0];
    int openCount = 1; // 首先假设门在第一个时刻打开

    // 遍历所有时刻，检查门是否需要重新打开
    for (int i = 1; i < n + m; i++) {
        // 如果当前到达的时刻大于门关闭时刻 + d 秒，说明门需要重新打开
        if (values[i] > lastSelectedTime + d) {
            openCount++;  // 重新打开门
            lastSelectedTime = values[i]; // 更新门最后一次打开的时刻
        }
    }

    // 输出门打开的总次数
    cout << openCount << endl;
    return 0;
}
