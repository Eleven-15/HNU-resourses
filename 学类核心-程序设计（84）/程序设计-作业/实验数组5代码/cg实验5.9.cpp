#include<iostream>
#include<algorithm>
using namespace std;
int main() {
	int n, k, M, D, i;
	cin >> n >> k >> M >> D;
	int a[M]; //����ÿ��ѭ���������е��ǹ�
	for (i = 0; i < M; i++) {
		a[i] = 0;
	}
	int D1, n1;
	D1 = D;
	n1 = n;
	for (i = 1; i <= M; i++) { //һ��ʼ����һ���ǹ�
		D = D1;
		n = n1;
		for (int j = 0;; j++) { //�ǹ��ķ��� ��������η����ǹ�
			if (D <= 0) {
				break; //������������ˣ���break
			}
			n -= i * k;     //ÿ����һ�Σ��ǹ�����Ӧ�ļ���
			a[i - 1] += i; // �����Ϸ����ǹ� Ȼ�����������     
			if (n < i) { 
				break;//���ʣ���ǹ�С��Ӧ�������ǹ�������ѭ��
			}
			D--;
			if (n <= 0) { //û�ǹ���break
				break;
			}
		}
	}
	sort(a, a + M); //��sort��������STL������ö�ٿ�����set���������Զ�����ȥ�أ�
	cout << a[M - 1]; // Ȼ���������
	return 0;
}
