#pragma once
#include<iostream>
#include<queue>
#include<pthread.h>
namespace ns_blockqueue
{
  const int ret=5;
  template<class T>
  class blockqueue 
  {
  private:
    std::queue<T> _bq;
    int _size;
    pthread_mutex_t _mtx;
    pthread_cond_t _full;
    pthread_cond_t _empty;
  private:
    bool isfull()
    {
      return _bq.size()==_size;
    }
    bool isempty()
    {
      return _bq.size()==0;
    }
    void lockqueue()
    {
      pthread_mutex_lock(&_mtx);
    }
    void unlockqueue()
    {
      pthread_mutex_unlock(&_mtx);
    }
    void productwait()
    {
      pthread_cond_wait(&_empty,&_mtx);
    }
    void serverwait()
    {
      pthread_cond_wait(&_full,&_mtx);
    }
    void signalproduct()
    {
      pthread_cond_signal(&_empty);
    }
    void signalserverduct()
    {
      pthread_cond_signal(&_full);
    }
  public:
    blockqueue(int size=ret)
      :_size(size)
    {
      pthread_mutex_init(&_mtx,nullptr);
      pthread_cond_init(&_full,nullptr);
      pthread_cond_init(&_empty,nullptr);
    }
    
    void push(const T& data)
    {
      lockqueue();
      if(isfull())
      {
        //signalserverduct(); 
        productwait();
      }
      _bq.push(data);
      if(_bq.size()>_size/2)
      {
        signalserverduct();
      }
      unlockqueue();
    }
    void pop(T* value)
    {
      lockqueue();
      if(isempty())
      {
        serverwait();
      }
      *value=_bq.front();
      _bq.pop();
      if(_bq.size()<_size/2)
      {
        signalproduct();
      }
      unlockqueue();
    }
    ~blockqueue()
    {
      pthread_mutex_destroy(&_mtx);
      pthread_cond_destroy(&_full);
      pthread_cond_destroy(&_empty);
    }
  };
}
