# cub3D

## A Raycasting-Based 3D Maze Explorer Inspired by Wolfenstein 3D

## 🔍 Preview

![Screenshot of the game](imgs/screenshots/help.png)

![Screenshot of the game](imgs/screenshots/1.png)

![Screenshot of the game](imgs/screenshots/2.png)

![Screenshot of the game](imgs/screenshots/3.png)

![Screenshot of the game](imgs/screenshots/5.png)

![Screenshot of the game](imgs/screenshots/4.png)

---

## 🔍 Description

Cub3D is a 3D maze navigation project inspired by the classic game Wolfenstein 3D.
Using raycasting technology, it creates a retro-style first-person experience by transforming 2D map data into a dynamic 3D environment.
Developed in C with the MiniLibX graphics library, the project highlights core principles of computer graphics and game development,
offering a practical exploration of rendering techniques and real-time visual simulation.

---

## 🎮 Key Features

- **Raycast Rendering Engine**
  Efficient 3D projection from 2D maps using the **DDA (Digital Differential Analyzer)** algorithm.
  
- **GTA-Style Rotating Minimap**
  Dynamic overhead map rotates with player orientation for intuitive navigation.
  Built using Inverse Mapping (Reverse Transformation/Destination-Driven Warping).

- **Interactive Door System**
  Animated doors that open/close with smooth transitions.

- **Fluid Controls**
  WASD movement, mouse/trackpad camera rotation, and real-time minimap rendering.

---

## 🛠️ Installation

### Tested on macOS/Linux

1. **Clone Repository**

   ```bash
   git clone https://github.com/olaaroub/42_Cub3D.git && cd 42_Cub3D
   ```

2. **Install Dependencies**
   - MiniLibX (included) requires:
   - gcc
   - make
   - X11 include files (package xorg)
   - XShm extension must be present (package libxext-dev)

   - ```Utility functions from BSD systems - development files (package libbsd-dev)
     sudo apt-get install gcc make xserver-xorg-dev xorg-dev libbsd-dev
     sudo apt-get install libxext-dev libxrandr-dev libx11-dev libxml2-dev
     ```
---

### Controls

|       Action          |       Key       |
|-----------------------|-----------------|
| Move                  | `W` `A` `S` `D` |
| Turn Left/Right       | Right/Left arrow|
| Rotate Camera         | Mouse/Trackpad  |
| Open/Close Doors      | `F`      `E`    |
| Quit                  | `ESC`           |

---

## 🌟 Resources

- [**Wolfenstein 3D**](http://users.atw.hu/wolf3d/)
- [**Raycasting in JS**](http://www.playfuljs.com/a-first-person-engine-in-265-lines/)
- [**Raycasting theory**](https://lodev.org/cgtutor/raycasting.html)
- [**MiniLibX**](https://harm-smits.github.io/42docs/libs/minilibx)
