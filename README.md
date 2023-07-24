This is copy from [turtlebot3-UE](https://github.com/rapyuta-robotics/turtlebot3-UE).
# Turtlebot UE

UE Project which includes examples to use rclUE.

## Documentation
- [rclUE](): This repo enables communication between UE and ROS 2.
- [RapyutaSimulationPlugins](): This repo has classes/tools to create ROS 2 enables robots with rclUE.
## Branches
- `devel`: Main branch. Compatible with Unreal Engine 5.1 with Ubuntu 20.04
- `jammy`: Compatible with Unreal Engine 5.1 with Ubuntu 22.04
- `UE4`: Compatible with Unreal Engine 4.27


## Setup and run
* please check [Getting Started](https://rapyutasimulationplugins.readthedocs.io/en/doc_update/getting_started.html) as well.

1.  Download UE5.1 for Linux by following [Unreal Engine for Linux](https://www.unrealengine.com/en-US/linux)
2.  Clone this repo : `git clone --recurse-submodules git@github.com:rapyuta-robotics/turtlebot3-UE.git`
3.  Retrieve the large files : `git-lfs pull && git submodule foreach git-lfs pull`
4.  Build and run
    ```
    cd turtlebot3-UE
    export UE5_DIR=<path to UE5>
    ./run_editor.sh <false or true to use dds server or not> $(pwd) <ue_exe>
    ```
\* Since the prooject is set to use 
[ROS2 with Discovery Server](https://docs.ros.org/en/foxy/Tutorials/Advanced/Discovery-Server/Discovery-Server.html)
to communicate with ROS2 Node in UE, you needs to execute `source turtlebot3_UE/fastdds_setup.sh`. You can run without server by `./run_editor.sh false`


## Install pre-commit
Please install pre-commit before commiting your changes.
Follow this instruction https://pre-commit.com/

then run

```bash
./setup_pre_commit.sh
```

this will setup pre-commit to all submodules as well.

## Turtlebot3 navigation

### Installation

1. [Install ROS2 foxy](https://docs.ros.org/en/foxy/Installation.html)
    * you can use ROS2 humble as well by checkout `Plugins/rclUE` to `UE5_devel_humble` branch.
2. [Install Nav2](https://navigation.ros.org/getting_started/index.html)

### Run

1. Play turtlebot3-UE
2. `cd turtlebot3-UE && source fastdds_setup.sh` #if you use ROS2 Discovery Server. You don't need this if you start editor with `./run_editor false`.
3. `ros2 launch nav2_bringup tb3_simulation_launch.py use_simulator:=False map:=<path to turtlebot3-UE>/Content/Turtlebot3_benchmark.yaml `

### Tests
!NOTE: The test script is setup to run with fastdds, which requires UE to start before ROS is enabled, thus `/opt/ros/<ros_distro>/setup.bash`, which is already run in the script, needs to be not added to `~/.bashrc`
```sh
./ExternalTest/run_local_sim_tb3_tests.sh <ue_exe> <ue_map> <tb3_model> <tb3_name> <tb3_init_pos> <tb3_init_rot>
```

with:

- `<ue_exe>`: path to the UE editor executor, eg: `~/UE/UnrealEngine/Engine/Binaries/Linux/UE4Editor`
- `<ue_map>`: ue map name, eg: `Turtlebot3AutoTest`
- `<tb3_model>`: `burger` or `waffle`
- `<tb3_name>` as the robot given names, eg: `burger0`
- `<tb3_init_pos>` as the robot initial position (x,y,z), eg: `0.0,0.0,0.1`
- `<tb3_init_rot>` as the robot initial rotation (r,p,y), eg: `0.0,0.0,0.0`
