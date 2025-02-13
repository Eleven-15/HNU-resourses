#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

// 计算最小覆盖子串
string minWindowSubstring(const string &s, const string &t)
{
    if (t.empty()) return "";

    unordered_map<char, int> tCount;
    unordered_map<char, int> windowCount;

    for (char c: t)
    {
        tCount[c]++;
    }

    int required = tCount.size();
    int formed = 0;

    int left = 0, right = 0;
    int minLength = INT_MAX;
    int minLeft = 0;
    int length = s.size();
    while (right < length)
    {
        char c = s[right];
        windowCount[c]++;

        // 如果当前字符满足 t 中的需求，则 formed 增加
        if (windowCount[c] == tCount[c])
        {
            formed++;
        }

        // 当窗口符合条件时，尝试收缩窗口
        while (left <= right && formed == required)
        {
            if (right - left + 1 < minLength)
            {
                minLength = right - left + 1;
                minLeft = left;
            }

            // 收缩窗口
            windowCount[s[left]]--;
            if (windowCount[s[left]] < tCount[s[left]])
            {
                formed--;
            }
            left++;
        }

        right++;
    }

    // 如果没有找到符合条件的子串，返回空字符串
    if (minLength == INT_MAX)
    {
        return "";
    } else
    {
        return s.substr(minLeft, minLength);
    }
}

// 统计字符频率并排序
string sortByFrequency(const string &s)
{
    unordered_map<char, int> freq;

    // 统计字符频率
    for (char c: s)
    {
        freq[c]++;
    }

    // 将频率和字符放入一个 vector
    vector<pair<char, int> > freqList(freq.begin(), freq.end());

    // 按频率升序，如果频率相同则按字符的 ASCII 值升序
    sort(freqList.begin(), freqList.end(), [](const pair<char, int> &a, const pair<char, int> &b)
    {
        if (a.second == b.second)
        {
            return a.first < b.first;
        }
        return a.second > b.second;
    });

    // 构造排序后的字符串
    string result;
    for (const auto &p: freqList)
    {
        result.append(p.second, p.first);
    }

    return result;
}

void processTestCase(const string &t, const string &s)
{
    string result = minWindowSubstring(s, t);

    if (result.empty())
    {
        // 如果没有找到最小覆盖子串，进行字符频率排序
        result = sortByFrequency(s);
    }

    cout << result << endl;
}

int main()
{
    int n;
    cin >> n;

    while (n--)
    {
        string t, s;
        cin >> t >> s;

        processTestCase(t, s);
    }

    return 0;
}



