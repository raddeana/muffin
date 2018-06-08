#### GPIO驱动结构
- 在 linux 中, 会在 gpiolib.c 中定义一个 ARCH_NR_GPIOS 大小的数组 static struct gpio_desc gpio_desc[ARCH_NR_GPIOS];
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
    struct gpio_chip    *chip;
    int         status = -EPROBE_DEFER;
    unsigned long       flags;

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
