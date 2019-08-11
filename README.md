# Overkill Engine II

### About
The Overkill Engine II is the second version of a small game engine that is being developed as a hobby project.
Overkill group:
- Halvor Smedås  
- Jone Skaara  
  
Overkill as a group (OK), created Overkill Engine I as the larger of two assignments in a Graphics Programming course at NTNU in Gjøvik. We later restarted the project as Overkill Engine II (OKEII), in order to improve on what OKEI was lacking. OKEII is more generallized and easier to expand on, making it more suitable to actually write a game in.

### Featrues
- [X] Sprite that can draw images to the screen.
- [X] SpriteAnimation that go though a sprite sheet(atlas) to "create motion".
- [X] Text renderer that uses instance rendering to display a string using a single sprite.
- [X] Transformable GameObjects.
- [X] Components that are put on GameObjects to give them behaviour.
- [X] GameObject transformation hierarchy. A child-GameObject is translated, rotated and scaled by its parent. 
- [ ] ParticleSystem that uses a data driven structure and instance rendering to draw, lots and lots, of particles.
- [ ] Resource Manager that loads and stores resources like ShaderPrograms and Textures, and hands out references to them.

### Structure
General structure of the Overkill Engine II.
![](https://github.com/Stektpotet/overkill-engine-II/blob/master/docs/OKEII.png?raw=true)


### Installation
#### Windows
TODO:

#### Ubuntu
1. Install latest grapics drivers. The OKEII uses OpenGL version 4.3.
1. Install CMake 3.8 version or above.
    ```bash
    sudo apt-get install cmake libx11-dev xorg-dev libglu1-mesa-dev freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev
    ```
1. Install g++-7:
    ```bash
    sudo apt-get install -y software-properties-common
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt update
    sudo apt install g++-7 -y
    ```
1. Install glew globally as the repo only has the windows binaries.
    ```bash
    sudo apt-get install libglew-dev
    ```
    (not sure if also glu and/or glm)
1. Set up repo:
    ```bash
    git clone [REPO LINK]
    cd overkill-engine-II
    mkdir build && cd build
    cmake .. -DCMAKE_CXX_COMPILER=g++-7
    make
    ./overkill-engine-II
    ```
