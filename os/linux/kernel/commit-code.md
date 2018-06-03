#### 向 Linux 内核提交代码
##### 安装和配置 msmtp
##### 安装和配置 Git 环境
  - 订阅 mailinglist
  - 下载 Linux 源代码
  - 阅读 Documentation/SubmittingPatches，这很重要
  
- 补丁描述
- 如何生成补丁
```cmd
# git format-patch HEAD^
0001-au0828-fix-logic-of-tuner-disconnection.patch
# cat 0001-au0828-fix-logic-of-tuner-disconnection.patch
From cc4f6646ae5eb0d75d56cca62e2d60c1ac8cad66 Mon Sep 17 00:00:00 2001
From: Changbing Xiong <cb.xiong@samsung.com>
Date: Tue, 22 Apr 2014 16:10:29 +0800
Subject: [PATCH] au0828: fix logic of tuner disconnection     // 此处的 [PATCH] 是工具自动加上的

The driver crashed when the tuner was disconnected while restart stream
restart stream operations has been released.

Change-Id: Iaa1b93f4d5b08652921069182cdd682aba151dbf          // 需要通过 vim 删除此行
Signed-off-by: peter liu <peter.liu@gitchat.com>
---
 drivers/media/usb/au0828/au0828-dvb.c |   13 +++++++++++++
```
- 检查补丁
```cmd
./scripts/checkpatch.pl 000*
---------------------------------------
0001-clk-samsung-mark-symbols-static-where-possible-for-s.patch
---------------------------------------
WARNING: Possible unwrapped commit description (prefer a maximum 75 chars per line)
#9:
 void__init s3c2410_common_clk_init(struct device_node *np, unsigned long xti_f,

WARNING: line over 80 characters
#29: FILE:drivers/clk/samsung/clk-s3c2410.c:363:
+static void __init s3c2410_common_clk_init(struct device_node *np, unsigned long xti_f,

total: 0 errors, 2 warnings, 8 lineschecked 
```
- 补丁的提交
```cmd
au0828: fix logic of tuner disconnection                                                     // 标题，带上模块名称，如au0828
                                                                                             // 此处必须空一行
The driver crashed when the tuner was disconnected while restart stream
operations are still being performed. Fixed by adding a flag in struct
au0828_dvb to indicate whether restart stream operations can be performed.

If the stream gets misaligned, the work of restart stream operations are
 usually scheduled for many times in a row. If tuner is disconnected at
this time and some of restart stream operations are still not flushed,
then the driver crashed due to accessing the resource which used in
restart stream operations has been released.
                                                                                             // 此处必须空一行
Signed-off-by: Changbing Xiong <cb.xiong@samsung.com>                                        // 通过git commit –s 自动生成
```
- 发送补丁
```cmd
git send-email 000* --tokgene@kernel.org, krzk@kernel.org, s.nawrocki@samsung.com, tomasz.figa@gmail.com, cw00.choi@samsung.com, mturquette@baylibre.com, sboyd@codeaurora.org--cc linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org, linux-clk@vger.kernel.org, linux-kernel@vger.kernel.org
```


