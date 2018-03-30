#### SqueezeNet
小型化的网络模型结构，该网络能在保证不损失精度的同时，将原始AlexNet压缩至原来的510倍左右
SqueezeNet的核心指导思想是——在保证精度的同时使用最少的参数

SqueezeNet提出了3点网络结构设计策略：
- 将3x3卷积核替换为1x1卷积核
- 减小输入到3x3卷积核的输入通道数
- 尽可能的将降采样放在网络后面的层中

基于以上三个策略，作者提出了一个类似inception的网络单元结构，取名为fire module。
一个fire module 包含一个squeeze 卷积层（只包含1x1卷积核）和一个expand卷积层（包含1x1和3x3卷积核）。

#### Deep Compression
#### XNorNet
#### Distilling
#### MobileNet
#### ShuffleNet
