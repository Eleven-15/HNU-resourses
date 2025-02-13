#include <bits/stdc++.h>
using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    // 获取字符串的长度
    auto lena = s1.length();
    auto lenb = s2.length();

    // 如果长度不相等，直接返回 false
    if (lena != lenb) {
        cout << "false" << endl;
        return 0;
    }

    // 用数组来表示字符映射关系，初始值为 ' '，表示未映射
    vector<char> map_s_to_t(256, ' ');  // 从s到t的映射
    vector<char> map_t_to_s(256, ' ');  // 从t到s的映射

    // 遍历两个字符串的每个字符
    for (size_t i = 0; i < lena; i++) {
        char char_s = s1[i];
        char char_t = s2[i];

        // 检查是否已经有映射
        if (map_s_to_t[char_s] == ' ' && map_t_to_s[char_t] == ' ') {
            // 如果没有映射，建立映射关系
            map_s_to_t[char_s] = char_t;
            map_t_to_s[char_t] = char_s;
        } else if (map_s_to_t[char_s] != char_t || map_t_to_s[char_t] != char_s) {
            // 如果已经有映射，但不一致，返回 false
            cout << "false" << endl;
            return 0;
        }
    }

    // 如果遍历完成没有问题，则返回 true
    cout << "true" << endl;
    return 0;
}
/*
* 【问题描述】

给定两个字符串 s 和 t ，判断它们是否是同构的。如果是同构的，输出true，否则，输出false。

注：如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。

【输入形式】

输入由两行组成，第一行为字符串s，第二行为字符串t
【输出形式】

输出包含一行，值为true或者false

【样例输入1】

egg
add
【样例输出1】

true
【样例说明1】

字符串s中的'e'映射成'a'，'g'映射成'd'，可以转化成字符串t。

【样例输入2】

foo
bar
【样例输出2】

false
【样例说明2】

字符串s中的'o'映射成'a'和'r'，不符合条件。

【样例输入3】

paper
title
【样例输出3】

true
【评分标准】
 * */