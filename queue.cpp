#include<iostream>
#include<algorithm>
using namespace std;


template<class T>
class queue
{
public:
   virtual bool empty()=0;
   virtual int size()=0;
   virtual void pop()=0;
   virtual T&front()=0;
   virtual T&back()=0;
   virtual void push(const T&thelement)=0;
};

template<class T>
class arrayqueue:public queue<T>
{
public:
   arrayqueue(int length=101):arraylength(length)
   {
      queuefront=0;
      queueback=0;  
      queue=new T[length]();
   }
   bool empty() override
   {
      return (queueback+1)%arraylength==queuefront;
   }  
   int size() override
   {
     return (arraylength+queueback-queuefront)%arraylength;
   }

   void pop() override
   {
    if(!empty())
    {
      queuefront=(queuefront+1)%arraylength;
      queue[queuefront].~T();
    }
    return;
   }

   void push(const T&thelement) override
   {
      if((queueback+1)%arraylength==queuefront)
      {
        changelength();
      }
      queueback=(queueback+1)%arraylength;
      queue[queueback]=thelement;
      return;
   }

   T& front() override
   {
       return queue[(queuefront+1)%arraylength];
   }

   T& back() override
   {
     return queue[queueback];
   }
private:
  int queuefront;
  int queueback;
  T*queue;
  void changelength();
  int arraylength; 
};
template<class T>
void arrayqueue<T>::changelength()
{
    T*newqueue=new T[2*arraylength];
    
    int start=(queuefront+1)%arraylength;

    if(start<2)//表示这个队列的queuefront在最后一个或者是第一个
    {
       copy(queue+start,queue+start+arraylength-1,newqueue);
    }else{
        copy(queue+start,queue+arraylength,newqueue);
        copy(queue,queue+queueback+1,newqueue+arraylength-start);
    }
    
    queuefront=2*arraylength-1;
    queueback=arraylength-2;
    arraylength*=2;
    delete [] queue;
    queue=newqueue;
    return;
}

int main()
{
    arrayqueue<int>num;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        num.push(i);
    }

    while(num.size()>=2)
    {
      //int temp1=num.front();
      //cout<<"the first is "<<temp1<<endl;
      num.pop();
      int temp=num.front();
      //cout<<"the second is "<<temp<<endl;
      num.pop();
      num.push(temp);
    }
    cout<<num.front()<<endl;
    return 0;
}