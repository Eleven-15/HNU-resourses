//消解法
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*输完一个前提条件请按回车，不输直接回车则结束
析+,合*,条-,双=,否定!
        前提中只能为双条件、单条件、析取式,
若为2个条件的合取,请输入2个前提,文字请在最前面输入:
A
A-B
C-D
!B+!D

输入要推理的结论，结论只能是文字，
若是条件式，析取式请先手工转换为条件，将前件作为附加前提：!C
我推出来了,推理过程如下:
(1)     A为真                   前提条件---文字
(2)     A-B为真                 前提条件
(3)     !A-B为真                        (2)条件式转为析取式---条件式
(4)     C-D为真                 前提条件
(5)     !C-D为真                        (4)条件式转为析取式---条件式
(6)     !B-!D为真                       前提条件---条件式
(7)     B为真                   (1)(3)消解---文字
(8)     !D为真                  (7)(6)消解---文字
(9)     !C为真                  (8)(5)消解---文字*/
struct tm{
	char gs[120],gsLast[120],niyou[120];//前件与后件及理由
	int nLitter,nUsed,isLitter,isCond; 
};
void nonoop2(char aa[])
{
	// !!p=p
	int i=0,j=0;
    while(i<strlen(aa)-2)//减二  ！！
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
			printf("(%d)\t%s为真\t\t\t%s---文字\n",i+1,tmrec[i].gs,tmrec[i].niyou);
        else if(tmrec[i].isCond==1)
            printf("(%d)\t%s-%s为真\t\t\t%s---条件式\n",i+1,tmrec[i].gs,tmrec[i].gsLast,tmrec[i].niyou);
        else
            printf("(%d)\t%s为真\t\t\t%s\n",i+1,tmrec[i].gs,tmrec[i].niyou);
	}
}
/* 修改点1：调换函数位置，否则会出现调用未定义函数的情况 */
int setNiyou( struct tm tmrec[], int np, char ny0[], int j0, int j1, int nUsed0, int isCond0, int isLitter0 )
{
	//将字符串ny0与j0赋到推理意见中
	char stmpj0[20], stmpj1[20];
	int nLen1 = 0, j = 0, nLenj0 = 0, nLenj1 = 0;
	nLen1 = strlen( ny0 );
	itoa( j0 + 1, stmpj0, 10 );
	nLenj0 = strlen( stmpj0 );//前一个依据
	itoa( j1 + 1, stmpj1, 10 );
	nLenj1 = strlen( stmpj1 );//后一个依据
	if (j0 == -1)
	{
		//原始前提
		for (j = 0; j < nLen1; j++)
			tmrec[np].niyou[j] = ny0[j];
		tmrec[np].niyou[j] = '\0';
	}
	else if (j1 == -1)//由前一步推理所得结论
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
		//由前二步推理所得
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

	tmrec[np].nUsed = nUsed0;//附加前提从未使用过nUsed0,int isCond0,int isLitter0
	tmrec[np].isCond = isCond0;//是条件式
	tmrec[np].isLitter = isLitter0;//是文字
}
/*修改点2构建swap函数 减小代码量*/ 
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
	char *ny0 = "前提条件";
	char *ny1 = "条件式转为析取式";
	char *ny2 = "双条件导出的析取式";
	int i = 0, j = 0, nLen = 0, k = 0;
	int i0 = 0;//原始条件
	printf( "输完一个前提条件请按回车，不输直接回车则结束\n析+,合*,条-,双=,否定!\n\
	前提中只能为双条件、单条件、析取式,\n若为2个条件的合取,请输入2个前提,文字请在最前面输入:\n" );
	while (1)
	{
		gets( pstate );
		nLen = strlen( pstate );
		if (nLen == 0)
		{
			break;
		}//设置nUsed,isLitter,isCond,nLittle的值
		//判断是否为文字
		if (nLen == 1)//标注单个文字
		{
			gs0[i].nLitter = strlen( pstate );
			gs0[i].gs[0] = pstate[0];
			gs0[i].gs[1] = '\0';
			gs0[i].gsLast[0] = '\0';
			setNiyou( gs0, i, ny0, -1, -1, 0, 0, 1 );//前提类型，无，无，未使用，不是条件式，是文字
		}
		else if ((nLen == 2) && (pstate[0] == '!')) //标注！p
		{
			gs0[i].nLitter = strlen( pstate );
			gs0[i].gs[0] = pstate[0];
			gs0[i].gs[1] = pstate[1];
			gs0[i].gs[2] = '\0';
			gs0[i].gsLast[0] = '\0';
			setNiyou( gs0, i, ny0, -1, -1, 0, 0, 1 );//前提类型，无，无，未使用，不是条件式，是文字
		}
		else
		{
			for (j = 0; j < nLen; j++)
			{
				if (pstate[j] == '-')//标注条件式p-q
				{
					gs0[i].nLitter = strlen( pstate );
					for (k = 0; k < nLen; k++) //此处循环不同于自然推理 
						gs0[i].gs[k] = pstate[k];//整个表达式进入gs
					gs0[i].gs[k] = '\0';
					gs0[i].gsLast[0] = '\0';
					setNiyou( gs0, i, ny0, -1, -1, 0, 0, 0 );//前提类型，无，无，未使用，不是析取式，不是文字

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
					setNiyou( gs0, i, ny1, i - 1, -1, 0, 1, 0 );//前提类型，无，无，未使用，是条件式，不是文字
					break;
				}

				else if (pstate[j] == '=')//标注双条件p=q
				{
					//先保存双条件
					gs0[i].nLitter = strlen( pstate );
					for (k = 0; k < strlen( pstate ); k++) { gs0[i].gs[k] = pstate[k]; }//双条件全部进gs
					gs0[i].gs[k] = '\0';
					gs0[i].gsLast[0] = '\0';
					setNiyou( gs0, i, ny0, -1, -1, 0, 0, 0 );//前提类型，无，无，未使用，是条件式，不是文字
															 //p-q即!p+q
					i++;
					gs0[i].nLitter = strlen( pstate );
					gs0[i].gs[0] = '!';
					for (k = 0; k < j; k++) { gs0[i].gs[k + 1] = pstate[k]; }//p进gs
					gs0[i].gs[k + 1] = '\0';
					for (k = j + 1; k < nLen; k++) { gs0[i].gsLast[k - j - 1] = pstate[k]; }//q进gsLast
					gs0[i].gsLast[k - j - 1] = '\0';
					setNiyou( gs0, i, ny2, i - 1, -1, 0, 1, 0 );//前提类型，无，无，未使用，是条件式，不是文字
					nonoop2( gs0[i].gs );//去掉可能存在的!!?
										 //q-p=p+!q
					i++;
					gs0[i].nLitter = gs0[i - 1].nLitter;
					for (k = 0; k < j; k++) { gs0[i].gs[k] = pstate[k]; }//条件前件p进gs
					gs0[i].gs[k] = '\0';
					gs0[i].gsLast[0] = '!';
					for (k = j + 1; k < nLen; k++) { gs0[i].gsLast[k - j - 1 + 1] = pstate[k]; }//条件后件!q进gsLast
					gs0[i].gsLast[k - j - 1 + 1] = '\0';
					setNiyou( gs0, i, ny2, i - 2, -1, 0, 1, 0 );//前提类型，无，无，未使用，是条件式，不是文字
					nonoop2( gs0[i].gsLast );//去掉可能存在的!!?
					break;

				}

				else if (pstate[j] == '+')//标注析取式p+q，也要分解到gs与gsLast中
				{
					gs0[i].nLitter = strlen( pstate );
					for (k = 0; k < j; k++)
						gs0[i].gs[k] = pstate[k];    //前件进gs
					gs0[i].gs[k] = '\0';
					for (k = j + 1; k < nLen; k++)
						gs0[i].gsLast[k - j - 1] = pstate[k];    //条件全部进gs
					gs0[i].gsLast[k - j - 1] = '\0';
					setNiyou( gs0, i, ny0, -1, -1, 0, 1, 0 );//前提类型,无，无，未使用，是条件式，不是文字
					break;
				}
			}
			if (j >= nLen)//不是条件式，也不是文字，则是普通的条件
			{
				gs0[i].nLitter = strlen( pstate );
				for (k = 0; k < nLen; k++)
					gs0[i].gs[k] = pstate[k];    //公式全进gs
				gs0[i].gs[k] = '\0';
				gs0[i].gsLast[0] = '\0'; //gsLast为空串
				setNiyou( gs0, i, ny0, -1, -1, 0, 0, 0 );//前提类型，无，无，未使用，不是条件式，不是文字
			}
		}
		i++;//当前公式处理完以后，指针i的值增1
	}
	nLen = i;//按字符串的长度排序
	for (i = 0; i < nLen - 1; i++)
	{
		k = i;
		/* 修改点3：修改循环条件使得最后的元素可排序 nlen-1 变为nlen */
		for (j = i + 1; j < nLen ; j++)
			if (gs0[k].nLitter > gs0[j].nLitter)
				k = j;
		if (k > i)
		{
			/* 修改点4：使用自定义的swaptmd排序 */
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
	struct tm gs0[100];//推理前提条件
	char result0[128]; //结论
	struct tm tmrec[1024];//最多1000步

	char stmp[128];
	char lastNiYou[128] = " ";//上一个推理式的理由
	char *ny01 = "消解";
	int i = 0, j = 0, k = 0;
	int np = 1, np0 = 0, isOk = 0;
	int i0 = 0, nPosLitter = 0, nPosCond = 0;//文字起始的位置，首个文字的位置，消解式的位置
	np0 = inputPrimary( gs0 );
	//输入结论
	printf( "输入要推理的结论，结论只能是文字，\n若是条件式，析取式请先手工转换为条件，将前件作为附加前提：" );
	gets( result0 );
	fflush( stdin );
	for (i = 0; i < np0; i++)
	{
		tmrec[i] = gs0[i];//所有原始公式转抄到tmrec中
	}
	np = i;//推理队列的尾部指针
	nPosLitter = 0;//文字的位置号
	nPosCond = 0;//条件的位置号
	isOk = 0;
	i0 = -1;
	while (1)
	{
		i = i0 + 1;//寻找下一个文字，i是起始位置，np是命令串的长度
		while ((i < np) && (tmrec[i].isLitter != 1))
			i++;
		if (i >= np)
			break;//找不到文字我就没法推理了
		i0 = i;//记录从源头查询的首个文字的位置号，下次从此号往后寻找
		nPosLitter = i;//记录文字的位置
		strcpy( stmp, tmrec[i].gs );//保存当前文字的内容
		np0 = np - 1;
		while (np > np0) //从当前文字的下一个位置起寻找析取式，则一路往下走
		{
			np0 = np;
			for (i = 0; i < np; i++)//找到一个没有用过的戏曲式
				if ((tmrec[i].isCond == 1) && (tmrec[i].nUsed == 0))
					break;
			if (i == np)
				break;//没有找到则结束推理，所有条件式都用到了
			while (i < np)//若找到了这样的条件式
			{
				if ((tmrec[i].isCond == 1))//若是条件式
				{
					//与上条命令的来源不同，或者但是同为前提条件也是可以的，即首个字符不是（
					if (((strcmp( lastNiYou, tmrec[i].niyou ) != 0) || ((strcmp( lastNiYou, tmrec[i].niyou ) == 0) && tmrec[i].niyou[0] != '(')))
					{

						if ((tmrec[i].gs[0] == '!') && (stmp[0] != '!') && (strlen( tmrec[i].gs ) - strlen( stmp ) == 1))    ////////// !p+q p cuo
						{
							//如果析取式的前件与stmp即可消解，则将后件保存的stmp中
							j = 0;
							while (j < strlen( stmp ))//依次比较每个字符
							{
								if (tmrec[i].gs[j + 1] != stmp[j])
									break;//有一个不相等则结束比较
								j++;
							}

							if (j >= strlen( stmp ))  //如果比到最后仍然相等，则这二个可消解
							{
								strcpy( lastNiYou, tmrec[i].niyou );
								tmrec[nPosLitter].nUsed++;  //这个文字用过一次了
								tmrec[i].nUsed++;  //这个析取式用过一次了

								strcpy( stmp, tmrec[i].gsLast );  //将次消解结果保存到推导序列中
								strcpy( tmrec[np].gs, stmp );  //将当前推出来的结果保存起来
								tmrec[np].gsLast[0] = '\0';  //后件清空，保存当前条件
								setNiyou( tmrec, np, ny01, nPosLitter, i, 0, 0, 1 );  //前提类型，有，无，未使用，不是条件
								nPosLitter = np;  //记录当前文字的序号
								np++;
								if (strcmp( result0, stmp ) == 0)
								{
									isOk = 1;    //推出结论同条原是调节的下一轮
									break;
								}
							}
						}
						else if ((tmrec[i].gsLast[0] == '!') && (stmp[0] != '!') && (strlen( tmrec[i].gsLast ) - strlen( stmp ) == 1))		//a+!b  b dui
						{
							//如果析取式的后件与stmp即可消解，则将前件保存到stmp中
							j = 0;
							while (j < strlen( stmp ))  //依次比较每一个字符
							{
								if (tmrec[i].gsLast[j + 1] != stmp[j])
									break;    //有一个不相等则结束比较
								j++;
							}
							if (j >= strlen( stmp ))  //如果比到最后仍然相等，则这两个可消解
							{
								strcpy( lastNiYou, tmrec[i].niyou );
								tmrec[nPosLitter].nUsed++;  //这个文字用过一次了
								tmrec[i].nUsed++;  //这个析取式用过一次了

								strcpy( stmp, tmrec[i].gs );  //将次消解结果保存到推导序列中
								strcpy( tmrec[np].gs, stmp );  //将当前推出来的结果保存起来
								tmrec[np].gsLast[0] = '\0';  //后件清空，保存当前条件
								setNiyou( tmrec, np, ny01, nPosLitter, i, 0, 0, 1 );  //前提类型，有，无，未使用，不是条件
								nPosLitter = np;  //记录当前文字的序号
								np++;
								if (strcmp( result0, stmp ) == 0)
								{
									isOk = 1;    //推出结论同条原是调节的下一轮
									break;
								}
							}
						}
						else if ((tmrec[i].gs[0] != '!') && (stmp[0] == '!') && (strlen( tmrec[i].gs ) - strlen( stmp ) == -1))		//	p+q !p
						{
							//如果析取式的后件与stmp即可消解，则将前件保存到stmp中
							j = 0;
							while (j < strlen( tmrec[i].gs ))  //依次比较每一个字符
							{
								if (stmp[j + 1] != tmrec[i].gs[j])
									break;    //有一个不相等则结束比较
								j++;
							}
							if (j >= strlen( tmrec[i].gs ))
							{
								strcpy( lastNiYou, tmrec[i].niyou );
								tmrec[nPosLitter].nUsed++;  //这个文字用过一次了
								tmrec[i].nUsed++;  //这个析取式用过一次了

								strcpy( stmp, tmrec[i].gsLast );  //将次消解结果保存到推导序列中
								strcpy( tmrec[np].gs, stmp );  //将当前推出来的结果保存起来
								tmrec[np].gsLast[0] = '\0';  //后件清空，保存当前条件
								setNiyou( tmrec, np, ny01, nPosLitter, i, 0, 0, 1 );  //前提类型，有，无，未使用，不是条件
								nPosLitter = np;  //记录当前文字的序号
								np++;
								if (strcmp( result0, stmp ) == 0)
								{
									isOk = 1;    //推出结论同条原是调节的下一轮
									break;
								}
							}

						}
						else if ((tmrec[i].gsLast[0] != '!') && (stmp[0] == '!') && (strlen( tmrec[i].gsLast ) - strlen( stmp ) == -1))		//p+q !q
						{
							//如果析取式的后件与stmp即可消解，则将前件保存到stmp中
							j = 0;
							while (j < strlen( tmrec[i].gsLast ))//依次比较每一个字符
							{
								if (stmp[j + 1] != tmrec[i].gsLast[j])
									break;    //有一个不相等则结束比较
								j++;
							}
							if (j >= strlen( tmrec[i].gsLast ))//如果比到最后仍然相等，则这两个可消解
							{
								strcpy( lastNiYou, tmrec[i].niyou );
								tmrec[nPosLitter].nUsed++;	//这个文字用过一次了
								tmrec[i].nUsed++;			//这个条件用过一次了

								strcpy( stmp, tmrec[i].gs );	    //将此中间结果保存到推导序列中
								strcpy( tmrec[np].gs, stmp );		//将当前推出来的结果保存起来
								tmrec[np].gsLast[0] = '\0';		//后件清空，保存当前条件
								setNiyou( tmrec, np, ny01, nPosLitter, i, 0, 0, 1 );//前提类型，有，无，未使用，不是条件式
								nPosLitter = np;		            //记录当前文字的序号
								np++;
								if (strcmp( result0, stmp ) == 0)
								{
									isOk = 1;    //推出结论同原始条件的下一轮
									break;
								}
							}
						}
					}
				}
				i++;//判断下一个表达式是否为条件，是否为可推理的条件式
			}
		}
		if (isOk == 1)
			break;    //我推出来了，不要再找下一个文字了
	}
	if (isOk == 1)
		printf( "我推出来了,推理过程如下:\n" );
	else
		printf( "我推不出来,推理过程如下:\n" );
	printfYsh( tmrec, np );

}


