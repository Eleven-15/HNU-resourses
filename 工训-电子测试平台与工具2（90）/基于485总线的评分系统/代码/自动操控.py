import binascii
import serial.tools.list_ports

#read config
def openreadconfig(file_name):
    data = []
    file = open(file_name, 'r',encoding='utf-8')  # 打开文件
    file_data = file.readlines()  # 读取所有行
    count = 0
    for row in file_data:
        tmp_list = row.split(' ')  # 按‘，'切分每行的数据
        tmp_list[-1] = tmp_list[-1].replace('\n','') #去掉换行符
        count+=1
        if count == 1:
            data.append(float(tmp_list[1]))  # 将每行数据插入data中
        else:
            data.append(int(float(tmp_list[1])))  # 将每行数据插入data中
    return data
config = openreadconfig('config.txt')

my_timeout = config[0] #timeout 设置为0.04
device_upper = config[1] #机器编号范围上限是多少
polling_num = config[2] #轮询次数 设置为15
debug = config[3] #是否打印调试信息 1为打印
if debug: print("读入参数列表为{}".format(config))


# initial
plist = list(serial.tools.list_ports.comports())  # 获取端口列表
#ser = serial.Serial(list(plist[0])[0], 9600, timeout=my_timeout)  # 导入pyserial模块
ser = serial.Serial("COM6", 9600, timeout=my_timeout)  # 导入pyserial模块
#其中timeout参数为操作未完成时发生超时之前的毫秒数
#9600为波特率，不需要调节

#从串口读数据
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


devices=list(range(0,device_upper)) #初次遍历机器的范围
print(devices)

onlineDevices=[] # 在线的机器

# part 1: 查询在线从机信息
print("查询在线从机信息")
for device in devices:
    data = [0x5A, device, 0x08, 0x13]
    data.append(sum(data))
    if debug: print("{}\n从机设备编号: {:2d} 校验信息为: {}\n尝试校验中...".format('-'*50, device, data))
    for _ in range(polling_num):
        ser.write(data)
        retdata = read_times()
        if retdata:
            if debug: print("返回值：{}".format(retdata))
            retdata = [int(i,16) for i in retdata]
            if retdata == data:
                if debug: print("返回的校验信息为: {}，从机正常。".format(retdata))
                print("从机{:2d}在线".format(device))
                onlineDevices.append(device)
            break

# part 2： 读取从机分数
total=0
print('-'*50)
print('从机分数读取：')
for device in onlineDevices:
    data = [0x5A, 0x00, 0x03, device]
    data.append(sum(data))
    if debug: print("{}\n从机设备编号: {:2d} 发送信息为: {}\n尝试获取分数中...".format('-'*50, device, data))
    flag = True
    while 1:
        ser.write(data)
        retdata = read_times()
        if retdata:
            if debug: print("返回值：{}".format(retdata))
            retdata = [int(i,16) for i in retdata]
            if debug: print("返回值：{}".format(retdata))
            if retdata[1] == device and retdata[4] == sum(retdata[:4]):
                if retdata[3] == 0x6F:
                    print("读取错误，从机{:2d}分数未确认".format(device))
                else:
                    if debug: print("该从机分数为: {}，从机正常。".format(retdata[3]))
                    if retdata[3]>0x64:
                        print("分数错误：超过100分,记为0分")
                    else:
                        total+=retdata[3]
            else:
                print("从机传输结果异常")
            flag = False
            break
    if flag:
        print("从机{:2d}无返回".format(device))

# part 3: 计算输出平均分
average = total/len(onlineDevices)
print('-'*50)
print("平均分为{}".format(average))
print('-'*50)

# part 4: 从机复位操作
print('从机复位操作：')
data = [0x5A, 0x00, 0x01, 0x00, 0x5B]
for _ in range(100):
    ser.write(data)
print("从机已复位，可以开始下一轮评分。")
