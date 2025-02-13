#include <bits/stdc++.h>
using namespace std;

struct Contestant {
	string name;        // ѡ������
	vector<int> scores; // ��ί���
	int totalScore;     // ���յ÷�
};

// �ȽϺ��������ܵ÷����򣨽���
bool compareByTotalScore(const Contestant &a, const Contestant &b) {
	return a.totalScore > b.totalScore; // ����类与对象���ܷ��Ƿ����b
}

int main() {
	int n;  // ����ѡ������
	cin >> n;
	vector<Contestant> participants(n); // ��������Ϣ

	// ��ȡ��������Ϣ
	for (int i = 0; i < n; ++i) {
		cin >> participants[i].name;  // ѡ������
		participants[i].scores.resize(7);  // ÿλѡ��7����ί�ķ���
		for (int j = 0; j < 7; ++j) {
			cin >> participants[i].scores[j]; // ��ȡÿλ��ί�ķ���
		}
		// ����ȥ����ߺ���ͷ֣��������յ÷�
		sort(participants[i].scores.begin(), participants[i].scores.end());
		participants[i].totalScore = accumulate(participants[i].scores.begin() + 1, participants[i].scores.end() - 1, 0);  // ����ȥ��һ����߷ֺ�һ����ͷֺ���ܷ�
	}

	// �����ܷ�����ʹ�ô�ͳ�ıȽϺ���
	sort(participants.begin(), participants.end(), compareByTotalScore);

	// ��������Ľ��
	for (const auto &p : participants) {
		cout << p.name << " " << p.totalScore << endl; // ���ѡ�������͵÷�
	}

	return 0;
}

/*
������������

	   У԰����OK����������7����ί����һ��ѡ��K���֮�������˱����������ֺ�7λ��ίͬʱ���֣����չ�����ȥ��һ����߷ֺ�һ����ͷֺ�����5λ��ί�����ܺ�Ϊ��ѡ�ֵ����յ÷֡�

	   һ����n��ѡ�ֲμӱ����������дһ�����򣬵����б����������г�����ѡ�ֵ������Լ����յ÷������

	   �ٶ���������ܷ���ͬ��������ܷ���ͬʱ���Գ���˳�������������ǣ��Ժ���˵�ɣ� �Ǻǣ���ʱ���ܰ�)��

��������ʽ��

	   ��1��Ϊһ��������n����ʾ�������������n�У�ÿ�п�ʼΪѡ�ֵ����֣����7����������ʾ��ί������������ݼ��Կո�ָ���

�������ʽ��

	   �����������������ѡ�ֵ������Լ��ܷ֣��ܹ�n�С�

���������롿

4
Alice 90 90 85 92 90 90 90
Bob 92 99 88 92 92 92 92
Cindy 80 85 94 94 94 94 94
Dony 95 95 100 90 95 95 95
�����������

Dony 475
Cindy 461
Bob 460
Alice 450
 */