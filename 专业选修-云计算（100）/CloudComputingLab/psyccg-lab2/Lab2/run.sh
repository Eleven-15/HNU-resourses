#!/bin/bash

# 该脚本会自动测试并将输出保存到log中
cd tester-linux-x64
./http-server-tester run --mode basic | tee ../log-basic.txt
./http-server-tester run --mode advanced | tee ../log-advanced.txt
cd ..

# 输出提示信息
echo "执行完成，输出已保存到log中"
