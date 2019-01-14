# はじめに

## 私は,`ioctl()`について話します.

---

## なぜ`ioctl()`について調べようと思ったのか.


- 五号機 四号機 の違いを探していたためです.|

---

### 五号機

    ├── fifth_robot_pkgs
    │   ├── fifth_robot_2dnav # amcl move_base
    │   ├── fifth_robot_description #cartographer simulator
    │   ├── fifth_robot_launcher #sensor_bringup launchfile
    │   ├── fifth_robot_map #map
    │   └── fifth_robot_pkgs #nothing
    ├── goal_sender #targetpose from csv
    ├── goal_sender_msgs #msg generate for goal_sender
    ├── ros_imu_filter #imu config
    ├── teleop_master #radio control
    ├── third_party #laser-driver ypspur
    └── waypoints_reader #csv

---

### 五号機

---

### 四号機

    ├── fourth_robot_2dnav #map amcl move_base param
    ├── fourth_robot_2dnav_gazebo #sim amcl move_base param
    ├── fourth_robot_bringup #joy sensor bringup waypoints-csv
    ├── fourth_robot_control #ragio control
    ├── fourth_robot_description #sim urdf xacro
    ├── fourth_robot_driver #motor controller control
    ├── fourth_robot_gazebo #world for sim
    ├── fourth_robot_slam #for imu
    ├── README.md
    └── scripts
    
---

### 四号機

第三者のものが比較的少ない...

 管理が大変|

---

## `fifth_robot` `fourth_robot` の違い

|`fifth_robot`|`fourth_robot`|
---|---
|`imu`|`imu`|
|`3DLider`|`2DLider`|
|`ypspur`|`iMCS01`|

---

### driver 周辺の設定ファイルの違いを調べることにしました.

#### 四号機ではimcs01を使ってドライバの制御を行っていたため,imcs01に書き込むためにioctl()を使います.

---

### ioctl関数の宣言部

`<sys/ioctl.h>`

にて次のように宣言されています.

`extern int ioctl (int __fd, unsigned long int __request, ...) __THROW;`

---
