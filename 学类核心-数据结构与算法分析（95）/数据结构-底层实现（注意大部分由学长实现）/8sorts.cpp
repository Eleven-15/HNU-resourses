#include<bits/stdc++.h>
using namespace std;

//1.冒泡排序
//基本思想：在要排序的一组数中，对当前还未排好序的范围内的全部数，
//自上而下对相邻的两个数依次进行比较，让较大的数往下沉，较小的往上冒。
//即：每当两相邻的数比较后发现他们的排序与排序要求相反时，就将他们互换。
void Bubble_sort(int a[],int n)//冒泡排序 ，a[]用来接收数组，n用来接收数组长度 
{
	for(int i=0;i<n-1;i++)
	{
		int flag=1;
		for(int j=0;j<n-1;j++)
		{
			if(a[j]>a[j+1])
			{
				int team=a[j];
				a[j]=a[j+1];
				a[j+1]=team;
				flag=0;
			}
		}
		if(flag==1)
		break;
	}
}


//2.简单选择排序
//基本思想：第一趟：从第一个记录开始，将后面n-1个记录进行比较，找到其中最小的记录和第一个记录进行交换；
//第二趟：从第二个记录开始，将后面n-2个记录进行比较，找到其中最小的记录和第2个记录进行交换；
//…
//第i趟：从第i个记录开始，将后面n-i个记录进行比较，找到其中最小的记录和第i个记录进行交换；
//以此类推，经过n-1趟比较，将n-1个记录排到位，剩下一个最大记录直接排在最后；
void Select_sort(int a[],int n)//简单选择排序    a[]用来接收数组，n用来接收数组长度 
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(a[i]>a[j])
			{
				int team=a[i];
				a[i]=a[j];
				a[j]=team;
			}
		}
	}
} 

//3.直接插入排序
//基本思想：将一个记录插入到已排序好的有序表中，从而得到一个新的，记录数增1的有序表。
//即先将序列的第一个记录看成是一个有序的子序列，然后从第二个记录逐个进行插入，直至整个序列有序为止。
void Straight_Insertion_sort(int a[],int n)//直接插入排序	a[]用来接收数组，n用来接收数组长度  
{
	for(int i=1;i<n;i++)
	{
		if(a[i]>a[i-1])
		continue;
		for(int j=0;j<i;j++)
		{
			if(a[i]<a[j])
			{
				int team=a[i];
				for(int k=i-1;k>=j;k--)
				a[k+1]=a[k];
				a[j]=team;
				break;
			}
		}
	}
}


//4.希尔排序
//基本思想：先将整个待排序元素序列分割成若干子序列（由相隔某个“增量”的元素组成的）分别进行直接插入排序，
//然后依次缩减增量再进行排序，待整个序列中的元素基本有序（增量足够小）时，
//再对全体元素进行一次直接插入排序（因为直接插入排序在元素基本有序的情况下，效率很高）；
void Shell_sort(int a[],int n)//希尔排序	a[]用来接收数组，n用来接收数组长度 
{
	int i=5;
	while(i>=1)
	{
		for(int j=0;j<i;j++)
		{
			for(int k=j+i;k<n;k+=i)
			{
				for(int m=j;m<k;m+=i)
				{
					if(a[k]<a[m])
					{
						int team=a[k];
						for(int n=k-i;n>=m;n-=i)
						a[n+i]=a[n];
						a[m]=team;
						break;
					}
				}
			}
		}
		i-=2;
	}
} 


//5.堆排序
//基本思想：先将初始数组建成一个大根堆，此对为初始的无序区；
//再将最大的元素和无序区的最后一个记录交换，由此得到新的无序区和有序区，且满足<=的值；
//由于交换后新的根可能违反堆性质，故将当前无序区调整为堆。
//然后再次将其中最大的元素和该区间的最后一个记录交换，由此得到新的无序区和有序区，
//且仍满足关系的值<=的值，同样要将其调整为堆；
//…
//直到无序区只有一个元素为止；
void swap(int a[],int min,int max)//构建堆和快速排序时使用的函数，用于数组之间的值交换 	a[]用来接收数组，min接收下标较小的，max用来接收下标较大的 
{
	int team=a[max];
	a[max]=a[min];
	a[min]=team;
}

void build_sort(int a[],int start,int i)//构建堆 	a[]用来接收数组，start终端节点，i表示还有多少个数字还在堆上 
{
	if(start*2+1>i-1)
	return ;
	int num,m=a[start];
	if(start*2+2<i)
	{
		if(a[start*2+1]<a[start*2+2])
		num=start*2+2;
		else
		num=start*2+1;
	}
	else
	num=start*2+1;
	if(a[start]<a[num])
	swap(a,start,num);
	if(m!=a[start]&&(start-1)/2>=0&&a[start]>a[(start-1)/2])
	build_sort(a,(start-1)/2,i);
	else
	{
		if(start*2+1<i)
		build_sort(a,start*2+1,i);
		if(start*2+2<i)
		build_sort(a,start*2+2,i);
	}
}
void Heap_sort(int a[],int n)//堆排序	a[]用来接收数组，n用来接收数组长度 
{
	for(int i=0;i<n-1;i++)
	{
		build_sort(a,0,n-i);
		int team=a[0];
		a[0]=a[n-i-1];
		a[n-i-1]=team;
	}
} 

//6.快速排序 
//
//基本思想：选择一个基准元素，将比基准元素小的元素放在其前面，比基准元素大的元素放在其后面，
//然后在将小于基准值元素的子数列和大于基准元素的子数列按原来的方法排序，直到整个序列有序;
void Quick_sort(int a[],int low,int high)//快速排序递归		a[]用来接收数组，low是区间最小下标，high是区间最大下标	
{
	if(low<high)
	{
		int pivotkey=a[(low+high)/2],i=low,j=high;
		while(i<=j)
		{
			while(a[i]<pivotkey)
			i++;
			while(a[j]>pivotkey)
			j--;
			if(i<=j)
			{
				swap(a,i,j);
				i++;
				j--;
			}
			
		}
		Quick_sort(a,low,j);
		Quick_sort(a,i,high);
	}
}


//7.基数排序
//基本思想：通过序列中各个元素的值，对排序的N个元素进行若干趟的“分配”与“收集”来实现排序。
//分配：我们将L[i]中的元素取出，首先确定其个位上的数字，根据该数字分配到与之序号相同的桶中
//收集：当序列中所有的元素都分配到对应的桶中，再按照顺序依次将桶中的元素收集形成新的一个待排序列L[ ]
//对新形成的序列L[]重复执行分配和收集元素中的十位、百位…直到分配完该序列中的最高位，则排序结束；
//代码如下：
typedef struct LNode//基数排序时使用的结构体 
{
	int data;
	struct LNode* next;
	int length;
}LNode;
int Radix_sort1(int a[],int n,int s)
//基数排序	a[]用来接收数组，n表示数组的大小,s表示要排序s+1位 
{
	LNode e[10];
	for(int i=0;i<10;i++)
	{
		e[i].length=0;
		e[i].next=NULL;
	}
	for(int i=0;i<n;i++)
	{
		int k=a[i]/s%10;
		LNode* p=&e[k];
		while(p->next)
		p=p->next;
		LNode* m=new LNode;
		m->next=NULL;
		m->data=a[i];
		p->next=m;
		e[k].length++;
	}
	int i=0;
	for(int j=0;j<10;j++)
	{
		LNode* p=&e[j];
		while(p->next)
		{
			p=p->next;
			a[i]=p->data;
			i++;
		}
	}
	if(e[0].length==n)
	return 1;
	for(int i=0;i<10;i++)
	{
		if(e[i].length==0)
		continue;
		while(e[i].length)
		{
			LNode* p=&e[i];
			LNode* x=p->next;
			while(x->next)
			{
				p=p->next;
				x=x->next;
			}
			p->next=NULL;
			delete x;
			x=NULL;
			e[i].length--;
		}
	}
	return 0; 
}
void Radix_sort(int a[],int n,int num=0)
//基数排序(main函数中使用这个)	 a[]用来接收数组，n表示数组的大小，num默认为1（main中不需要填num） 
{	
	int s=1;
	for(int i=0;i<num;i++)
	s*=10;
	if(Radix_sort1(a,n,s)==1)
	return ;
	else
	return Radix_sort(a,n,num+1);
}

//8.归并排序 
//基本思想：首先将初始序列的n个记录看成是n个有序的子序列，每个子序列的长度为1，然后两两归并，得到n/2个长度为2的有序子序列，在此基础上，再对长度为2的有序子序列进行两两归并，得到若干个长度为4的有序子序列，以此类推，直到得到一个长度为n的有序序列为止；
//代码如下：
void Merge_sort1(int a[],int L,int M,int R)//归并排序
{
	int left_size=M-L;
	int right_size=R-M+1;
	int left[left_size];
	int right[right_size];
	for(int i=L;i<M;i++)
	{
		left[i-L]=a[i];
	}
	for(int i=M;i<=R;i++)
	{
		right[i-M]=a[i];
	}
	int i=0,j=0;
	for(int k=L;k<=R;k++)
	{
		if(left[i]<right[j])
		{
			a[k]=left[i];
			i++;
		}
		else
		{
			a[k]=right[j];
			j++;
		}
		if(i==left_size)
		{
			k++;
			while(k<=R)
			{
				a[k]=right[j];
				j++;
				k++;
			}
		}
		if(j==right_size)
		{
			k++;
			while(k<=R)
			{
				a[k]=left[i];
				i++;
				k++;
			}
		}
	}
} 

void Merge_sort(int a[],int n,int sum=2)
//归并排序（main函数中使用这个）
//a[]用来接收数组，n表示数组的大小，sum表示一个子数列中有多少个元素（默认值为2） 
{
	if(sum/2>=n)
	return ;
	for(int i=0;i<n;i+=sum)
	{
		if(i+sum<=n)
		Merge_sort1(a,i,i+sum/2,i+sum-1);
		else if(i+sum/2<n&&i+sum>=n)
		Merge_sort1(a,i,i+sum/2,n-1);
	}
	return Merge_sort(a,n,2*sum);
}


int main()
{
	int n=9;
//	cin>>n;
//	int *m0=new int[n];
	int *m=new int[n];
//	for (int i=0;i<n;i++) cin>>m0[i];
	int m0[n]={43,65,21,9,32,54,98,33,90};
	
	cout<<"冒泡排序"<<endl; 
	for (int i=0;i<n;i++) m[i]=m0[i];
	Bubble_sort(m,n);
	for (int i=0;i<n;i++) cout<<m[i]<<" ";
	cout<<endl<<endl;

	cout<<"选择排序"<<endl; 
	for (int i=0;i<n;i++) m[i]=m0[i];
	Select_sort(m,n);
	for (int i=0;i<n;i++) cout<<m[i]<<" ";
	cout<<endl<<endl;

	cout<<"直接插入排序"<<endl; 
	for (int i=0;i<n;i++) m[i]=m0[i];
	Straight_Insertion_sort(m,n);
	for (int i=0;i<n;i++) cout<<m[i]<<" ";
	cout<<endl<<endl;
	
	cout<<"希尔排序"<<endl; 
	for (int i=0;i<n;i++) m[i]=m0[i];
	Shell_sort(m,n);
	for (int i=0;i<n;i++) cout<<m[i]<<" ";
	cout<<endl<<endl;
	
	cout<<"堆排序"<<endl; 
	for (int i=0;i<n;i++) m[i]=m0[i];
	Heap_sort(m,n);
	for (int i=0;i<n;i++) cout<<m[i]<<" ";
	cout<<endl<<endl;
	
	cout<<"快速排序"<<endl; 
	for (int i=0;i<n;i++) m[i]=m0[i];
	Quick_sort(m,0,n-1);
	for (int i=0;i<n;i++) cout<<m[i]<<" ";
	cout<<endl<<endl;
	
	cout<<"基数排序"<<endl; 
	for (int i=0;i<n;i++) m[i]=m0[i];
	Radix_sort(m,n,0);
	for (int i=0;i<n;i++) cout<<m[i]<<" ";
	cout<<endl<<endl;
	
	cout<<"归并排序"<<endl; 
	for (int i=0;i<n;i++) m[i]=m0[i];
	Merge_sort(m,n,2);
	for (int i=0;i<n;i++) cout<<m[i]<<" ";
	cout<<endl<<endl;
	
	return 0;
}

