# tcp协议
### 1 TCP协议的特征
>- 有连接：在进行通信之前，会先在客户端和服务端之间构建连接，当链接成功之后才会进行通信
>- 可靠：他有确认机制，重传机制，当数据没有到达对端或者有遗失时，他会有补救措施
>- 面向字节流：对数据的发送和接收都是基于字节流的
>- 全双工：可以同时接收和发送数据
### 2 TCP报头
>![image](https://github.com/Lp700750/Blogs/assets/104414865/858b81ee-f119-4053-86b6-a291b3eb8225)
>- 如何封装解包？
>   -  TCP包头里面包含有4位首部长度(单位是4字节)，代表由0000-1111(0-15),也就表明了报头的最大的长度是15×4=60字节，但是一般TCP的报头都是20个字节，也就是说包头里面的4位首部长度都是0101，知道了报头的大小，也就知道了如何进行封装和解包。
>- 如何进行向上交付？
>   -  传输层向上交付，交付给应用层，实际是交付给应用层的某个进程，UDP当中的目的端口号就是确认向上交付给应用层的哪个进程。
### 报头里面各个指标的含义
>- 16位源端口号：请求端发送请求的具体进程号码
>- 16位目的端口号：接受请求的目的端的具体进程号码
>- 32位序号：TCP传输数据是按字节流的，按字节为单位发送数据。在发送数据时，是一次性发送多条数据，接收端收到数据的顺序不一定和发送端发送数据的    顺序一致，因为可能走的网络路径不同，不一致的话，可能导致最终数据错误。TCP为了保证数据是有序的，会将发送的每一个字节的数据编号。接收方虽然在接收数据时不一定是有序的，但是在就收到数据后，会按照序号将数据排好序，放在接收缓冲区中。序列号保证了，数据的有序性。
>- 32位确认序号：确认序列号是接收方收到数据后，向发送方确认应答时，在报文的确认序列号中填写的序号。确认序列号在原始序列号的基础上加1。有两个作用：
>   -  告诉发送方，在此确认序列号之间的数据，都收到了。
>   -  告诉发送方，下一次发送数据时的序列号。
>- 4位首部长度：里面的长度是0000-1111(0-15)，代表报头的实际长度，另外它的单位是4字节
>- 6个标志位：不同的标志位代表这不同的报头类型
>   -  ACK：代表确认号是否有效
>   -  SYN：请求建立连接，将SYN标识称作同步报文段
>   -  RST：请求重新建立连接，将RST称作复位报文段
>   -  PSH：提示接收端将接收缓冲区里面的数据读走
>   -  URG：紧急指针，一般和16位紧急指针一起使用(该标志位一般很少使用)
>   -  FIN：请求断开连接，将FIN也称作结束报文段
>- 16位窗口大小(流量控制)：表示的是接收缓冲区的剩余大小，通过该窗口来控制数据传输的速度
>- 16位紧急指针：一般和URG标志位一起使用，表示该报文数据需要紧急优先处理，不能继续排序，16位紧急指针指向的位置就是该数据的地址，但是一次只能移动一个字节的大小，该紧急指针一般很少会使用
>- 16位校验和：发送端进行填充，CRC校验，接收端校验不通过，则会认为数据不通过，就会认为数据有问题，此处的检验和不光包含TCP的首部，也会包含部分的TCP数据
