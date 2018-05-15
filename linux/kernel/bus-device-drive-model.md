#### 设备驱动模型的需求
- 总线、设备和驱动模型，如果把它们之间的关系比喻成生活中的例子是比较容易理解的
- 所谓高内聚低耦合是模块内各元素联系越紧密就代表内聚性就越高，模块间联系越不紧密就代表耦合性低

#### GITCHAT
设想一个叫 GITCHAT 的网卡，它需要接在 CPU 的内部总线上，需要地址总线、数据总线和控制总线，以及中断 pin 脚
那么在 GITCHAT 的驱动里需要定义 GITCHAT 的基地址、中断号等信息
假设 GITCHAT 的地址为0x0001，中断号是 2，那么
```c
#define GITCHAT_BASE 0x0001
#define GITCHAT_INTERRUPT 2

int gitchat_send () {
    writel(GITCHAT_BASE + REG, 1);
}

int gitchat_init () {
    request_init(GITCHAT_INTERRUPT, ...);
}
```

#### 设备驱动模型的实现
- 现在 CPU 板级信息和驱动分开的需求已经刻不容缓
- 但是基地址、中断号等板级信息始终和驱动是有一定联系的，因为驱动毕竟要取出基地址、中断号等
- 对软件工程熟悉的读者肯定立刻想到能不能设计一个类似接口适配器的类（adapter）去适配不同的板级信息
- 这样板子上的基地址、中断号等信息都在一个 adapter 里去维护，然后驱动通过这个 adapter 不同的 API 去获取对应的硬件信息

#### Linux 把设备驱动分为了总线、设备和驱动三个实体
##### 设备: 
- 描述基地址、中断号、时钟、DMA、复位等信息
- 代码：
  - arch/arm
  - arch/blackfin
  - arch/xxx
##### 驱动
- 完成外设的功能，如网卡收发包，声卡录放，SD卡读写
- 代码：
  - drivers/net
  - sound
  - drivers/mmc

##### 总线
- 完成驱动和设备关联
- 代码：
  - drivers/base/platform.c
  - drivers/pci/pci-driver.c
  
#### 模型设计好后，下面来看一下具体驱动的实践，首先把板子的硬件信息填入设备端，然后让设备向总线注册，这样总线就间接的知道了设备的硬件信息
```c
static struct resource gitchat_resource[] = {
  {
    .start = ...,
    .end = ...,
    .flags = IORESOURCE_MEM
  }
};

static struct platform_device gitchat_device = {
  .name = "gitchat";
  .id = 0;
  .num_resources = ARRAY_SIZE(gitchat_resource);
  .resource = gitchat_resource,
};

static struct platform_device *ip0x_device __initdata = {
  &gitchat_device,
};

static ini __init ip0x_init (void) {
  platform_add_devices(ip0x_device, ARRAY_SIZE(ip0x_device));
}
```

#### 驱动注册总线
```c
static int gitchat_probe (struct platform_device *pdev) {
  db->addr_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
  db->data_res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
  db->irq_res  = platform_get_resource(pdev, IORESOURCE_IRQ, 2);
}
```

#### 总线里有很多匹配方式
```c
static int platform_match (struct device *dev, struct device_driver *drv) {
  struct platform_device *pdev = to_platform_device(dev);
  struct platform_driver *pdrv = to_platform_driver(drv);

  // When driver_override is set, only bind to the matching driver
  if (pdev->driver_override) 
    return !strcmp(pdev->driver_override, drv->name);

  // Attempt an OF style match first
  if (of_driver_match_device(dev, drv))
    return 1;

  // Then try ACPI style match
  if (acpi_driver_match_device(dev, drv))
    return 1;

  // Then try to match against the id table
  if (pdrv->id_table)
    return platform_match_id(pdrv->id_table, pdev) != NULL;

  // fall-back to driver name match
  return (strcmp(pdev->name, drv->name) == 0);
}
```

#### 设备驱动模型的改善
相信通过上面的学习，相信对于设备、驱动通过总线来匹配的模型已经有所了解
- gitchat 驱动（driver/gitchat/gitchat.c）
  - bus
    - A板信息 arch/arm/match-A/board-A.c
    - B板信息 arch/arm/match-B/board-B.c
    - C板信息 arch/arm/match-C/board-C.c

- 最底层是不同板子的板级文件代码，中间层是内核的总线，最上层是对应的驱动
- 现在描述板级的代码已经和驱动解耦了，这也是 Linux 设备驱动模型最早的实现机制
