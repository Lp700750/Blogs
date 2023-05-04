#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#define NUM 128
int main()
{
  //pid_t childpid=fork();
  while(1)
  {
    //1.输出自己的专属行logo
    printf("Home@Zonda$:");
    fflush(stdout);


    //2.输入要替换的文件
    char str[NUM];
    fgets(str,NUM,stdin);//ls -a -l\0
    char* argv[64];
    const char* sep=" ";
    argv[0]=strtok(str,sep);
    int i=1;
    while(argv[i]!=NULL)
    {
      argv[i]=strtok(NULL,sep);
      i++;
    }

    //3.子进程替换
    pid_t childpid=fork();
    if(childpid==0)
    {
      //执行成功将会被替换
      execvp(argv[0],argv);
      
      //替换失败才会执行该部分
      exit(1);
    }
    
    //4.主进程等待
    int status=0;
    pid_t pid=waitpid(childpid,&status,0);
    if(pid>0&&(status&0x7f)==0)
    {
      printf("%d\n",(status>>8)&0xff);
    }
    else
    {
      printf("%d\n",status&0x7f);
    }
  }



  return 0;
}
