Redis 有序集合和集合一样也是string类型元素的集合,且不允许重复的成员。
不同的是每个元素都会关联一个double类型的分数。redis正是通过分数来为集合中的成员进行从小到大的排序。
有序集合的成员是唯一的,但分数(score)却可以重复。
集合是通过哈希表实现的，所以添加，删除，查找的复杂度都是O(1)。 集合中最大的成员数为 232 - 1 

#### 有序集合命令
ZADD key score1 member1 [score2 member2] 
ZCARD key 
ZCOUNT key min max 
ZINCRBY key increment member 
ZINTERSTORE destination numkeys key [key ...] 
ZLEXCOUNT key min max 
ZRANGE key start stop [WITHSCORES] 
ZRANGEBYLEX key min max [LIMIT offset count] 
ZRANGEBYSCORE key min max [WITHSCORES] [LIMIT] 
ZRANK key member
ZREM key member [member ...] 
ZREMRANGEBYLEX key min max 
ZREMRANGEBYRANK key start stop 
ZREMRANGEBYSCORE key min max 
ZREVRANGE key start stop [WITHSCORES] 
ZREVRANGEBYSCORE key max min [WITHSCORES] 
ZREVRANK key member 
ZSCORE key member 
ZUNIONSTORE destination numkeys key [key ...] 
ZSCAN key cursor [MATCH pattern] [COUNT count] 
