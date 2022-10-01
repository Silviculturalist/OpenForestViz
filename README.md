# OpenForestViz
Forest Visualisation with OpenGL. Experimental. For learning. Can change at any time. 

Utilises vcpkg as a package manager.
vcpkg.json provides list of dependencies and necessary components.

CMakePresets.json provides a configuration preset for the generator, e.g. microsoft VS.("default")

Get vcpkg and install dependencies:
```
cmake -S . -Bbuild -DCMAKE_BUILD_TYPE=Release \ -DCMAKE_TOOLCHAIN_FILE=$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake
```

Create a solution file:
```
cmake --preset=default
```

Build solution in Visual Studio.

TODO:
- Add assimp dependency for model handling. (ASSet IMPort)
- Triangle demo with Dear imgui.
