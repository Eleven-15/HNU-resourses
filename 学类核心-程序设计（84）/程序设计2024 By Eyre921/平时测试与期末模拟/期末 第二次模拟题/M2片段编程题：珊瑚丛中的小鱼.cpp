#include <iostream>
#include <string>

using namespace std;

// 基类 Fish，用于表示鱼类
class Fish {
	protected:
		float length;  // 鱼的长度
		float ambientTempture;  // 环境温度

	public:
		string fishName;  // 鱼的名字

		// 构造函数：接受环境温度并输入鱼的长度
		Fish(float ambTemp) {
			ambientTempture = ambTemp;  // 设置环境温度
			cin >> length;  // 输入鱼的长度
		}

		// 纯虚函数，用于操作符重载
		virtual float operator++() = 0;

		// 虚析构函数
		virtual ~Fish() {};
};

// Guppy类，继承自Fish类，表示一种特定的鱼：孔雀鱼
class Guppy : public Fish {
		float brightness;  // 孔雀鱼的亮度

	public:
		Guppy(float brtness, float ambTemp);  // 构造函数

		float operator++();  // 操作符重载

		virtual ~Guppy();  // 虚析构函数

		static int GuppyExitNum;  // 记录离开的孔雀鱼数量
};

// Macropodus类，继承自Fish类，表示另一种特定的鱼：巨口鱼
class Macropodus : public Fish {
	private:
		float speed;  // 巨口鱼的速度

	public:
		static int MacroExitNum;  // 记录离开的巨口鱼数量

		Macropodus(float ambTemp);  // 构造函数

		float operator++();  // 操作符重载

		virtual ~Macropodus();  // 虚析构函数
};

// 珊瑚礁类，表示鱼群生态环境
class CoralReef {
		Fish **pFishes;  // 鱼群数组指针
		int orgFishNum;  // 原始鱼的数量
		float guppyLen;  // 孔雀鱼的长度阈值
		float macropodusLen;  // 巨口鱼的长度阈值
		float ambientTempture;  // 环境温度
		float brightness;  // 亮度

	public:
		// 构造函数：接受环境亮度和温度
		CoralReef() {
			cin >> brightness;  // 输入环境亮度
			cin >> ambientTempture;  // 输入环境温度
		}

		void hatchFishes();  // 孵化鱼群

		// 排除超出最大长度的鱼
		void expelFishes() {
			for (int i = 0; i < orgFishNum; i++) {
				// 如果鱼的种类是孔雀鱼并且长度达到阈值，或者是巨口鱼并且长度达到阈值，则将其移除
				if ((pFishes[i]->fishName == "Guppy") && (++(*pFishes[i]) >= guppyLen) || (
				            (pFishes[i]->fishName == "Macropodus") && (++(*pFishes[i]) >= macropodusLen))) {
					delete pFishes[i];  // 删除鱼对象
					pFishes[i] = NULL;  // 清空指针
				}
			}
		}

		void report();  // 输出报告

		// 析构函数：释放资源
		~CoralReef();
};

// 主函数：程序入口
int main() {
	CoralReef crlrf;  // 创建珊瑚礁对象
	crlrf.hatchFishes();  // 孵化鱼群
	crlrf.expelFishes();  // 排除超长鱼
	cout << "report:" << endl;  // 输出提示
	crlrf.report();  // 输出报告
	return 0;
}

// Guppy类的构造函数
Guppy::Guppy(float brtness, float ambTemp) : Fish(ambTemp) {
	fishName = "Guppy";  // 设置鱼的名称
	brightness = brtness;  // 设置亮度
}

// Guppy类的析构函数
Guppy::~Guppy() {
	GuppyExitNum = GuppyExitNum + 1;  // 增加离开孔雀鱼的数量
};

// 重载++操作符，增加鱼的长度
float Guppy::operator++() {
	return length * (1.0 + (int(length) * 10 + int(brightness / 100) * 10 + (ambientTempture < 25 ? 10 : 0)) / 100.0);
}

// 静态成员变量，记录离开的孔雀鱼数量
int Guppy::GuppyExitNum = 0;

// Macropodus类的构造函数
Macropodus::Macropodus(float ambTemp) : Fish(ambTemp) {
	fishName = "Macropodus";  // 设置鱼的名称
	cin >> speed;  // 输入鱼的速度
}

// 重载++操作符，增加鱼的长度
float Macropodus::operator++() {
	return length * (1.0 + ((int(speed) / 2) * 10 + (ambientTempture > 26 ? 20 : 0)) / 100.0);
}

// Macropodus类的析构函数
Macropodus::~Macropodus() {
	MacroExitNum = MacroExitNum + 1;  // 增加离开巨口鱼的数量
}

// 静态成员变量，记录离开的巨口鱼数量
int Macropodus::MacroExitNum = 0;

// hatchFishes函数：孵化鱼群
void CoralReef::hatchFishes() {
	cin >> orgFishNum;  // 输入原始鱼的数量
	pFishes = new Fish *[orgFishNum];  // 动态分配鱼群数组
	for (int i = 0; i < orgFishNum; i++) {
		string a;  // 存储鱼的种类
		cin >> a;  // 输入鱼的种类
		if (a == "Guppy")
			pFishes[i] = new Guppy(brightness, ambientTempture);  // 创建孔雀鱼对象
		else
			pFishes[i] = new Macropodus(ambientTempture);  // 创建巨口鱼对象
	}
	cin >> guppyLen >> macropodusLen;  // 输入孔雀鱼和巨口鱼的最大长度
}

// report函数：输出报告
void CoralReef::report() {
	cout << "exit Guppy:" << Guppy::GuppyExitNum << endl;  // 输出离开的孔雀鱼数量
	cout << "exit Macropodus:" << Macropodus::MacroExitNum << endl;  // 输出离开的巨口鱼数量
	cout << "remaining Fish:" << orgFishNum - Guppy::GuppyExitNum - Macropodus::MacroExitNum;  // 输出剩余的鱼数量
}

// CoralReef类的析构函数，释放鱼群资源
CoralReef::~CoralReef() {
	for (int i = 0; i < orgFishNum; i++) {
		if (pFishes[i])  // 如果指针不为空
			delete pFishes[i];  // 删除鱼对象
	}
	delete[]pFishes;  // 删除鱼群数组
}
