#include "calculator.h"
#include "inf_int.h"
#include <fstream>
#include <assert.h>

void test() {
    std::ifstream input("input.in");
    std::ifstream output("output.out");
    int cnt = 0;

    while(!input.eof()) {
        if(cnt % 10000 == 0) std::cout << cnt << "/80100 tested" << std::endl;
        std::string n1, n2, plus, minus, times;
        input >> n1 >> n2;
        output >> plus >> minus >> times;

        if(n1 == "") break;

        assert((inf_int(n1.c_str()) + inf_int(n2.c_str())) == inf_int(plus.c_str()));
        assert((inf_int(n1.c_str()) - inf_int(n2.c_str())) == inf_int(minus.c_str()));
        assert((inf_int(n1.c_str()) * inf_int(n2.c_str())) == inf_int(times.c_str()));
        cnt++;
    }
    std::cout << "80100/80100 testing finished" << std::endl << std::endl;
}

int main() {
//    test();
    calculator c;
    c.run();
    return 0;
}