#include<iostream>
#include<cstdlib>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include"posix_blockqueue.hpp"
void* customer(void* args)
{
  ns_posix::PosixQueue<int>* bq=(ns_posix::PosixQueue<int>*)args;
  int value=0;
  while(true)
  {
    bq->getData(value);
    std::cout<<"sub:"<<value<<std::endl;
    sleep(3);
  }
}
void* product(void* args)
{
  ns_posix::PosixQueue<int>* bq=(ns_posix::PosixQueue<int>*)args;
  int data=0;
  while(true)
  {
    data=rand()%10+1;
    bq->addData(data);
    std::cout<<"add:"<<data<<std::endl;
    sleep(3);
  }  
}
int main()
{
  pthread_t c,p;
  srand((long long)time(nullptr));
  //ns_posix::PosixQueue<int> bq(10);
  ns_posix::PosixQueue<int>* bq=new ns_posix::PosixQueue<int>(10);
  pthread_create(&c,nullptr,customer,(void*)bq);
  pthread_create(&p,nullptr,product,(void*)bq);

  pthread_join(c,nullptr);
  pthread_join(p,nullptr);


  return 0;
}
