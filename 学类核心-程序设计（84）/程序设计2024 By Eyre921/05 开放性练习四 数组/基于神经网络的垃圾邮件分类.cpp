#include<iostream>
using namespace std;

int main() {
    int T, N, minX, maxX;
    cin >> T;  // 输入测试用例数量

    for (int i = 0; i < T; i++) {
        int result[2] = {0, 0};  // result[0]：偶数用户数量，result[1]：奇数用户数量
        cin >> N >> minX >> maxX;

        int b[N][2];  // 用来存储每层的wi和bi
        for (int x = 0; x < N; x++) {
            cin >> b[x][0] >> b[x][1];  // 输入每层的wi和bi
        }

        // 计算网络传递后的初始值
        int t = minX, s = 1;
        for (int x = 0; x < N; x++) {
            t = t * b[x][0] + b[x][1];  // 计算每一层的输出
            s = s * b[x][0];  // 计算权重的乘积
        }

        // 对于第一个用户 minX 判断奇偶性
        if (t % 2 == 0) {
            result[0]++;  // 偶数
        } else {
            result[1]++;  // 奇数
        }

        // 计算从 minX+1 到 maxX 范围内奇偶数的数量
        // 每次加上s，判断 t 是偶数还是奇数
        if (s != 0) {
            // 计算每一轮变化的奇偶性
            int range_size = maxX - minX;  // 计算区间大小
            int even_count = 0, odd_count = 0;

            // 用 s 来递推所有值的奇偶性
            for (int i = 0; i < range_size; i++) {
                t = t + s;  // 增加s
                if (t % 2 == 0) {
                    even_count++;
                } else {
                    odd_count++;
                }
            }

            // 输出结果
            result[0] += even_count;
            result[1] += odd_count;
        }

        cout << result[0] << ' ' << result[1] << endl;
    }

    return 0;
}
