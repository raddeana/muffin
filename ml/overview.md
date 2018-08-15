### 监督式学习
- 这个算法由一个目标变量或结果变量（或因变量）组成
- 这些变量由已知的一系列预示变量（自变量）预测而来
- 利用这一系列变量，我们生成一个将输入值映射到期望输出值的函数
  - 回归
  - 决策树
  - 随机森林
  - K – 近邻算法
  - 逻辑回归

### 非监督式学习
- 没有任何目标变量或结果变量要预测或估计
- 这个算法用在不同的组内聚类分析
- 这种分析方式被广泛地用来细分客户，根据干预的方式分为不同的用户组

### 强化学习
- 机器被放在一个能让它通过反复试错来训练自己的环境中
- 机器从过去的经验中进行学习，并且尝试利用了解最透彻的知识作出精确的商业判断
- 强化学习的例子有马尔可夫决策过程

#### 回归（Regression）
回归是在自变量和需要预测的变量之间构建一个模型，并使用迭代的方法逐渐降低预测值和真实值之间的误差
- Ordinary Least Squares（最小二乘法）
- Logistic Regression（逻辑斯底回归）
- Stepwise Regression（逐步回归）
- Multivariate Adaptive Regression Splines（多元自适应回归样条法）
- Locally Estimated Scatterplot Smoothing（局部加权散点平滑法）

#### 基于样例的方法（Instance-based Methods）
基于样例的方法需要一个样本库，当新样本出现时，在样本库中找到最佳匹配的若干个样本，然后做出推测
- k-Nearest Neighbour (kNN) 
- Learning Vector Quantization (LVQ) 
- Self-Organizing Map (SOM)

#### 正则化方法（Regularization Methods）
这是一个对其他方法的延伸（通常是回归方法），这个延伸就是在模型上加上了一个惩罚项，相当于奥卡姆提到，对越简单的模型越有利，有防止过拟合的作用，并且更擅长归纳
- Ridge Regression 
- Least Absolute Shrinkage and Selection Operator (LASSO) 
- Elastic Net

#### 决策树模型（Decision Tree Learning）
决策树方法建立了一个根据数据中属性的实际值决策的模型
- Classification and Regression Tree (CART) 
- Iterative Dichotomiser 3 (ID3) 
- C4.5 
- Chi-squared Automatic Interaction Detection (CHAID) 
- Decision Stump 
- Random Forest 
- Multivariate Adaptive Regression Splines (MARS) 
- Gradient Boosting Machines (GBM)

#### 贝叶斯（Bayesian）
贝叶斯方法是在解决归类和回归问题中应用了贝叶斯定理的方法
- Naive Bayes
- Averaged One-Dependence Estimators (AODE)
- Bayesian Belief Network (BBN)

#### 核方法（Kernel Methods）
核方法中最有名的是Support Vector Machines(支持向量机)
- Support Vector Machines (SVM) 
- Radial Basis Function (RBF) 
- Linear Discriminate Analysis (LDA)

#### 聚类（Clustering Methods）
聚类本身就形容了问题和方法。聚类方法通常是由建模方式分类的比如基于中心的聚类和层次聚类。所有的聚类方法都是利用数据的内在结构来组织数据，使得每组内的点有最大的共同性。
- K-Means 
- Expectation Maximisation (EM)

#### 联合规则学习（Association Rule Learning）
联合规则学习是用来对数据间提取规律的方法，通过这些规律可以发现巨量多维空间数据之间的联系，而这些重要的联系可以被组织拿来使用或者盈利
- Apriori algorithm 
- Eclat algorithm

#### 人工神经网络（Artificial Neural Networks）
受生物神经网络的结构和功能的启发诞生的人工神经网络属于模式匹配一类，经常被用于回归和分类问题，但是它存在上百个算法和变种组成
- Perceptron 
- Back-Propagation 
- Hopfield Network 
- Self-Organizing Map (SOM) 
- Learning Vector Quantization (LVQ)

#### 深度学习（Deep Learning）
Deep Learning(深度学习)方法是人工神经网络在当下的一个变种
- Restricted Boltzmann Machine (RBM) 
- Deep Belief Networks (DBN) 
- Convolutional Network 
- Stacked Auto-encoders

#### 降维（Dimensionality Reduction）
与聚类方法类似，对数据中的固有结构进行利用，使用无监督的方法学习一种方式，该方式用更少的信息来对数据做归纳和描述
- Principal Component Analysis (PCA) 
- Partial Least Squares Regression (PLS) 
- Sammon Mapping 
- Multidimensional Scaling (MDS) 
- Projection Pursuit

#### 组合方法（Ensemble Methods）
Ensemble methods(组合方法)由许多小的模型组成，这些模型经过独立训练，做出独立的结论，最后汇总起来形成最后的预测
- Boosting
- Bootstrapped Aggregation (Bagging)
- AdaBoost
- Stacked Generalization (blending)
- Gradient Boosting Machines (GBM)
- Random Forest
