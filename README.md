# Downloading SDL2 for visual c++ in windows system
1. Go to this website https://www.libsdl.org/download-2.0.php
2. Development Libraries-> SDL2-devel-2.0.16-VC.zip (Visual C++ 32/64-bit)
# Setting up SDL2 in visual studio
1. Create or add existing the cpp file to the source file section
2. Change the settings to x64
3. Go to project->properties
4. Go to VC++ directories->Include Directories->Edit->Add downloaded SDL2 folder's include folder
5. Linker->Input->Additional Dependencies->Edit-> Add two lines SDL2.lib;SDL2main.lib;
6. VC++ directories->Library Directories->Edit->downloaded SDL2 folder->lib->x64

# Computer-Graphics using SDL2 library
1. Line Drawing (using DDA and Bressenam's algorithm)
2. Circle Drawing (using midpoint and Bressenham's algorithm)
3. Flood fill and Boundary fill algorithm (using graphics.h)
4. Scan Line algorithm
