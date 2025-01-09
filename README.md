# 🚀 Ball Chaser Robot - Project

Welcome to theproject! This is where robots meet fun, chasing a white ball in a Gazebo simulation using ROS 1. 

---

## 📦 Project Overview

This project consists of two key packages:

- **`my_robot`**: Contains the robot's URDF, sensors, and Gazebo world setup.
- **`ball_chaser`**: Includes the brains of the operation—control nodes for chasing the ball.

---

## 🛠️ Prerequisites

Make sure you have the following:

- **ROS 1** (tested on Noetic 🐢)
- **Gazebo** (comes with ROS Noetic by default)
- **catkin tools**: Install it with:
  ```bash
  sudo apt install python3-catkin-tools
  ```
- Additional ROS packages:
  ```bash
  sudo apt install ros-noetic-joint-state-publisher \
                   ros-noetic-joint-state-publisher-gui \
                   ros-noetic-xacro \
                   ros-noetic-gazebo-ros \
                   ros-noetic-rviz
  ```

---

## 🏗️ How to Clone and Run

### Clone the Repository
```bash
git clone https://github.com/vishnuajaykumar/ball_chaser_robot.git
cd ball_chaser_robot
```

### Build the Workspace
```bash
catkin_make
source devel/setup.bash
```

### Launch the Simulation
```bash
roslaunch my_robot world.launch
```

### Launch the Ball Chaser Nodes
```bash
roslaunch ball_chaser ball_chaser.launch
```

---

## 🗂️ Project Directory Structure

```
ball_chaser_robot/                   
├── src/                      
│   ├── my_robot/             
│   │   ├── launch/             # Launch files
│   │   ├── meshes/             # Sensor and model meshes
│   │   ├── urdf/               # Robot description files
│   │   ├── world/              # Gazebo world files
│   │   ├── CMakeLists.txt      # Build configuration
│   │   ├── package.xml         # ROS package metadata
│   ├── ball_chaser/          
│   │   ├── launch/             # Launch files
│   │   ├── src/                # C++ source files
│   │   ├── srv/                # Service definitions
│   │   ├── CMakeLists.txt      # Build configuration
│   │   ├── package.xml         # ROS package metadata
├── build/                      # Build artifacts (do not commit)
├── devel/                      # Development space (do not commit)
```

---

## 🎮 How It Works

### 🤖 Simulation in Gazebo
- The **`my_robot`** package defines the robot’s URDF with wheels, a camera, and LIDAR.
- The simulation includes a Gazebo world (`BallChaser.world`) with a white ball waiting to be chased!

### ⚡ Ball Chasing Behavior
1. **Image Processing**:  
   The `process_image` node processes the camera feed to spot the white ball.  
2. **Decision Making**:  
   It determines the ball’s position (left, center, or right) and sends movement commands accordingly.  
3. **Motion Control**:  
   The `drive_bot` node handles wheel movement to chase that ball like there’s no tomorrow.

### 🧠 Nodes Overview
- **`drive_bot.cpp`**: Sends wheel commands to make the robot move.  
- **`process_image.cpp`**: Analyzes the camera feed to find the ball and trigger movement commands.

---

## 🛠️ Troubleshooting

- **Test the `/ball_chaser/command_robot` service**:  
  Use the following command to move the robot forward:
  ```bash
  rosservice call /ball_chaser/command_robot "linear_x: 0.5 angular_z: 0.0"
  ```

- **View the Camera Feed**:  
  Open RViz and visualize the `/camera/rgb/image_raw` topic:
  ```bash
  rosrun rviz rviz
  ```
  Add an **"Image" display** and set the topic to `/camera/rgb/image_raw`.

---

## 🛑 Known Issues

### 🚗 Robot Not Moving?
- Double-check that the `/camera/rgb/image_raw` topic matches your Gazebo camera feed.
- Ensure the `process_image` and `drive_bot` nodes are running.

### 🚀 Launch Errors?
- Confirm that the paths in your launch files align with the workspace structure.

---

## 🤝 Contributing

Have ideas for improvements? Found a bug? 🐞  
Contributions are always welcome—submit an issue or a pull request and join the fun!
