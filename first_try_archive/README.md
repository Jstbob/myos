# 自制操作系统

自制自己的类`Unix`的操作系统，仅供自己学习所用。

# 计划

1. 收集资料。

2. 列出完成目标的大纲。

暂时将自制的过程分为三个阶段：

1. [汇编语言学习](./gas/index.md)
2. 80386 CPU 学习
3. 自制操作系统

# 环境

qemu、windows wsl、GNU Binutils、gcc

# 参考

xv6-public，Mit 操作系统 Lab，网上非常有名的免费实验课；

[osdev](https://wiki.osdev.org/Main_Page)，操作系统开发社区，有你需要的一切知识。

# 怎么运行

在该目录下，运行以下指令：

```
qemu-system-i386 -cdrom myos.iso
```

# 运行的演示截图

![image-20210101080021174](https://gitee.com/ningbocai/pictures/raw/master/20230924/image-20210101080021174.png)

# 再次编译后出现错误

运行`make qemu`出现以下错误：

```
qemu-system-i386: Error loading uncompressed kernel without PVH ELF Note
```
