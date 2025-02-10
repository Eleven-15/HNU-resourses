#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, s;  // n：航班数量，s：最小起飞间隔
    cin >> n >> s;

    // 读取每个着陆航班的时间（小时和分钟）
    vector<pair<int, int>> landings(n);
    for (int i = 0; i < n; i++) {
        cin >> landings[i].first >> landings[i].second;
    }

    // 扩展着陆时间列表，b[0]为最后一个着陆时间，b[1..n]为原始着陆时间
    vector<pair<int, int>> extended(n + 1);
    extended[0] = landings[n - 1];
    for (int i = 1; i <= n; i++) {
        extended[i] = landings[i - 1];
    }

    int hour = 0, minute = 0;  // 最早起飞时间（小时和分钟）

    for (int i = 0; i <= n; i++) {
        if (i < n) {
            // 当前着陆时间转换为分钟数
            int curr = extended[i].first * 60 + extended[i].second;
            // 计算起飞时间：当前着陆时间 + 1分钟（起飞时间） + 最小间隔
            int takeoff = curr + 1 + s;
            if (takeoff >= 1440) {  // 如果超过24小时，回到新的一天
                takeoff -= 1440;
            }

            // 下一个着陆时间转换为分钟数
            int next = extended[i + 1].first * 60 + extended[i + 1].second;
            // 计算起飞时间与下一个着陆时间之间的间隔
            int gap = next - takeoff;

            // 判断是否满足最小间隔条件
            if (gap >= (s + 1)) {
                hour = takeoff / 60;
                minute = takeoff % 60;
                break;  // 找到最早的起飞时间后，退出循环
            }
        } else {
            // 在所有着陆航班之后起飞
            int last = extended[i].first * 60 + extended[i].second;
            int takeoff = last + 1 + s;
            if (takeoff >= 1440) {  // 如果超过24小时，回到新的一天
                takeoff -= 1440;
            }
            hour = takeoff / 60;
            minute = takeoff % 60;
        }
    }

    // 输出最早的起飞时间
    cout << hour << " " << minute << endl;

    return 0;
}
