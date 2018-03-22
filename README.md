# DynamicLighting

C++ SFML experimental dynamic lighting project without shaders.

## Preview ##
![Preview][1]

## Build ##
Project uses [CMake][2] to generate platform and compiler-specific build files.

### Dependencies ###
Before building, make sure that [SFML 2.0+][3] (only tested with 2.4) is installed. Also note that this project uses `C++11` features such as `auto` and `lambdas`, and therefore requires a `C++11` compliant compiler in order to build successfully.

### Building on Windows (Visual Studio) ###
1. Ensure SFML is installed (if CMake fails to find SFML automatically, edit the `SFML_ROOT` variable in the [CMakeLists.txt][4])

2. Clone the repository
    ```
    git clone https://github.com/Seng3694/DynamicLighting SengDynamicLighting
    ```

3. Generate the build files (depending on your Visual Studio Version the `cmake` command differs. In this case `"Visual Studio 15"` will generate the Visual Studio 2017 project files)
    ```
    mkdir build
    cd build
    cmake -G "Visual Studio 15" ../SengDynamicLighting
    ```

4. Open the `.sln` file in Visual Studio and build the `ALL_BUILD` target.

[1]: https://cdn.discordapp.com/attachments/425728769236664350/426402375188611077/dynamic_lighting_preview.gif
[2]: http://www.cmake.org/
[3]: http://www.sfml-dev.org/
[4]: https://github.com/Seng3694/DynamicLighting/blob/master/CMakeLists.txt