#### GPIO驱动结构
- gpiolib.c 中定义一个 ARCH_NR_GPIOS 大小的数组 static struct gpio_desc gpio_desc[ARCH_NR_GPIOS];
- 每个元素对应于当前 CPU 上各个 GPIO 接口的信息，记录各个 GPIO 的描述符，即对应 struct gpio_desc 结构体
- struct gpio_desc 内的成员 gpio_chip 又指向了一系列关于 GPIO 的操作

```c
/**
 * These "optional" allocation calls help prevent drivers from stomping
 * On each other, and help provide better diagnostics in debugfs
 * They are called even less than the "set direction" calls
 */
static int gpiod_request(struct gpio_desc *desc, const char *label)
{
  struct gpio_chip *chip;
  int status = -EPROBE_DEFER;
  unsigned long flags;

  if (!desc) {
    pr_warn("%s: invalid GPIO\n", __func__);
    return -EINVAL;
  }

  spin_lock_irqsave(&gpio_lock, flags);
  chip = desc->chip;
    
  if (chip == NULL) {
    goto done;
  }

  if (!try_module_get(chip->owner)) {
    goto done;
  }
    
  /** 
   * NOTE:  gpio_request() can be called in early boot,
   * before IRQs are enabled, for non-sleeping (SOC) GPIOs.
   */
   if (test_and_set_bit(FLAG_REQUESTED, &desc->flags) == 0) {
     desc_set_label(desc, label ? : "?");
     status = 0;
   } else {
     status = -EBUSY;
     module_put(chip->owner);
     goto done;
   }

   if (chip->request) {
     /* chip->request may sleep */
     spin_unlock_irqrestore(&gpio_lock, flags);
     status = chip->request(chip, gpio_chip_hwgpio(desc));
     spin_lock_irqsave(&gpio_lock, flags);

     if (status < 0) {
       desc_set_label(desc, NULL);
       module_put(chip->owner);
       clear_bit(FLAG_REQUESTED, &desc->flags);
       goto done;
     }
   }
    
  if (chip -> get_direction) {
    /* chip -> get_direction may sleep */
    spin_unlock_irqrestore(&gpio_lock, flags);
    gpiod_get_direction(desc);
    spin_lock_irqsave(&gpio_lock, flags);
  }
done:
    if (status) {
      gpiod_dbg(desc, "%s: status %d\n", __func__, status);
    }
    
    spin_unlock_irqrestore(&gpio_lock, flags);
    return status;
}

int gpio_request (unsigned gpio, const char *label)
{
  return gpiod_request(gpio_to_desc(gpio), label);
}

EXPORT_SYMBOL_GPL(gpio_request);
```

#### GPIO的数据结构
- struct gpio_chip: 标记GPIO所属的控制器，里面包含诸多回调函数，用于控制GPIO的行为，各个板卡都有实现自己的gpio_chip控制模块 
- struct gpio_desc: 用于标记一个GPIO

#### GPIO驱动
- 定义了GPIO板级控制的内容，包括设置 set gpio，get gpio，dir_in，dir_out，gpio_to_irq等行为;
- 获取GPIO板级的资源，包括 gpio_reg_base,并赋值给 struct gpio_chip;
- 将struct gpio_chip添加到GPIOLIB中；

```c
static struct platform_driver xxx_gpio_driver = {
  .probe = xxx_gpio_probe,
  .remove = xxx_gpio_remove,
  .driver.owner = THIS_MODULE,
  .driver = {
    .name = "xxx-gpio",
  },
};

static int __init xxx_gpio_init (void) {
  return platform_driver_register(&xxx_gpio_driver);
}
```

#### 添加与之对应的platform设备
在arch/arm/mach-xxx/xxx.c会添加 platform 的设备
```c
static struct platform_device xxx_gpio_device = {
  .name = "xxx-gpio",
  .id = 0,
  .num_resources = ARRAY_SIZE(xxx_gpio_resources),
  .resource = xxx_gpio_resources,
};
```

#### struct gpio_chip添加到GPIOLIB
- probe() 中初始化struct gpio_chip结构体的成员
- 并调用 gpiochip_add()将gpio_chip添加到 GPIOLIB 中
- GPIOLIB 提供GPIO调用的接口函数
