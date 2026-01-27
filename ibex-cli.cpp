#include <iostream>
#include <ibex/ibex.hpp>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: <Expression>" << std::endl;
        return 1;
    }
    double res = ibex::eval(argv[1]);
    if (std::isnan(res)) {return 1;}
    std::cout << res << std::endl;
    return 0;
}
