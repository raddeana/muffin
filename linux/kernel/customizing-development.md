#### 添加一个新的 SOC
- 我们在 arch/arm 目录下创建一个 mach-gitchat 的目录，然后创建 arch/arm/machgitchat/Kconfig，Makefile，common.c
- Kconfig 里做了一个叫 ARCH_GITCHAT 的假芯片，common.c 是对应的驱动，Makefile 里对这个驱动做了编译

#### 添加对应的 DTS
- 在 arch/arm/boot/dts 下创建 csdn-gitchat.dtsi 和 csdn-gitchat-evb.dts
- csdn-gitchat.dtsi 是对芯片的描述，csdn-gitchat-evb.dts 是针对这个芯片的 evb 板子描述

```c
/*
 * DTS file for demo platform for Dec20,2017 CSDN/Gitchat course
 * Copyright (c) 2017 xxx <xxx@gmail.com>
 * Licensed under GPLv2.
 */

/ {
  compatible = "csdn,gitchat";
  #address-cells = <1>;
  #size-cells = <1>;
  interrupt-parent = <&intc>;

  aliases {
    serial0 = &uart0;
  };

  cpus {
    #address-cells = <1>;
    #size-cells = <0>;

    cpu@0 {
      compatible = "arm,cortex-a9";
      device_type = "cpu";
      reg = <0x0>;
    };
    cpu@1 {
      compatible = "arm,cortex-a9";
      device_type = "cpu";
      reg = <0x1>;
    };
  };

  axi@40000000 {
    compatible = "simple-bus";
    #address-cells = <1>;
    #size-cells = <1>;
    ranges = <0x40000000 0x40000000 0x80000000>;

    l2-cache-controller@80040000 {
      compatible = "arm,pl310-cache";
      reg = <0x80040000 0x1000>;
      interrupts = <59>;
      arm,tag-latency = <1 1 1>;
      arm,data-latency = <1 1 1>;
      arm,filter-ranges = <0 0x40000000>;
    };

    intc: interrupt-controller@80020000 {
      #interrupt-cells = <1>;
      interrupt-controller;
      compatible = "csdn,gitchat";
      reg = <0x80020000 0x1000>;
    };

    peri-iobg@b0000000 {
      compatible = "simple-bus";
      #address-cells = <1>;
      #size-cells = <1>;
      ranges = <0x0 0xb0000000 0x180000>;

      ethernet@10000 {
        compatible = "davicom,dm9000";
        reg = <0x10000 0x2 0x10004 0x2>;
        interrupts = <7>;
        davicom,no-eeprom;
      };

      timer@20000 {
        compatible = "csdn,gitchat-tick";
        reg = <0x20000 0x1000>;
        interrupts = <0>;
        clocks = <&clks 11>;
      };

      clks: clock-controller@30000 {
        compatible = "csdn,gitchat-clkc";
        reg = <0x30000 0x1000>;
        #clock-cells = <1>;
      };

      gpio0: goio@40000 {
        #gpio-cells = <2>;
        #interrupt-cells = <2>;
        compatible = "csdn,gitchat-gpio";
        reg = <0x40000 0x200>;
        interrupts = <43>;
        gpio-controller;
        interrupt-controller;
      };

      uart0: uart@50000 {
        cell-index = <0>;
        compatible = "csdn,gitchat-uart";
        reg = <0x50000 0x1000>;
        interrupts = <17>;
        status = "disabled";
      };

      spi0: spi@d0000 {
        cell-index = <0>;
        compatible = "csdn,gitchat-spi";
        reg = <0xd0000 0x10000>;
        interrupts = <15>;
        #address-cells = <1>;
        #size-cells = <0>;
        status = "okay";
      };

      i2c0: i2c@e0000 {
        cell-index = <0>;
        compatible = "csdn,gitchat-i2c";
        reg = <0xe0000 0x10000>;
        interrupts = <24>;
        #address-cells = <1>;
        #size-cells = <0>;
        status = "okay";
      };
    };
  };
};
```

```c
/dts-v1/;

/include/ "csdn-gitchat.dtsi"

/ {
    model = "Csdn Gitchat EVB Board";
    compatible = "csdn,gitchat-evb", "csdn,gitchat";

    memory {
        device_type = "memory";
        reg = <0x00000000 0x20000000>;
    };

    chosen {
        bootargs = "console=ttyS0,115200 root=/dev/mtdblock5 rw rootfstype=ubifs";
    };

    axi@40000000 {
        peri-iobg@b0000000 {
            spi@d0000 {
                status = "disabled";
            };
            i2c@e0000 {
                pixcir_ts@5c {
                    compatible = "pixcir,pixcir_tangoc";
                    reg = <0x5c>;
                    interrupt-parent = <&gpio0>;
                    interrupts = <17 0>;
                    attb-gpio = <&gpio0 22 0>;
                    touchscreen-size-x = <1024>;
                    touchscreen-size-y = <600>;
                };
            };
        };
    };

};

&uart0 {
    status = "okay";
};
```

#### DTS 的编译
- 在 arch/arm/boot/dts/Makefile 里添加我们的板子
- dtc -I dts -O dtb csdn-gitchat-evb.dts -o csdn-gitchat-evb.dtb
