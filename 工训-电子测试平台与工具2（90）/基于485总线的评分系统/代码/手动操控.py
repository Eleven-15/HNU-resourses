import binascii
import serial.tools.list_ports

# init
plist = list(serial.tools.list_ports.comports())  # 获取端口列表
#ser = serial.Serial(list(plist[0])[0], 9600, timeout=0.05)  # 导入pyserial模块
ser = serial.Serial("COM6", 9600, timeout=0.05)  # 导入pyserial模块

def read_times():
    while 1:
        dic = []
        reading = ser.read(5)  # 读取串口数据
        if reading != b'':
            a = str(hex(int(binascii.hexlify(reading), 16)))
            b = a.replace("0x", "")
            for index in range(0, len(b), 2):
                dic.append(b[index] + b[index + 1])
        return dic

devices = list(map(int, input("请输入设备下位机，中间以' '隔开：").split())) # 存储设备列表
print(devices)

# part 1: 校验下位机设备
for device in devices:
    data = [0x5A, device, 0x08, 0x13]
    data.append(sum(data))
    print("{}\n从机设备编号: {:2d} 校验信息为: {}\n尝试校验中...".format('-'*50, device, data))
    flag = True
    for _ in range(100):
        ser.write(data)
        retdata = read_times()
        if retdata:
            print(retdata)
            retdata = [int(i,16) for i in retdata]
            if retdata == data:
                print("返回的校验信息为: {}，从机正常。".format(retdata))
            else:
                print("从机传输结果异常")
            flag = False
            break
    if flag:
        print("从机无返回")

print('-'*50)
print('从机分数读取：')
for device in devices:
    data = [0x5A, 0x00, 0x03, device]
    data.append(sum(data))
    print("{}\n从机设备编号: {:2d} 发送信息为: {}\n尝试获取分数中...".format('-'*50, device, data))
    flag = True
    for _ in range(100):
        ser.write(data)
        retdata = read_times()
        if retdata:
            print(retdata)
            retdata = [int(i,16) for i in retdata]
            print(retdata)
            if retdata[1] == device and retdata[4] == sum(retdata[:4]):
                print("该从机分数为: {}，从机正常。".format(retdata[3]))
            elif retdata[3] == 0x6F:
                print("从机分数大于100，错误")
            else:
                print("从机传输结果异常")
            flag = False
            break
    if flag:
        print("从机无返回")

print('-'*50)
print('从机复位操作：')
data = [0x5A, 0x00, 0x01, 0x00, 0x5B]
ser.write(data)
print("从机已复位，可以开始下一轮评分。")
