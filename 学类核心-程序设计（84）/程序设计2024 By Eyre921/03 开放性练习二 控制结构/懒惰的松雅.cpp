#include <iostream>
#include <string>
using namespace std;

bool is_lucky(int hh, int mm);

int main()
{
	int x, hh, mm, t = 0;
	cin >> x >> hh >> mm;
	while (!(hh / 10 == 7 || hh % 10 == 7 || mm / 10 == 7 || mm % 10 == 7 || mm == 7 || hh == 7))
	{
		mm -= x;
		if (mm < 0)
		{
			int hours_cut = (abs(mm) + 59) / 60; // 向上取整
			hh -= hours_cut;
			mm = (mm + 60 * hours_cut) % 60;
		}
		if (hh < 0)
		{
			hh = (hh + 24) % 24; //小时不够的处理
		}
		t++;
	}
	cout << t << endl;
	     return 0;
}


