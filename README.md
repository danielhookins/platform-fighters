```
__________.__          __    _____                     
\______   \  | _____ _/  |__/ ____\___________  _____  
 |     ___/  | \__  \\   __\   __\/  _ \_  __ \/     \ 
 |    |   |  |__/ __ \|  |  |  | (  <_> )  | \/  Y Y  \
 |____|   |____(____  /__|  |__|  \____/|__|  |__|_|  /
                    \/                              \/ 
___________.__       .__     __                        
\_   _____/|__| ____ |  |___/  |_  ___________  ______ 
 |    __)  |  |/ ___\|  |  \   __\/ __ \_  __ \/  ___/ 
 |     \   |  / /_/  >   Y  \  | \  ___/|  | \/\___ \  
 \___  /   |__\___  /|___|  /__|  \___  >__|  /____  > 
     \/      /_____/      \/          \/           \/ 
```


# Platform Fighters
2D, platform, fighting game.
Players fight on platforms.


## Third Party Libraries
This project requires [RayLib](https://github.com/raysan5/raylib)

Compile and add Raylib Library `libray.a` to `/lib`:  
Follow the instructions on the [RayLib Wiki](https://github.com/raysan5/raylib/wiki)
- I'll add more documentation on this later.


## Build
Compile with GCC on Windows  
`gcc main.c -o build/platform-fighers-dev.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm`

- Still need to add a proper Make file.
