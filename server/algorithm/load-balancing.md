#### 负载均衡
负载均衡，英文名称为Load Balance，指由多台服务器以对称的方式组成一个服务器集合，
每台服务器都具有等价的地位，都可以单独对外提供服务而无须其他服务器的辅助

```java
public class IpMap 
{
  public static HashMap<String, Integer> serverWeightMap = new HashMap<String, Integer>();
  
  static {
    serverWeightMap.put("192.168.1.100", 1);
    serverWeightMap.put("192.168.1.101", 1);
    serverWeightMap.put("192.168.1.102", 4);
    serverWeightMap.put("192.168.1.103", 1);
    serverWeightMap.put("192.168.1.104", 1);
    serverWeightMap.put("192.168.1.105", 3);
    serverWeightMap.put("192.168.1.106", 1);
    serverWeightMap.put("192.168.1.107", 2);
    serverWeightMap.put("192.168.1.108", 1);
    serverWeightMap.put("192.168.1.109", 1);
    serverWeightMap.put("192.168.1.110", 1);
  }
}
```

#### 常用算法
- 轮询（Round Robin）
- 随机（Random）
- 源地址哈希（Hash）
- 加权轮询（Weight Round Robin）
- 加权随机（Weight Random）
- 最小连接数（Least Connections）
