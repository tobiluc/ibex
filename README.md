# ibex

A simple mathematical expression parser. Some examples are shown below:

### Commandline Tool

Go to the ibex directory (where the CMakeLists.txt file is located) and build the project using cmake.
```console
mkdir build
cd build
cmake ..
make
```
Run the commandline tool
```console
./Build/bin/ibex-cli "1 + 1/12"
1.08333
```

### Library
ibex can be included in your project as a library. Using FetchContent:
```cmake
include(FetchContent)
set(EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")

if (NOT TARGET ibex)
    message(STATUS "Fetching ibex")
    FetchContent_Declare(ibex
        GIT_REPOSITORY https://github.com/tobiluc/ibex.git
        GIT_TAG main
        SOURCE_DIR "${EXTERNAL_DIR}/ibex"
    )
    FetchContent_MakeAvailable(ibex)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC
    ibex
)
```

### Code Examples
```cpp
#include <ibex/ibex.hpp>

int main()
{
    // Expressions
    ibex::eval("2+3*2"); // = 8
    ibex::eval("2^3^2"); // = 512
    ibex::eval("3/(2*(10-4))"); // = 0.25
    ibex::eval("sin(0)"); // = 0
    ibex::eval("max(1,5,2,4)"); // = 5

    // Variable Assignments
    ibex::Variables vars; // an empty dictionary mapping strings to doubles
    ibex::Functions funcs;
    ibex::eval("x = 2", vars, funcs); // vars["x"] now holds the value 2

    // Registering a custom function
    vars = ibex::common_variables(); // contains pi, e
    funcs = ibex::common_functions(); // contains sin, cos, exp, min, ...
    funcs["argmax"] = [](const ibex::FunctionArgs& args) -> double {
        int argmax(0);
        for (int i = 0; i < args.size(); ++i) {
            if (args[i] > args[argmax]) {
                argmax = i;
            }
        }
        return argmax;
    };
    ibex::eval("argmax(1,4,10,9)", vars, funcs); // = 2

    return 0;
}
```