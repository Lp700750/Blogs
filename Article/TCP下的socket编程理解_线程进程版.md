## TCP下的socket编程理解_线程进程版
### 0 前言
> 前面使用的TCP下的socket编程，是一种基础的版本，进行测试后就可能就发现，它只一个单进程版本，每一次只能服务一台客户端，其他的客户端如果访问的时候就只能等待该客户端终止之后才能够进行连接，这对于当前互联网的大并发来讲是不适用的，因此今天来讲述其进阶版本，使用多进程或者多线程来进行网络通信。
### 1 进程版本
为了解决上面可能会出现的大并发的问题，我们在这里引入多进程来进行，看如下的代码
```
void srvice(int accept_fd)
{
  while(true)
  {
    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    ssize_t s=read(accept_fd,buffer,sizeof(buffer)-1);
    if(s>0)                                                                                   
    {
      buffer[s]=0;
      std::cout<<"client:"<<buffer<<std::endl;
      std::string service_say("hello client");
      write(accept_fd,service_say.c_str(),service_say.size());
    }
  }
}
signal(SIGCHLD, SIG_IGN);
while(true)
{
      struct sockaddr_in peer;
      socklen_t len=sizeof(peer);
      int accept_fd=accept(socket_fd,(struct sockaddr*)&peer,&len);
      if(accept_fd<0)
      {
        continue;
      }
  
      //提供服务
      int fd=fork();
      if(fd<0)
      {
        std::cout<<"fork fail"<<std::endl;
      }
      else if(fd==0)
      {
        //子进程执行服务请求
        close(socket_fd);
        if(fork()>0)
        {
          exit(0);
        }
        service(accept_fd);
        close(socket_fd);
      }
      else
      {
        //父进程等着就行
        close(accept_fd);
      }
}
```   
这里面有几个问题需要注意一下    
- **进程可以看作是程序的一次执行过程**
- **子进程是对父进程的代码一次拷贝，数据发生写时拷贝，子进程的数据发生改变对父进程是不影响的，因为两者是两个执行流**
- 子进程继承了父进程的代码，内部会把socket_fd文件描述符也给继承过来，如果不关掉，大量的子进程过来，会造成文件描述符泄露，造成资源的浪费，所以用完之后要进行close关闭。
- 子进程执行的过程中，如果没有特殊请求，是需要父进程进行等待的，如果这里要进行等待的话，父进程不管是阻塞式等待还是非阻塞式等待，对于大并发的情况之下，都会影响运行的效果，因此这里我们需要将父子进程进行“分离处理”，处理的方法有两个：    
 1. 采用信号signal(SIGCHLD, SIG_IGN)，这时子进程就可以自己退出，不用父进程等待
 2. 在子进程里面创建子进程，子进程退出，然后只用执行孙子进程，这时孙子进程就是孤儿进程，由操作系统管理，(父进程不用等待孙子进程)

