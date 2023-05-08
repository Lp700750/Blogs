#pragma once
#include<iostream>
#include<vector>
#include<cstdlib>
#include<unistd.h>
#include<semaphore.h>
namespace ns_posix
{
  template<class T>
  class PosixQueue
  {
  private:
    std::vector<T> vect;
    int vectCap;
    sem_t dataNum;
    sem_t blankNum;
    int dataStep;
    int blankStep;
  public:
    PosixQueue(int capacity)
      :vect(capacity)
      ,vectCap(capacity)
    {
      sem_init(&dataNum,0,0);
      sem_init(&blankNum,0,vectCap);
      dataStep=0;
      blankStep=0;
    }
    
    void addData(const T& data)
    {
      sem_wait(&blankNum);
      vect[dataStep]=data;
      dataStep++;
      dataStep%=vectCap;
      sem_post(&dataNum);
    }
    
    void getData(T& data)
    {
      sem_wait(&dataNum);
      data=vect[blankStep];
      blankStep++;
      blankStep%=vectCap;
      sem_post(&blankNum);
    }

    ~PosixQueue()
    {
      sem_destroy(&dataNum);
      sem_destroy(&blankNum);
    }
  };
}
