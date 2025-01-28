#include  <iostream>
using  namespace  std;
typedef  struct  LNode*  PtrToLNode;
struct  LNode{
        int  data;
        PtrToLNode  next;
};
PtrToLNode  mergeList(PtrToLNode  head1,  PtrToLNode  head2)
{
PtrToLNode preHead=new LNode;   //对于新建立的需要存储内存的指针，先分配类空间 
PtrToLNode prev=preHead;
head1=head1->next;              //头指针为空 
head2=head2->next;              //头指针为空 
while(head1!=NULL&&head2!=NULL){
	if(head1->data<head2->data)
	{
		prev->next=head1;
		head1=head1->next; 
	}
	else{ 
		prev->next=head2;
		head2=head2->next;
	}
	prev=prev->next;
	}
prev->next=head1==NULL?head2:head1;
	return preHead;
}
void  printList(PtrToLNode  head)
{
        PtrToLNode  p  =  head->next;
        while(p!=NULL)
        {
                cout  <<  p->data  <<  "  ";
                p  =  p->next;
        }
        cout  <<  endl;
}

int  main()
{
        int  data[2][8]  =  {{-484,  0,  10,  45,  371,  425,  895,  908},{0,  3,  12,  50,  900,  999,  1024,  2048}};
        int  arrSize  =  sizeof(data[0])/sizeof(data[0][0]);
        //  将数组  data  创建带头结点的为一个单向链表  
        PtrToLNode  head1,  head2,  p,  tail;
        head1  =  tail  =  new  struct  LNode;
        for(int  i  =  0;  i  <  arrSize;i++){
                p  =  new  struct  LNode;
                p->data  =  data[0][i];
                p->next  =  NULL;
                tail->next  =  p;
                tail  =  p;
        }
        head2  =  tail  =  new  struct  LNode;
        for(int  i  =  0;  i  <  arrSize;i++){
                p  =  new  struct  LNode;
                p->data  =  data[1][i];
                p->next  =  NULL;
                tail->next  =  p;
                tail  =  p;
        }
        //  合并有序链表  
        PtrToLNode  head  =  mergeList(head1,  head2);
        //  顺序打印输出单向链表中各个节点的data数据  
        printList(head);
        //  释放链表空间  
        while(head->next!=NULL){
                p  =  head->next;
                head->next  =  p->next;
                delete  p;
        }
        delete  head;
        return  0;
}
