# ibex

A simple mathematical expression parser. Some examples are shown below:

```cpp
ibex::eval("2^3^2"); // = 512
ibex::eval("3/(2*(10-4))"); // = 0.25
ibex::eval("sin(0)"); // = 0
ibex::eval("max(1,5,2,4)"); // = 5
```

```cpp
ibex::Variables vars;
ibex::Functions funcs;
ibex::eval("x = 2", vars, funcs); // vars["x"] now holds the value 2
```

```cpp
// Register a custom function
ibex::Variables vars = common_variables(); // pi, e
ibex::Functions funcs = common_functions(); // sin, cos, exp, ...
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
```