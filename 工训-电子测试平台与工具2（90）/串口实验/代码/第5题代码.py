import serial
#import requests
import serial.tools.list_ports

# 字节转字符串


def b2s(data):
    return ''.join([f'{ch:0>2x}' for ch in data]).upper()


# 连接设备
ser = serial.Serial(list(serial.tools.list_ports.comports()[0])[0], 1200)
# 判断是否连接到设备
assert(ser != None)
# 输入学号
studentID = input("学号:")
# 判断学号是否正确
assert(studentID.isdigit() and len(studentID) == 12)

# 读入序列号
number = b2s(ser.read(6))
# 断言魔数为AA55
assert(number[:4] == "AA55")

# 取出序列号
number = number[4:]
# 判断序列号长度是否正确
assert(len(number) == 4 * 2)
print(f'序列号:{number}')

# 使用学号构造即将发送的字节数据
startData = b'\xaa\x55' + bytes([ord(ch) - ord('0') for ch in studentID])
# 写入数据
ser.write(startData)

password = b''  # 读到的密码
i = 1   # 记录循环次数2

# 开启永真循环，直到Ctrl+C被按下
try:
    while True:
        data = ser.read_all()
        sdata = b2s(data)
        if data != b'' and sdata[:4] == "AA55":
            password = data[-4:]
            if len(password) == 4:
                print(f'[{i}]密码:{b2s(password)}')

                # 使用这次读到的密码构造数据，发送给设备以读取下一次的密码
                ser.write(b'\xaa\x55' + password)
                i += 1

# 当Ctr+C被按下时执行，建议在读到的密码不再变化时按下，大概在256次循环之后
except KeyboardInterrupt:
    print(f'[结束]最后一串密码为:{b2s(password)}')
    print(f'[正在提交]http://132.232.98.70:6363/checkSecret?id={studentID}&v={number}&s={b2s(password)}')

    # 提交实验结果至服务器
    # r = requests.get(f"http://132.232.98.70:6363/checkSecret?id={studentID}&v={number}&s={b2s(password)}")
    #
    # # 判断提交是否成功
    # assert(r.status_code == 200 and r.text.isdigit())
    # print(f'[提交成功]学号:{studentID} 密码循环次数:{r.text}')

