#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#define NUM 128
int main()
{
  //1.create pipe
  //pid_t pid=fork();
  int fd[2];
  if(pipe(fd)<0)
  {
    perror("pipe:");
    exit(1);
  }
  
  //create child process
  pid_t pid=fork();
  if(pid<0)
  {
    printf("fork fail!\n");
    exit(2);
  }

  //2.parent write
  if(pid>0)
  {
    const char* str="hello China";
    if(write(fd[1],str,strlen(str))<0)
    {
      printf("write fail!\n");
      exit(3);
    }

    int status=0;
    pid_t _pid=waitpid(pid,&status,0);
    if(_pid>0&&(status&0x7f)==0)
    {
      printf("exitNum:%d\n",(status>>8)&0xff);
    }
  }
  
  
  //3.child read
  else 
  {
    char buffer[NUM];
    if(read(fd[0],buffer,NUM)<0)
    {
      printf("read fail!\n");
      exit(4);
    }
    printf("%s\n",buffer);

  }


  return 0;
}
