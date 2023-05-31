
GDT和IDT是描述符表，是由位值组成的数组。

x86架构有两种内存保护和提供虚拟内存的方法 —— 分段和分页。

分段：每个段当作操作内存的窗口。

分页：地址空间被分割成4KB页，页映射到物理内存上。

特权：ring0、ring3，段描述符里面有一个标志，代表它所处的级别。

GDT 是针对物理地址进行权限管控的。

# GDT

GRUB本身就为我们设置了一个GDT。

在x86 cpu中，有6个段寄存器。

代码段寄存器必须引用代码段描述符。

其余段寄存器必须引用数据段描述符。

# GDT Entry

```
// This structure contains the value of one GDT entry.  
// We use the attribute 'packed' to tell GCC not to change  
// any of the alignment in the structure.  
struct gdt_entry_struct  
{  
   u16int limit_low;           // The lower 16 bits of the limit.  
   u16int base_low;            // The lower 16 bits of the base.  
   u8int  base_middle;         // The next 8 bits of the base.  
   u8int  access;              // Access flags, determine what ring this segment can be used in.  
   u8int  granularity;  
   u8int  base_high;           // The last 8 bits of the base.  
} __attribute__((packed));  
typedef struct gdt_entry_struct gdt_entry_t;
```
# intel 3卷 3.4.5

## GDT

![[Pasted image 20230519001727.png]]

## GDTR

![[Pasted image 20230519002627.png]]

```
struct gdt_ptr_t{
    uint16_t limit;    
    uint32_t base;      // 指向 GDT
};
```

base + limit 为最后一个条目的地址。

# IDT

IDT 为中断向量表，当触发 ”int 2“ 这类中断时，cpu 会陷入中断向量表执行。