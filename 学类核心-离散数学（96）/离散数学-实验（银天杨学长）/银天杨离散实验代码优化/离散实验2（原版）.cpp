#include <bits/stdc++.h>
using namespace std;
int getalpha(char a[], char b[]){
	char tmpc = ' ';
	int n = strlen(a), i = 0, j = 0, k = 0;
	for (i = 0; i<n; i++){
		if (((a[i] >= 'a') && (a[i] <= 'z')) || ((a[i] >= 'A') && (a[i] <= 'Z'))){
			/*for (k = 0; k<j; k++){
				if (b[k] == a[i]){
					break;
				}
			}
			if (k >= j){
				b[j] = a[i];
				j++;
			}*/
			/* 修改点1：用strchr函数替代循环搜索，优化了运行速度 */
            if(strchr(b,a[i])==NULL)
            {
                b[j]=a[i];
                j++;
            }
		}
	}
	/*for (i = 0; i<j - 1; i++){
		for (k = 0; k<j - i - 1; k++){
			if (b[k]>b[k + 1]){
				tmpc = b[k];
				b[k] = b[k + 1];
				b[k + 1] = tmpc;
			}
		}
	}*/
	/* 修改点2：用sort函数替代冒泡排序，优化了运行速度 */
    sort(b,b+j);
	b[j] = '\0';
	return j;
}
void fillValue(char a[], char varchar[], int nvar, char valchar[], char resultchar[]){
	int nLen = strlen(a), i = 0, j = 0, k = 0;
	for (i = 0; i<nLen; i++){
		resultchar[i] = a[i];
	}
	resultchar[i] = '\0';
	for (i = 0; i<nLen; i++){
		for (j = 0; j<nvar; j++){
			if (resultchar[i] == varchar[j]){
				resultchar[i] = valchar[j];
				break;
			}
		}
	}
}
/* 修改点3：重复代码编写成函数，减少代码量 */
void eraser(int r,int &i,int &j,char a[],int w)
{
    if(r==1)
    {
        j++;
        while(a[j+w]!='\0')
        {
            a[j]=a[j+w];
            j++;
        }
        a[j]='\0';
    }
    else
        i++;
}
void negatecal(char a[]){
	int _result = 0, i = 0, j = 0;
	while (i<strlen(a)){
		j = i;
		_result = 0;
		if ((j + 1<strlen(a)) && (a[j] == '!') && (a[j + 1] == '1')){
			a[j] = '0'; _result = 1;
		}
		else if ((j + 1<strlen(a)) && (a[j] == '!') && (a[j + 1] == '0')){
			a[j] = '1'; _result = 1;
		}
		/*if (_result == 1){
			j++;
			while (a[j + 1] != '\0'){
				a[j] = a[j + 1];
				j++;
			}
			a[j] = '\0';
		}
		else{
			i++;
		}*/
		eraser(_result,i,j,a,1);
	}
}
void kuanhao(char a[]){
	int _result = 0, i = 0, j = 0;
	while (i<strlen(a)){
		j = i;
		_result = 0;
		if ((j + 2<strlen(a)) && (a[j] == '(') && (a[j + 1] == '1') && (a[j + 2] == ')')){
			a[j] = '1';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '(') && (a[j + 1] == '0') && (a[j + 2] == ')')){
			a[j] = '0';
			_result = 1;
		}
		/*if (_result == 1){
			j++;
			while (a[j + 2] != '\0'){
				a[j] = a[j + 2];
				j++;
			}
			a[j] = '\0';
		}
		else{
			i++;
		}*/
		eraser(_result,i,j,a,2);
	}
}
void conYsh(char a[]){
	int _result = 0, i = 0, j = 0;
	while (i<strlen(a)){
		j = i;
		_result = 0;
		if ((j + 2<strlen(a)) && (a[j] == '0') && (a[j + 1] == '*') && (a[j + 2] == '0')){
			a[j] = '0';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '0') && (a[j + 1] == '*') && (a[j + 2] == '1')){
			a[j] = '0';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '1') && (a[j + 1] == '*') && (a[j + 2] == '0')){
			a[j] = '0';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '1') && (a[j + 1] == '*') && (a[j + 2] == '1')){
			a[j] = '1';
			_result = 1;
		}
		/*if (_result == 1){
			j++;
			while (a[j + 2] != '\0'){
				a[j] = a[j + 2];
				j++;
			}
			a[j] = '\0';
		}
		else{
			i++;
		}*/
		eraser(_result,i,j,a,2);
	}
}
void biCondYsh(char a[]){
	int _result = 0, i = 0, j = 0;
	while (i<strlen(a)){
		j = i;
		_result = 0;
		if ((j + 2<strlen(a)) && (a[j] == '0') && (a[j + 1] == '=') && (a[j + 2] == '0')){
			a[j] = '1';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '0') && (a[j + 1] == '=') && (a[j + 2] == '1')){
			a[j] = '0';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '1') && (a[j + 1] == '=') && (a[j + 2] == '0')){
			a[j] = '0';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '1') && (a[j + 1] == '=') && (a[j + 2] == '1')){
			a[j] = '1';
			_result = 1;
		}
		/*if (_result == 1){
			j++;
			while (a[j + 2] != '\0'){
				a[j] = a[j + 2];
				j++;
			}
			a[j] = '\0';
		}
		else{
			i++;
		}*/
		eraser(_result,i,j,a,2);
	}
}
void condYsh(char a[]){
	int _result = 0, i = 0, j = 0;
	while (i<strlen(a)){
		j = i;
		_result = 0;
		if ((j + 2<strlen(a)) && (a[j] == '0') && (a[j + 1] == '-') && (a[j + 2] == '0')){
			a[j] = '1';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '0') && (a[j + 1] == '-') && (a[j + 2] == '1')){
			a[j] = '1';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '1') && (a[j + 1] == '-') && (a[j + 2] == '0')){
			a[j] = '0';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '1') && (a[j + 1] == '-') && (a[j + 2] == '1')){
			a[j] = '1';
			_result = 1;
		}
		/*if (_result == 1){
			j++;
			while (a[j + 2] != '\0'){
				a[j] = a[j + 2];
				j++;
			}
			a[j] = '\0';
		}
		else{
			i++;
		}*/
		eraser(_result,i,j,a,2);
	}
}
void disConjYsh(char a[]){
	int _result = 0, i = 0, j = 0;
	while (i<strlen(a)){
		j = i;
		_result = 0;
		if ((j + 2<strlen(a)) && (a[j] == '0') && (a[j + 1] == '+') && (a[j + 2] == '0')){
			a[j] = '0';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '0') && (a[j + 1] == '+') && (a[j + 2] == '1')){
			a[j] = '1';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '1') && (a[j + 1] == '+') && (a[j + 2] == '0')){
			a[j] = '1';
			_result = 1;
		}
		else if ((j + 2<strlen(a)) && (a[j] == '1') && (a[j + 1] == '+') && (a[j + 2] == '1')){
			a[j] = '1';
			_result = 1;
		}
		/*if (_result == 1){
			j++;
			while (a[j + 2] != '\0'){
				a[j] = a[j + 2];
				j++;
			}
			a[j] = '\0';
		}
		else{
			i++;
		}*/
		eraser(_result,i,j,a,2);
	}
}
/* 修改点4：标准化输入，避免输入格式错误 */
void getformula(char a[])
{
    char cc;
    int cnt=0;
    while((cc=getchar())!='\n')
        if((cc>='a'&&cc<='z')||(cc>='A'&&cc<='Z')||cc=='='||cc=='-'||
           cc=='+'||cc=='*'||cc=='!'||cc=='0'||cc=='1'||cc=='('||cc==')')
            a[cnt++]=cc;
}
int main(){
	/* 修改点5：持续化输入，方便使用 */
    while(1)
    {
	char pstate[120] = { ' ' }, pstate0[120] = { ' ' }, charList[120] = { ' ' }, charVal[120] = { ' ' };
	char minItem[1024][52] = { ' ' }, truetable[1024] = { ' ' };
	int i = 0, nold = 0, nnew = 0, nvar = 1, nRow = 1, j = 0, flagsum = 1, iMinItem = 0;
	printf("请输入公式(析+，合*，条-，双=，否定！，01):\n");
	gets(pstate0);
	fflush(stdin);
	nold = strlen(pstate0) + 1;
	nnew = strlen(pstate0);
	for (i = 0; i<nnew; i++){
		pstate[i] = pstate0[i];
	}
	pstate[i] = '\0';
	nvar = getalpha(pstate, charList);
	nRow = 1;
	for (i = 0; i<nvar; i++){
		charVal[i] = '0';
		nRow = nRow * 2;
	}
	charVal[i] = '\0';
	printf("\n");
	for (i = 0; i<nvar; i++){
		printf("%4c", charList[i]);
	}
	printf("%15c%s\n", ' ', pstate);
	for (i = 0; i<nvar; i++){
		printf("%4c", '-');
	}
	printf("|");
	for (i = 0; i<60; i++){
		printf("%c", '-');
	}
	printf("\n");
	for (i = 0; i<nRow; i++){
		for (j = 0; j<nvar; j++){
			printf("%4c", charVal[j]);
		}
		pstate[0] = '\0';
		fillValue(pstate0, charList, nvar, charVal, pstate);
		nold = strlen(pstate0) + 1;
		nnew = strlen(pstate);
		while (nnew<nold){
			nold = strlen(pstate);
			negatecal(pstate);
			kuanhao(pstate);
			conYsh(pstate);
			biCondYsh(pstate);
			condYsh(pstate);
			disConjYsh(pstate);
			nnew = strlen(pstate);
		}
		if (strlen(pstate) == 1){
			if (pstate[0] == '1'){
				for (j = 0; j<nvar; j++){
					minItem[iMinItem][j] = charVal[j];
				}
				minItem[iMinItem][j] = '\0';
				iMinItem++;
			}
			truetable[i] = pstate[0];
		}
		printf("%20c%s", ' ', pstate);
		printf("\n");
		flagsum = 1;
		for (j = nvar - 1; j >= 0; j--){
			if (charVal[j] == '1'){
				if (flagsum == 1){
					charVal[j] = '0';
					flagsum = 1;
				}
				else{
					break;
				}
			}
			else if (charVal[j] == '0'){
				if (flagsum == 1){
					charVal[j] = '1';
					flagsum = 0;
					break;
				}
				else{
					break;
				}
			}
		}
	}
	for (i = 0; i<iMinItem; i++){
		if (i == 0){
			printf("m%s", minItem[i]);
		}
		else{
			printf("+m%s", minItem[i]);
		}
	}
	printf("\n");
	for (i = 0; i<iMinItem; i++){
		if (i == 0){
			printf("(");
			for (j = 0; j<nvar; j++){
				if (j == 0){
					if (minItem[i][j] == '1'){
						printf("%c", charList[j]);
					}
					else{
						printf("!%c", charList[j]);
					}
				}
				else{
					if (minItem[i][j] == '1'){
						printf("*%c", charList[j]);
					}
					else{
						printf("*!%c", charList[j]);
					}
				}
			}
			printf(")");
		}
		else{
			printf("+(");
			for (j = 0; j<nvar; j++){
				if (j == 0){
					if (minItem[i][j] == '1'){
						printf("%c", charList[j]);
					}
					else{
						printf("!%c", charList[j]);
					}
				}
				else{
				    if (minItem[i][j] == '1'){
						printf("*%c", charList[j]);
					}
					else{
						printf("*!%c", charList[j]);
					}
                } 
			}
			printf(")");
		}
	}
	printf("\n");
}
    return 0;
}
