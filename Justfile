init:
    #!/usr/bin/env bash
    # https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux
    # https://github.com/raylib-extras/raylib-quickstart
    sudo apt install build-essential git
    sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
    sudo apt-get install libzip-dev

build:
    #!/usr/bin/env bash
    cd src
    make build

run:
    #!/usr/bin/env bash
    cd src
    make clean
    make run
