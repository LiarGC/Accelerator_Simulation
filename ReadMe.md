# 加速器模拟

## 1.介绍

> 闲来无事把学到的加速器知识用代码写出来

## 2.环境
### 2.1 visual studio

### 2.2 mkl（高性能矩阵运算）
#### 下载并安装mkl https://software.intel.com/content/www/us/en/develop/tools/oneapi/components/onemkl/download.html?operatingsystem=window&distributions=webdownload&options=offline  
![Image text](https://github.com/LiarGC/Accelerator_Simulation/blob/master/image/image1.png)  
#### 2.2.1 mkl单线程
mkl安装完成后，visual studio中会出现相关的选项，如下图选择单线程模式  
![Image text](https://github.com/LiarGC/Accelerator_Simulation/blob/master/image/image2.png)  
然后在需要的地方#include "mkl.h"即可开始使用mkl库  

#### 2.2.2 mkl多线程（可选）
多线程的设置稍微麻烦一点
1. 和上图一样的地方，但选择Parallel  
![Image text](https://github.com/LiarGC/Accelerator_Simulation/blob/master/image/image3.png)  
2. 此时直接编译会报错，找不到libiomp5md.dll，因此需要将libiomp5md.dll加入visual studio的工作环境中  
在下图位置填写libiomp5md.dll所在的目录。记得写PATH; 只写路径会报错  
![Image text](https://github.com/LiarGC/Accelerator_Simulation/blob/master/image/image4.png)  
我的libiomp5md.dll位于D:\Program Files\intel\oneAPI\compiler\2021.3.0\windows\redist\ia32_win\compiler，你需要根据自己mkl的安装路径来调整  
3. 然后在需要的地方#include “mkl.h”即可开始使用mkl库