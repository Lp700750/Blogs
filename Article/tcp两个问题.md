# tcp两个问题
### 面向字节流
>- TCP当中，他在应用层将数据拷贝到发送缓冲区之后，应用层就不管了，而在发送缓冲区和接收缓冲区，里面的数据都是以字节的形式存在于缓冲区当中
### 粘包问题
>- 上面说到，TCP当中的数据是以字节的形式放在缓冲区当中，当有许多的数据都放在缓冲区当中时，就会出现不知道每一个TCP数据的边界，当上层取数据的时候，少取或者多取其他的数据到这个TCP当中，这就是出现了粘包问题。
>这个问题对于TCP，他是没有能力来进行避免或者说处理的，于是这个问题就只能交给应用层来进行处理，在http协议的报头当中的Content_length就是来获取有效载荷的大小，就是来避免粘包问题
>但是在UDP当中，由于它的报头是固定的20字节，有效载荷在报头里面有，因此UDP不存在说粘包问题
>避免粘包问题的措施，定制定长的报头和有效载荷，明确两个包的边界值
