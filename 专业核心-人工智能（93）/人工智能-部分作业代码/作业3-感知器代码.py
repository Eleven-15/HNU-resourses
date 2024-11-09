import numpy as np

# 简单感知器
class Perceptron(object):
    def __init__(self, lr, epoch):
        # 指定 X 维度数，这里是2
        self.input_dim = 2
        # 指定激活函数，这里用阶跃函数
        self.activator = self.__step
        # 指定学习率与训练轮数
        self.lr = lr
        self.epoch = epoch
        # 权重向量初始化为[-0.5,0.5]随机数
        self.weights = np.random.uniform(-0.5, 0.5, self.input_dim)
        self.bias = np.random.uniform(-0.5, 0.5)

    # 阶跃函数
    def __step(self, x):
        return 1 if x > 0 else 0

    # 返回感知机的参数
    def __str__(self):
        return 'weight: %s\n  bias: %f\n' % (self.weights, self.bias)

    # 正向传播
    def __forward(self, X):
        y_temp = np.dot(self.weights, X) + self.bias
        Y = self.activator(y_temp)
        return Y

    # 训练
    def __train(self, inputs, labels):
        for _ in range(self.epoch):
            samples = zip(inputs, labels)
            for input, label in samples:
                output = self.__forward(input)
                self.__update_weights(input, output, label)

    # 反向传播，更新数值
    def __update_weights(self, input, output, label):
        delta = label - output
        self.weights += self.lr * delta * input
        self.bias += self.lr * delta

    # 训练（外部接口）
    def train(self, inputs, labels):
        self.__train(inputs, labels)

    # 预测（外部接口）
    def predict(self, X):
        return self.__forward(X)


def get_train_dataset(mode):
    # 构建训练数据
    if mode=="and":
        input_vecs = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])  # X
        labels = np.array([0, 0, 0, 1])  # labels
        return input_vecs, labels
    if mode=="or":
        input_vecs = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])  # X
        labels = np.array([0, 1, 1, 1])  # labels
        return input_vecs, labels

if __name__ == "__main__":
    # 选择模式 and 还是 or , 直接输入即可
    mode = "and"

    # 实例化感知机
    perceptron = Perceptron(lr=0.001,epoch=1000)
    # 获取数据集
    input_vecs, labels = get_train_dataset(mode=mode)
    # 训练
    perceptron.train(input_vecs, labels)
    # 输出权重信息
    print(perceptron)
    #测试真值表
    print("0 {mode} 0 = {ans}".format(mode=mode,ans=perceptron.predict([0, 0])))
    print("0 {mode} 1 = {ans}".format(mode=mode,ans=perceptron.predict([0, 1])))
    print("1 {mode} 0 = {ans}".format(mode=mode,ans=perceptron.predict([1, 0])))
    print("1 {mode} 1 = {ans}".format(mode=mode,ans=perceptron.predict([1, 1])))
