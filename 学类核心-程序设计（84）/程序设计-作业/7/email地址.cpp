#include <iostream>
#include <string>
using namespace std;

int main()
{
	string email;
	cin >> email;
	int len = email.size(), result = 0, num1, num2;
	for (int i = 0; i < len - 1; i++)
	{
		if (email[i] == '@')
		{
			num1 = 0, num2 = 0;
			for (int j = i - 1; j >= 0; j--)
			{
				if (email[j] == '.' || email[j] == '@')  break;
				if (email[j] >= 97 && email[j] <= 122) num1++;
			}
			for (int j = i + 1; j < len - 1; j++)
			{
				if (email[i + 1] == '.') break;
				if (email[j] == '_' || email[j] == '@') break;
				if (email[j] == '.')
				{
					for (int k = j+1; k < len ; k++)
					{
						if ((email[k] >= '0' && email[k] <= '9') || email[k] == '.' || email[k] == '_' || email[k] == '@')						
							break;
						else
							num2++;	
					}					
				}
				if (num2 > 0)  break;
			}
			result += num2 * num1;
		}
	}
	cout << result;
	return 0;
}
						

