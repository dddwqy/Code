#include"chain_source.h"

#include<iostream>
using namespace std;

int temp[6000];
int top;

template<class T>
class merge_chain
{
public:
   merge_chain(){}
   int radix(T input,int n=10,int c=0);
   void radixsort(chain<T>&thechain,int n,int c);
  // void boinsort(chain<T>&temp,int range,int num);//这个num表示是数字上的第几位数字
   void merge_two(chain<T>&chain_one,chain<T>&chain_two,int n, int c);
   void cal_xor(chain<T>&thechain);
   ~merge_chain(){}
private:
   chain<T> answer_head;//定义一个储存答案链表的链表头
};

template<class T>
int merge_chain<T>::radix(T input,int n,int c)
{
    int r1=1,r2=1;
   for(int i=0;i<c;i++)
   {
      r1*=n;
      r2*=n;
   }
   r2*=n;
   return (input%r2)/r1;//返回一个该数位上的值
}

template<class T>
void merge_chain<T>::radixsort(chain<T>&thechain,int n,int c)
{
    chain<T>* boin=new chain<T> [n];
    for(int j=0;j<c;j++)
    {
       int nr =thechain.size();
       if(nr!=0)
       {
        for(int i=0;i<nr;i++)
        {
          T rec=thechain.get(0);
          thechain.erase(0);
          boin[radix(rec,n,j)].insert(0,rec);
        }
        for(int i=n-1;i>=0;i--)
        {
          while(!boin[i].empty())
          {
            T rec=boin[i].get(0);
            boin[i].erase(0);
            thechain.insert(0,rec);
          }
        }
       } 
    }
    delete [] boin;
    return;
}   

template<class T>
void merge_chain<T>::cal_xor(chain<T>& thechain)
{
    typename chain<T>::iterator head=thechain.begin();
    typename chain<T>::iterator ends=thechain.end();
    int out=0;
    int index=0;

    while(head!=ends)
    {
      out+=index^(*head);
      index++;
      ++head;
    }

    temp[top]=out;
    top++;
    
    return;
}

template<class T>
void merge_chain<T>::merge_two(chain<T>&chain_one,chain<T>&chain_two,int n,int c)
{
    int answer=0;
    radixsort(chain_one,n,c);//将两个链表进行基数排
    radixsort(chain_two,n,c);
    cal_xor(chain_one);
    cal_xor(chain_two);
    int size_one=chain_one.size();
    int size_two=chain_two.size();
    int size_total=size_one+size_two;//answer地总长度

    typename chain<T>::iterator one_begin=chain_one.begin();
    typename chain<T>::iterator one_end=chain_one.end();
    typename chain<T>::iterator two_begin=chain_two.begin();
    typename chain<T>::iterator two_end=chain_two.end();


    for(int i=0;i<=size_total;i++)
    {
      T cur;
     if(one_begin==one_end&&two_begin==two_end)
     {
        //cout<<"answer is "<<answer<<endl;
         temp[top]=answer;
         top++;
         return;
     }

     if(one_begin!=one_end&&two_begin!=two_end)
     {
        if(*one_begin<=*two_begin)
        {   
            cur=*one_begin;
            ++one_begin;
        }else{
            cur=*two_begin;
            ++two_begin;
        }
          answer+=i^cur;
          answer_head.insert(i,cur);
          continue;
     }else if(one_begin!=one_end&&two_begin==two_end){
          cur=*one_begin;
          //cout<<"cur:"<<cur<<endl;
          ++one_begin;
          answer+=i^cur;
          answer_head.insert(i,cur);
          continue;
     }else if(one_begin==one_end&&two_begin!=two_end){
        cur=*two_begin;
        ++two_begin;
        answer+=i^cur;
        answer_head.insert(i,cur);
        continue;
     }
    }
    
    return;
}

int main()
{
    int N=0,M=0;
    chain<long> one;
    chain<long> two;
    cin>>N>>M;
    for(int i=0;i<N;i++)
    {
      long val;
      cin>>val;
      one.insert(i,val);
    }
    for(int i=0;i<M;i++)
    {
      long val;
      cin>>val;
      two.insert(i,val);
    }
    merge_chain<long> merge;
    merge.merge_two(one,two,10,5);
    ///cout<<top<<endl;
    for(int i=0;i<top;i++)
    {
      cout<<temp[i]<<endl;
    }
    return 0;
}