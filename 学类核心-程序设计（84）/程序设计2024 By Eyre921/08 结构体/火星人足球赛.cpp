#include <bits/stdc++.h>
using namespace std;

// ���巸���¼�ṹ��
struct Foul {
    int time;     // ����ʱ��
    int id;       // ��Ա���
    bool isHome;  // �Ƿ�Ϊ������Ա��0Ϊ���ӣ�1Ϊ�Ͷ�
    bool redCard; // �Ƿ��Ѿ���ú���
};

int main() {
    // ��ȡ���ӺͿͶӵĶ���
    string home, away;
    cin >> home >> away;

    int n; // �������
    cin >> n;

    vector<Foul> fouls(n); // �洢�����¼

    // ����ÿ�η����¼
    for (int i = 0; i < n; i++) {
        int t, pId;
        char team, card;

        cin >> t >> team >> pId >> card;

        fouls[i].time = t;
        fouls[i].id = pId;
        fouls[i].isHome = (team == 'h') ? 0 : 1; // ����Ϊ0���Ͷ�Ϊ1
        fouls[i].redCard = (card == 'r'); // ���Ʊ��
    }

    // ��¼���ƴ���
    unordered_map<int, int> yellowHome, yellowAway;
    vector<Foul> redCards; // �洢��ú��Ƶ���Ա

    // �������¼���ж��Ƿ�Ӧ��������
    for (int i = 0; i < n; i++) {
        Foul &foul = fouls[i];

        // ����Ѿ��Ǻ��ƣ�����
        if (foul.redCard) {
            redCards.push_back(foul);
            continue;
        }

        // �������
        if (foul.isHome == 0) { // ����
            yellowHome[foul.id]++;
            if (yellowHome[foul.id] == 2) {
                foul.redCard = true;
                redCards.push_back(foul);
            }
        } else { // �Ͷ�
            yellowAway[foul.id]++;
            if (yellowAway[foul.id] == 2) {
                foul.redCard = true;
                redCards.push_back(foul);
            }
        }
    }

    // ���û�к��ƣ���� "No Red Card"
    if (redCards.empty()) {
        cout << "No Red Card" << endl;
        return 0;
    }

    // ����ʱ�䡢��Ӻ���Ա�������
    sort(redCards.begin(), redCards.end(), [](const Foul &a, const Foul &b) {
        if (a.time == b.time) {
            if (a.isHome == b.isHome) {
                return a.id > b.id; // ��Ŵ����ǰ��
            }
            return a.isHome < b.isHome; // ������ǰ��
        }
        return a.time < b.time; // ʱ������
    });

    // ������Ƽ�¼
    for (const Foul &foul : redCards) {
        cout << (foul.isHome == 0 ? home : away) << " "
             << foul.id << " " << foul.time << endl;
    }

    return 0;
}
/*
������������

       �������������ı�������������˵ı���������Щ�ǳ����ƣ��������ط��棬����������ƾ��棬�ر����صķ��棬���������ֱ�ӷ��£�������˵õ���2�Ż��ƣ����Զ���ú��Ʒ��£�����ͬ����ȡ���ͳ��ơ�

       ���������������ͬ���ǣ�������������ÿ�ӿ����ϳ�����������̶�Ϊ11�ˣ����Զ���ˣ�����ʱ��Ҳ�����һЩ��

       ����ʱ�Ĳ���Ա�ǻ����ˣ��з��ǳ�������������˻�ú���ƣ������˲��н��Զ���¼��ʱ�������

��������ʽ��

       ����ĵ�һ��Ϊ���Ӷ������ڶ���Ϊ�ͶӶ����������ĳ��Ȳ�����20���ַ���

       ������Ϊһ������ n (0?��?n?��?90) ����ʾ�õ�����Ƶķ��������

       ��������n�У�ÿ�а����ÿո�ָ���4�����֣���ʾ��������:

����Ϊһ����������ʾ�����ʱ�䣨���ӣ�

����Ϊһ���ַ�"h"��"类与对象"�����Ϊ"h"����ʾ�����ƻ����������Ա�����������Ͷ���Ա

������Ϊ��Ա���m  (1?��?m?��?99)

������Ϊһ���ַ�"y"��"r"�����Ϊ"y"����ʾΪ���ƣ�����Ϊ����

       ��ͬ��ӵ���Ա��������ͬ�ĺ��룬��ͬһ�����Ա�ĺ��벻��ͬ�������¼��ʱ��˳�����С�

�������ʽ��

       �����ʱ��˳�����еĻ�ú��Ƶļ�¼�����ʱ����ͬ������������ǰ�棬���ͬһʱ��ͬһ����ж��˻�ú��ƣ����Ŵ������ǰ�档ÿ������һ�У�����3�����֣���Ա������ӵ����֡�������Ա��š���ú���ʱ�䡣

      ���ȫ�������޺��ƣ����"No Red Card"
���������롿

MC
CSKA
9
28 类与对象 3 y
62 h 25 y
66 h 42 y
70 h 25 y
77 类与对象 4 y
79 类与对象 25 y
82 h 42 r
89 h 16 y
90 类与对象 13 r
�����������

MC 25 70
MC 42 82
CSKA 13 90
 */