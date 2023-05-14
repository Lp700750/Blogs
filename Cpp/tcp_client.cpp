#include<iostream>
#include<string>
#include<cerrno>
#include<cstdlib>
#include<cstring>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
void usage()
{
  std::cout<<"./client/ip/port"<<std::endl;
}
int main(int argc,char* argv[])
{
  if(argc!=3)
  {
    usage();
    return 0;
  }
  //1.socket 
  int socket_fd=socket(AF_INET,SOCK_STREAM,0);
  if(socket_fd<0)
  {
    std::cerr<<"socket fail"<<errno<<std::endl;
    return 1;
  }

  //bind 不用显示的进行bind
  //connect
  struct sockaddr_in remote;
  memset(&remote,0,sizeof(remote));
  remote.sin_family=AF_INET;
  std::string ip=argv[1];
  uint16_t port=(uint16_t)atoi(argv[2]);
  remote.sin_port=htons(port);
  remote.sin_addr.s_addr=inet_addr(ip.c_str());

  int connect_fd=connect(socket_fd,(struct sockaddr*)&remote,sizeof(remote));
  if(connect_fd<0)
  {
    std::cerr<<"connect fail"<<errno<<std::endl;
    return 2;
  }

  //提供服务
  while(true)
  {
    std::cout<<"client_say:"<<std::endl;
    char buffer[1024];
    fgets(buffer,sizeof(buffer)-1,stdin);
    write(socket_fd,buffer,sizeof(buffer));
    ssize_t s=read(socket_fd,buffer,sizeof(buffer));
    if(s>0)
    {
      buffer[s]=0;
      std::cout<<"service_say:"<<buffer<<std::endl;
    }
  }
    

  return 0;
}
