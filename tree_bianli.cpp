#include<iostream>
using namespace std;

struct node{
  int element;
  node*left;
  node*right;
  node(int melement=-1,node*mleft=nullptr,node*mright=nullptr)
  {
      element=melement;
      left=mlelft;
      right=mright;
  }
};

int forward_num[10000]={0};
int in_num[10000]={0};

int main()
{
   int n;
   int end;
   cin>>n;
   for(int i=1;i<=n;i++)//输入前序遍历
   {
     cin>>forward_num[i];
   }
   for(int j=1;j<=n;j++)//输入中序遍历
   {
     cin>>in_num[j];
   }
   node*first=new node(forward_num[1],nullptr,nullptr);
   for(int i=2;i<=n;i++)
   {
     if(in_num[i]==forward_num[1])
     {
        end=i;
     }
   }
   huanyuan(first,2,end,1,end-1,1,3);//这里输入左子树的序列,1标识这是左节点
   huanyuan(first,end+1,n,end+1,n,0,1);//这里输入右子树的序列，0标识这是右节点
   return 0;
}

void huanyuan(node*curnode,int start_forward,int end_forward,int start_in,int end_in,int sign,int num)//利用前序遍历和中序遍历构造出一个树
                                                                                                      //num表示这个序列的长度为多少
{
  if(num<=0)
  {
     return;
  }

  int end=0;
  int temp=forward_num[start_forward];
  node*newnode=new node(temp,nullptr,nullptr);
  if(sign==1)//输入新的节点
  {
     curnode->left=newnode;
  }else if(sign==0)
  {
     curnode->right=newnode;
  }

  for(int i=start_in;i<=end_in;i++)
  {
    if(in_num[i]==temp)
    {
       end=i;
    }
  }   
  new_start_forward=start_forward+1;
  new_end_forward=start_forward+(end-start_in);
  new_start_in=start_in;
  new_end_in=start_in+end-start_in-1;
  new_num=end-start_in;
  huanyuan(newnode,new_start_forward,new_end_forward,new_start_in,new_end_in,1,new_num);
  huanyuan(newnode,new_end_forward+1,new_end_forward+end_in-end-1,end+1,end_in,0,end_in-end);
  return;
}

void postorder(node*curnode)
{
    if(curnode!=nullptr)
    {
       postorder(curnode->left);
       postorder(curnode->right);
       cout<<curnode->element<<' ';
    }
    return;
}