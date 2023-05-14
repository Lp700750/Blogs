#include<iostream>
#include<string>
#include<cstring>
#include<cerrno>
#include<cstdlib>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
void usage()
{
  std::cout<<"./service port"<<std::endl;
}
int main(int argc,char* argv[])
{
  if(argc!=2)
  {
    usage();
    return 0;
  }
  int socket_fd=socket(AF_INET,SOCK_STREAM,0);
  if(socket_fd<0)
  {
    std::cerr<<"socket fail"<<errno<<std::endl;
    return 1;
  }


  struct sockaddr_in client;
  memset(&client,0,sizeof(client));
  client.sin_family=AF_INET;
  client.sin_port=htons(atoi(argv[1]));
  client.sin_addr.s_addr=INADDR_ANY;
  int bind_fd=bind(socket_fd,(struct sockaddr*)&client,sizeof(client));
  if(bind_fd<0)
  {
    std::cerr<<"bind fail"<<errno<<std::endl;
    return 2;
  }

  const int Log=5;
  int listen_fd=listen(socket_fd,Log);
  if(listen_fd<0)
  {
    std::cerr<<"listen fail"<<errno<<std::endl;
    return 3;
  }

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

  return 0;
}
