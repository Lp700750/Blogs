# volatile关键字
> ![Volatile关键字](https://github.com/Lp700750/Blogs/assets/104414865/2e064643-23cf-484f-9f38-9375f2ad577b)
> - o3：表示优化级别最高
> ### volatile关键字优化前后
> ![Volatile优化的前后对比](https://github.com/Lp700750/Blogs/assets/104414865/bc84808f-fca6-4123-a034-f6a706320df4)
> - volatile的作用：告诉编译器不要将我定义的这个变量进行优化，读取的时候必须贯穿式的读取内存，不要读取中间缓冲区寄存区的数据<font color="red">**（保持内存的可见性）**</font>

