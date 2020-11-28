# 视觉导航智能车开发任务清单

[TOC]

## 一、开发计划

​		开发一款基于视觉的自主导航的ROS智能车。按照预置线路巡航。

- 室内环境
- 二维平面
- 视觉避障		
- 自主导航

## 二、任务列表

任务主要分三大块：

1. ROS智能车
2. 视觉路况分析软件
3. 安卓平板APP

### 2.1、ROS 智能车

整合所有传感器、构建运动模型、载入地图、开发导航算法。

| 智能车模块     | 型号            | 数量 | 详细                      |
| -------------- | --------------- | ---- | ------------------------- |
| 摄像头         | 自研            | 1    |                           |
| 激光测距传感器 | TFmini Plus     | 8    |                           |
| 四轮差速底盘   | autolabor       | 1    |                           |
| 主控芯片       | Raspberry Pi 4B | 1    |                           |
| 行车灯         |                 | 1    |                           |
| WIFI 无线网    | RL-5WRT         | 1    | 300Mbps无线 100M LAN WLAN |
| 18650电池组    |                 | 1    |                           |
| UWB定位模块    | Nooploop        | 1    | 室内测距                  |

#### 2.1.1 机械结构

1. **设计**底盘
2. **设计**外壳
3. **布局**传感器模块

#### 2.1.2 电气	

1. **设计**电池组
2. **升级**大功率电机
3. **布局**无线通讯设备

#### 2.1.3 软件	

主控采用Raspberry Pi 4B；电机驱动采用Arduino。操作系统采用ubuntu20.04LTS；机器人操作系统[ROS Noetic](http://wiki.ros.org/noetic)。

工程构建catkin。

1. **修改**四轮差速驱动运动模型
2. **发布**激光传感器数据
3. **发布**定位姿态传感器数据
4. **整合**车轮里程计、位姿、惯导。
5. **绘制**地图
6. **配置**导航包。（局部导航**DWA**算法；全局导航navfn算法。）
7. **协助**完成视觉分析软件的开发
8. **协助**完成安卓平板APP开发

### 2.2、视觉路况分析软件

图像处理，分析地面路况。

#### 2.2.1 视觉路况分析GPU版

​	操作系统采用Window/Ubuntu。使用NVIDIA的CUDA平台来加速。使用Cmake构建工程。

##### 	i.软件

1. 视频解码
2. 识别室内场景
3. 室内场景数据转换为平面地图路况
4. 发布地图数据

##### 	ii.界面	

1. 地平面标定方法;（手动标定与自动标定）
2. 标定板参数输入；

##### 	iii.算法

1. 识别室内场景的**算法**优化
2. 识别室内场景的**参数**优化

#### 2.2.2 视觉分析FPGA版

​			操作系统采用petaLinux。使用Xilinx的zynq7100平台来加速。使用Xilinx SDK构建工程。

##### i. FPGA开发

##### ii. petaLinux软件开发

### 2.3、安卓平板APP

- 监视小车实时运动状态；显示视频流；控制小车运动；调用导航功能包；设定小车巡航线路；
- 适配安卓平板

#### 2.3.1 开发平台

集成开发环境Android Studio。java语言。使用rosjava开发APP。

#### 2.3.2 开发任务

调用ROS主机集成好的功能。设置规划的巡航线路，完成自动巡航功能。

##### i. 读取数据在界面上显示

1. 二维平面地图
2. 世界地图
3. 线扫描激光、单点激光、图像深度
4. 图像节点的视频流
5. 里程计（运动状态）、位置、姿态。实时监控小车运行状态
6. GPS坐标 

##### ii. 控制小车运动

1. 设计遥感按钮发布控制小车运动的命令。
2. 调用ROS导航包提供的自动导航功能。

##### iii. 自动巡航功能

1. 设置规划的巡航线路，智能车按照既定线路自动导航。

## 三、存在问题

### 3.1 电气

1. Wifi是百兆网；
2. 电机功率3W；

### 3.3硬件

1. 使用4个摄像头。观察前后左右的路况。

### 3.2软件

1. 局部导航**DWA**算法。navfn算法（可以根据场景升级）

   

## 四、未来展望

1. 3D导航

2. 室外环境、工业环境

3. 更换底盘，麦克拉姆轮、转向舵

   

   