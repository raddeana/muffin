#### 聚类分析
- 聚类分析 (Cluster analysis) 是一组将研究对象分为相对同质的群组 (Clusters) 的统计分析技术
- 聚类分析区别于分类分析 (Classification analysis)，前者是无监督学习，而后者是有监督学习
- 无监督学习也就是预先没有类别的标准，K-means 方法是最常见的聚类方法之一，在R语言的 kmeans() 函数中，聚类数目的参数 centers 是必须人为输入的

#### 数据
收集了96例患者的两个生化指标(a、b)，研究者拟根据a、b两个指标将96例患者分类若干组，进而对不同的组深入分析，制定不同的治疗方案
a、b两个指标的关系如下图(下面是模拟数据，实际情况通常没有那么明显的距离)

```c
set.seed(2018);
n = 100;
g = 6;
mydata = data.frame(a=unlist(lapply(1:g,function(i) rnorm(n/g, runif(1)*i^2))), b=unlist(lapply(1:g, function (i) rnorm(n/g, runif(1)*i^2)))); 
mydata = scale(mydata);
```

#### 组内平方和
画出不同聚类数目(通常是1到10)对应的组内平方和，以组内平方和基本不再明显变化为标准(较为主观)，从而确定聚类的数目
```
ss=(nrow(mydata)-1)*sum(apply(mydata, 2, var))  
for(i in 2:10){ss[i]=kmeans(mydata, centers=i)$tot.withinss}  
plot(1:10,ss,type="b",xlab="聚类数目",ylab="组内平方和") 
```

#### Medoids周围分类法
通过partitioning around medoids来估计最优的聚类数目
```c
library(fpc)
library(cluster)
fit=pamk(mydata)
plot(pam(mydata,fit$nc))
```

#### Calinsky准则
Calinsky是一个定量的评价指标，该值越大越好
```c
library(vegan)
fit=cascadeKM(mydata,inf.gr=1,sup.gr=10,iter=1000)
plot(fit,sortg=TRUE,grpmts.plot=TRUE)
```

#### BIC
BIC就是贝叶斯信息准则(Bayesian Information Criterion)，但与其用于模型的拟合判断(越小越好)不同的是，这里用于判断聚类数目的判断标准为越大越好
```c
library(mclust)  
fit=Mclust(mydata)  
plot(fit) 
```

#### AP法
AP表示Affinity propagation的意思，旨在通过Affinity propagation的方法估计最优的聚类数目
```c
library(apcluster)  
fit=apcluster(negDistMat(r=2),mydata)  
heatmap(fit) 
```

#### 多目标决策
NbClust函数提供30种的判断指标，我们可以用类似投票的原理，看看通过30种指标选出的最优聚类数目
```c
library(NbClust)  
fit = NbClust(mydata,min.nc=2,max.nc=10,method="kmeans",index="alllong")
```
