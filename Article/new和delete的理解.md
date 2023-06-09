## new和delete的理解
### 0 前言 
> 最近看到这样的一个问题“怎样操作使得一个类对象只在栈（堆）上分配空间？”，要想解答这个问题就需要对new和delete有一定的理解才可以。
### 1 展开来谈谈
>在C语言阶段，对于空间的开辟与销毁，我们常常会用到malloc和free这对动态内存函数，随着语言的提升，到了C++这里我们对于动态内存的开辟，用到最多的变成了new和delete的，为什么会变成这样呢？我觉得这还得和C++的封装特性有关，这两个操作符背后有构造函数与析构函数，体现了一个整体性的效应；另外据说对于大型项目优势更大，毕竟咱们C++是做大事的人；最后一点，malloc和free毕竟是C语言的东西，咱们都到了C++了，还用别人的可能也不太好吧:smile:，不然配不上咱们高级语言的称号吗，所以new和delete就出来了
### 2 内部
- new:表面上我们调用new这个操作符，系统就会给我们分配出想要的空间，但是但底层他其实是分成两步来进行的，如下面的图所示，第一步就是调用operator new，把我们需要的空间给开出来，这里需要注意的是，operator new的底层其实还是调用malloc等函数进行开辟空间，第二步就是调用该类型的构造函数，给已经赋值完毕的空间赋初值。
- delete:同样的，在表层我们调用delete这个操作符，会把new出来的空间进行销毁，但是在底层他其实也是需要花费两步来进行，首先他需要调用析构函数将空间里面的资源都给处理掉，然后再将调用operator delete的函数，将开辟出来的空间都给释放掉。
![new和delete drawio](https://github.com/Lp700750/Blogs/assets/104414865/f0b0277d-4e8f-4f46-968b-d1ec0c9af033)
### 3 题解
[参考来源](https://blog.csdn.net/tkp2014/article/details/48846715)    
- 静态建立类对象：是由编译器为对象在栈空间中分配内存，是通过直接移动栈顶指针，挪出适当的空间，然后在这片内存空间上调用构造函数形成一个栈对象。使用这种方法，直接调用类的构造函数。    
- 动态建立类对象，是使用new运算符将对象建立在堆空间中。这个过程分为两步，第一步是执行operator new()函数，在堆空间中搜索合适的内存并进行分配；第二步是调用构造函数构造对象，初始化这片内存空间。这种方法，间接调用类的构造函数。
- 如果说将构造函数设置成为private时，静态建立类对象就不会在栈上面调用构造函数，这时是不是意味着就可以在堆上面使用new来动态创建对象呢？不可以，上面已经讲过，使用new还是会第二步还是会调用构造函数。
- 如果说将析构函数设置成private会怎样呢，对于静态构建对象，编辑器会管理对象的整个生命周期，他会预先去检查析构函数，如果析构函数也是private时，那么它将不会创建对象，因此这时只能够使用new在堆上面动态开辟内存了。
### 4定位new
定位new是指在已经分配原始内存的空间当中调用析构函数来初始化一个对象，它主要的使用场所在内存池当中,下面是他的主要使用方法，其中如果类初始化时有参数(2),则后面需要进行传参。
```c++
1. new(ptr) type
2. new(ptr) type(initializer-list)
```   
