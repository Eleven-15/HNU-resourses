import serial.tools.list_ports


# 字符串转字符串
def b2s(data):
    return ''.join([f'{ch:0>2x}' for ch in data]).upper()


# 连接设备

ser = serial.Serial(list(serial.tools.list_ports.comports()[0])[0], 1200)
# 判断是否连接到设备
assert (ser != None)
# 输入学号
studentID = input("学号:")
# 判断学号是否正确
assert (studentID.isdigit() and len(studentID) == 12)
# 读入序列号
number = b2s(ser.read(13))
# 断言魔数为AA55
assert (number[:4] == "AA55")
# 取出序列号
number = number[4:]
assert (len(number) == 11 * 2)
print(f'序列号:{number}')
# 使用学号构造即将发送的字节数据
startData = b'\xaa\x55' + bytes([ord(ch) - ord('0') for ch in studentID])
# 写入设备
ser.write(startData)
password = b''  # 读到的密码
i = 1  # 循环次数
# 开启永真循环，直到ctrl+c被按下
while True:
    # 读1位，探测魔数
    t = b2s(ser.read(1))
    # 第一个魔数应该是AA
    if t != "AA":
        continue
    # 再读一位
    t = b2s(ser.read(1))
    # 第二个魔数应该是55
    if t != "55":
        continue
    # 判断魔数后可以放心读取数据
    # 读入密码开始位置的索引
    index = list(ser.read(1))[0]
    # 若索引大于4，则表明中间有无关字节，吸收掉无关字节
    if index - 4 > 0:
        ser.read(index - 4)
    # 读入四字节的密码
    password = ser.read(4)
    print(f'[{i}]密码:{b2s(password)}')
    # 使用这次读到的密码构造数据，发送给设备以读取下一次的密码
    ser.write(b'\xaa\x55' + password)
    i += 1
