Install

まず,ros2の公式インストールページへ行く.

[ros2 install](https://index.ros.org/doc/ros2/Installation/Linux-Install-Debians/)

そこに記述されている.

```
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8
sudo apt update && sudo apt install curl gnupg2 lsb-release
curl http://repo.ros2.org/repos.key | sudo apt-key add -

sudo sh -c 'echo "deb [arch=amd64,arm64] http://packages.ros.org/ros2/ubuntu `lsb_release -cs` main" > /etc/apt/sources.list.d/ros2-latest.list'

export CHOOSE_ROS_DISTRO=crystal  # or bouncy or ardent
sudo apt update

sudo apt install ros-$CHOOSE_ROS_DISTRO-desktop

[Ubuntu 18.04]
sudo apt install python3-argcomplete

source /opt/ros/$CHOOSE_ROS_DISTRO/setup.bash
echo "source /opt/ros/$CHOOSE_ROS_DISTRO/setup.bash" >> ~/.bashrc

sudo apt update
sudo apt install ros-$CHOOSE_ROS_DISTRO-rmw-opensplice-cpp # for OpenSplice
sudo apt install ros-$CHOOSE_ROS_DISTRO-rmw-connext-cpp # for RTI Connext (requires license agreement)
```

をコマンドラインで打ち込む.

