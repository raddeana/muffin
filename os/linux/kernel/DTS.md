#### 设备树的出现
通过 DTS 可以像应用程序里的 XML 语言一样很方便的对硬件信息进行配置

#### arch/xxx/mach-xxx/board-xxx.c
```c
static struct resource gitchat_resource[] = {
  {
    .start = 0x20100000 ,
    .end = 0x20100000 +1,
    .flags = IORESOURCE_MEM 
    …
    .start = IRQ_PF IRQ_PF 15 ,
    .end = IRQ_PF IRQ_PF 15 ,
    .flags = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE
  }
};

static struct platform_device gitchat_device = {
  .name name ="gitchat",
  .id = 0,
  .num_resources num_resources = ARRAY_SIZE(gitchat_resource),
  .resource = gitchat_resource,
};

static struct platform_device *ip0x_devices[] __initdata ={
  &gitchat_device,
};

static int __init ip0x_init(void)
{
  platform_add_devices(ip0x_devices, ARRAY_SIZE(ip0x_devices)); 
}
```

```c
eth:eth@ 4,c00000 {
  compatible = "csdn, gitchat";
  
  reg =<
    4 0x00c00000 0x2
    4 0x00c00002 0x2
  >;
  
  interrupt-parent = <&gpio 2>;
  interrupts = <14 IRQ_TYPE_LEVEL_LOW>;
};
```

#### 驱动在 c 文件里的关系图
- gitchat 驱动
  - bus
    - arch/arm/mach-A/A.dts
    - arch/arm/mach-B/B.dts
    - arch/arm/mach-C/C.dts

这样对于 GITCHAT 驱动写一份就可以在 A、B、C 三个板子里共用

#### 设备树的文件结构和剖析
设备树和设备树之间到底是什么关系，有着哪些依赖和联系，先看下设备树之间的关系图
- gitchat1.dtsi
  - arch/arm/match-A/A.dts
  - arch/arm/match-B/B.dts
  - arch/arm/match-D/D.dts
- gitchat2.dtsi
  - arch/arm/match-A/A.dts
  - arch/arm/match-B/B.dts
  - arch/arm/match-C/C.dts
- gitchat3.dtsi
  - arch/arm/match-C/C.dts
  - arch/arm/match-D/D.dts

设备树（DTS）外，还存有 dtsi 文件，就像代码里的头文件一样，是不同设备树共有的设备文件，这不难理解
但是值得注意的是如果 dts 和 dtsi 里都对某个属性进行定义的话，底层覆盖上层的属性定义
设备树文件的格式是 dts，包含的头文件格式是 dtsi，dts 文件是一种程序员可以看懂的格式，但是 Uboot 和 Linux 只能识别二进制文件，不能直接识别

#### 设备树的应用
##### 这里介绍三大法宝: 文档、脚本、代码
- struct device_node *of_find_node_by_phandle(phandle handle);
- struct device_node *of_get_parent(const struct device_node_ *node);
- of_get_child_count()
- of_property_read_u32_array()
- of_property_read_u64()
- of_property_read_string()
- of_property_read_string_array()
- of_property_read_bool()

##### 设备树可以总结为三大作用:
- 平台标识，所谓平台标识就是板级识别，让内核知道当前使用的是哪个开发板，这里识别的方式是根据 root 节点下的 compatible 字段来匹配
- 运行时配置，就是在内核启动的时候 ramdisk 的配置，比如 bootargs 的配置，ramdisk 的起始和结束地址
- 设备信息集合，这也是最重要的信息，集合了各种设备控制器，接下来的实践课会对这一作用重点应用

##### platform identification
用DT来标识特定的machine, root字节的compatible字段, 匹配machine_desc的dt_compat
比如：compatible="ti,omap3-beagleboard" "ti,omap3450"

##### runtime configuration
chosen 节点属性
```c
chosen {
  bootargs = "console = ttySo, 115200 loglevel = 8"
  initrd-start = <oxc8000000>
  initrd-end = <oxc8200000>
}
```

##### device population
```c
serial@70006300 {
  compatible="nvidia, tegra20-uart"
  reg=<ox70006300 ox100>
  interrupts=<122>
}
```
