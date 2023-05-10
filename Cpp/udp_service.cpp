#include<iostream>
#include<string>
#include<cerrno>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
const uint16_t port=8080;
int main()
{
  //1.socket 
  int socket_fd=socket(AF_INET,SOCK_DGRAM,0);
  if(socket_fd<0)
  {
    std::cerr<<"socket fail:"<<errno<<std::endl;
    return 1;
  }

  //2.bind 给服务器绑定端口号和ip
  struct sockaddr_in local_net;
  local_net.sin_family=AF_INET;
  local_net.sin_port=htons(port);
  local_net.sin_addr.s_addr=INADDR_ANY;
  int bind_fd=bind(socket_fd,(struct sockaddr*)&local_net,sizeof(local_net));
  if(bind_fd<0)
  {
    std::cerr<<"bind fail:"<<errno<<std::endl;
    return 2;
  }

  //3.添加服务
  char buffer[1024];
  while(true)
  {
    struct sockaddr_in client;
    socklen_t client_len=sizeof(client);
    //3.1 接收请求
    recvfrom(socket_fd,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&client,&client_len);
    std::cout<<"client:"<<buffer<<std::endl;

    //3.2 反馈请求
    std::string service_say="hello service";
    sendto(socket_fd,service_say.c_str(),service_say.size(),0,(struct sockaddr*)&client,client_len);
  }

  return 0;
}
