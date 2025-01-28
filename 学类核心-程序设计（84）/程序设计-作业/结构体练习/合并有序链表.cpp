#include  <iostream>
using  namespace  std;
typedef  struct  LNode*  PtrToLNode;
struct  LNode{
        int  data;
        PtrToLNode  next;
};
PtrToLNode  mergeList(PtrToLNode  head1,  PtrToLNode  head2)
{
PtrToLNode preHead=new LNode;   //�����½�������Ҫ�洢�ڴ��ָ�룬�ȷ�����ռ� 
PtrToLNode prev=preHead;
head1=head1->next;              //ͷָ��Ϊ�� 
head2=head2->next;              //ͷָ��Ϊ�� 
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
        //  ������  data  ������ͷ����Ϊһ����������  
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
        //  �ϲ���������  
        PtrToLNode  head  =  mergeList(head1,  head2);
        //  ˳���ӡ������������и����ڵ��data����  
        printList(head);
        //  �ͷ�����ռ�  
        while(head->next!=NULL){
                p  =  head->next;
                head->next  =  p->next;
                delete  p;
        }
        delete  head;
        return  0;
}
