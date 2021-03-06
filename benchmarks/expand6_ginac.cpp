// To compile on a debian system you need to install libginac-dev first
// $ sudo apt-get install libginac-dev
// Then compile with the following command,
// $ g++ -std=c++0x -o expand6_ginac -Wl,--no-as-needed `pkg-config --cflags --libs ginac` expand6_ginac.cpp
// See this SO answer: http://stackoverflow.com/a/18696743/1895353

#include <iostream>
#include <chrono>

#include <ginac/ginac.h>
using GiNaC::ex;
using GiNaC::pow;
using GiNaC::add;
using GiNaC::expand;
using GiNaC::exmap;
using GiNaC::symbol;
using GiNaC::sqrt;
using GiNaC::numeric;

int main(int argc, char* argv[])
{
    int N;
    if (argc == 2) {
        N = std::atoi(argv[1]);
    } else {
        N = 100;
    }

    ex e, f, s, a0, a1;
    a0 = symbol("a0");
    a1 = symbol("a1");
    e = a0 + a1;
    f = 0;
    for (int i = 2; i < N; i++) {
        s = sqrt(ex(2))*symbol("a"+std::to_string(i));
        e = e + s;
        f = f - s;
    }
    e = expand(e * e);
    e = e.subs(a0 == f);

    auto t1 = std::chrono::high_resolution_clock::now();
    e = expand(e);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout
        << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
        << "ms" << std::endl;
    std::cout << e << std::endl;

    return 0;
}
