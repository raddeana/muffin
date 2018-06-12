#### 语音识别
- 主流的语音识别系统普遍采用基于深度神经网络和隐马尔可夫（Deep Neural Networks-Hidden Markov Model，DNN-HMM）的声学模型
- 声学模型的输入是传统的语音波形经过加窗、分帧，然后提取出来的频谱特征，如 PLP， MFCC 和 FBK
- 模型的输出一般采用不同粒度的声学建模单元，例如单音素 (mono-phone)、单音素状态、绑定的音素状态 (tri-phonestate) 

最早采用的网络结构是前馈全连接神经网路（Feedforward Fully-connected Neural Networks, FNN）
FNN 实现固定输入到固定输出的一对一映射，其存在的缺陷是没法有效利用语音信号内在的长时相关性信息

#### FSMN 模型的前世今生
- FSMN 模型
- FSMN 到 cFSMN 的发展历程

#### LFR-DFSMN 声学模型
- Deep-FSMN（DFSMN）网络结构
- 基于 LFR-DFSMN 的语音识别声学模型

#### 基于多机多卡的大数据声学模型训练
#### 解码延时、识别速度和模型大小

#### kaldi
https://github.com/tramphero/kaldi
