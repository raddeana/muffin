#### LR与SVM的异同
##### 相同点：
逻辑回归和SVM都是有监督学习，本质都是线性分类判别模型

##### 不同点：
- 原理不同：逻辑回归LR基于损失函数最小化（经验风险最小化），而支持向量机SVM基于最大化间隔（结构风险最小化）
- LR的分类决策面由所有样本决定，而SVM的决策面即分割超平面只由少数样本即支撑向量决定
- SVM使用核函数，而LR一般不使用
- LR使用正则化来抑制过拟合，而SVM自带正则化，但SVM使用松弛因子来实现软间隔
- SVM只给出属于哪一类，而LR在给出类别的同时，还给出了后验概率（这使得LR可以用于医疗诊断、点击率预估、推荐系统等）

#### SVM核函数
若数据样本在低维空间线性不可分，它在某个高维空间是线性可分的，这就需要将样本数据从低维空间映射到高维空间，但这个映射关系难以确定
更重要的一点是，SVM中的运算是点积运算，而使用核函数，更确切的说是核技巧（Kernel trick），能将低维向量映射到高维空间并进行点积运算，转化为低维空间的简单运算，使得运算复杂度大大降低

#### 核函数
- 线性核函数
- 多项式核函数
- RBF径向基核函数
- Sigmoid核函数

#### SVM的多分类问题主要有以下几种策略
- 一对多One against Rest：训练两类分类器1 vs 2,3,4、2 vs 1,3,4、3 vs 1,2,4、 4 vs 1,2,3 共N个两类分类器，测试时将N个分类器结果投票
- 一对一One against One：训练两类分类器：训练1 vs 2、1 vs 3、1 vs 4、2 vs 3、2 vs 4、3 vs 4共N*（N-1）/ 2个分类器，测试时通过这些分类器进行投票
- 按类别层次划分

SVM基于间隔最大化来寻找分割超平面，需要做数据归一化，采用的loss function是hinge loss，深度学习常用的Softmax Regression是对逻辑回归LR的一种扩展的多类分类器
LR本质上是一种线性分类算法，基于损失函数最小化，其分类决策面与所有样本点都有关，为了防止过拟合可以加入正则项，多分类问题可以分解成one vs rest问题
其主要优点有：
- LR除了给出类别之外，还能给出后验概率（它采用的映射函数来自于sigmoid函数，输出可看作0~1的概率值），因此可以用于医疗诊断、CTR点击率预估、推荐系统等
- 可解释性强，特征可控性高，训练快，添加特征简单

决策树DT主要有ID3、C4.5、CART等方法，分别基于信息增益、信息增益率、基尼系数来做特征选取样本数据集划分，生成一颗决策树，除了叶节点外所有节点都对应着某个特征
缓解过拟合的方法包括剪枝和随机森林，随机森林是将多颗决策树即多个弱分类器组合成强分类器的方法

#### bagging、随机森林、boosting和adaboost
- bagging是在所有样本中有放回的随机选取n个样本，使用所有样本特征，训练得到一个分类器，重复m次得到m个分类器，最后采用投票的方式得到决策结果，各分类器权重一样
- 随机森林在所有样本中有放回的随机选取n个样本，在所有样本特征中随机选取k个特征，训练得到一个分类器，重复m次得到m个分类器，最后采用投票的方式得到决策结果，各分类器权重一样
- boosting相对于bagging，各分类器的权重由其分类的准确率决定，adaboost在boosting的基础上，每一个样本给定相同的初始权重，分类出错的样本的权重上升，分类正确的样本权重下降，即它是在前一个分类器训练的基础上训练得到新的分类器，分类器的权重根据其分类的准确率决定，组合弱分类器形成强分类器，不容易过拟合

PCA主成分分析，目的是特征降维，降低特征间相关性，实际上是将原始特征空间变换到一个复杂度更低并尽可能保留了原始信息的特征空间
- 去均值；
- 计算协方差矩阵；
- 特征分解，选取前 top k 特征；
- 特征降维

#### 样本不均衡
- 若正样本远多于负样本，且负样本数量足够大，可以对正样本进行下/降采样，例如随机采样，实际场景下可能用到分层采样
- 若正样本远多于负样本，且负样本数量不够多，可以收集更多的负样本，或对负样本进行上采样数据增广（例如对于图像数据，进行随机旋转、平移、缩放、镜像、图像增强等），还有修改损失函数的loss weights