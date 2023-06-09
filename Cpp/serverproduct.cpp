#include<iostream>
#include<string>
#include<cstdlib>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include"blockqueue.hpp"
void* server(void* args)
{
  ns_blockqueue::blockqueue<int>* bq=(ns_blockqueue::blockqueue<int>*)args;
  while(true)
  {
    int value=0;
    (*bq).pop(&value);
    std::cout<<"customer:"<<value<<std::endl;
    sleep(3);
  }
}
void* product(void* args)
{
  ns_blockqueue::blockqueue<int>* bq=(ns_blockqueue::blockqueue<int>*)args;
  while(true)
  {
    int data=rand()%10+1;
    std::cout<<"product:"<<data<<std::endl;
    (*bq).push(data);
    sleep(3);
  }
}
int main()
{
  srand((long)time(nullptr));
  pthread_t s,p;
  ns_blockqueue::blockqueue<int>* bq=new ns_blockqueue::blockqueue<int>;
  pthread_create(&s,nullptr,server,(void*)bq);
  pthread_create(&p,nullptr,product,(void*)bq);

  pthread_join(s,nullptr);
  pthread_join(p,nullptr);

  return 0;
}
