# 自动驾驶视觉导航车

## 一、导航目标

车辆自主分析路况信息。自动驾驶到目标地点。

## 二、导航组件

### 1. 硬件模块

#### 1.1机器人结构

| 功能模块 | 硬件支持                                    |
| -------- | ------------------------------------------- |
| 控制主板 | Raspberry Pi 2 Model B，NVIDIA Jetson TX2， |
| 底盘结构 | Differential Drive (两轮差速)               |
| 传感器   | UWB，IMU，Camera，radar，Encoder            |

#### 1.2传感器模块

硬件主要由空间定位、姿态反馈、行驶方向路况采集、四周行车路况采集、车轮驱动系统等几部分组成；

| 功能模块         | 硬件支持                                                     |
| ---------------- | ------------------------------------------------------------ |
| 空间定位         | GPS 、基站定位、二维码 、 RFID 、 蓝牙、LoRa、Wifi、UWB      |
| 姿态反馈         | 三维电子罗盘，惯性测量单元IMU                                |
| 行驶方向路况采集 | 空间识别相机、毫米波雷达、激光雷达、深度相机（depth camera） |
| 四周行车路况采集 | 雷达（radar）                                                |
| 车轮驱动系统     | 驱动马达；电机编码器；                                       |

#### 1.2.1 空间定位

##### 功能简介

​		空间定位模块用于确定小车在空间中的位置。

​		空间位置可以是地球坐标系（Earth-Fixed Coordinate System）下的经纬度，也可以是室内环境（如，物流仓库、工业生产现场等）中三维[笛卡尔坐标系](https://baike.baidu.com/item/笛卡尔坐标系)下的空间位置坐标。

##### 定位技术原理

| 测量方法 | 英文全称                  | 中文             |
| -------- | ------------------------- | ---------------- |
| AOA      | Angle of Arriva           | 到达角度定位     |
| TOA      | Time of Arriva            | 到达时间定位     |
| TDOA     | Time Difference of Arriva | 到达时间差法     |
| TOF      | Time of flight            | 飞行时间测距法   |
| RSS      | Received Signal Strength  | 接收信号强度定位 |
|          |                           |                  |

##### 几种定位比较

| 技术                                                         | 精度          | 优点     | 缺点   | 场景 |
| ------------------------------------------------------------ | ------------- | -------- | ------ | ---- |
| GPS([全球卫星定位系统](https://www.baidu.com/s?wd=全球卫星定位系统&tn=SE_PcZhidaonwhc_ngpagmjz&rsv_dl=gh_pc_zhidao)) | 10米          |          |        |      |
| GNSS(全球导航卫星系度统)                                     | 厘米          |          |        |      |
| 基站定位                                                     | 500米到2000米 |          |        |      |
| 蓝牙                                                         | 3米-5米       |          |        |      |
| WIFI                                                         | 2米           |          |        |      |
| 地磁定位                                                     | 0.1 米到 2 米 |          | 米级   |      |
| RFID                                                         |               |          |        |      |
| UWB                                                          | 1厘米-10厘米  | 实时性好 | 怕干扰 | 工厂 |

##### 传感器

​		常用的定位手段有利用GPS 、基站定位、二维码 、 RFID 、 蓝牙、LoRa、Wifi、UWB等。

#### 1.2.2姿态反馈

##### 功能简介

​		用于确定导航车的姿态信息。导航车姿态包含俯仰（pitch）、滚转（roll）、偏航（yaw）。欧拉角（姿态角）用以确保导航车处于 正确的行驶方向。

##### 传感器

​		三维电子罗盘广泛应用于航空、航天、机器人、航海、车辆自主导航等领域。

#### 1.2.3行驶方向路况采集

##### 功能简介

​		导航车必须能够识别道路及道路上的路况，在无障碍物的路面上向前行驶，因此在行驶方向上必须能检测到足够远的障碍物。

##### 传感器

​		汽车行驶方向分析路况用到的传感器有空间识别相机、毫米波雷达、激光雷达、深度相机（depth camera）等。

#### 1.2.4四周行车路况采集

##### 功能简介

​		导航车行驶过程中需要与左右车辆或障碍物保持一定的安全距离。

##### 传感器

​		雷达测距。

#### 1.2.5车轮驱动系统

功能简介

​		驱动导航车运动，同时反馈导航车的运动状态（即，速度矢量、行驶里程）。

传感器

​		测速编码器。

### 2. 软件模块

| 功能模块     |      |
| ------------ | ---- |
| 位置姿态控制 |      |
| 视觉图像分析 |      |
| 运动控制     |      |
| 雷达测距     |      |
| 构建地图     |      |
| 路径规划     |      |

#### 2.1位置姿态控制

​		导航车感知自身位姿，确保行车安全。能够根据目标线路迅速调整偏航角。协助完成路径规划。

#### 2.2视觉图像分析

​		图像分析识别路面及路面障碍物。确定障碍物的相对位置（比如，极坐标系下的角度θ和距离ρ），同时在地图上动态构建障碍物。协助完成本地实时路径规划。

#### 2.3运动控制

​		控制小车按照给定的速度矢量运动，同时反馈当前的速度矢量。协助完成运动规划。

#### 2.4雷达测距

​		确定近距离内的障碍物。同时在地图上动态构建障碍物。协助完成本地实时路径规划。

#### 2.5构建地图

##### 2.5.1静态地图

​		静态地图是指那些静止车辆驶入的河流、山川、建筑，墙体，草坪等。静态地图获取方式主要是测绘。

| 地图类型           | 地图坐标系                                                   | 来源      |
| ------------------ | ------------------------------------------------------------ | --------- |
| 世界地图           | 地球坐标系                                                   | 高德/百度 |
| 室内或厂区平面地图 | 二维[笛卡尔坐标系](https://zh.wikipedia.org/wiki/笛卡尔坐标系) | 自行测绘  |
| 立体车库           | 三维[笛卡尔坐标系](https://zh.wikipedia.org/wiki/笛卡尔坐标系) | 自行测绘  |

##### 2.5.2动态地图

​		行驶过程中利用传感器动态发现近距离障碍物。并将障碍物添加到地图中，用于本地实时路径规划。

​		传感器主要有视觉传感器、雷达测距传感器等。

​		障碍物可以是的路中央的花坛，两边的围栏、隧道墙体等，也可以是临时放置的水马围挡等路障，或者是正在行驶的车辆、路边行走和过马路的行人。

#### 2.6路径规划

##### 2.6.1全局路径规划（global planner）

​		根据给定的目标位置进行总体路径的规划。

##### 2.6.2本地实时规划（local planner）

​		根据附近的障碍物进行躲避路线规划。
