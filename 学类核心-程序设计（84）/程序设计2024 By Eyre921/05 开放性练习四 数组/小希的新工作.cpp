#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, totalTime, relaxTime;  // n: 客人数量, totalTime: 总工作时间, relaxTime: 每次放松所需时间
    cin >> n >> totalTime >> relaxTime;

    vector<int> arrival(n), service(n);  // arrival: 到达时间, service: 服务时间

    // 输入每个客人的到达时间和服务时间
    for (int i = 0; i < n; i++) {
        cin >> arrival[i] >> service[i];
    }

    int relaxCount = 0;  // 最大放松次数

    // 1. 工作开始到第一个客人之间的空闲时间
    if (arrival[0] >= relaxTime) relaxCount++;

    // 2. 客人与客人之间的空闲时间
    for (int i = 1; i < n; i++) {
        int freeTime = arrival[i] - (arrival[i - 1] + service[i - 1]);
        if (freeTime >= relaxTime) relaxCount += freeTime / relaxTime;
    }

    // 3. 最后一个客人结束到工作结束之间的空闲时间
    int remainingTime = totalTime - (arrival[n - 1] + service[n - 1]);
    if (remainingTime >= relaxTime) relaxCount += remainingTime / relaxTime;

    // 输出最大放松次数
    cout << relaxCount << endl;

    return 0;
}
