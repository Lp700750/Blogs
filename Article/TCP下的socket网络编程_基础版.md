## TCP下的socket网络编程_基础版
### 0 前言
> 作为Linux跨网络通信的技术的体现，socket套接字编程这里说实话确实有许多的难点不好理解，最近又看了这部分的知识，决定将这部分进行梳理一下，想对他来一次系统性的理解。
### 1 服务器端
作为提供服务的一端，服务器端的任务就会重很多，他在主要是分成如下的五个部分，主要的功能也如下：  
- [x] 1 socket创建套接字---我的理解这部分是用来进行开启网络通信服务   
```
int socket(int domain, int type, int protocol);
```  
- domain:需要我们传入进去的是ip的协议类型，目前我们所用的通信协议大多是ipv4，因此这里应当输入AF_INET  
- type:需要我们传入的是传输层协议类型，此处我们所使用得到是TCP,因此这里需要传入的是SOCK_STREAM,以文件流的形式进行网络通信
- protocol:这里我们一般传入的都是0   
- return：如果创建成功将返回一个非负整数(socket_fd)，创建失败则返回一个负数，同时有错误码导出  
- [x] 2 bind绑定网络接口---我理解这部分是用来绑定网络通信文件的fd
```
int bind(int socket, const struct sockaddr *address,socklen_t address_len);
```   
- socket:上面成功创建套接字的返回值socket_fd
- address:网络协议的地址
> 它通常有三种，分别是struct sockaddr,struct sockaddr_in和struct sockaddr_un,一般我们采用的是struct sockaddr_in,但是bind里面采用的是struct sockaddr,因此这里需要我们进行强转，另外sockaddr_in里面有三个成员变量需要我们进行传参
> sin_port

