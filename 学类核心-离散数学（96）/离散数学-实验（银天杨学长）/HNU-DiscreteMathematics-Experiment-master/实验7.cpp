/*
 * �� 6 ���޸ĵ�
 * �޸ĵ�1������ͷ�ļ�
 * �޸ĵ�2���ϲ�if��for��䣬ʹ�������׶�
 * �޸ĵ�3����strchr������������������
 * �޸ĵ�4��ʹ��memset�������˫��ѭ����ʼ������
 * �޸ĵ�5�����ò��������Ż�����
 * �޸ĵ�6������while�ж������Ƿ�Ϸ�
 */

/* �޸ĵ�1������ͷ�ļ� */
#include <bits/stdc++.h>
/*
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
*/
#define N 100

//���ϵĻ������㽻��������ԳƲֱ��
int printYsh(char a[])
{
	//���ڼ��ϱ�����һ���ַ�������ʾʱ�ڸ�Ԫ��֮����붺�ţ������س���
	int nLen = 0;
	int i = 0;
	nLen = strlen(a);
	if (nLen > 0)
	{
		printf("%c", a[0]);
	}
	for (i = 1; i < nLen; i++)
	{
		printf(",%c", a[i]);
	}
	printf("\n");
	return nLen;
}
int printRelaYsh(char a[][3], int n)
{
	//���ڼ��ϱ�����һ���ַ�������ʾʱ�ڸ�Ԫ��֮����붺�ţ������س���
	int i = 0;
//	if (n > 0)
//	{
//		printf("<%c,%c>", a[0][0], a[0][1]);
//	}
//	for (i = 1; i < n; i++)
//	{
//		printf(",<%c,%c>", a[i][0], a[i][1]);
//	}
    for (i = 1; i <= n; i++)
	{
		printf(",<%c,%c>", a[i-1][0], a[i-1][1]);
	}
	/* �޸ĵ�2���ϲ�if��for��䣬ʹ�������׶� */
	printf("\n");
	return n;
}
int printRelaMatrix(int M[][N], int n)
{
	//��ӡ��ϵ�����ֵ
	int i = 0, j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf("%4d", M[i][j]);
		printf("\n");
	}
}
int inputYsh(char a[])
{
	//���ڼ��ϱ�����һ���ַ�������������ʱ���ַ����ö��ŷָ���
	//�β�a��һ�����飬������һ����ֵַ���ں����Ը�������޸Ļᷴӳ��������
	char nLen = 0, i = 0, j = 0, k = 0;
	char stmp[1024];//���1024���ַ�
	printf("����Ԫ��ֻ����A-Za-z0-9,�����ַ��������ָ�����ȥ����\n");
	gets(stmp);
	fflush(stdin);
	nLen = strlen(stmp);
	for (i = 0; i < nLen; i++)
	{
		if (((stmp[i] >= 'A') && (stmp[i] <= 'Z')) ||
		        ((stmp[i] >= 'a') && (stmp[i] <= 'z')) || ((stmp[i] >= '0') && (stmp[i] <= '9')))
			//��Ҫ�жϸ��ַ� �Ƿ��Ѿ���a�г��ֹ�
			/* �޸ĵ�3����strchr������������������ */
			if(strchr(a,stmp[i])==NULL)
            {
                a[j]=stmp[i];
                j++;
            }
	}
	a[j] = '\0';
	return j;//�ַ����ĳ���
}
int inputRelaYsh(char a[][3])
{
	//������ż�Ǳ�����һ���ַ�������������ʱ���ַ����ö��ŷָ���
	char nLen = 0, i = 0, j = 0;
	int nbit = 0;
	char stmp[1024];//���1024���ַ�
	printf("��żֻ����A-Za-z0-9�������ַ��������ָ�����ȥ��������<a,b>:\n");
	gets(stmp);
	fflush(stdin);
	nLen = strlen(stmp);
	for (i = 0; i < nLen; i++)
	{
		if (((stmp[i] >= 'A') && (stmp[i] <= 'Z')) ||
		        ((stmp[i] >= 'a') && (stmp[i] <= 'z')) ||
		        ((stmp[i] >= '0') && (stmp[i] <= '9')))
		{
			a[j][nbit] = stmp[i];
			nbit++;
			if (nbit == 2)
			{
				a[j][2] = '\0';
				j++;
				nbit = 0;
			}
		}
	}
	return j;//�ַ����ĳ���
}

int relaCompose(char R[][3], char S[][3], char T[][3], int nR, int nS)
{
	//��ϵ�ĸ��ϣ���RS��ÿ����ż���бȽϣ���ϳɹ���д�뵽T��
	int i = 0, j = 0, k = 0, m = 0;
	char a1 = ' ', a2 = ' ';
	for (i = 0; i < nR; i++)
	{
		for (j = 0; j < nS; j++)
		{
			if (R[i][1] == S[j][0]) //<a,b> of R,<b,c> of S then <a,c> in T
			{
				a1 = R[i][0];//��Ҫ��T��Ѱ������ż�Ƿ����
				a2 = S[j][1];
				m = 0;
				for (m = 0; m < k; m++)
				{
					//����Ѿ���������ֹ
					if ((T[m][0] == a1) && (T[m][1] == a2))
					{
						break;
					}
				}
				if (m >= k) //���ԭ�����������������
				{
					T[k][0] = a1;
					T[k][1] = a2;
					T[k][2] = '\0';
					k++;
				}
			}
		}
	}
	return k;
}
int relaSelf(char a[], char R[][3], int nR, char T[][3])
{
	//�Է��հ����жϼ���a�и���ż�Ƿ��ڹ�ϵR�г��֣���û�������������
	int i = 0, j = 0, k = 0;
	int nLen = 0;
	nLen = strlen(a);
	//�Ƚ���ϵRȫ��ת����T��
	for (i = 0; i < nR; i++)
	{
		T[i][0] = R[i][0];
		T[i][1] = R[i][1];
	}
	for (i = 0; i < nLen; i++)
	{
		for (j = 0; j < nR; j++)
		{
			if ((R[j][0] == a[i]) && (R[j][1] == a[i])) //<x,x> in R
			{
				break;
			}
		}
		if (j >= nR) //���ڹ�ϵR��
		{
			T[j][0] = a[i];
			T[j][1] = a[i];
			T[j][2] = '\0';
			nR++;
		}
	}
	return nR;
}

int relaSym(char R[][3], char T[][3], int nR)
{
	//�Է��հ�:�жϼ���a�и���ż�Ƿ��ڹ�ϵR�г��֣���û���ּ�������
	int i = 0, j = 0, k = 0;
	int nLen = nR;
	//�Ƚ���ϵRȫ��ת����T��
	for (i = 0; i < nR; i++)
	{
		T[i][0] = R[i][0];
		T[i][0] = R[i][0];
	}
	for (i = 0; i < nR; i++)
	{
		for (j = 0; j < nR; j++)
		{

			//ÿ����ż������ϵ��Ѱ�Ҷ�ż��ϵ�����ҵ������ǶԳƣ��������
			if ((R[j][0] == R[i][1]) && (R[j][1] == R[i][0])) //<x,y>,<y,a> inR
			{
				break;
			}
		}
		if (j >= nR) //���ǳɶԳ���
		{
			T[nLen][0] = R[i][1];
			T[nLen][1] = R[i][0];
			T[nLen][2] = '\0';
			nLen++;
		}
	}
	return nLen;
}

void rela2matrix(char a[], char R[][3], int nR, int M[][N])
{
	//��ϵ��������������������ڻ���Ԫ�ؼ�����a�е�ǰԪ�صĸ���
	int i = 0, j = 0, na = 0, k = 0, m = 0;
	na = strlen(a); //����Ԫ�صĸ���
	//��ϵ�����ÿ��Ԫ����0
//	for (i = 0; i < na; i++)
//	{
//		for (j = 0; j < na; j++)
//		{
//			M[i][j] = 0;
//		}
//	}
    memset(M,0,sizeof(M));
    /* �޸ĵ�4��ʹ��memset�������˫��ѭ����ʼ������ */

	//Ѱ�ҹ�ϵR��ÿ����ż֮Ԫ�ض�Ӧ����ţ�
	//�Ӷ�������M��ָ��λ���ó�1
	for (i = 0; i < nR; i++)
	{
		//ȷ����i����ż���׸�Ԫ���ڻ���Ԫ�ؼ��е����
		for (j = 0; j < na; j++)
		{
			if (R[i][0] == a[j])
			{
				k = j;
				break;
			}
		}
		//ȷ����i����ż�Ĵθ�Ԫ���ڻ���Ԫ�ؼ��е����
		for (j = 0; j < na; j++)
		{
			if (R[i][1] == a[j])
			{
				m = j;
				break;
			}
		}
		M[k][m] = 1;
	}
}

int matrix2rela(char a[], char R[][3], int M[][N])
{
	int i = 0, j = 0, k = 0, nLen = 0;
	nLen = strlen(a);
	for (i = 0; i < nLen; i++)
	{
		for (j = 0; j < nLen; j++)
		{
			if (M[i][j] == 1)
			{
				//�д���ż������Ҳ
				R[k][0] = a[i];
				R[k][1] = a[j];
				k++;
			}
		}
	}
	return k;
}
void matrixmulti(int M[][100], int R[][N], int T[][N], int n)
{
	//����������ˣ���������Ϊ1
	int i = 0, j = 0, k = 0, nsum = 0;
	for (i = 0; i < n; i++)
	{
		for(j=0; j<n; j++)
		{
			nsum = 0;
			for (k = 0; k < n; k++)
			{
				nsum = nsum + M[i][k] * R[k][j];
				if (nsum >= 1)
				{
					nsum = 1;
					break;
				}
			}
			T[i][j] = nsum;
		}
	}
}


int trorder(char R[][3], char RM[][3], int nR, int n)
{
	char T[1024][3], T2[1024][3];//��ϵR��i�η�
	int i = 0, nT = 0, j = 0, k = 0, nRM = 0, nT2 = 0;
	//�Ƚ�R���浽RM��
	for (i = 0; i < nR; i++)
	{
		RM[i][0] = R[i][0];
		RM[i][1] = R[i][1];
		T[i][0] = R[i][0];
		T[i][1] = R[i][1];
	}
	nRM = nR;
	nT = nR;
	for (i = 2; i <= n; i++)//n-1Ϊֹ
	{
		//��R@R�ĸ��Ϻ����ݴ浽T
		printRelaYsh(T, nT);
		printRelaYsh(R, nR);
		nT2 = relaCompose(T, R, T2, nT, nR);
		printRelaYsh(T2, nT2);
		printf("\n");
		//�������Ժ����ӵ�R�У��õ�R+R@R���޳��ظ���Ԫ��
		for (j = 0; j < nT2; j++)
		{
			for (k = 0; k < nRM; k++)
			{
				if ((T2[j][0] == RM[k][0]) && (T2[j][1] == RM[k][1]))
				{
					break;
				}
			}
			if (k >= nRM)//���û���ҵ������������
			{
				RM[nRM][0] = T2[j][0];
				RM[nRM][1] = T2[j][1];
				nRM++;
			}
		}
		//��T2���Ƹ�T
		for (j = 0; j < nT2; j++)
		{
			T[j][0] = T2[j][0];
			T[j][1] = T2[j][1];
		}
		nT = nT2;
	}
	return nRM;
}

int rPower(char R[][3], char T[][3], int nR, int n, int np)
{
	//R��np�η�
	char T2[1024][3];//��ϵR��i�η�
	int i = 0, nT = 0, j = 0, k = 0, nRM = 0, nT2 = 0;
	//�Ƚ�R���浽T��
	for (i = 0; i < nR; i++)
	{
		T[i][0] = R[i][0];
		T[i][1] = R[i][1];
	}
	nT = nR;
	for (i = 2; i <= np; i++) //n-1Ϊֹ
	{
		//��T@R�ĸ����ݴ浽T2
		nT2 = relaCompose(T, R, T2, nT, nR);
		//��T2���Ƹ�T
		for (j = 0; j < nT2; j++)
		{
			T[j][0] = T2[j][0];
			T[j][1] = T2[j][1];
		}
		nT = nT2;
	}
	return nT;
}

int trmatrix(int R[][N], int n)
{
	int i = 0, j = 0, k = 0;
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < n; i++)
		{
			if (R[i][j] == 1)
			{
				for (k = 0; k < n; k++)
				{
					//����j�мӵ���i��
					R[i][k] = R[i][k] + R[j][k];
					if (R[i][k] >= 1)
					{
						R[i][k] = 1;
					}
				}
			}
		}
	}
	return n;
}

int main()
{
	char a[1024], R1[1024][3], R2[1024][3], T[1024][3];
	int nLen1 = 0, nLen2 = 0, nT = 0, M[N][N], nChoice = 0;
	int MR1[N][N], MR2[N][N];
	int i = 0, n = 0;
	/* �޸ĵ�5�����ò��������Ż����� */
	bool flag=false;
	while (1)
	{
		printf("\n========================\n");
		if(!flag)
            printf("1...�������Ԫ��ֵ\n");
        if(flag)
        {
            printf("2...R1*R2��ϵ�ĸ���\n");
            printf("3...�Է��հ�\n");
            printf("4...�ԳƱհ�\n");
            printf("5...��ż��ʽ�Ĺ�ϵת��ϵ����\n");
            printf("6...���þ������ϵ�ĸ���\n");
            printf("7...������ż��ʽ�ĸ����󴫵ݱհ�\n");
            printf("8...����warshall�㷨���󴫵ݱհ�\n");
            printf("9...R2*R1��ϵ�ĸ���\n");
            printf("10..R1������η�\n");
            printf("11..R2������η�\n");
        }
		printf("0...�˳�\n");
		printf("========================\n����ѡ��: ");
		//scanf("%d", &nChoice);
		//fflush(stdin);
		/* �޸ĵ�6������while�ж������Ƿ�Ϸ� */
		while(scanf("%d",&nChoice))
            if((nChoice>=0&&nChoice<=8)) break;
            else printf("����������\n");
        
		if (nChoice == 0)
		{
			break;
		}

		switch (nChoice)
		{
			case 1:
			{
			    flag=true;
				printf("���뼯��a:");
				inputYsh(a);
				printf("�����ϵR1:");
				nLen1 = inputRelaYsh(R1);
				printf("�����ϵR2:");
				nLen2 = inputRelaYsh(R2);
				printf("A:");
				printYsh(a);
				printf("��ϵR1:");
				printRelaYsh(R1, nLen1);
				printf("��ϵR2:");
				printRelaYsh(R2, nLen2);
				break;
			}

			case 2:
			{
				nT = relaCompose(R1, R2, T, nLen1, nLen2);
				printf("R1@R2:");
				printRelaYsh(T, nT);
				break;
			}
			case 9:
			{
				nT = relaCompose(R2, R1, T, nLen2, nLen1);
				printf("R2@R1:");
				printRelaYsh(T, nT);
				break;
			}
			case 3:
			{
				nT = relaSelf(a, R1, nLen1, T);
				printf("R1���Է��հ���");
				printRelaYsh(T, nT);
				break;
			}
			case 4:
			{
				nT = relaSym(R1, T, nLen1);
				printf("R1�ĶԳƱհ���");
				printRelaYsh(T, nT);
				break;
			}
			case 5:
			{
				//��ż��ʽ�Ĺ�ϵת��Ϊ������ʽ
				rela2matrix(a, R1, nLen1, M);
				printf("R1��ϵ����ż");
				printRelaYsh(R1, nLen1);
				printf("R1��ϵ�ľ���\n");
				printRelaMatrix(M, strlen(a));
				break;
			}
			case 6:
			{
				//���þ������ϵ�ĸ���
				//�����������ϵ�Ĺ�ϵ����
				rela2matrix(a, R1, nLen1, MR1);
				printf("R1��ϵ�ľ���\n");
				printRelaMatrix(MR1, strlen(a));
				rela2matrix(a, R2, nLen2, MR2);
				printf("R2��ϵ�ľ���\n");
				printRelaMatrix(MR2, strlen(a));
				matrixmulti(MR1, MR2, M, strlen(a));
				printf("���Ϻ�ľ���\n");
				printRelaMatrix(M, strlen(a));
				printf("\n���Ϻ����ż");
				nT = matrix2rela(a, T, M);
				printRelaYsh(T, nT);
				break;
			}

			case 7://trorder(char R[][3],char RM[][3],int nR,int n)
			{
				nT = trorder(R1, T, nLen1, strlen(a));
				printf("R1�Ĵ��ݱհ�:");
				printRelaYsh(T, nT);
				printf("\n��żת��Ϊ����\n");
				rela2matrix(a, T, nT, M);
				printRelaMatrix(M, strlen(a));
				break;
			}
			case 8:
			{
				rela2matrix(a, R1, nLen1, M);
				printf("R1��ϵ����ż");
				printRelaYsh(R1, nLen1);
				printf("R1��ϵ�еľ���\n");
				printRelaMatrix(M, strlen(a));
				trmatrix(M, strlen(a));
				printf("warshall��ľ���\n");
				printRelaMatrix(M, strlen(a));
				printf("\n��ż");
				nT = matrix2rela(a, T, M);
				printRelaYsh(T, nT);
				break;
			}
			case 10:
			{
				printf("n=?");
				scanf("%d", &n);
				fflush(stdin);
				nT = rPower(R1, T, nLen1, strlen(a), n);
				printf("R1��%d�η���", n);
				printRelaYsh(T, nT);
				printf("\n��żת��Ϊ����\n");
				rela2matrix(a, T, nT, M);
				printRelaMatrix(M, strlen(a));
				break;
			}
			case 11:
			{
				printf("n=?");
				scanf("%d", &n);
				fflush(stdin);
				nT = rPower(R2, T, nLen2, strlen(a), n);
				printf("R2��%d�η���", n);
				printRelaYsh(T, nT);
				printf("\n��żת��Ϊ����\n");
				rela2matrix(a, T, nT, M);
				printRelaMatrix(M, strlen(a));
				break;
			}
			//��ż��ʽ�Ĺ�ϵ����ϵ����
			/*
			a,b,c,d,e
			<a,b>;<b,c>;<a,d>;<c,e>;<e,a>;<d,b>
			<b,a>;<c,b>;<d,a>;<e,c>;<a,e>;<b,d>
			*/
		}
	}
}

