#include  <iostream>

using  namespace  std;

typedef  struct  LNode*  PtrToLNode;
struct  LNode{
        long  data;
        PtrToLNode  next;
};
//  逆转单向链表函数
void  reverseList(PtrToLNode  head)
{
		PtrToLNode New,Old,Tag,sta;
		int n=1;
		New=head->next;
		Old=New->next;
		while(n<6)
		{
			Tag=Old->next;
			Old->next=New;
			New=Old;
			Old=Tag;
			n++;
		}
		head->next->next=NULL;
		Tag=Tag->next;
		Tag->next=Old;
		Old->next=New;
		head->next=Tag;
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
        long  data[8]  =  {10,  45,  895,  371,  908,  425,  -484,  0};
        int  arrSize  =  sizeof(data)/sizeof(data[0]);
        //  将数组  data  创建带头结点的为一个单向链表  
        PtrToLNode  head,p,tail;
        head  =  tail  =  new  struct  LNode;
        for(int  i  =  0;  i  <  arrSize;i++){
                p  =  new  struct  LNode;
                p->data  =  data[i];
                p->next  =  NULL;
                tail->next  =  p;
                tail  =  p;
        }
        //  逆置单向链表  
        reverseList(head);
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
