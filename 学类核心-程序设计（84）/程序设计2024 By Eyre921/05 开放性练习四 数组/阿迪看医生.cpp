#include <iostream>
#include <vector>
#include <cmath> // 引入cmath库以使用ceil函数
using namespace std;

int main()
{
	int doctorCount;
	cin >> doctorCount;

	// 使用vector存储每个医生的首次出诊日和出诊间隔
	vector<pair<int, int>> doctors(doctorCount);
	for(int i = 0; i < doctorCount; ++i)
	{
		cin >> doctors[i].first >> doctors[i].second;
	}

	// 初始化当前时间为第一个医生的首次出诊日
	int currentDay = doctors[0].first;

	// 遍历后续的每个医生
	for(int i = 1; i < doctorCount; ++i)
	{
		int firstDay = doctors[i].first;
		int interval = doctors[i].second;

		// 计算下一个预约日必须在前一个医生看诊日之后一天
		int requiredDay = currentDay + 1;

		if(firstDay >= requiredDay)
		{
			// 如果医生的首次出诊日已经满足要求，直接预约
			currentDay = firstDay;
		}
		else
		{
			// 计算需要经过多少个间隔才能满足要求
			// 使用ceil来确保天数向上取整
			int k = ceil(static_cast<double>(requiredDay - firstDay) / interval);
			currentDay = firstDay + k * interval;
		}
	}

	// 输出完成所有预约所需的最少天数
	cout << currentDay;

	return 0;
}
