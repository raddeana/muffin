### IP ADDRESS
- internet protocol ADDRESS         // 网络进程地址
- ipv4 internet protocol version 4

### 子网掩码
- 用来划分网络区域
- 子网掩码非0位对应的ip上的数字表示这个ip的网络位
- 子网掩码0位对应的数字是ip的主机位
- 网络位表示网络区域
- 主机位表示网络区域里的某台主机

### IP通信判定
```
172.25.254.1/24       24=255.255.255.0      // 前24位为网络位1表示为第一台主机
172.25.254.2/24                             // 前24位为网络位1表示为第一台主机
172.25.0.1/16         16=255.255.0.0        // 前16位为网络位1表示为第一台主机
```
```
- 172.25.254.0/8  (第一位是网络位)
- 172.25.254.0/16 (前俩位为网络位)
- 172.25.254.0/24 (前三位是网络位)
```

### 网络设定工具
```
ping                 ## 检测网络是否通畅
ping -c 1 -w 1       ## -c（次数）  -w（时间）

ifconfig  device  ip/24      ## 设定ip为临时设定
ifconfig                     ## 查看或设定网络接口

ifconfig   device  down      ## 关闭网卡
ifconfig   device  up        ## 开启网卡


ip   addr                    ## 检测这项网络接口
ip   addr  show              ## 检测

ip addr add  ip/24  dev device  ## 设定
```

### 图形方式设定ip
```
nm-connection-editor   ##修改后不生效

systemctl  stop NetworkManager    // 关闭NetworkManager服务
systemctl  restart  network       // 重启网络
systemctl  start  NetworkManager  // 开启NetworkManager服务
```

### 命令方式设定网络
- 使用设备名称
```
nmcli                                      ## NetworkManager必须开启
nmcli   device  connect  eth0              ## 启用eth0网卡
nmcli   device disconnect  eth0            ## 关闭eth0网卡
nmcli   device  show   eth0                ## 查看网卡信息
```

```
nmcli     device  status eth0              ## 查看网卡服务接口信息 
```

- 使用网络名称
```
nmcli  connection  show        // 显示网络信息  
nmcli  connection down eth0    // 关闭
nmcli  connection  up  eth0    // 开启
nmcli  connection delete eth0  // 删除
```

```
nmcli  connection add type ethernet con-name westos ifname eth0 ip4 // 添加一个名字为 westos ip 为172.25.254.102/24的网
nmcli  connection modify westos ipv4.method auto                    // 修改为动态的网络
nmcli connection modify westos ipv4.method manual                   // 修改为静态的网络
nmcli connection modify westos ipv.4  addresses 172.25.254.202/24   // 修改网络ip
```

### 管理网络配置文件
- 网络配置目录
```
/etc/sysconfig/network-scripts
```

- 网络配置文件的命名规则
```
DEVICE=****                 // 设备名称
BOOTPROTO=dhcp/static/none  // 设备工作方式（静态/动态/无）
ONBOOT=yes                  // 网络服务开启时自动激活网卡
IPADDR=yes                  // ip地址
PREFIX=24                   // 子网掩码设置形式1
NETMASK=255.255.255.0 //子网掩码设置形式2
NAME=eth0             // 接口名称
TYPE=Ethernet         // 网卡工作模式 (以太网)
```
```
vim /etc/sysconfig/network-scripts/ifconfig-zllvim /etc/sysconf
vim /etc/sysconfig/network-scripts/ifconfig-westos
```

### 网关
```
sysctl -a | grep ip_forward ## 查看内核路由功能是否开启，内核的路由功能负责网路转换
```

- 如果内核路由功能打开
```
net.ipv4.ip_forward=1
```

- 如果内核路由功能没有打开
```
net.ipv4.ip_forward=0

vim /etc/sysctl.conf ## 写入：net.ipv4.ip_forward=1
sysctl -p            ## 生效
```

- 开启临时防火墙伪装
```
systemctl  start firewalld      // 开启火墙
firewalld-cmd -add-masquerade   // 伪装防火墙
```

### 客户端设置网关
```
vim /etc/sysconfig/network-scripts/ifcfg-eth0  // 设置单独网卡的网关vim
vim /etc/sysconfig/network                     // 设置全局网关，对所有网卡都生效，访问外网时将所有的数据包都扔给这个网关
systemctl restart network                      // 设定好后要记得重启网络
route -n                                       // 查看路由
```

```
ping 172.25.254.250         ## 在客户端检测网络是否通畅
traceroute  172.25.254.250  ## 跟踪客户端访问175.25.254.202的过程
```

FROM: https://blog.csdn.net/weixin_44224288/article/details/86528439





