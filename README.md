# 自制操作系统
`first_try_archive`目录是第一次尝试写操作系统内核的存档，是之前的老的代码，没有在这一次中使用。

`main`目录是第二次尝试编写内核的主目录，所有的源代码都放在该目录下。

# 怎么运行

在`main`目录下，运行`make qemu-driver-nodebug`可以进入系统，进入系统后有三个可以运行的指令：

* ls — 显示文件名和文件大小
* cat [file] — 读取文件内容，file为文件的名字
* clear — 清屏

qemu运行的截图演示：

![image-20230924204356394](https://gitee.com/ningbocai/pictures/raw/master/20230924/image-20230924204356394.png)

# 注意

该系统只是试验上的作品，只用于自己的学习，有很多的`bug`。
