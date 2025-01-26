import subprocess
import time
import matplotlib.pyplot as plt
import itertools

# 每个矩阵测试轮数
test_num = 20
# 测试矩阵名
matrix_name = "psmigr_3"

# 定义需要测试的线程数
thread_num1 = range(1,32)               # 范围
thread_num2 = [64,96,112,128,192,256]   # 离散点
thread_numbers = sorted(list(itertools.chain(thread_num1, thread_num2)))
print(thread_numbers)

# 记录每个线程数的平均speedup
speedups = []
speedups2 = []
speedups3 = []

for thread_num in thread_numbers:
    total_speedup = 0
    total_speedup2 = 0
    total_speedup3 = 0
    for _ in range(test_num):
        # 执行可执行文件并记录时间
        result = subprocess.run(['./mv', str(thread_num), matrix_name], stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)

        # 解析输出结果
        lines = result.stdout.strip().split('\n')
        speedup = 0
        speedup2 = 0
        speedup3 = 0
        for line in lines:
            if line.startswith('speedup1'):
                speedup = float(line.split('=')[1][:-1])
            if line.startswith('speedup2'):
                speedup2 = float(line.split('=')[1][:-1])
            if line.startswith('speedup3'):
                speedup3 = float(line.split('=')[1][:-1])
        total_speedup += speedup
        total_speedup2 += speedup2
        total_speedup3 += speedup3
    print("thread_num {} complete".format(thread_num))

    # 计算平均speedup
    avg_speedup = total_speedup / test_num
    speedups.append(avg_speedup)
    avg_speedup2 = total_speedup2 / test_num
    speedups2.append(avg_speedup2)
    avg_speedup3 = total_speedup3 / test_num
    speedups3.append(avg_speedup3)


print(speedups)
print(speedups2)
print(speedups3)
# 绘制参数-speedup图
plt.figure(figsize=(10, 6))
plt.plot(thread_numbers, speedups, label="basic", color="blue")
plt.plot(thread_numbers, speedups2, label="schedule", color="red")
plt.plot(thread_numbers, speedups3, label="inner", color="green")
plt.xlabel('Thread Number')
plt.ylabel('Average Speedup')
plt.legend()
plt.title('Thread Number vs. Average Speedup')
plt.grid()
plt.savefig('thread_speedup.png')
