## TCP下的socket网络编程_基础版
### 0 前言
> 作为Linux跨网络通信的技术的体现，socket套接字编程这里说实话确实有许多的难点不好理解，最近又看了这部分的知识，决定将这部分进行梳理一下，想对他来一次系统性的理解。
### 1 服务器端
[服务端代码](https://github.com/Lp700750/Blogs/blob/master/Cpp/tcp_service.cpp)
作为提供服务的一端，服务器端的任务就会重很多，他在主要是分成如下的五个部分，主要的功能也如下：  
- [x] **1 socket创建套接字---我的理解这部分是用来进行开启网络通信服务**   
```
int socket(int domain, int type, int protocol);
```  
- domain:需要我们传入进去的是ip的协议类型，目前我们所用的通信协议大多是ipv4，因此这里应当输入AF_INET  
- type:需要我们传入的是传输层协议类型，此处我们所使用得到是TCP,因此这里需要传入的是SOCK_STREAM,以文件流的形式进行网络通信
- protocol:这里我们一般传入的都是0   
- return：如果创建成功将返回一个非负整数(socket_fd)，创建失败则返回一个负数，同时有错误码导出  
- [x] **2 bind绑定网络接口---我理解这部分是用来绑定网络通信文件的fd**
```
int bind(int socket, const struct sockaddr *address,socklen_t address_len);
```   
- socket:上面成功创建套接字的返回值socket_fd
- address:网络协议的地址
> 它通常有三种，分别是struct sockaddr,struct sockaddr_in和struct sockaddr_un,一般我们采用的是struct sockaddr_in,但是bind里面采用的是struct sockaddr,因此这里需要我们进行强转，另外sockaddr_in里面有三个成员变量需要我们进行传参    
> - sin_family:需要传入网络通信协议，这里好理解通常采用的是ipv4，也就是AF_INET   
> - sin_port：需要我们传入网络通信绑定的端口号，对于服务器来说这个端口各个厂家都相对比较固定,知识这里需要注意的是，我们输入的是本地的主机序列，为了便于移植性，我们需要将他在装变成网络序列,需要采取的转换函数是htons(16位)或者是htonl(32位)   
> - sin_addr：需要我们传入的是网络通信绑定的ip地址，需要注意的是，这里的sin_addr是一个ipv4地址的结构体，真正需要的是里面的s_addr,也就是sin_addr.s_addr,通常这个值我们不直接传入服务器的ip地址，然是直接传入0(INADDR_ANY),原因是因为服务器可能有多个ip地址，如果这里直接明文绑定某个ip地址，那么这台服务器的其他ip地址当中传送进来的服务就无法被接收到。我们要的是这台服务器的所有进程服务，而不是某一个ip地址当中的进程服务。
>   1. 这里需要注意的是如果我们传入进来的ip地址是一个字符串类型的时候，我们需要采用inet_addr函数，该函数的两个作用
>   2.  将点分十进制的字符串风格的IP，转化成为4字节IP
>   3.  将4字节由主机序列转化成为网络序列
   
- address_len:该网络协议地址，注意它的类型是socklen_t
- [x] **3 listen监听网络套接字---我理解这部分是接收所有来自客户端的请求**    
```
int listen(int socket, int backlog);
```      
- socket:上面成功创建套接字的返回值socket_fd
- backlog:暂时不解释，后面进行补充
- return：如果监听正确，那么0将会被返回，如果监听错误，那么-1将会被返回
- [x] **4 accept接收客户端请求**  
```
int accept(int socket, struct sockaddr *restrict address,socklen_t *restrict address_len);
```
- socket:上面成功创建套接字的返回值socket_fd
- address:网络协议的地址(同上面的bind)
- address_len:该网络协议地址，注意它的类型是socklen_t(同上面的bind)
- return:如果成功，他将会返回一个新的文件fd,这个文件fd专门用来处理网络通信的内容，失败的话将会返回-1并提供errno      
- [x] **5 文件操作**
- read:读取来自客户端的请求
- write:给客户端提供反馈


