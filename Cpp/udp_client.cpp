#include<iostream>
#include<string>
#include<cerrno>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
void usage(std::string proc)
{
  std::cout<<"usage service_ip service_port"<<std::endl;
}
int main(int argc,char* argv[])
{
  if(argc!=3)
  {
    usage(argv[0]);
    return 0;
  }

  //1.socket
  int socket_fd=socket(AF_INET,SOCK_DGRAM,0);
  if(socket_fd<0)
  {
    std::cerr<<"socket_fd fail:"<<errno<<std::endl;
    return 1;
  }

  //2.bind Linux OS会自动分配
  
  //3.提供服务
  struct sockaddr_in remote_net;
  remote_net.sin_family=AF_INET;
  remote_net.sin_port=htons(atoi(argv[2]));
  remote_net.sin_addr.s_addr=inet_addr(argv[1]);
  char buffer[1024];
  while(1)
  {
    //1.发送服务
    std::string client_say="hello service";
    sendto(socket_fd,client_say.c_str(),client_say.size(),0,(struct sockaddr*)&remote_net,sizeof(remote_net));

    //2.接受服务
    struct sockaddr_in temp_addr;
    socklen_t len=sizeof(temp_addr);
    recvfrom(socket_fd,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&temp_addr,&len);
    std::cout<<"service say:"<<buffer<<std::endl;
  }

  return 0;
}
