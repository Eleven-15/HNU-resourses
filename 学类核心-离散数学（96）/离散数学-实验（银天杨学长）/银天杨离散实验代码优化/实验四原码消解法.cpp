//���ⷨ
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*����һ��ǰ�������밴�س�������ֱ�ӻس������
��+,��*,��-,˫=,��!
        ǰ����ֻ��Ϊ˫����������������ȡʽ,
��Ϊ2�������ĺ�ȡ,������2��ǰ��,����������ǰ������:
A
A-B
C-D
!B+!D

����Ҫ����Ľ��ۣ�����ֻ�������֣�
��������ʽ����ȡʽ�����ֹ�ת��Ϊ��������ǰ����Ϊ����ǰ�᣺!C
���Ƴ�����,�����������:
(1)     AΪ��                   ǰ������---����
(2)     A-BΪ��                 ǰ������
(3)     !A-BΪ��                        (2)����ʽתΪ��ȡʽ---����ʽ
(4)     C-DΪ��                 ǰ������
(5)     !C-DΪ��                        (4)����ʽתΪ��ȡʽ---����ʽ
(6)     !B-!DΪ��                       ǰ������---����ʽ
(7)     BΪ��                   (1)(3)����---����
(8)     !DΪ��                  (7)(6)����---����
(9)     !CΪ��                  (8)(5)����---����*/
struct tm{
	char gs[120],gsLast[120],niyou[120];//ǰ������������
	int nLitter,nUsed,isLitter,isCond; 
};
void nonoop2(char aa[])
{
	// !!p=p
	int i=0,j=0;
    while(i<strlen(aa)-2)//����  ����
	{
		if((i+1)<strlen(aa)&&aa[i]=='!'&&aa[i+1]=='!') 
		{
			j=i;
			while(j<strlen(aa)-2)
			{
				aa[j]=aa[j+2];
				j++;
			}
			aa[j]='\0';
			break;
		}
		else i++;
	 } 
} 

void printfYsh(struct tm tmrec[], int np)
{
	int i=0;
	for(i=0;i<np;i++)
	{
		if(tmrec[i].isLitter==1)
			printf("(%d)\t%sΪ��\t\t\t%s---����\n",i+1,tmrec[i].gs,tmrec[i].niyou);
        else if(tmrec[i].isCond==1)
            printf("(%d)\t%s-%sΪ��\t\t\t%s---����ʽ\n",i+1,tmrec[i].gs,tmrec[i].gsLast,tmrec[i].niyou);
        else
            printf("(%d)\t%sΪ��\t\t\t%s\n",i+1,tmrec[i].gs,tmrec[i].niyou);
	}
}
/* �޸ĵ�1����������λ�ã��������ֵ���δ���庯������� */
int setNiyou( struct tm tmrec[], int np, char ny0[], int j0, int j1, int nUsed0, int isCond0, int isLitter0 )
{
	//���ַ���ny0��j0�������������
	char stmpj0[20], stmpj1[20];
	int nLen1 = 0, j = 0, nLenj0 = 0, nLenj1 = 0;
	nLen1 = strlen( ny0 );
	itoa( j0 + 1, stmpj0, 10 );
	nLenj0 = strlen( stmpj0 );//ǰһ������
	itoa( j1 + 1, stmpj1, 10 );
	nLenj1 = strlen( stmpj1 );//��һ������
	if (j0 == -1)
	{
		//ԭʼǰ��
		for (j = 0; j < nLen1; j++)
			tmrec[np].niyou[j] = ny0[j];
		tmrec[np].niyou[j] = '\0';
	}
	else if (j1 == -1)//��ǰһ���������ý���
	{
		tmrec[np].niyou[0] = '(';
		for (j = 0; j < nLenj0; j++)
			tmrec[np].niyou[j + 1] = stmpj0[j];
		tmrec[np].niyou[j + 1] = ')';

		for (j = 0; j < nLen1; j++)
			tmrec[np].niyou[j + 2 + nLenj0] = ny0[j];
		tmrec[np].niyou[j + 2 + nLenj0] = '\0';
	}
	else
	{
		//��ǰ������������
		tmrec[np].niyou[0] = '(';
		for (j = 0; j < nLenj0; j++)
			tmrec[np].niyou[j + 1] = stmpj0[j];
		tmrec[np].niyou[j + 1] = ')';

		tmrec[np].niyou[nLenj0 + 2] = '(';
		for (j = 0; j < nLenj1; j++)
			tmrec[np].niyou[nLenj0 + 3 + j] = stmpj1[j];
		tmrec[np].niyou[nLenj0 + 3 + j] = ')';

		for (j = 0; j < nLen1; j++)
			tmrec[np].niyou[nLenj0 + nLenj1 + 4 + j] = ny0[j];
		tmrec[np].niyou[nLenj0 + nLenj1 + 4 + j] = '\0';
	}

	tmrec[np].nUsed = nUsed0;//����ǰ���δʹ�ù�nUsed0,int isCond0,int isLitter0
	tmrec[np].isCond = isCond0;//������ʽ
	tmrec[np].isLitter = isLitter0;//������
}
/*�޸ĵ�2����swap���� ��С������*/ 
void swaptm(tm &a,tm &b)
{
    tm temp;
    temp=a;
    a=b;
    b=temp;
}


int inputPrimary( struct tm gs0[] )
{
	struct tm tmp;
	char pstate[120];
	char *ny0 = "ǰ������";
	char *ny1 = "����ʽתΪ��ȡʽ";
	char *ny2 = "˫������������ȡʽ";
	int i = 0, j = 0, nLen = 0, k = 0;
	int i0 = 0;//ԭʼ����
	printf( "����һ��ǰ�������밴�س�������ֱ�ӻس������\n��+,��*,��-,˫=,��!\n\
	ǰ����ֻ��Ϊ˫����������������ȡʽ,\n��Ϊ2�������ĺ�ȡ,������2��ǰ��,����������ǰ������:\n" );
	while (1)
	{
		gets( pstate );
		nLen = strlen( pstate );
		if (nLen == 0)
		{
			break;
		}//����nUsed,isLitter,isCond,nLittle��ֵ
		//�ж��Ƿ�Ϊ����
		if (nLen == 1)//��ע��������
		{
			gs0[i].nLitter = strlen( pstate );
			gs0[i].gs[0] = pstate[0];
			gs0[i].gs[1] = '\0';
			gs0[i].gsLast[0] = '\0';
			setNiyou( gs0, i, ny0, -1, -1, 0, 0, 1 );//ǰ�����ͣ��ޣ��ޣ�δʹ�ã���������ʽ��������
		}
		else if ((nLen == 2) && (pstate[0] == '!')) //��ע��p
		{
			gs0[i].nLitter = strlen( pstate );
			gs0[i].gs[0] = pstate[0];
			gs0[i].gs[1] = pstate[1];
			gs0[i].gs[2] = '\0';
			gs0[i].gsLast[0] = '\0';
			setNiyou( gs0, i, ny0, -1, -1, 0, 0, 1 );//ǰ�����ͣ��ޣ��ޣ�δʹ�ã���������ʽ��������
		}
		else
		{
			for (j = 0; j < nLen; j++)
			{
				if (pstate[j] == '-')//��ע����ʽp-q
				{
					gs0[i].nLitter = strlen( pstate );
					for (k = 0; k < nLen; k++) //�˴�ѭ����ͬ����Ȼ���� 
						gs0[i].gs[k] = pstate[k];//�������ʽ����gs
					gs0[i].gs[k] = '\0';
					gs0[i].gsLast[0] = '\0';
					setNiyou( gs0, i, ny0, -1, -1, 0, 0, 0 );//ǰ�����ͣ��ޣ��ޣ�δʹ�ã�������ȡʽ����������

					i++;
					gs0[i].nLitter = gs0[i - 1].nLitter;
					gs0[i].gs[0] = '!';
					for (k = 0; k < j; k++)
						gs0[i].gs[k + 1] = pstate[k];
					gs0[i].gs[k + 1] = '\0';
					nonoop2( gs0[i].gs ); 

					for (k = j + 1; k < nLen; k++)
						gs0[i].gsLast[k - j - 1] = pstate[k];
					gs0[i].gsLast[k - j - 1] = '\0';
					setNiyou( gs0, i, ny1, i - 1, -1, 0, 1, 0 );//ǰ�����ͣ��ޣ��ޣ�δʹ�ã�������ʽ����������
					break;
				}

				else if (pstate[j] == '=')//��ע˫����p=q
				{
					//�ȱ���˫����
					gs0[i].nLitter = strlen( pstate );
					for (k = 0; k < strlen( pstate ); k++) { gs0[i].gs[k] = pstate[k]; }//˫����ȫ����gs
					gs0[i].gs[k] = '\0';
					gs0[i].gsLast[0] = '\0';
					setNiyou( gs0, i, ny0, -1, -1, 0, 0, 0 );//ǰ�����ͣ��ޣ��ޣ�δʹ�ã�������ʽ����������
															 //p-q��!p+q
					i++;
					gs0[i].nLitter = strlen( pstate );
					gs0[i].gs[0] = '!';
					for (k = 0; k < j; k++) { gs0[i].gs[k + 1] = pstate[k]; }//p��gs
					gs0[i].gs[k + 1] = '\0';
					for (k = j + 1; k < nLen; k++) { gs0[i].gsLast[k - j - 1] = pstate[k]; }//q��gsLast
					gs0[i].gsLast[k - j - 1] = '\0';
					setNiyou( gs0, i, ny2, i - 1, -1, 0, 1, 0 );//ǰ�����ͣ��ޣ��ޣ�δʹ�ã�������ʽ����������
					nonoop2( gs0[i].gs );//ȥ�����ܴ��ڵ�!!?
										 //q-p=p+!q
					i++;
					gs0[i].nLitter = gs0[i - 1].nLitter;
					for (k = 0; k < j; k++) { gs0[i].gs[k] = pstate[k]; }//����ǰ��p��gs
					gs0[i].gs[k] = '\0';
					gs0[i].gsLast[0] = '!';
					for (k = j + 1; k < nLen; k++) { gs0[i].gsLast[k - j - 1 + 1] = pstate[k]; }//�������!q��gsLast
					gs0[i].gsLast[k - j - 1 + 1] = '\0';
					setNiyou( gs0, i, ny2, i - 2, -1, 0, 1, 0 );//ǰ�����ͣ��ޣ��ޣ�δʹ�ã�������ʽ����������
					nonoop2( gs0[i].gsLast );//ȥ�����ܴ��ڵ�!!?
					break;

				}

				else if (pstate[j] == '+')//��ע��ȡʽp+q��ҲҪ�ֽ⵽gs��gsLast��
				{
					gs0[i].nLitter = strlen( pstate );
					for (k = 0; k < j; k++)
						gs0[i].gs[k] = pstate[k];    //ǰ����gs
					gs0[i].gs[k] = '\0';
					for (k = j + 1; k < nLen; k++)
						gs0[i].gsLast[k - j - 1] = pstate[k];    //����ȫ����gs
					gs0[i].gsLast[k - j - 1] = '\0';
					setNiyou( gs0, i, ny0, -1, -1, 0, 1, 0 );//ǰ������,�ޣ��ޣ�δʹ�ã�������ʽ����������
					break;
				}
			}
			if (j >= nLen)//��������ʽ��Ҳ�������֣�������ͨ������
			{
				gs0[i].nLitter = strlen( pstate );
				for (k = 0; k < nLen; k++)
					gs0[i].gs[k] = pstate[k];    //��ʽȫ��gs
				gs0[i].gs[k] = '\0';
				gs0[i].gsLast[0] = '\0'; //gsLastΪ�մ�
				setNiyou( gs0, i, ny0, -1, -1, 0, 0, 0 );//ǰ�����ͣ��ޣ��ޣ�δʹ�ã���������ʽ����������
			}
		}
		i++;//��ǰ��ʽ�������Ժ�ָ��i��ֵ��1
	}
	nLen = i;//���ַ����ĳ�������
	for (i = 0; i < nLen - 1; i++)
	{
		k = i;
		/* �޸ĵ�3���޸�ѭ������ʹ������Ԫ�ؿ����� nlen-1 ��Ϊnlen */
		for (j = i + 1; j < nLen ; j++)
			if (gs0[k].nLitter > gs0[j].nLitter)
				k = j;
		if (k > i)
		{
			/* �޸ĵ�4��ʹ���Զ����swaptmd���� */
			swaptm(gs0[i],gs0[k]);
			/*tmp = gs0[i];
			gs0[i] = gs0[k];
			gs0[k] = tmp;*/
		}
	}
	return nLen;
}

int main ()
{
	struct tm gs0[100];//����ǰ������
	char result0[128]; //����
	struct tm tmrec[1024];//���1000��

	char stmp[128];
	char lastNiYou[128] = " ";//��һ������ʽ������
	char *ny01 = "����";
	int i = 0, j = 0, k = 0;
	int np = 1, np0 = 0, isOk = 0;
	int i0 = 0, nPosLitter = 0, nPosCond = 0;//������ʼ��λ�ã��׸����ֵ�λ�ã�����ʽ��λ��
	np0 = inputPrimary( gs0 );
	//�������
	printf( "����Ҫ����Ľ��ۣ�����ֻ�������֣�\n��������ʽ����ȡʽ�����ֹ�ת��Ϊ��������ǰ����Ϊ����ǰ�᣺" );
	gets( result0 );
	fflush( stdin );
	for (i = 0; i < np0; i++)
	{
		tmrec[i] = gs0[i];//����ԭʼ��ʽת����tmrec��
	}
	np = i;//������е�β��ָ��
	nPosLitter = 0;//���ֵ�λ�ú�
	nPosCond = 0;//������λ�ú�
	isOk = 0;
	i0 = -1;
	while (1)
	{
		i = i0 + 1;//Ѱ����һ�����֣�i����ʼλ�ã�np������ĳ���
		while ((i < np) && (tmrec[i].isLitter != 1))
			i++;
		if (i >= np)
			break;//�Ҳ��������Ҿ�û��������
		i0 = i;//��¼��Դͷ��ѯ���׸����ֵ�λ�úţ��´δӴ˺�����Ѱ��
		nPosLitter = i;//��¼���ֵ�λ��
		strcpy( stmp, tmrec[i].gs );//���浱ǰ���ֵ�����
		np0 = np - 1;
		while (np > np0) //�ӵ�ǰ���ֵ���һ��λ����Ѱ����ȡʽ����һ·������
		{
			np0 = np;
			for (i = 0; i < np; i++)//�ҵ�һ��û���ù���Ϸ��ʽ
				if ((tmrec[i].isCond == 1) && (tmrec[i].nUsed == 0))
					break;
			if (i == np)
				break;//û���ҵ������������������ʽ���õ���
			while (i < np)//���ҵ�������������ʽ
			{
				if ((tmrec[i].isCond == 1))//��������ʽ
				{
					//�������������Դ��ͬ�����ߵ���ͬΪǰ������Ҳ�ǿ��Եģ����׸��ַ����ǣ�
					if (((strcmp( lastNiYou, tmrec[i].niyou ) != 0) || ((strcmp( lastNiYou, tmrec[i].niyou ) == 0) && tmrec[i].niyou[0] != '(')))
					{

						if ((tmrec[i].gs[0] == '!') && (stmp[0] != '!') && (strlen( tmrec[i].gs ) - strlen( stmp ) == 1))    ////////// !p+q p cuo
						{
							//�����ȡʽ��ǰ����stmp�������⣬�򽫺�������stmp��
							j = 0;
							while (j < strlen( stmp ))//���αȽ�ÿ���ַ�
							{
								if (tmrec[i].gs[j + 1] != stmp[j])
									break;//��һ�������������Ƚ�
								j++;
							}

							if (j >= strlen( stmp ))  //����ȵ������Ȼ��ȣ��������������
							{
								strcpy( lastNiYou, tmrec[i].niyou );
								tmrec[nPosLitter].nUsed++;  //��������ù�һ����
								tmrec[i].nUsed++;  //�����ȡʽ�ù�һ����

								strcpy( stmp, tmrec[i].gsLast );  //�������������浽�Ƶ�������
								strcpy( tmrec[np].gs, stmp );  //����ǰ�Ƴ����Ľ����������
								tmrec[np].gsLast[0] = '\0';  //�����գ����浱ǰ����
								setNiyou( tmrec, np, ny01, nPosLitter, i, 0, 0, 1 );  //ǰ�����ͣ��У��ޣ�δʹ�ã���������
								nPosLitter = np;  //��¼��ǰ���ֵ����
								np++;
								if (strcmp( result0, stmp ) == 0)
								{
									isOk = 1;    //�Ƴ�����ͬ��ԭ�ǵ��ڵ���һ��
									break;
								}
							}
						}
						else if ((tmrec[i].gsLast[0] == '!') && (stmp[0] != '!') && (strlen( tmrec[i].gsLast ) - strlen( stmp ) == 1))		//a+!b  b dui
						{
							//�����ȡʽ�ĺ����stmp�������⣬��ǰ�����浽stmp��
							j = 0;
							while (j < strlen( stmp ))  //���αȽ�ÿһ���ַ�
							{
								if (tmrec[i].gsLast[j + 1] != stmp[j])
									break;    //��һ�������������Ƚ�
								j++;
							}
							if (j >= strlen( stmp ))  //����ȵ������Ȼ��ȣ���������������
							{
								strcpy( lastNiYou, tmrec[i].niyou );
								tmrec[nPosLitter].nUsed++;  //��������ù�һ����
								tmrec[i].nUsed++;  //�����ȡʽ�ù�һ����

								strcpy( stmp, tmrec[i].gs );  //�������������浽�Ƶ�������
								strcpy( tmrec[np].gs, stmp );  //����ǰ�Ƴ����Ľ����������
								tmrec[np].gsLast[0] = '\0';  //�����գ����浱ǰ����
								setNiyou( tmrec, np, ny01, nPosLitter, i, 0, 0, 1 );  //ǰ�����ͣ��У��ޣ�δʹ�ã���������
								nPosLitter = np;  //��¼��ǰ���ֵ����
								np++;
								if (strcmp( result0, stmp ) == 0)
								{
									isOk = 1;    //�Ƴ�����ͬ��ԭ�ǵ��ڵ���һ��
									break;
								}
							}
						}
						else if ((tmrec[i].gs[0] != '!') && (stmp[0] == '!') && (strlen( tmrec[i].gs ) - strlen( stmp ) == -1))		//	p+q !p
						{
							//�����ȡʽ�ĺ����stmp�������⣬��ǰ�����浽stmp��
							j = 0;
							while (j < strlen( tmrec[i].gs ))  //���αȽ�ÿһ���ַ�
							{
								if (stmp[j + 1] != tmrec[i].gs[j])
									break;    //��һ�������������Ƚ�
								j++;
							}
							if (j >= strlen( tmrec[i].gs ))
							{
								strcpy( lastNiYou, tmrec[i].niyou );
								tmrec[nPosLitter].nUsed++;  //��������ù�һ����
								tmrec[i].nUsed++;  //�����ȡʽ�ù�һ����

								strcpy( stmp, tmrec[i].gsLast );  //�������������浽�Ƶ�������
								strcpy( tmrec[np].gs, stmp );  //����ǰ�Ƴ����Ľ����������
								tmrec[np].gsLast[0] = '\0';  //�����գ����浱ǰ����
								setNiyou( tmrec, np, ny01, nPosLitter, i, 0, 0, 1 );  //ǰ�����ͣ��У��ޣ�δʹ�ã���������
								nPosLitter = np;  //��¼��ǰ���ֵ����
								np++;
								if (strcmp( result0, stmp ) == 0)
								{
									isOk = 1;    //�Ƴ�����ͬ��ԭ�ǵ��ڵ���һ��
									break;
								}
							}

						}
						else if ((tmrec[i].gsLast[0] != '!') && (stmp[0] == '!') && (strlen( tmrec[i].gsLast ) - strlen( stmp ) == -1))		//p+q !q
						{
							//�����ȡʽ�ĺ����stmp�������⣬��ǰ�����浽stmp��
							j = 0;
							while (j < strlen( tmrec[i].gsLast ))//���αȽ�ÿһ���ַ�
							{
								if (stmp[j + 1] != tmrec[i].gsLast[j])
									break;    //��һ�������������Ƚ�
								j++;
							}
							if (j >= strlen( tmrec[i].gsLast ))//����ȵ������Ȼ��ȣ���������������
							{
								strcpy( lastNiYou, tmrec[i].niyou );
								tmrec[nPosLitter].nUsed++;	//��������ù�һ����
								tmrec[i].nUsed++;			//��������ù�һ����

								strcpy( stmp, tmrec[i].gs );	    //�����м������浽�Ƶ�������
								strcpy( tmrec[np].gs, stmp );		//����ǰ�Ƴ����Ľ����������
								tmrec[np].gsLast[0] = '\0';		//�����գ����浱ǰ����
								setNiyou( tmrec, np, ny01, nPosLitter, i, 0, 0, 1 );//ǰ�����ͣ��У��ޣ�δʹ�ã���������ʽ
								nPosLitter = np;		            //��¼��ǰ���ֵ����
								np++;
								if (strcmp( result0, stmp ) == 0)
								{
									isOk = 1;    //�Ƴ�����ͬԭʼ��������һ��
									break;
								}
							}
						}
					}
				}
				i++;//�ж���һ�����ʽ�Ƿ�Ϊ�������Ƿ�Ϊ�����������ʽ
			}
		}
		if (isOk == 1)
			break;    //���Ƴ����ˣ���Ҫ������һ��������
	}
	if (isOk == 1)
		printf( "���Ƴ�����,�����������:\n" );
	else
		printf( "���Ʋ�����,�����������:\n" );
	printfYsh( tmrec, np );

}


