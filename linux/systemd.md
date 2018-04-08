#### 作为 Linux 的系统启动器
Linux 系统通常都使用 cron 设置定时任务，但是 Systemd 也有这个功能
优点：
- 自动生成日志，配合 Systemd 的日志工具，很方便除错
- 可以设置内存和 CPU 的使用额度，比如最多使用50%的 CPU
- 任务可以拆分，依赖其他 Systemd 单元，完成非常复杂的任务

#### 邮件脚本
```sh
#!/usr/bin/env bash
echo "This is the body" | /usr/bin/mail -s "Subject" someone@example.com
```

#### systemd 单元
单元就是 Systemd 的最小功能单位，是单个进程的描述; 一个个小的单元互相调用和依赖，组成一个庞大的任务管理系统，这就是 Systemd 的基本思想
Service 单元负责后台服务，Timer 单元负责定时器，Slice 单元负责资源的分配

单元描述文件:
- /lib/systemd/system 系统默认的单元文件
- /etc/systemd/system 用户安装的软件的单元文件
- /usr/lib/systemd/system 用户自己定义的单元文件

查看所有的单元文件的命令:
- 查看所有单元 systemctl list-unit-files
- 查看所有 Service 单元 systemctl list-unit-files --type service
- 查看所有 Timer 单元 systemctl list-unit-files --type timer

单元的管理命令:
- 启动单元 systemctl start [UnitName]
- 关闭单元 systemctl stop [UnitName]
- 重启单元 systemctl restart [UnitName]
- 杀死单元进程 systemctl kill [UnitName]
- 查看单元状态 systemctl status [UnitName]
- 开机自动执行该单元 systemctl enable [UnitName]
- 关闭开机自动执行 systemctl disable [UnitName]

#### Service 单元
新建 Service 非常简单，就是在/usr/lib/systemd/system目录里面新建一个文件，例子：
```
[Unit]
Description=MyTimer
[Service]
ExecStart=/bin/bash /path/to/mail.sh
```

[Service]部分用来定制行为
- ExecStart: systemctl start所要执行的命令
- ExecStop: systemctl stop所要执行的命令
- ExecReload: systemctl reload所要执行的命令
- ExecStartPre: ExecStart之前自动执行的命令
- ExecStartPost: ExecStart之后自动执行的命令
- ExecStopPost: ExecStop之后自动执行的命令

#### Timer 单元
/usr/lib/systemd/system目录里面，新建一个mytimer.timer文件
```
[Unit]
Description=Runs mytimer every hour

[Timer]
OnUnitActiveSec=1h
Unit=mytimer.service

[Install]
WantedBy=multi-user.target
```

[Timer]部分定制定时器。Systemd 提供以下一些字段：
- OnActiveSec：定时器生效后，多少时间开始执行任务
- OnBootSec：系统启动后，多少时间开始执行任务
- OnStartupSec：Systemd 进程启动后，多少时间开始执行任务
- OnUnitActiveSec：该单元上次执行后，等多少时间再次执行
- OnUnitInactiveSec： 定时器上次关闭后多少时间，再次执行
- OnCalendar：基于绝对时间，而不是相对时间执行
- AccuracySec：如果因为各种原因，任务必须推迟执行，推迟的最大秒数，默认是60秒
- Unit：真正要执行的任务，默认是同名的带有.service后缀的单元
- Persistent：如果设置了该字段，即使定时器到时没有启动，也会自动执行相应的单元
- WakeSystem：如果系统休眠，是否自动唤醒系统

#### [Install] 和 target
mytimer.timer文件里面，还有一个[Install]部分，定义开机自启动（systemctl enable）和关闭开机自启动（systemctl disable）这个单元时，所要执行的命令

#### 定时器的相关命令
- 启动 sudo systemctl start mytimer.timer
- 查看状态 systemctl status mytimer.timer
- 查看定时器 systemctl list-timers
- 关闭 systemctl stop myscript.timer
- 自动运行 systemctl enable myscript.timer
- 关闭开机自启动 systemctl disable myscript.timer

#### 日志
- 查看整个日志 sudo journalctl
- 查看 mytimer.timer 的日志 sudo journalctl -u mytimer.timer
- 查看 mytimer.timer 和 mytimer.service 的日志 sudo journalctl -u mytimer
- 从结尾开始查看最新日志 sudo journalctl -f
- 从结尾开始查看 mytimer.timer 的日志 journalctl -f -u timer.timer

